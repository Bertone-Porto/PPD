//mpicc ex2_mpi.c -o exec2
//mpiexec -n 5./exec2 {nome do arquivo}
/*
Escreva um programa que teste quão justa
é a implementação da passagem de mensagens.
Para isso, todos os processos, exceto o processo zero, 
deve enviar 100 mensagens (quaisquer) para o processo zero. 
O processo zero deve escrever as mensagens recebidas num 
arquivo de saída. O nome do arquivo de saída deve ser 
um parâmetro na linha de comando. Use na recepção de 
mensagens as variáveis pré-definidas MPI_ANY_SOURCE e 
MPI_ANY_TAG. A implementação MPI é justa?  
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
   int numtasks, rank, dest, source, count, tag=1;
   int inmsg, outmsg;
   //char * outmsg;
   MPI_Status Stat;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if (rank == 0){
      FILE *fp; 
      fp = fopen(argv[1], "w");
      for (source = 0; source < (numtasks-1)*100; source++){
           MPI_Recv(&inmsg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat); 
           fprintf(fp, "Recebido %d da Task %d \n", inmsg, Stat.MPI_SOURCE);
      } fclose(fp);
   } else {
      for (source = 0; source < 100; source++){
          outmsg = 13;
          MPI_Send(&outmsg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD); 
      }
   }
   
   MPI_Finalize();
} 
