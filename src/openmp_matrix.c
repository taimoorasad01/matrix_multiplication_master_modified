#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void matrix_multiply(double **A, double **B, double **C, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double** allocate_matrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void initialize_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (double)(rand() % 10);
        }
    }
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix_size> <num_threads>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    omp_set_num_threads(num_threads);
    
    printf("OpenMP Matrix Multiplication: %dx%d with %d threads\n", n, n, num_threads);
    
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **C = allocate_matrix(n);
    
    srand(time(NULL));
    initialize_matrix(A, n);
    initialize_matrix(B, n);
    
    double start = omp_get_wtime();
    matrix_multiply(A, B, C, n);
    double end = omp_get_wtime();
    
    printf("Time taken: %.6f seconds\n", end - start);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    
    return 0;
}
