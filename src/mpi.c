#include "mpi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

static int next_comm_id = 10;
static int next_win_id = 1000;
static int next_keyval = 1;
static int custom_type_sizes[1024];
static int next_type_id = 100;
static int next_errhandler = 10;
static int next_op_id = 100;
static int next_group_id = 1;

/* --- Initialization & Information --- */
int MPI_Init(int *argc, char ***argv) { return MPI_SUCCESS; }
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided) { *provided = required; return MPI_SUCCESS; }
int MPI_Finalize(void) { return MPI_SUCCESS; }
int MPI_Initialized(int *flag) { *flag = 1; return MPI_SUCCESS; }
int MPI_Finalized(int *flag) { *flag = 0; return MPI_SUCCESS; }
int MPI_Abort(MPI_Comm comm, int errorcode) { exit(errorcode); return MPI_SUCCESS; }
double MPI_Wtime(void) { struct timeval tv; gettimeofday(&tv, NULL); return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0; }

/* --- Error Handling --- */
int MPI_Error_string(int errorcode, char *string, int *resultlen) { 
    const char *msg = "MPI_STUB_ERROR";
    if (string) strncpy(string, msg, MPI_MAX_ERROR_STRING); 
    if (resultlen) *resultlen = strlen(msg); 
    return MPI_SUCCESS; 
}
int MPI_Add_error_class(int *errorclass) { if (errorclass) *errorclass = 100; return MPI_SUCCESS; }
int MPI_Add_error_code(int errorclass, int *errorcode) { if (errorcode) *errorcode = 1000; return MPI_SUCCESS; }
int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler) { if (errhandler) *errhandler = next_errhandler++; return MPI_SUCCESS; }
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_fn *function, MPI_Errhandler *errhandler) { if (errhandler) *errhandler = next_errhandler++; return MPI_SUCCESS; }
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }

/* --- Communicator, Group & Attribute Utilities --- */
int MPI_Comm_size(MPI_Comm comm, int *size) { *size = 1; return MPI_SUCCESS; }
int MPI_Comm_rank(MPI_Comm comm, int *rank) { *rank = 0; return MPI_SUCCESS; }
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm) { *newcomm = next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_free(MPI_Comm *comm) { *comm = MPI_COMM_NULL; return MPI_SUCCESS; }
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm) { if (newcomm) *newcomm = next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm) { if (newcomm) *newcomm = next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result) { if (result) *result = (comm1 == comm2) ? MPI_IDENT : MPI_UNEQUAL; return MPI_SUCCESS; }
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen) { const char* name = "MPI_STUB_COMM"; if (comm_name) strncpy(comm_name, name, MPI_MAX_OBJECT_NAME); if (resultlen) *resultlen = strlen(name); return MPI_SUCCESS; }
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group) { if (group) *group = next_group_id++; return MPI_SUCCESS; }

int MPI_Group_size(MPI_Group group, int *size) { if (size) *size = 1; return MPI_SUCCESS; }
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]) { if (ranks1 && ranks2) { for(int i=0; i<n; i++) ranks2[i] = ranks1[i]; } return MPI_SUCCESS; }
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { if (newgroup) *newgroup = next_group_id++; return MPI_SUCCESS; }
int MPI_Group_free(MPI_Group *group) { if (group) *group = MPI_GROUP_NULL; return MPI_SUCCESS; }

int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state) { if (comm_keyval) *comm_keyval = next_keyval++; return MPI_SUCCESS; }
int MPI_Comm_free_keyval(int *comm_keyval) { if (comm_keyval) *comm_keyval = MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag) { if (flag) *flag = 0; return MPI_SUCCESS; }
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval) { return MPI_SUCCESS; }

/* --- Info Objects --- */
int MPI_Info_free(MPI_Info *info) { if (info) *info = MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo) { if (newinfo) *newinfo = info; return MPI_SUCCESS; }
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys) { if (nkeys) *nkeys = 0; return MPI_SUCCESS; }
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key) { if (key) key[0] = '\0'; return MPI_SUCCESS; }
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag) { if (flag) *flag = 0; return MPI_SUCCESS; }

