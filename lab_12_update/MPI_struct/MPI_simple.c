#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

struct struktura{
int liczba;
char znak;
float tab[5];
};

int main( int argc, char** argv ){ 
	int i, j;
  struct struktura stc;
  
  int rank, ranksent, size, source, dest, tag, rozmiar, rozm_pakietu, pozycja; 
  void* bufor;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar);
  rozm_pakietu=rozmiar;
  MPI_Pack_size(1, MPI_CHAR, MPI_COMM_WORLD, &rozmiar);
  rozm_pakietu+=rozmiar;
  MPI_Pack_size(3, MPI_FLOAT, MPI_COMM_WORLD, &rozmiar);
  rozm_pakietu+=rozmiar;
  bufor=(void *)malloc(3*rozm_pakietu);
  pozycja=0;
  
	
  

  if(size>1){
    
    if( rank != 0 && (rank != (size-1)) ){ 
	dest=rank+1; tag=0, source=rank-1;
      MPI_Recv( bufor, 3*rozm_pakietu, MPI_PACKED, source, tag, MPI_COMM_WORLD, &status);
      printf("Proces o nr %d odebral liczbe od procesu (%d)\n", rank, source);
      MPI_Send( bufor, 3*rozm_pakietu, MPI_PACKED, dest, tag, MPI_COMM_WORLD );
      printf("Proces o nr %d wyslal liczbe do procesu (%d)\n", rank, dest);
      
    } 
	else if (rank == 0){
	  stc.liczba=0, stc.znak='X';
	  printf("Liczba: %d, znak: %c\n", stc.liczba, stc.znak);
	  for(j=0;j<5;j++){
	  stc.tab[j]=j+1;
	  printf("Tablica: %f", stc.tab[j]);
	  }
  	  printf("\n");
  	  
  	    MPI_Pack(&stc.liczba, 1, MPI_INT, bufor, 3*rozm_pakietu, &pozycja, MPI_COMM_WORLD);
		MPI_Pack(&stc.znak, 1, MPI_CHAR, bufor, 3*rozm_pakietu, &pozycja, MPI_COMM_WORLD);
		MPI_Pack(&stc.tab[0], 5, MPI_DOUBLE, bufor, 3*rozm_pakietu, &pozycja, MPI_COMM_WORLD);
    	
    	dest=rank+1, tag=0;
    	MPI_Send( bufor, pozycja, MPI_PACKED, dest, tag, MPI_COMM_WORLD );
    	printf("Proces o nr %d wyslal liczbe do procesu (%d)\n", rank, dest);
    }
    else if(rank == size-1){
    	source=rank-1, tag=0;
    	MPI_Recv( bufor, 3*rozm_pakietu, MPI_PACKED, source, tag, MPI_COMM_WORLD, &status);
    	printf("Proces o nr %d odebral liczbe od procesu (%d)\n", rank, source);
    	
    	MPI_Unpack(bufor, 3*rozm_pakietu, &pozycja, &stc.liczba, 1, MPI_INT, MPI_COMM_WORLD);
    	MPI_Unpack(bufor, 3*rozm_pakietu, &pozycja, &stc.znak, 1, MPI_CHAR, MPI_COMM_WORLD);
    	MPI_Unpack(bufor, 3*rozm_pakietu, &pozycja, &stc.tab[0], 5, MPI_FLOAT, MPI_COMM_WORLD);
    	printf("Liczba: %d, znak: %c\n", stc.liczba, stc.znak);
    	for (j=0;j<5;j++){
    		printf("Tablica: %f\n", stc.tab[j]);
    	}
    }
    
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

