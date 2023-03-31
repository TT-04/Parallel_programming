#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int i, j, n, k;
    
    int* temp;
    int rank, size;
    int** matrix;
    n = 5; // n - это количество строк (и столбцов, соответственно)
    temp = (int*)calloc(n, sizeof(int));
	matrix = (int**)calloc(n, sizeof(int*));
    
    for(i = 0; i < n; i++){
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
	for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrix[i][j] = j + 1;
		}
	}
    
	MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(size != (n + 1)){
		printf("Wrong number of processes\n");
		MPI_Finalize();
		return 0;
		}

    if(rank == 0){
       for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("Rank of the matrix = %d\n", n);

        for (j = 1; j <= n; j++){
            MPI_Recv(temp, n, MPI_INT, j, 3, MPI_COMM_WORLD, &status);
			for(k = 0; k < n; k++){
				*(matrix[j-1] + k) = temp[k];
			}
        }

        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                printf("%d ", matrix[i][j]);
            }
        printf("\n");
        } 
    }

    else{
		for(j = 1; j <= size; j++){
			if(rank == j){
				for(i = 0; i < n; i++){
					temp[i] = *(matrix[i] + j-1);
				}
			}
		}
		MPI_Ssend(temp, n, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    free(temp); 
	for(i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);  
    return 0;
}