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

    int dataset[8];
    int results[8];
    int local_data[2]; // Each process handles 2 elements

    // Rank 0 initializes the dataset
    if (rank == 0) {
        for (int i = 0; i < 8; i++) {
            dataset[i] = i + 1; // [1, 2, 3, 4, 5, 6, 7, 8]
        }
    }

    // 1. Scatter 2 elements to each process
    MPI_Scatter(dataset, 2, MPI_INT, local_data, 2, MPI_INT, 0, MPI_COMM_WORLD);

    // 2. Each process squares its local elements
    local_data[0] = local_data[0] * local_data[0];
    local_data[1] = local_data[1] * local_data[1];
    printf("Rank %d squared its data to %d and %d\n", rank, local_data[0], local_data[1]);

    // 3. Gather the 2 elements from each process back into the results array
    MPI_Gather(local_data, 2, MPI_INT, results, 2, MPI_INT, 0, MPI_COMM_WORLD);

    // Rank 0 prints the final results
    if (rank == 0) {
        printf("Final Squared Array: ");
        for (int i = 0; i < 8; i++) {
            printf("%d ", results[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