/* --- Datatypes --- */
int MPI_Type_size(MPI_Datatype datatype, int *size) {
    if (datatype >= 100 && datatype < 1124) {
        *size = custom_type_sizes[datatype - 100];
        return MPI_SUCCESS;
    }
    switch (datatype) {
        case MPI_CHAR: case MPI_BYTE: case MPI_UNSIGNED_CHAR: case MPI_C_BOOL: case MPI_SIGNED_CHAR: *size = 1; break;
        case MPI_SHORT: case MPI_UNSIGNED_SHORT: *size = sizeof(short); break;
        case MPI_INT: case MPI_INT32_T: *size = 4; break;
        case MPI_UNSIGNED: *size = sizeof(unsigned); break;
        case MPI_LONG: *size = sizeof(long); break;
        case MPI_LONG_LONG_INT: case MPI_INT64_T: *size = 8; break;
        case MPI_UNSIGNED_LONG: *size = sizeof(unsigned long); break;
        case MPI_UNSIGNED_LONG_LONG: *size = sizeof(unsigned long long); break;
        case MPI_AINT: *size = sizeof(MPI_Aint); break;
        case MPI_FLOAT: *size = sizeof(float); break;
        case MPI_DOUBLE: *size = sizeof(double); break;
        case MPI_2DOUBLE_PRECISION: *size = 2 * sizeof(double); break;
        case MPI_COMPLEX: case MPI_C_FLOAT_COMPLEX: *size = 2 * sizeof(float); break;
        case MPI_DOUBLE_COMPLEX: case MPI_C_DOUBLE_COMPLEX: *size = 2 * sizeof(double); break;
        case MPI_2INT: *size = 2 * sizeof(int); break;
        default: *size = 0; return MPI_ERR_UNKNOWN;
    }
    return MPI_SUCCESS;
}
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype) { if (newtype) *newtype = oldtype; return MPI_SUCCESS; }
int MPI_Type_commit(MPI_Datatype *datatype) { return MPI_SUCCESS; }
int MPI_Type_free(MPI_Datatype *datatype) { if (datatype) *datatype = MPI_DATATYPE_NULL; return MPI_SUCCESS; }
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype) { int old_size; MPI_Type_size(oldtype, &old_size); if (newtype) { *newtype = next_type_id++; custom_type_sizes[*newtype - 100] = count * old_size; } return MPI_SUCCESS; }
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner) { if (num_integers) *num_integers = 0; if (num_addresses) *num_addresses = 0; if (num_datatypes) *num_datatypes = 0; if (combiner) *combiner = MPI_COMBINER_NAMED; return MPI_SUCCESS; }
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent) { int size; MPI_Type_size(datatype, &size); if (lb) *lb = 0; if (extent) *extent = size; return MPI_SUCCESS; }
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent) { return MPI_Type_get_extent(datatype, true_lb, true_extent); }
int MPI_Type_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype) { if (newtype) *newtype = next_type_id++; return MPI_SUCCESS; }
int MPI_Type_create_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype) { return MPI_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype); }
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype) { if (newtype) { *newtype = next_type_id++; custom_type_sizes[*newtype - 100] = extent; } return MPI_SUCCESS; }
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { int old_size; MPI_Type_size(oldtype, &old_size); if (newtype) { *newtype = next_type_id++; custom_type_sizes[*newtype - 100] = count * blocklength * old_size; } return MPI_SUCCESS; }

/* --- Operations --- */
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op) { if (op) *op = next_op_id++; return MPI_SUCCESS; }
int MPI_Op_free(MPI_Op *op) { if (op) *op = MPI_OP_NULL; return MPI_SUCCESS; }

/* --- Collectives --- */
int MPI_Barrier(MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(datatype, &type_size); memcpy(recvbuf, sendbuf, (size_t)count * type_size); return MPI_SUCCESS; }
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_Reduce(sendbuf, recvbuf, count, datatype, op, 0, comm); }
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(recvtype, &type_size); memcpy(recvbuf, sendbuf, (size_t)recvcount * type_size); return MPI_SUCCESS; }
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(sendtype, &type_size); memcpy(recvbuf, sendbuf, (size_t)sendcount * type_size); return MPI_SUCCESS; }
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, 0, comm); }
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(recvtype, &type_size); memcpy(recvbuf, sendbuf, (size_t)recvcount * type_size); return MPI_SUCCESS; }
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(datatype, &type_size); memcpy(recvbuf, sendbuf, (size_t)count * type_size); return MPI_SUCCESS; }
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(datatype, &type_size); memcpy(recvbuf, sendbuf, (size_t)recvcounts[0] * type_size); return MPI_SUCCESS; }
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(sendtype, &type_size); memcpy((char*)recvbuf + displs[0] * type_size, sendbuf, (size_t)sendcount * type_size); return MPI_SUCCESS; }
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm) { return MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if (sendbuf == MPI_IN_PLACE || sendbuf == recvbuf) return MPI_SUCCESS; int type_size; MPI_Type_size(recvtype, &type_size); memcpy(recvbuf, (char*)sendbuf + displs[0] * type_size, (size_t)recvcount * type_size); return MPI_SUCCESS; }
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op) { return MPI_SUCCESS; }

