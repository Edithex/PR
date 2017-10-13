#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;
#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];

double czasozajmowacz(){
    int i, j, k;
    int n=WYMIAR;
    for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
    for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            c[i+n*j]=0.0;
            for(k=0;k<n;k++){
                c[i+n*j] += a[i+n*k]*b[k+n*j];
            }
        }
    }
    return(c[ROZMIAR-1]);
}

void * zadanie_watku (void * arg_wsk)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,
    NULL);
long unsigned int a = pthread_self();
    printf("\twatek potomny id systemowe: %lu\n", a);
    printf("\twatek potomny id iteracji: %d\n", arg_wsk);

    return(NULL);
}
int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    void *wynik;
    int i;

    //Watek przylaczalny
    printf("watek glowny: tworzenie watku potomnego nr 1\n");

    /*Tu wstaw kod tworzenia watku z domyslnymi
    wlasnosciami*/
	for(i=0; i<10; i++){
    pthread_create (&tid, NULL, zadanie_watku, i);
    sleep(2); // czas na uruchomienie watku

 
}
    
    pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
