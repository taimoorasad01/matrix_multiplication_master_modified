CC = gcc
MPICC = mpicc
CFLAGS = -O3 -Wall
PTHREAD_FLAGS = -pthread
OPENMP_FLAGS = -fopenmp

SRC_DIR = src
BUILD_DIR = build

SEQ_MATRIX = $(BUILD_DIR)/sequential_matrix
PTHREAD_MATRIX = $(BUILD_DIR)/pthread_matrix
OPENMP_MATRIX = $(BUILD_DIR)/openmp_matrix
MPI_MATRIX = $(BUILD_DIR)/mpi_matrix

SEQ_SORT = $(BUILD_DIR)/sequential_sort
PTHREAD_SORT = $(BUILD_DIR)/pthread_sort
OPENMP_SORT = $(BUILD_DIR)/openmp_sort

all: matrix sort

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

matrix: $(BUILD_DIR) $(SEQ_MATRIX) $(PTHREAD_MATRIX) $(OPENMP_MATRIX) $(MPI_MATRIX)

$(SEQ_MATRIX): $(SRC_DIR)/sequential_matrix.c
	$(CC) $(CFLAGS) $< -o $@

$(PTHREAD_MATRIX): $(SRC_DIR)/pthread_matrix.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(OPENMP_MATRIX): $(SRC_DIR)/openmp_matrix.c
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) $< -o $@

$(MPI_MATRIX): $(SRC_DIR)/mpi_matrix.c
	$(MPICC) $(CFLAGS) $< -o $@

sort: $(BUILD_DIR) $(SEQ_SORT) $(PTHREAD_SORT) $(OPENMP_SORT)

$(SEQ_SORT): $(SRC_DIR)/sequential_sort.c
	$(CC) $(CFLAGS) $< -o $@

$(PTHREAD_SORT): $(SRC_DIR)/pthread_sort.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(OPENMP_SORT): $(SRC_DIR)/openmp_sort.c
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR) results

.PHONY: all clean matrix sort
