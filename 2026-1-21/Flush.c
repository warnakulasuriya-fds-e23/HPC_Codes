#include <stdio.h>
#include <omp.h>

int done = 0;

int main() {
    // Start a prallel region with 4 threads
    #pragma omp parallel num_threads(4) shared(done)
    {   
        //Get tje current thread ID
        int tid = omp_get_thread_num();

        //Thread 0 performs some work
        if (tid == 0){

            // Set the shared flag
            done = 1;

            // Ensure the write to 'done' is visible to all threads
            #pragma omp flush(done)

            //Print confirmation
            printf("Thread %d set done =1n", tid);
        }else{

            // Other threads wait until 'done' becomes 1
            while(!done){

                // Force re-read of 'done' from memory
                #pragma omp flush(done)

                // Print confirmation
                printf("Thread %d detected done = 1\n", tid);
            } 
        }

    }
    return 0;
}