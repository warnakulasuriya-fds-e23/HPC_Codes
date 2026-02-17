#include <stdio.h>
#include <omp.h>

int main() {
    int instructions = 0;
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        // Only master thread wrrties instructions
        #pragma omp master
        {
            for (int i=0; i<=5; i++){
                printf("i value is %d: from thread %d \n",i,tid);
            }
            printf("\n");
        }
    }
    return 0;
}