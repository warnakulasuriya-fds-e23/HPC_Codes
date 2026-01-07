#include <stdio.h>
#include <omp.h>

int main(){
    int a[100];
    #pragma omp parallel for 
    for (int i=0; i<200; i++){
        a[i]= i*i;
        printf("Thread %d did iteration %d\n", omp_get_thread_num(), i);
    }
    return 0;
}