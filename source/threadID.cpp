# include <stdio.h> // short for Standard-In-Out, includes the declarations and definitions for creating/changing/... files, keyboard input and text output
# include <omp.h> // library for parallel programming in the shared-memory processors

int main (int argc, char* argv[]) {

    int numThreads; //part of the process, has its own stack and CPU-register-state, has the adress-space of the process
    int threadID; //number of the specific thread
    double start, end; //time of the start and end of the program, used for calculating the duration

    start = omp_get_wtime(); //returns elapsed wall clock time in seconds, starting point

    /* creates specified number of parallel threads */
    #pragma omp parallel num_threads(1)
    {
        threadID = omp_get_thread_num(); //returns the thread number
        printf("Hello from thread %d\n", threadID);
    
        /* omp_get_thread_num() returns 0 if it is called from the sequential part of a program */
        if (threadID == 0) {
            numThreads = omp_get_num_threads(); //returns number of threads
            printf("Number of threads: %d\n", numThreads); }
        }
    }
    end = omp_get_wtime(); //returns elapsed wall clock time in seconds, end point
    printf("This task took %f seconds\n", end-start);
    
    return 0;
}
