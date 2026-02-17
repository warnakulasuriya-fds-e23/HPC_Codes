//Synchronization: Atomic Operation
#include <stdio.h>
#include <omp.h>

int main(){
    int counter=0;
    #pragma omp parallel num_threads(4) 
    {
        #pragma omp atomic
            counter++;
            printf("Thread %d incremented counter.\n", omp_get_thread_num());
       
    } 
    printf("Final counter value= %d\n", counter);
    return 0;
}