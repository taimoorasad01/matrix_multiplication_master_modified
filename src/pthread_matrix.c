#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    double **A;
    double **B;
    double **C;
    int n;
    int start_row;
    int end_row;
} ThreadData;

void* matrix_multiply_thread(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->n; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->n; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
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
    printf("Pthread Matrix Multiplication: %dx%d with %d threads\n", n, n, num_threads);
    
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **C = allocate_matrix(n);
    
    srand(time(NULL));
    initialize_matrix(A, n);
    initialize_matrix(B, n);
    
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int rows_per_thread = n / num_threads;
    
    clock_t start = clock();
    
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].n = n;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? n : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, matrix_multiply_thread, &thread_data[i]);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    
    return 0;
}
