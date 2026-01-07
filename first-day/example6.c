#include <stdio.h>
#include <omp.h>

int main(){
    int counter=0;
    #pragma omp parallel 
    {
        #pragma omp critical
        {
            counter++;
            printf("Thread %d in critical section.\n", omp_get_thread_num());
        }
       
    } 
    printf("Final counter value= %d\n", counter);
    return 0;
}