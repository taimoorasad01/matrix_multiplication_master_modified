#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

double** allocate_matrix(int rows, int cols) {
    double **matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

void initialize_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(rand() % 10);
        }
    }
}

void free_matrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: mpirun -np <num_processes> %s <matrix_size>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    int n = atoi(argv[1]);
    int rows_per_process = n / size;
    
    double **A = NULL;
    double **B = allocate_matrix(n, n);
    double **C_local = allocate_matrix(rows_per_process, n);
    double **A_local = allocate_matrix(rows_per_process, n);
    
    if (rank == 0) {
        A = allocate_matrix(n, n);
        srand(time(NULL));
        initialize_matrix(A, n, n);
        initialize_matrix(B, n, n);
        
        printf("MPI Matrix Multiplication: %dx%d with %d processes\n", n, n, size);
    }
    
    // Broadcast matrix B to all processes
    for (int i = 0; i < n; i++) {
        MPI_Bcast(B[i], n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    
    // Scatter rows of A
    if (rank == 0) {
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < n; j++) {
                A_local[i][j] = A[i][j];
            }
        }
        for (int p = 1; p < size; p++) {
            for (int i = 0; i < rows_per_process; i++) {
                MPI_Send(A[p * rows_per_process + i], n, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        for (int i = 0; i < rows_per_process; i++) {
            MPI_Recv(A_local[i], n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    
    double start_time = MPI_Wtime();
    
    // Local computation
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < n; j++) {
            C_local[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C_local[i][j] += A_local[i][k] * B[k][j];
            }
        }
    }
    
    double end_time = MPI_Wtime();
    
    // Gather results
    if (rank == 0) {
        double **C = allocate_matrix(n, n);
        for (int i = 0; i < rows_per_process; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = C_local[i][j];
            }
        }
        for (int p = 1; p < size; p++) {
            for (int i = 0; i < rows_per_process; i++) {
                MPI_Recv(C[p * rows_per_process + i], n, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        
        printf("Time taken: %.6f seconds\n", end_time - start_time);
        free_matrix(C, n);
        free_matrix(A, n);
    } else {
        for (int i = 0; i < rows_per_process; i++) {
            MPI_Send(C_local[i], n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }
    
    free_matrix(B, n);
    free_matrix(C_local, rows_per_process);
    free_matrix(A_local, rows_per_process);
    
    MPI_Finalize();
    return 0;
}
