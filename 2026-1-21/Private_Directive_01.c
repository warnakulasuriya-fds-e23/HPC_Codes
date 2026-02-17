#include <stdio.h>
#include <omp.h>

int main() {
    int x = 0;

    #pragma omp parallel private(x)
    {
        x = omp_get_thread_num();
        printf("Thread %d: x=%d\n", omp_get_thread_num(), x);
    }
    return 0;
}