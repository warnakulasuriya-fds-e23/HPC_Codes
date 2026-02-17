#include <stdio.h>
#include <omp.h>

int main() {

    int data;
    #pragma omp parallel private(data)

    #pragma omp single copyprivate(data)
    {
        data = 42;
        printf("Thread %d sees data  = %d\n", omp_get_thread_num(), data);
    }
    return 0;
}