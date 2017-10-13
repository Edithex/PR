# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "mpi.h"

int main ( int argc, char *argv[] )
{
  int id; // rank
  int size;  // size
	int i;
	int root;
	int n;
	int n_lok;
	int n_pocz, n_kon;
	double suma = 0.0;
	double sum = 0.0;

	MPI_Init ( &argc, &argv );
  	MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  	MPI_Comm_size ( MPI_COMM_WORLD, &size );

	root = 0;
	scanf("%d",&n);
	MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
	
	if((n%size) == 0)
		n_lok = n/size;
	else 	
		n_lok = (n/size)+1;	

	n_pocz = id * n_lok;
	n_kon = n_lok * (id+1);

	for(i=n_pocz; i<n_kon; i+=2) {
		sum += (1.0)/((2*i)+1);
	}

	for(i=n_pocz+1; i<n_kon; i+=2) {
		sum -= (1.0)/((2*i)+1);
	}

	MPI_Reduce(&sum, &suma, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);


	if(id==0){
		printf("Suma ciagu: %lf\n", suma);
		printf("Roznica: %lf\n", (M_PI/4.0)-suma);
	}




  MPI_Finalize ( );

  return;
}
