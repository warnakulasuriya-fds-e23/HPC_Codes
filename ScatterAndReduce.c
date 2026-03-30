#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) printf("Please run with exactly 4 processes.\n");
        MPI_Finalize();
        return 0;
    }

    int big_data[16];
    int local_chunk[4]; // Each process gets 4 elements
    int local_sum = 0;
    int grand_total = 0;

    // Rank 0 fills the array with 1s (so the grand total should be 16)
    if (rank == 0) {
        for (int i = 0; i < 16; i++) {
            big_data[i] = 1;
        }
    }

    // 1. Scatter 4 elements to each process
    MPI_Scatter(big_data, 4, MPI_INT, local_chunk, 4, MPI_INT, 0, MPI_COMM_WORLD);

    // 2. Each process calculates the sum of its own chunk
    for (int i = 0; i < 4; i++) {
        local_sum += local_chunk[i];
    }
    printf("Rank %d calculated a local sum of %d\n", rank, local_sum);

    // 3. Reduce all the local_sums into the grand_total on Rank 0
    MPI_Reduce(&local_sum, &grand_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 prints the final result
    if (rank == 0) {
        printf("The grand total of all elements in the array is: %d\n", grand_total);
    }

    MPI_Finalize();
    return 0;
}
