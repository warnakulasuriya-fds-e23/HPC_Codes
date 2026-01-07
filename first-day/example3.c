#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel sections
    {
        #pragma omp section
        printf("Section 1 executed by thread %d\n", omp_get_thread_num());

        #pragma omp section
        printf("Section 2 executed by thread %d\n", omp_get_thread_num());        
    } 

    return 0;
}