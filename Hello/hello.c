/*
  gcc -o exec hello.c -fopenmp
  ./exec
*/

#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
	
	#pragma omp parallel 
	{
		printf("hello, %d:\n", omp_get_thread_num());
	}
}
