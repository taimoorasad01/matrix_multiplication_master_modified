# Matrix Multiplication & Sorting — Modified Project


## Structure
- `src/` : C source files for matrix multiplication (sequential, pthreads, OpenMP, MPI) and merge sort (sequential, pthreads, OpenMP).
- `build/` : build outputs (generated after `make`).
- `results/` : scripts write outputs here.
- `scripts/` : helper scripts to run benchmarks.
- `Makefile` : unified Makefile to build both matrix and sorting programs.
- `README.md` : this file.

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
