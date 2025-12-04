# Matrix Multiplication & Sorting — Modified Project


## Structure
matrix_multiplication_master_modified/
├── scripts/
│   ├── run_benchmarks.sh
│   └── run_sort_benchmarks.sh
│
├── src/
│   ├── mpi_matrix.c
│   ├── openmp_matrix.c
│   ├── openmp_sort.c
│   ├── pthread_matrix.c
│   ├── pthread_sort.c
│   ├── sequential_matrix.c
│   └── sequential_sort.c
│
├── .gitattributes
├── Makefile
├── Makefile.orig_from_os_codes
├── OS_codes.txt
└── README.md

## Build
To compile everything:
```
make
```

To clean builds and results:
```
make clean
```

## Run (examples)
- Sequential matrix multiplication (n x n):
  ```
  ./build/sequential_matrix 500
  ```

- Pthread matrix multiplication:
  ```
  ./build/pthread_matrix 500 4
  ```

- OpenMP matrix multiplication:
  ```
  ./build/openmp_matrix 500 4
  ```

- MPI matrix multiplication (example using 4 processes):
  ```
  mpirun -np 4 ./build/mpi_matrix 500
  ```

- Sequential merge sort:
  ```
  ./build/sequential_sort 100000
  ```

- Pthread merge sort:
  ```
  ./build/pthread_sort 100000 4
  ```

- Run provided benchmark scripts (if desired; ensure MPI environment is available for MPI runs)
  ```
  cd scripts
  ./run_benchmarks.sh
  ./run_sort_benchmarks.sh
  ```
