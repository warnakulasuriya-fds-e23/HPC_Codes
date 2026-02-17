#include <stdio.h>
#include <omp.h>

int main() {
    int i;

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    #pragma omp parallel for private(i)
    for(i=0; i<8; i++){
        printf("Thread %d: i = %d\n", omp_get_thread_num(), i);
    }
    return 0;
}