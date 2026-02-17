#include <stdio.h>
#include <omp.h>

int main() {
    int instructions = 0;
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        // Every thread writes the innstructions
        for (int i=0; i<=5; i++){
            printf("i value is %d: from thread %d \n",i,tid);
        }
    }
    return 0;
}