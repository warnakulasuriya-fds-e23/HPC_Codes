#include <stdio.h>
#include <omp.h>

int main() {
    int instructions = 0;
    int a=0, b=0;
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                printf("Task 1 Working...\n");
                a=10;
                printf("a value is : %d \n",a);
            }

            #pragma omp task
            {
                printf("Task 2 Working...\n");
                b=20;
                printf("b value is : %d \n",b);
            }

            //May execute before tasks finish
            printf("Sum = %d\n",a+b);
        }
    }
    return 0;
}