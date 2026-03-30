#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int shared_value;

    // STEP 1: Only the root prepares the data
    if (rank == 0) {
        shared_value = 555; 
    }

    // STEP 2: The actual communication
    // Every process runs this same line. 
    // Rank 0 knows to "Push"; all others know to "Pull".
    MPI_Bcast(&shared_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // STEP 3: Everyone now has the data
    printf("Process %d now holds the value: %d\n", rank, shared_value);

    MPI_Finalize();
    return 0;
}
