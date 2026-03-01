#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mpi.h"

#define ASSERT_SUCCESS(err) do { \
    if ((err) != MPI_SUCCESS) { \
        fprintf(stderr, "MPI Call Failed at %s:%d\n", __FILE__, __LINE__); \
        exit(1); \
    } \
} while(0)

void test_init_and_comm() {
    printf("Running Initialization & Communicator Tests...\n");
    int argc = 0;
    char **argv = NULL;
    int provided;
    
    ASSERT_SUCCESS(MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided));
    assert(provided == MPI_THREAD_MULTIPLE);

    int init_flag = 0;
    ASSERT_SUCCESS(MPI_Initialized(&init_flag));
    assert(init_flag == 1);

    int rank, size;
    ASSERT_SUCCESS(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    ASSERT_SUCCESS(MPI_Comm_size(MPI_COMM_WORLD, &size));
    
    assert(rank == 0);
    assert(size == 1);
    printf("  [OK] Initialization & Communicators\n");
}

void test_point_to_point() {
    printf("Running Point-to-Point Tests...\n");
    int send_val = 42;
    int recv_val = 0;
    MPI_Request req;
    MPI_Status status;

    ASSERT_SUCCESS(MPI_Isend(&send_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req));
    assert(req == MPI_REQUEST_NULL); // Stub should nullify requests immediately

    ASSERT_SUCCESS(MPI_Irecv(&recv_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req));
    assert(req == MPI_REQUEST_NULL);

    ASSERT_SUCCESS(MPI_Wait(&req, &status));
    
    ASSERT_SUCCESS(MPI_Sendrecv_replace(&send_val, 1, MPI_INT, 0, 0, 0, 0, MPI_COMM_WORLD, &status));
    assert(status.MPI_SOURCE == 0);
    
    printf("  [OK] Point-to-Point\n");
}

void test_collectives() {
    printf("Running Collectives Tests...\n");
    int data[5] = {1, 2, 3, 4, 5};
    int recv[5] = {0};
    MPI_Request req;

    ASSERT_SUCCESS(MPI_Bcast(data, 5, MPI_INT, 0, MPI_COMM_WORLD));
    
    // Test blocking reduce
    ASSERT_SUCCESS(MPI_Allreduce(data, recv, 5, MPI_INT, MPI_SUM, MPI_COMM_WORLD));
    
    // Test MPI-3 non-blocking collective (crucial for DOLFINx)
    ASSERT_SUCCESS(MPI_Iallreduce(data, recv, 5, MPI_INT, MPI_SUM, MPI_COMM_WORLD, &req));
    assert(req == MPI_REQUEST_NULL);
    
    // Scatter/Gather
    ASSERT_SUCCESS(MPI_Igather(data, 5, MPI_INT, recv, 5, MPI_INT, 0, MPI_COMM_WORLD, &req));
    ASSERT_SUCCESS(MPI_Iscatter(data, 5, MPI_INT, recv, 5, MPI_INT, 0, MPI_COMM_WORLD, &req));

    printf("  [OK] Collectives\n");
}

void test_attribute_caching() {
    printf("Running Attribute Caching Tests (PETSc requirements)...\n");
    int flag;
    void *val_ptr;

    // Test Built-in Attributes
    ASSERT_SUCCESS(MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_TAG_UB, &val_ptr, &flag));
    assert(flag == 1);
    assert(*(int*)val_ptr > 0);

    ASSERT_SUCCESS(MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_WTIME_IS_GLOBAL, &val_ptr, &flag));
    assert(flag == 1);
    assert(*(int*)val_ptr == 1);

    // Test Custom Attribute Storage
    int custom_key = 1001;
    long custom_data = 9999;
    
    ASSERT_SUCCESS(MPI_Comm_set_attr(MPI_COMM_WORLD, custom_key, (void*)&custom_data));
    ASSERT_SUCCESS(MPI_Comm_get_attr(MPI_COMM_WORLD, custom_key, &val_ptr, &flag));
    assert(flag == 1);
    assert(*(long*)val_ptr == 9999);

    // Delete Attribute
    ASSERT_SUCCESS(MPI_Comm_delete_attr(MPI_COMM_WORLD, custom_key));
    ASSERT_SUCCESS(MPI_Comm_get_attr(MPI_COMM_WORLD, custom_key, &val_ptr, &flag));
    assert(flag == 0); // Should be gone

    printf("  [OK] Attribute Caching\n");
}

void test_file_io() {
    printf("Running File I/O Tests (HDF5 requirements)...\n");
    MPI_File fh;
    const char* filename = "test_mpi_io.tmp";
    char write_data[] = "MPI_STUB_IO_TEST";
    char read_data[32] = {0};
    MPI_Status status;

    // Open (Create)
    ASSERT_SUCCESS(MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh));
    
    // Write at offset
    ASSERT_SUCCESS(MPI_File_write_at(fh, 0, write_data, strlen(write_data), MPI_CHAR, &status));
    
    // Read at offset
    ASSERT_SUCCESS(MPI_File_read_at(fh, 0, read_data, strlen(write_data), MPI_CHAR, &status));
    assert(strcmp(write_data, read_data) == 0);
    
    // Close & Delete
    ASSERT_SUCCESS(MPI_File_close(&fh));
    ASSERT_SUCCESS(MPI_File_delete(filename, MPI_INFO_NULL));

    printf("  [OK] File I/O\n");
}

void test_finalize() {
    printf("Running Finalize Tests...\n");
    ASSERT_SUCCESS(MPI_Finalize());

    int final_flag = 0;
    ASSERT_SUCCESS(MPI_Finalized(&final_flag));
    assert(final_flag == 1);
    
    printf("  [OK] Finalize\n");
}

int main(int argc, char** argv) {
    printf("=== Starting MPI Stub Test Suite ===\n");
    
    test_init_and_comm();
    test_point_to_point();
    test_collectives();
    test_attribute_caching();
    test_file_io();
    test_finalize();

    printf("=== All Tests Passed Successfully! ===\n");
    return 0;
}