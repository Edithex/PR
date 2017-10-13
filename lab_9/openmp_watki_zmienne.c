#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int b_private;

int main(){

#ifdef   _OPENMP
  printf("\nKompilator rozpoznaje dyrektywy OpenMP\n");
#endif

  int liczba_watkow;
  int a_shared = 1;
  int c_firstprivate = 3;
  int e_atomic=5;


#pragma omp threadprivate(b_private)


  printf("przed wejsciem do obszaru rownoleglego -  nr_threads %d, thread ID %d\n",
	 omp_get_num_threads(), omp_get_thread_num());
  printf("\ta_shared \t= %d\n", a_shared);
  printf("\tb_private \t= %d\n", b_private);
  printf("\tc_firstprivate \t= %d\n", c_firstprivate);
  printf("\te_atomic \t= %d\n", e_atomic);

omp_lock_t writelock;
omp_init_lock(&writelock);


#pragma omp parallel num_threads(7)  shared(a_shared, e_atomic) firstprivate(c_firstprivate )
  {
    int i;
    int d_local_private;
    
	omp_set_lock(&writelock);	
	d_local_private = a_shared + c_firstprivate;
	omp_unset_lock(&writelock);

 	#pragma omp barrier

    b_private = omp_get_thread_num();
	omp_set_lock(&writelock);
    for(i=0;i<10;i++){
      a_shared ++;
   }
	omp_unset_lock(&writelock);


    for(i=0;i<10;i++){
      c_firstprivate += omp_get_thread_num();
    }

	//#pragma omp atomic
    for(i=0;i<10;i++){
	#pragma omp atomic
      e_atomic+=omp_get_thread_num();
    }

	#pragma omp barrier
	omp_set_lock(&writelock);
    {

      printf("\nw obszarze równoległym: aktualna liczba watkow %d, moj ID(aktualny watek) %d\n",
	  omp_get_num_threads(), omp_get_thread_num());

      printf("\ta_shared \t= %d\n", a_shared);
      printf("\tb_private \t= %d\n", b_private);
      printf("\tc_firstprivate \t= %d\n", c_firstprivate);
      printf("\td_local_private = %d\n", d_local_private);
      printf("\te_atomic \t= %d\n", e_atomic);

   }
	omp_unset_lock(&writelock);

/*
#pragma omp single
    {
  //#pragma omp master

           printf("\ninside single: nr_threads %d, thread ID %d\n",
     	     omp_get_num_threads(), omp_get_thread_num());

           // Get environment information
           int procs = omp_get_num_procs();
           int nthreads = omp_get_num_threads();
           int maxt = omp_get_max_threads();
           int inpar = omp_in_parallel();
           int dynamic = omp_get_dynamic();
           int nested = omp_get_nested();

           // Print environment information
           printf("Number of processors = %d\n", procs);
           printf("Number of threads = %d\n", nthreads);
           printf("Max threads = %d\n", maxt);
           printf("In parallel? = %d\n", inpar);
           printf("Dynamic threads enabled? = %d\n", dynamic);
           printf("Nested parallelism supported? = %d\n", nested);
     }
*/
  }
omp_destroy_lock(&writelock);

printf("\nWyswietlanie liczby watku poprzez jego zmienna prywatna");

#pragma omp parallel num_threads(7)
 {

 	printf("\tidentyfikator wątku dla zmiennej b_private:  \t= %d\n", b_private);

 }

  printf("po zakonczeniu obszaru rownoleglego:\n");
  printf("\ta_shared \t= %d\n", a_shared);
  printf("\tb_private \t= %d\n", b_private);
  printf("\tc_firstprivate \t= %d\n", c_firstprivate);
  printf("\te_atomic \t= %d\n", e_atomic);

int i;
#pragma omp parallel num_threads(4)
  {
    #pragma omp for schedule(dynamic,3) ordered

    for (i = 0; i < 17; i++)
	{ 	
		#pragma omp ordered
      printf("-----1----- Iteracja %0d, IDwątku %0d\n", i, omp_get_thread_num());
	}

    #pragma omp for schedule(dynamic) ordered

    for (i = 0; i < 17; i++){
	#pragma omp ordered
      printf("-----2----- Iteracja %0d, IDwątku %0d\n", i, omp_get_thread_num());
 	} 
 	#pragma omp for schedule(static,3) ordered
	
	
    for (i = 0; i < 17; i++)
	{	
	#pragma omp ordered
      printf("-----3----- Iteracja %0d, IDwątku %0d\n", i, omp_get_thread_num());
	}
    #pragma omp for schedule(static) ordered
    for (i = 0; i < 17; i++)
    {
	#pragma omp ordered
      printf("-----4----- Iteracja %0d, IDwątku %0d\n", i, omp_get_thread_num());
	}
  }
}

