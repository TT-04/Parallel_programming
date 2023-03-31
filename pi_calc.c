#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

 double f(double x)
 {
 return 1/(1+x*x);
 }

 int main(int argc, char** argv)
 {
    double pi, sum = 0, term, h;
    int rank, size, n, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
    if(rank == 0)
    {
        printf("Number of iterations = ");
        scanf("%d", &n);
		for (i = 1; i < size; i++){
			MPI_Ssend(&n, 1, MPI_INT, i, 3, MPI_COMM_WORLD);
		}
    }
    //MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	else{
		MPI_Recv(&n, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
	}
    h = 1.0/n;
    for(i = rank + 1; i <= n; i += size){
        sum += f(h * (i - 0.5));
    }
    term = 4*h*sum;
    MPI_Reduce(&term, &pi, 1, MPI_DOUBLE, MPI_SUM,0,MPI_COMM_WORLD);
    if(rank == 0){
        printf("Computed value of pi = %lf\n", pi);
    }
    MPI_Finalize();
    return 0;
 }