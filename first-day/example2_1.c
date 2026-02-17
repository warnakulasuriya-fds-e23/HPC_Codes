#include <stdio.h>
#include <omp.h>

int main(){
    int a[8];
    #pragma omp parallel 
    {

        #pragma omp for
        for (int i=0; i<8; i++){
            a[i]= i*i;
            printf("Thread %d did iteration %d\n", omp_get_thread_num(), i);
        }
    }
    
    return 0;
}