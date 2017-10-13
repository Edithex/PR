#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

int main( int argc, char** argv )
{ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;
  char hostname[256];
	
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  if(size>1)
	{
    
    if( rank != 0 )
		{
      MPI_Recv(&hostname, sizeof(hostname), MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, 					MPI_COMM_WORLD , &status);
			printf("Proces %d dane od procesu o randze 0, hostname to %s\n", rank, hostname);
      } else {
      gethostname(hostname, sizeof(hostname));
			tag = 0;
      for( i=1; i<size; i++ )
				MPI_Send(&hostname, sizeof(hostname), MPI_CHAR, i, tag, MPI_COMM_WORLD);
    }
  }
		else{
		printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  MPI_Finalize(); 
  
  return(0);

}
