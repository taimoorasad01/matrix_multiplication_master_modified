#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct {
    int *arr;
    int left;
    int right;
} ThreadData;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void* parallel_merge_sort(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    merge_sort(data->arr, data->left, data->right);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <num_threads>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    printf("Pthread Merge Sort: %d elements with %d threads\n", n, num_threads);
    
    int *arr = (int*)malloc(n * sizeof(int));
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
    
    clock_t start = clock();
    
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int chunk_size = n / num_threads;
    
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].arr = arr;
        thread_data[i].left = i * chunk_size;
        thread_data[i].right = (i == num_threads - 1) ? (n - 1) : ((i + 1) * chunk_size - 1);
        pthread_create(&threads[i], NULL, parallel_merge_sort, &thread_data[i]);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Merge all sorted chunks
    for (int i = 1; i < num_threads; i++) {
        int left = 0;
        int mid = i * chunk_size - 1;
        int right = (i == num_threads - 1) ? (n - 1) : ((i + 1) * chunk_size - 1);
        merge(arr, left, mid, right);
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);
    
    free(arr);
    return 0;
}
