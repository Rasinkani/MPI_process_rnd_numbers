#include <mpi.h>
# include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char** argv) {
	time_t t;
	int rnd_num[512];
	int i,j, num_loop;
	int *arr[5];
	MPI_Init(&argc, &argv);
	MPI_Status status;
	// size is number of processes
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//my_rank is rak of the process
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	num_loop = my_rank * 6;
	int rnd_numbers = 6 * (size - 1);
	if (my_rank == 0) {
		printf("num of rnd numbers %d \n", rnd_numbers);
		//initialize random number generator
		srand((unsigned)time(&t));
		for (i = 0; i < rnd_numbers; i++) {
			rnd_num[i] = rand();
			printf(" %d ,  ", rnd_num[i]);
		}
		
		//for (i = 1; i < size; i++) {
			//arr[i] = &rnd_num[i * 6];
			
		//}
		//for (j = 0; j < 6; j++) {
			//printf(" before send  %d, ", arr[i][j]);
		//}
		//for (j = 0; j < 6; j++) {
			//printf(" before send  %d, ", arr[1][j]);
		//}
		//for (i = 1; i < size; i++) {
			//if (i < size) {
				//MPI_Send(arr[0], 6, MPI_INT, 1, 1, MPI_COMM_WORLD);
			//}
		//}
		MPI_Send(rnd_num, 512, MPI_INT, 1, 1, MPI_COMM_WORLD);
		//MPI_Send(rnd_num, 512, MPI_INT, 2, 2, MPI_COMM_WORLD);
	} else if(my_rank==1){
		printf("loops %d, rank %d \n", num_loop, my_rank);
	//} else {
		//process other than root process
		//for (i = 1; i < size; i++) {
			//MPI_Recv(arr[1], 6, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
			//for (j = 0; j < 6; j++) {
			//	printf("%d, ", arr[0][j]);
			//}
			MPI_Recv(rnd_num, 512, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
			
			for (j = 0; j < num_loop; j++) {
				printf("%d, ", rnd_num[j]);
			}
		//}
			printf("\n ");
	} 
	/*else if (my_rank == 2) {
		printf("loops %d, rank %d \n", num_loop, my_rank);
		MPI_Recv(rnd_num, 512, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		for (j = num_loop-6; j < num_loop; j++) {
			printf("%d, ", rnd_num[j]);
		}
		printf("\n ");
	}*/
	MPI_Finalize();
}
