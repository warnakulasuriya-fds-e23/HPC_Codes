#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel num_threads(4) 
    {
            printf("Thread %d BEFORE barier.\n", omp_get_thread_num());

            #pragma omp barrier

            printf("Thread %d AFTER barier.\n", omp_get_thread_num());
       
    } 
    return 0;
}