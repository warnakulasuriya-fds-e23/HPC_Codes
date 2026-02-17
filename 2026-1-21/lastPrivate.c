#include <stdio.h>
#include <omp.h>

int main() {
    int x = -1;

    #pragma omp parallel for lastprivate(x)
    for(int i=0; i<5; i++){
        x = i*10;
        printf("Thread %d sets x = %d\n", omp_get_thread_num(),x);
        printf("After loop x = %d\n", x);
    }
    return 0;
}