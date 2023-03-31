#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int rank;
	float a, b;
    double time_start = 0, time_finish = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	a = 0.0;
	b = 0.0;
	if(rank == 0)
	{
		b = 1.0;
		time_start = MPI_Wtime();
		MPI_Send(&b, 1, MPI_FLOAT, 1, 5, MPI_COMM_WORLD);
		MPI_Recv(&a, 1, MPI_FLOAT, 1, 5, MPI_COMM_WORLD, &status);
		time_finish = MPI_Wtime();
		printf("first result time = %f\n", time_finish - time_start);
	}
	if(rank == 1)
	{
		a = 2.0;
		time_start = MPI_Wtime();
		MPI_Recv(&b, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD, &status);
		MPI_Send(&a, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD);
		time_finish = MPI_Wtime();
		printf("second result time = %f\n", time_finish - time_start);
	}
	
	MPI_Finalize();
}
