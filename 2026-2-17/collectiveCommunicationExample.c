#include "mpi.h"
#include <stdio.h>
#define SIZE 4

void rowMultiplyByMatrixAndGetValue(float m1[SIZE], float m2[SIZE][SIZE], float result[SIZE]);

int main(int argc, char *argv[])  {
int numtasks, rank, sendcount, recvcount, source;
float sendbuf[SIZE][SIZE] = {
    {1.0, 2.0, 3.0, 4.0},
    {5.0, 6.0, 7.0, 8.0},
    {9.0, 10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0, 16.0}  };
float recvbuf[SIZE];

float b_mat[SIZE][SIZE] = {
    {16.0, 15.0, 14.0, 13.0},
    {12.0, 11.0, 10.0, 9.0},
    {8.0, 7.0, 6.0, 5.0},
    {4.0, 3.0, 2.0, 1.0} };

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

if (numtasks == SIZE) {
    float localResult[SIZE];
    MPI_Bcast(b_mat, SIZE*SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    // define source task and elements to send/receive, then perform collective scatter
    source = 0;
    sendcount = SIZE;
    recvcount = SIZE;
    
    MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount,
                MPI_FLOAT,source,MPI_COMM_WORLD);

    if (rank!=0){
        // printf("Worker process of rank %d has received the following data from broadcast:\n", rank);
        // for (int i = 0; i < SIZE; i++) {
        //     for (int j = 0; j < SIZE; j++) {
        //         printf("%f ", b_mat[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("Worker process of rank %d has received the following data from scatter:\n", rank);
        // for (int i = 0; i < SIZE; i++) {
        //     printf("%f ", recvbuf[i]);
        // }
        // printf("\n");
        // printf("Worker %d got results:\n",rank);
        // for (int i = 0; i < SIZE; i++) {
        //     printf("%f ", localResult[i]);
        // }
        // printf("\n");
    }else{
    }
    
    rowMultiplyByMatrixAndGetValue(recvbuf, b_mat, localResult);
    
    float finalResult[SIZE][SIZE];
    MPI_Gather(localResult,SIZE,MPI_FLOAT,finalResult,SIZE,MPI_FLOAT,0,MPI_COMM_WORLD);

    if (rank==0){
        printf("The Final result is\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%f ", finalResult[i][j]);
                if (j == SIZE -1){
                    printf("\n");
                }
            }
        }
    }
}
    
else
    printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
}

void rowMultiplyByMatrixAndGetValue(float m1[SIZE], float m2[SIZE][SIZE], float result[SIZE])
{

    for (int i = 0; i < SIZE; i++) {
        for (int k=0; k <SIZE; k++){
            result[k] = 0.0;
            for (int j = 0; j < SIZE; j++) {
                result[k] += m1[j] * (m2[j][k]);
            }

        }

    }

}