/* --- Point-to-Point --- */
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { if (status) { status->MPI_SOURCE = 0; status->MPI_TAG = tag; status->MPI_ERROR = MPI_SUCCESS; status->_count = count; } return MPI_SUCCESS; }
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count) { if (count) *count = status ? (int)status->_count : 0; return MPI_SUCCESS; }
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Startall(int count, MPI_Request array_of_requests[]) { return MPI_SUCCESS; }
int MPI_Wait(MPI_Request *request, MPI_Status *status) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]) { if (array_of_requests) { for (int i = 0; i < count; i++) array_of_requests[i] = MPI_REQUEST_NULL; } return MPI_SUCCESS; }
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status) { if (indx) *indx = 0; if (array_of_requests && count > 0) array_of_requests[0] = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status) { if (flag) *flag = 1; if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) { if (flag) *flag = 1; if (array_of_requests) { for (int i = 0; i < count; i++) array_of_requests[i] = MPI_REQUEST_NULL; } return MPI_SUCCESS; }
int MPI_Request_free(MPI_Request *request) { if (request) *request = MPI_REQUEST_NULL; return MPI_SUCCESS; }

/* --- RMA / Windows and Misc --- */
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win) { if (win) *win = next_win_id++; return MPI_SUCCESS; }
int MPI_Win_free(MPI_Win *win) { if (win) *win = MPI_WIN_NULL; return MPI_SUCCESS; }
int MPI_Win_fence(int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_unlock(int rank, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_complete(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_wait(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get_library_version(char *version, int *resultlen) { const char *ver_string = "MPI Stub 1.0"; if (version) strncpy(version, ver_string, MPI_MAX_LIBRARY_VERSION_STRING); if (resultlen) *resultlen = strlen(ver_string); return MPI_SUCCESS; }

/* --- C/Fortran Interoperability --- */
MPI_Datatype MPI_Type_f2c(MPI_Fint datatype) { return (MPI_Datatype)datatype; }
MPI_Fint MPI_Type_c2f(MPI_Datatype datatype) { return (MPI_Fint)datatype; }
MPI_Comm MPI_Comm_f2c(MPI_Fint comm) { return (MPI_Comm)comm; }
MPI_Fint MPI_Comm_c2f(MPI_Comm comm) { return (MPI_Fint)comm; }
MPI_Op MPI_Op_f2c(MPI_Fint op) { return (MPI_Op)op; }
MPI_Fint MPI_Op_c2f(MPI_Op op) { return (MPI_Fint)op; }
MPI_Request MPI_Request_f2c(MPI_Fint request) { return (MPI_Request)request; }
MPI_Fint MPI_Request_c2f(MPI_Request request) { return (MPI_Fint)request; }
MPI_Win MPI_Win_f2c(MPI_Fint win) { return (MPI_Win)win; }
MPI_Fint MPI_Win_c2f(MPI_Win win) { return (MPI_Fint)win; }
MPI_Info MPI_Info_f2c(MPI_Fint info) { return (MPI_Info)info; }
MPI_Fint MPI_Info_c2f(MPI_Info info) { return (MPI_Fint)info; }
MPI_Group MPI_Group_f2c(MPI_Fint group) { return (MPI_Group)group; }
MPI_Fint MPI_Group_c2f(MPI_Group group) { return (MPI_Fint)group; }
MPI_Errhandler MPI_Errhandler_f2c(MPI_Fint errhandler) { return (MPI_Errhandler)errhandler; }
MPI_Fint MPI_Errhandler_c2f(MPI_Errhandler errhandler) { return (MPI_Fint)errhandler; }