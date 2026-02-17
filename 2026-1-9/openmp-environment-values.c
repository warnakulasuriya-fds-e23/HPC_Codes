#include <stdio.h>
#include <omp.h>

int main ()  {
// Here instead of specifying the number of threads to use within the code we can
// define and use the environment variable OMP_NUM_THREADS which would control the number
// of threads

// also we cnae set the OMP_DYNAMIC=FALSE through environment variables 

// basically set the two environment variables OMP_NUM_THREADS, OMP_DYNAMIC and make
// sure that the terminal that your going to use to compile this code has access to the 
// said environment variables and then you can observe that threads can be controlled via envs
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