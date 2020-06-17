#include <mpi.h>
# include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char** argv) {
	time_t t;
	int rnd_num[512];
	int new_mul_arr[6];
	int i,j,loop_begin,loop_end;
	int *arr[5];
	MPI_Init(&argc, &argv);
	MPI_Status status;
	// size is number of processes
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//my_rank is rank of the process
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	loop_begin = (my_rank - 1) * 6;
	loop_end = my_rank * 6;
	int rnd_numbers = 6 * (size - 1);
	if (my_rank == 0) {
		printf("num of rnd numbers %d \n", rnd_numbers);
		//initialize random number generator
		srand((unsigned)time(&t));
		for (i = 0; i < rnd_numbers; i++) {
			rnd_num[i] = rand();
			printf(" %d ,  ", rnd_num[i]);
		}
		printf("\n\n ");
		for (i = 1; i < size; i++) {
			
				MPI_Send(rnd_num, 512, MPI_INT, i, i, MPI_COMM_WORLD);
				MPI_Recv(new_mul_arr, 6,MPI_INT,i, i, MPI_COMM_WORLD,&status);
				printf("recieved from process %d to 0: ", i);
				for (j = 0; j < 6; j++) {
					printf("%d, ", new_mul_arr[j]);
				}
				printf("\n \n");
		}
		
		
	} else {
		
		
		for (i = 1; i < size; i++) {
			if (i == my_rank) {
				MPI_Recv(rnd_num, 512, MPI_INT, 0, i, MPI_COMM_WORLD, &status);
				printf("recieved from process 0 to %d : ",i);
				for (j = loop_begin; j < loop_end; j++) {
					printf("%d, ", rnd_num[j]);
					new_mul_arr[j - loop_begin] = rnd_num[j] * 3;
					
				}
				
				MPI_Send(new_mul_arr, 6, MPI_INT, 0, i, MPI_COMM_WORLD);
				printf("\n ");
			}
		}
	}
	MPI_Finalize();
}
