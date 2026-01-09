#include <stdio.h>
#include <omp.h>

int main ()  {

omp_set_num_threads(4);

printf("Number of processors available= %d\n", omp_get_max_procs());
printf("Number of threads set= %d\n", omp_get_max_threads());

double start = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int total = omp_get_num_threads();
   
        printf("Hello fromt thread %d out of %d threads\n", tid, total);
   
        if(omp_in_parallel()){
           printf("Thread %d is executing in paralle region\n", tid);
        }
    }

    double end = omp_get_wtime();
    printf("Execution Time: %f secods\n", end - start);

return 0;
}