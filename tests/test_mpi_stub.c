#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_initialization() {
    int init_flag;
    MPI_Initialized(&init_flag);
    assert(init_flag == 1);
    
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    assert(size == 1);
    assert(rank == 0);
    printf("[OK] Initialization and Rank\n");
}

void test_communicator_dup() {
    MPI_Comm newcomm1, newcomm2;
    MPI_Comm_dup(MPI_COMM_WORLD, &newcomm1);
    MPI_Comm_dup(MPI_COMM_WORLD, &newcomm2);
    
    // PETSc relies on unique handles for duplicated communicators to avoid attribute clashing
    assert(newcomm1 != MPI_COMM_WORLD);
    assert(newcomm1 != newcomm2);
    printf("[OK] Communicator Duplication\n");
}

void test_allreduce_memory() {
    double send_data[3] = {1.0, 2.0, 3.0};
    double recv_data[3] = {0.0, 0.0, 0.0};

    // Test 1: Distinct buffers (must copy)
    MPI_Allreduce(send_data, recv_data, 3, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    assert(recv_data[0] == 1.0 && recv_data[2] == 3.0);

    // Test 2: MPI_IN_PLACE (must NOT segfault or overlap, should leave data untouched)
    recv_data[0] = 5.0; // Reset
    MPI_Allreduce(MPI_IN_PLACE, recv_data, 3, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    assert(recv_data[0] == 5.0); // Data should remain unchanged in serial stub

    printf("[OK] Allreduce Memory Semantics\n");
}

int main(int argc, char **argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, 0, &provided);

    test_initialization();
    test_communicator_dup();
    test_allreduce_memory();

    MPI_Finalize();
    
    int fin_flag;
    MPI_Finalized(&fin_flag);
    assert(fin_flag == 0);
    
    printf("All MPI stub tests passed successfully.\n");
    return EXIT_SUCCESS;
}