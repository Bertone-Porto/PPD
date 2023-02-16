//mpicc ex1_mpi.c -o exec1
//mpiexec -n 5./exec1 {qtd} {nome do arquivo}
/*
Escreva um programa que transmita um dado do processo 
zero para todos os outros processos, da seguinte maneira: 
o processo i deve receber o dado do processo i-1, somar seu número de 
identificação e enviar o dado ao processo i+1, até que 
o último processo seja atingido.
Assuma que o dado consiste de um número inteiro. 
O processo zero deve ler o dado especificado pelo usuário
na linha de comando. Todos os processos devem enviar o 
valor calculado para o processo zero. Assim, o processo 
zero deve escrever no arquivo de saída o número de 
identificação do processo e o valor por ele calculado. 
O nome do arquivo de saída também deve ser um parâmetro 
na linha de comando. Por exemplo, suponha que o valor 
passado inicialmente é igual a 12, o arquivo de saída seria:

Identificação = 0 valor 12
Identificação = 1 valor 13 
Identificação = 2 valor 15 
Identificação = 3 valor 18
e assim por diante. 
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
   int tasks, rank, dest, fonte, count, tag=1;
   int inmsg, outmsg;
   MPI_Status Stat;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &tasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if (rank == 0){
       dest = rank+1;
       outmsg = atoi(argv[1]);
       FILE *fp; fp = fopen(argv[2], "w");
       fprintf(fp, "Valor inicial %d \n", outmsg);
       MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
       for (fonte = 1; fonte < tasks; fonte++){
            MPI_Recv(&inmsg, 1, MPI_INT, fonte, tag, MPI_COMM_WORLD, &Stat);
            fprintf(fp, "Identificação: %d valor %d \n", fonte, inmsg);
       } 
       fclose(fp);
   } else if (rank == tasks-1) {
       fonte = rank-1;
       MPI_Recv(&inmsg, 1, MPI_INT, fonte, tag, MPI_COMM_WORLD, &Stat);
       outmsg = inmsg + rank;
       MPI_Send(&outmsg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
   } else {
       fonte = rank-1;
       MPI_Recv(&inmsg, 1, MPI_INT, fonte, tag, MPI_COMM_WORLD, &Stat);
       dest = rank+1;
       outmsg = inmsg + rank;
       MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
       MPI_Send(&outmsg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
   }
   MPI_Finalize();

}
