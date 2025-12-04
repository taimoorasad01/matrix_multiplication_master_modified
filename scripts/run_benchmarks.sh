#!/bin/bash

SIZES=(10 500 1000)
THREADS=4
PROCESSES=4
RESULTS_FILE="results/matrix_results.txt"

echo "Matrix Multiplication Benchmarking Results" > $RESULTS_FILE
echo "==========================================" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE

for SIZE in "${SIZES[@]}"
do
    echo "Testing with matrix size: ${SIZE}x${SIZE}" | tee -a $RESULTS_FILE
    echo "----------------------------------------" | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "Sequential:" | tee -a $RESULTS_FILE
    ./build/sequential_matrix $SIZE | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "Pthreads ($THREADS threads):" | tee -a $RESULTS_FILE
    ./build/pthread_matrix $SIZE $THREADS | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "OpenMP ($THREADS threads):" | tee -a $RESULTS_FILE
    ./build/openmp_matrix $SIZE $THREADS | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "MPI ($PROCESSES processes):" | tee -a $RESULTS_FILE
    mpirun -np $PROCESSES ./build/mpi_matrix $SIZE | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "========================================" | tee -a $RESULTS_FILE
    echo "" | tee -a $RESULTS_FILE
done

echo "Benchmarking complete! Results saved to $RESULTS_FILE"




chmod +x run_benchmarks.sh
./run_benchmarks.sh



cat results/matrix_results.txt



Sorting:
