#!/bin/bash

SIZES=(10000 100000 1000000 10000000)
THREADS=4
RESULTS_FILE="results/sorting_results.txt"

echo "Merge Sort Benchmarking Results" > $RESULTS_FILE
echo "===============================" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE

for SIZE in "${SIZES[@]}"
do
    echo "Testing with array size: $SIZE" | tee -a $RESULTS_FILE
    echo "----------------------------------------" | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "Sequential:" | tee -a $RESULTS_FILE
    ./build/sequential_sort $SIZE | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "Pthreads ($THREADS threads):" | tee -a $RESULTS_FILE
    ./build/pthread_sort $SIZE $THREADS | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "OpenMP ($THREADS threads):" | tee -a $RESULTS_FILE
    ./build/openmp_sort $SIZE $THREADS | tee -a $RESULTS_FILE
    
    echo "" | tee -a $RESULTS_FILE
    echo "========================================" | tee -a $RESULTS_FILE
    echo "" | tee -a $RESULTS_FILE
done

echo "Benchmarking complete! Results saved to $RESULTS_FILE"
