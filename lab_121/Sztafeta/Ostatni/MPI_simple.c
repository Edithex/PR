#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  if(size>1){
    
    if( rank != 0 && (rank != (size-1)) ){ 
	dest=rank+1; tag=0, source=rank-1;
      MPI_Recv( &ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
      printf("Proces o nr %d odebral liczbe	%d od procesu (%d)\n", rank, ranksent, source);
      MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
      printf("Proces o nr %d wyslal liczbe %d do procesu (%d)\n", rank, rank, dest);
      
    } 
   /* else if (rank == 0){
    	dest=rank+1, tag=0, source=size-1;
    	MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
    	printf("Proces o nr %d wyslal liczbe %d do procesu (%d)\n", rank, rank, dest);
    	MPI_Recv( &ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    	printf("Proces o nr %d odebral liczbe	%d od procesu (%d)\n", rank, ranksent, source);
    	
    }*/
  /*  else if(rank == size-1){
    	source=rank-1, tag=0, dest=0;
    	MPI_Recv( &ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    	printf("Proces o nr %d odebral liczbe	%d od procesu (%d)\n", rank, ranksent, source);
    	MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
    	printf("Proces o nr %d wyslal liczbe %d do procesu (%d)\n", rank, rank, dest);
    	
    	
    }*/

	else if (rank == 0){
    	dest=rank+1, tag=0;
    	MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
    	printf("Proces o nr %d wyslal liczbe %d do procesu (%d)\n", rank, rank, dest);
    }
    else if(rank == size-1){
    	source=rank-1, tag=0;
    	MPI_Recv( &ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    	printf("Proces o nr %d odebral liczbe	%d od procesu (%d)\n", rank, ranksent, source);
    }
      
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

