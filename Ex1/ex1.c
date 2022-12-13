#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int numtasks, rank, i, l, destino, fonte, contador;
    MPI_Status Stat;
	
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        destino = rank + 1;

    }

    MPI_Finalize();	

}

