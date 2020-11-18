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
    
        /* omp_get_thread_num() returns 0 if it is called from the master thread (or asequential part) of a program */
        if (threadID == 0) {
            numThreads = omp_get_num_threads(); //returns number of threads
            printf("Number of threads: %d\n", numThreads);
        }
    }
    end = omp_get_wtime(); //returns elapsed wall clock time in seconds, end point
    printf("This task took %f seconds\n", end-start);
    
    return 0;
}


/* task 1.3

Example Tests:

10000 threads: This task took 0.863448 seconds
20000 threads: This task took 1.898515 seconds
25000 threads: libgomp: Thread creation failed: Resource temporarily unavailable
80000 threads: Segmentation fault (core dumped)

Explanation:

Increasing the num_threads parameter simultaneously increases the execution time. 
The threads are printed in random order. If the number of threads is increased to
25000 and more, the program does not create threads because the resource is
"temporarily unavailable". If the number of threads is increased to about 80000,
it causes a segmentation fault. */