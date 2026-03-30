#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int threshold;
    int local_value = rank * 5; // e.g., Rank 2 gets 10
    int local_contribution = 0;
    int global_sum = 0;

    // Rank 0 sets the threshold
    if (rank == 0) {
        threshold = 8;
        printf("Rank 0 broadcasting threshold: %d\n", threshold);
    }

    // 1. Broadcast the threshold to all processes
    MPI_Bcast(&threshold, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // 2. Each process checks its local value against the shared threshold
    if (local_value > threshold) {
        local_contribution = local_value;
    }

    printf("Rank %d has local_value %d -> contribution is %d\n", rank, local_value, local_contribution);

    // 3. Reduce (Sum) all contributions into the global_sum on Rank 0
    MPI_Reduce(&local_contribution, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 prints the final sum
    if (rank == 0) {
        printf("Total sum of values above the threshold is: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
