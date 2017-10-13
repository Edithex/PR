#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

struct
{
  int a;
  char b;
  float x[2];
} obj, temp;

int main(int argc, char **argv)
{

  int rank, ranksent, size, source, dest, tag, i;
  void *bufor;

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  tag = 0;

  MPI_Datatype NewType;
  int count = 3;
  int blocks[3] = {1, 1, 2};
  //MPI_Aint address_a, address_b, address_x;
  MPI_Aint intex, charex;
  /*
  MPI_Address(&(obj.a), &address_a);
  MPI_Address(&(obj.b), &address_b);
  MPI_Address(&(obj.x), &address_x);
  */
  MPI_Datatype types[3] = {MPI_INT, MPI_CHAR, MPI_FLOAT};
  MPI_Type_extent(MPI_INT, &intex);
  MPI_Type_extent(MPI_INT, &charex);
  MPI_Aint displacements[3] = {0, intex, intex + charex};
  MPI_Type_struct(count, blocks, displacements, types, &NewType);
  MPI_Type_commit(&NewType);

  if (size > 1)
  {

    int send_to_rank = (rank + 1) % size;
    int recv_from_rank = (rank == 0) ? size - 1 : rank - 1;
    if (rank == 0)
    {
      int tag = 0;
      obj.a = 17;
      obj.b = 'c';
      obj.x[0] = 3.14;
      obj.x[1] = 2.718;
      MPI_Send(&obj, 1, NewType, send_to_rank, tag, MPI_COMM_WORLD);
      printf("Proces %d NewType do procesu %d\n", rank, send_to_rank);
      printf("\t\tint= %d char= %c, floats= %f, %f\n", obj.a, obj.b, obj.x[0], obj.x[1]);

      MPI_Recv(&obj, 1, NewType, recv_from_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("\t\tint= %d char= %c, floats= %f, %f\n", obj.a, obj.b, obj.x[0], obj.x[1]);
      printf("Proces %d odebrał NewType od procesu %d\n", rank, recv_from_rank);
    }
    else
    {
      MPI_Recv(&obj, 1, NewType, recv_from_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("Proces %d odebrał NewType od procesu %d\n", rank, recv_from_rank);
      printf("\t\tint= %d char= %c, floats= %f, %f\n", obj.a, obj.b, obj.x[0], obj.x[1]);

      MPI_Send(&obj, 1, NewType, send_to_rank, tag, MPI_COMM_WORLD);
      printf("Proces %d wysłał NewType do procesu %d\n", rank, send_to_rank);
      printf("\t\tint= %d char= %c, floats= %f, %f\n", obj.a, obj.b, obj.x[0], obj.x[1]);
    }
  }
  else
  {
    printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  MPI_Type_free(&NewType);
  MPI_Finalize();

  return (0);
}