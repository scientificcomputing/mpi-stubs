#include "mpi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* =========================================================================
 * Internal Helpers for Status & Memory
 * ========================================================================= */
static int next_comm_id = 10;
static int next_win_id = 1000;
static int next_keyval = 1;
static int next_errhandler = 10;
static int next_op_id = 100;
static int next_group_id = 1;
static int next_info_id = 1;

/* Dynamic Datatype sizing mapping logic */
static int custom_type_sizes[1024];
static int next_type_id = 2000;

static void set_status_count(MPI_Status *status, int count) {
    if (status && status != MPI_STATUS_IGNORE) {
        memcpy(&status->MPI_internal[0], &count, sizeof(int));
        status->MPI_ERROR = MPI_SUCCESS;
    }
}

static int get_type_size(MPI_Datatype datatype) {
    int id = (int)(intptr_t)datatype;
    if (id >= 2000 && id < 3024) {
        return custom_type_sizes[id - 2000];
    }
    switch(id) {
        case 520: return sizeof(short);
        case 521: return sizeof(int);
        case 522: return sizeof(long);
        case 523: return sizeof(long long);
        case 528: return sizeof(float);
        case 532: return sizeof(double);
        case 544: return sizeof(long double);
        case 552: return sizeof(struct { float a; int b; });     /* MPI_FLOAT_INT */
        case 553: return sizeof(struct { double a; int b; });    /* MPI_DOUBLE_INT */
        case 554: return sizeof(struct { long a; int b; });      /* MPI_LONG_INT */
        case 555: return sizeof(struct { int a; int b; });       /* MPI_2INT */
        case 556: return sizeof(struct { short a; int b; });     /* MPI_SHORT_INT */
        case 557: return sizeof(struct { long double a; int b; });/* MPI_LONG_DOUBLE_INT */
        case 560: return sizeof(float) * 2;                      /* MPI_2REAL */
        case 561: return sizeof(double) * 2;                     /* MPI_2DOUBLE_PRECISION */
        case 562: return sizeof(int) * 2;                        /* MPI_2INTEGER */
        case 579: return 1;                                      /* MPI_CHAR */
        case 583: return 1;                                      /* MPI_BYTE */
        case 592: return 4;                                      /* MPI_INT32_T */
        case 600: return 8;                                      /* MPI_INT64_T */
        default: return 4;
    }
}

/* =========================================================================
 * A.3.1 Point-to-Point Communication
 * ========================================================================= */
int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Cancel(MPI_Request *request) { return MPI_SUCCESS; }
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count) { if(count && status && status!=MPI_STATUS_IGNORE) memcpy(count, &status->MPI_internal[0], sizeof(int)); return MPI_SUCCESS; }
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=0;status->MPI_TAG=tag;set_status_count(status,count);} return MPI_SUCCESS; }
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Request_free(MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { if(recvbuf!=sendbuf && sendbuf!=MPI_IN_PLACE) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=source;status->MPI_TAG=recvtag;set_status_count(status,recvcount);} return MPI_SUCCESS; }
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=source;status->MPI_TAG=recvtag;set_status_count(status,count);} return MPI_SUCCESS; }
int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Start(MPI_Request *request) { return MPI_SUCCESS; }
int MPI_Startall(int count, MPI_Request array_of_requests[]) { return MPI_SUCCESS; }
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status) { if(flag) *flag=1; if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) { if(flag) *flag=1; for(int i=0;i<count;i++) if(array_of_requests) array_of_requests[i]=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status) { if(flag) *flag=1; if(index) *index=0; if(array_of_requests && count>0) array_of_requests[0]=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Wait(MPI_Request *request, MPI_Status *status) { if(request) *request=MPI_REQUEST_NULL; if(status!=MPI_STATUS_IGNORE) set_status_count(status,0); return MPI_SUCCESS; }
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]) { for(int i=0;i<count;i++){ if(array_of_requests) array_of_requests[i]=MPI_REQUEST_NULL; if(array_of_statuses && array_of_statuses!=MPI_STATUSES_IGNORE) set_status_count(&array_of_statuses[i],0); } return MPI_SUCCESS; }
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status) { if(indx) *indx=0; if(array_of_requests && count>0) array_of_requests[0]=MPI_REQUEST_NULL; return MPI_SUCCESS; }

/* =========================================================================
 * A.3.3 Datatypes
 * ========================================================================= */
int MPI_Get_address(const void *location, MPI_Aint *address) { if(address) *address=(MPI_Aint)location; return MPI_SUCCESS; }
int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count) { return MPI_Get_count(status, datatype, count); }
int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size) { if(size) *size = incount * get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_commit(MPI_Datatype *datatype) { return MPI_SUCCESS; }
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * (array_of_blocklengths ? array_of_blocklengths[0] : 1) * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * blocklength * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_vector(count, blocklength, 0, oldtype, newtype); }
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * blocklength * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = extent; } return MPI_SUCCESS; }
int MPI_Type_create_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype) { return MPI_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype); }
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype=oldtype; return MPI_SUCCESS; }
int MPI_Type_free(MPI_Datatype *datatype) { if(datatype) *datatype=MPI_DATATYPE_NULL; return MPI_SUCCESS; }
int MPI_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]) { return MPI_SUCCESS; }
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner) { if(num_integers) *num_integers=0; if(num_addresses) *num_addresses=0; if(num_datatypes) *num_datatypes=0; if(combiner) *combiner=MPI_COMBINER_NAMED; return MPI_SUCCESS; }
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent) { if(lb) *lb=0; if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent) { return MPI_Type_get_extent(datatype, true_lb, true_extent); }
int MPI_Type_size(MPI_Datatype datatype, int *size) { if(size) *size=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = get_type_size(array_of_types[0]) * count; } return MPI_SUCCESS; } 
int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * blocklength * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm) { return MPI_SUCCESS; }

/* =========================================================================
 * A.3.4 Collective Communication
 * ========================================================================= */
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, 0, comm); }
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy((char*)recvbuf + displs[0]*get_type_size(recvtype), sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_Reduce(sendbuf, recvbuf, count, datatype, op, 0, comm); }
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Barrier(MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm) { return MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op) { if(op) *op=(MPI_Op)(intptr_t)next_op_id++; return MPI_SUCCESS; }
int MPI_Op_free(MPI_Op *op) { if(op) *op=MPI_OP_NULL; return MPI_SUCCESS; }
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op) { return MPI_SUCCESS; }
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcounts[0]*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, (char*)sendbuf + displs[0]*get_type_size(sendtype), recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }

/* =========================================================================
 * A.3.5 Groups, Contexts, Communicators, and Caching
 * ========================================================================= */
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result) { if(result) *result=(comm1==comm2)?MPI_IDENT:MPI_UNEQUAL; return MPI_SUCCESS; }
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state) { if(comm_keyval) *comm_keyval=next_keyval++; return MPI_SUCCESS; }
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval) { return MPI_SUCCESS; }
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_free(MPI_Comm *comm) { if(comm) *comm=MPI_COMM_NULL; return MPI_SUCCESS; }
int MPI_Comm_free_keyval(int *comm_keyval) { if(comm_keyval) *comm_keyval=MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen) { const char* name="MPI_STUB_COMM"; if(comm_name) strncpy(comm_name, name, MPI_MAX_OBJECT_NAME); if(resultlen) *resultlen=strlen(name); return MPI_SUCCESS; }
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group) { if(group) *group=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Comm_rank(MPI_Comm comm, int *rank) { if(rank) *rank=0; return MPI_SUCCESS; }
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Comm_size(MPI_Comm comm, int *size) { if(size) *size=1; return MPI_SUCCESS; }
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result) { if(result) *result=(group1==group2)?MPI_IDENT:MPI_UNEQUAL; return MPI_SUCCESS; }
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=MPI_GROUP_EMPTY; return MPI_SUCCESS; }
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_free(MPI_Group *group) { if(group) *group=MPI_GROUP_NULL; return MPI_SUCCESS; }
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=group1; return MPI_SUCCESS; }
int MPI_Group_rank(MPI_Group group, int *rank) { if(rank) *rank=0; return MPI_SUCCESS; }
int MPI_Group_size(MPI_Group group, int *size) { if(size) *size=1; return MPI_SUCCESS; }
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]) { if(ranks1 && ranks2){for(int i=0;i<n;i++) ranks2[i]=ranks1[i];} return MPI_SUCCESS; }
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=group1; return MPI_SUCCESS; }

/* =========================================================================
 * A.3.7 MPI Environmental Management
 * ========================================================================= */
int MPI_Abort(MPI_Comm comm, int errorcode) { exit(errorcode); return MPI_SUCCESS; }
int MPI_Add_error_class(int *errorclass) { if(errorclass) *errorclass = 100; return MPI_SUCCESS; }
int MPI_Add_error_code(int errorclass, int *errorcode) { if(errorcode) *errorcode = 1000; return MPI_SUCCESS; }
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_fn *function, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Errhandler_free(MPI_Errhandler *errhandler) { if(errhandler) *errhandler=MPI_ERRHANDLER_NULL; return MPI_SUCCESS; }
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Error_class(int errorcode, int *errorclass) { if(errorclass) *errorclass=errorcode; return MPI_SUCCESS; }
int MPI_Error_string(int errorcode, char *string, int *resultlen) { const char *msg="MPI_STUB_ERROR"; if(string) strncpy(string, msg, MPI_MAX_ERROR_STRING); if(resultlen) *resultlen=strlen(msg); return MPI_SUCCESS; }
int MPI_Get_library_version(char *version, int *resultlen) { const char *ver="MPI Stub 1.0"; if(version) strncpy(version, ver, MPI_MAX_LIBRARY_VERSION_STRING); if(resultlen) *resultlen=strlen(ver); return MPI_SUCCESS; }
int MPI_Get_processor_name(char *name, int *resultlen) { const char* host="localhost"; if(name) strncpy(name, host, MPI_MAX_PROCESSOR_NAME); if(resultlen) *resultlen=strlen(host); return MPI_SUCCESS; }
int MPI_Get_version(int *version, int *subversion) { if(version) *version=5; if(subversion) *subversion=0; return MPI_SUCCESS; }
int MPI_Init(int *argc, char ***argv) { return MPI_SUCCESS; }
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided) { if(provided) *provided=required; return MPI_SUCCESS; }
int MPI_Initialized(int *flag) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Finalize(void) { return MPI_SUCCESS; }
int MPI_Finalized(int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
double MPI_Wtime(void) { struct timeval tv; gettimeofday(&tv, NULL); return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0; }

/* =========================================================================
 * A.3.8 The Info Object
 * ========================================================================= */
int MPI_Info_create(MPI_Info *info) { if(info) *info=(MPI_Info)(intptr_t)next_info_id++; return MPI_SUCCESS; }
int MPI_Info_delete(MPI_Info info, const char *key) { return MPI_SUCCESS; }
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo) { if(newinfo) *newinfo=info; return MPI_SUCCESS; }
int MPI_Info_free(MPI_Info *info) { if(info) *info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys) { if(nkeys) *nkeys=0; return MPI_SUCCESS; }
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key) { if(key) key[0]='\0'; return MPI_SUCCESS; }
int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag) { if(valuelen) *valuelen=0; if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Info_set(MPI_Info info, const char *key, const char *value) { return MPI_SUCCESS; }

/* =========================================================================
 * A.3.10 One-Sided Communications
 * ========================================================================= */
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_complete(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win) { if(win) *win=(MPI_Win)(intptr_t)next_win_id++; return MPI_SUCCESS; }
int MPI_Win_fence(int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_free(MPI_Win *win) { if(win) *win=MPI_WIN_NULL; return MPI_SUCCESS; }
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_unlock(int rank, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_wait(MPI_Win win) { return MPI_SUCCESS; }

/* =========================================================================
 * A.3.12 I/O (Restoring POSIX Mapping for HDF5)
 * ========================================================================= */
int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh) {
    int flags = 0;
    if (amode & MPI_MODE_RDWR) flags |= O_RDWR;
    else if (amode & MPI_MODE_WRONLY) flags |= O_WRONLY;
    else flags |= O_RDONLY;
    if (amode & MPI_MODE_CREATE) flags |= O_CREAT;
    if (amode & MPI_MODE_EXCL) flags |= O_EXCL;
    if (amode & MPI_MODE_APPEND) flags |= O_APPEND;

    int fd = open(filename, flags, 0666);
    if (fd < 0) return MPI_ERR_OTHER;
    if (fh) *fh = (MPI_File)(intptr_t)fd;
    return MPI_SUCCESS;
}
int MPI_File_close(MPI_File *fh) {
    if (fh && *fh != MPI_FILE_NULL) { close((int)(intptr_t)*fh); *fh = MPI_FILE_NULL; }
    return MPI_SUCCESS;
}
int MPI_File_delete(const char *filename, MPI_Info info) { unlink(filename); return MPI_SUCCESS; }
int MPI_File_get_atomicity(MPI_File fh, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_File_get_info(MPI_File fh, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_File_get_size(MPI_File fh, MPI_Offset *size) { struct stat st; if (fstat((int)(intptr_t)fh, &st) != 0) return MPI_ERR_OTHER; if (size) *size = st.st_size; return MPI_SUCCESS; }
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = read((int)(intptr_t)fh, buf, (size_t)count * size);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = pread((int)(intptr_t)fh, buf, (size_t)count * size, offset);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read_at(fh, offset, buf, count, datatype, status); }
int MPI_File_set_atomicity(MPI_File fh, int flag) { return MPI_SUCCESS; }
int MPI_File_set_size(MPI_File fh, MPI_Offset size) { if (ftruncate((int)(intptr_t)fh, size) != 0) return MPI_ERR_OTHER; return MPI_SUCCESS; }
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info) { return MPI_SUCCESS; }
int MPI_File_sync(MPI_File fh) { fsync((int)(intptr_t)fh); return MPI_SUCCESS; }
int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = write((int)(intptr_t)fh, buf, (size_t)count * size);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = pwrite((int)(intptr_t)fh, buf, (size_t)count * size, offset);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write_at(fh, offset, buf, count, datatype, status); }

/* =========================================================================
 * A.3.13 Language Bindings (Fortran/C Interoperability)
 * ========================================================================= */
MPI_Comm MPI_Comm_f2c(MPI_Fint comm) { return (MPI_Comm)(intptr_t)comm; }
MPI_Fint MPI_Comm_c2f(MPI_Comm comm) { return (MPI_Fint)(intptr_t)comm; }
MPI_Errhandler MPI_Errhandler_f2c(MPI_Fint errhandler) { return (MPI_Errhandler)(intptr_t)errhandler; }
MPI_Fint MPI_Errhandler_c2f(MPI_Errhandler errhandler) { return (MPI_Fint)(intptr_t)errhandler; }
MPI_Group MPI_Group_f2c(MPI_Fint group) { return (MPI_Group)(intptr_t)group; }
MPI_Fint MPI_Group_c2f(MPI_Group group) { return (MPI_Fint)(intptr_t)group; }
MPI_Info MPI_Info_f2c(MPI_Fint info) { return (MPI_Info)(intptr_t)info; }
MPI_Fint MPI_Info_c2f(MPI_Info info) { return (MPI_Fint)(intptr_t)info; }
MPI_Op MPI_Op_f2c(MPI_Fint op) { return (MPI_Op)(intptr_t)op; }
MPI_Fint MPI_Op_c2f(MPI_Op op) { return (MPI_Fint)(intptr_t)op; }
MPI_Request MPI_Request_f2c(MPI_Fint request) { return (MPI_Request)(intptr_t)request; }
MPI_Fint MPI_Request_c2f(MPI_Request request) { return (MPI_Fint)(intptr_t)request; }
MPI_Datatype MPI_Type_f2c(MPI_Fint datatype) { return (MPI_Datatype)(intptr_t)datatype; }
MPI_Fint MPI_Type_c2f(MPI_Datatype datatype) { return (MPI_Fint)(intptr_t)datatype; }
MPI_Win MPI_Win_f2c(MPI_Fint win) { return (MPI_Win)(intptr_t)win; }
MPI_Fint MPI_Win_c2f(MPI_Win win) { return (MPI_Fint)(intptr_t)win; }

/* =========================================================================
 * A.3.14 Application Binary Interface (ABI)
 * ========================================================================= */
int MPI_Abi_get_version(int *abi_major, int *abi_minor) { if (abi_major) *abi_major = MPI_ABI_VERSION; if (abi_minor) *abi_minor = MPI_ABI_SUBVERSION; return MPI_SUCCESS; }
int MPI_Comm_toint(MPI_Comm comm) { return (int)(intptr_t)comm; }
MPI_Comm MPI_Comm_fromint(int comm) { return (MPI_Comm)(intptr_t)comm; }
int MPI_Type_toint(MPI_Datatype datatype) { return (int)(intptr_t)datatype; }
MPI_Datatype MPI_Type_fromint(int datatype) { return (MPI_Datatype)(intptr_t)datatype; }
int MPI_Group_toint(MPI_Group group) { return (int)(intptr_t)group; }
MPI_Group MPI_Group_fromint(int group) { return (MPI_Group)(intptr_t)group; }
int MPI_Request_toint(MPI_Request request) { return (int)(intptr_t)request; }
MPI_Request MPI_Request_fromint(int request) { return (MPI_Request)(intptr_t)request; }
int MPI_File_toint(MPI_File file) { return (int)(intptr_t)file; }
MPI_File MPI_File_fromint(int file) { return (MPI_File)(intptr_t)file; }
int MPI_Win_toint(MPI_Win win) { return (int)(intptr_t)win; }
MPI_Win MPI_Win_fromint(int win) { return (MPI_Win)(intptr_t)win; }
int MPI_Op_toint(MPI_Op op) { return (int)(intptr_t)op; }
MPI_Op MPI_Op_fromint(int op) { return (MPI_Op)(intptr_t)op; }
int MPI_Info_toint(MPI_Info info) { return (int)(intptr_t)info; }
MPI_Info MPI_Info_fromint(int info) { return (MPI_Info)(intptr_t)info; }
int MPI_Errhandler_toint(MPI_Errhandler errhandler) { return (int)(intptr_t)errhandler; }
MPI_Errhandler MPI_Errhandler_fromint(int errhandler) { return (MPI_Errhandler)(intptr_t)errhandler; }

/* =========================================================================
 * A.3.17 Deprecated C Bindings (Extensively requested by HDF5 & PETSc)
 * ========================================================================= */
int MPI_Attr_delete(MPI_Comm comm, int keyval) { return MPI_SUCCESS; }
int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count) { int c; MPI_Get_count(status, datatype, &c); if(count) *count = c; return MPI_SUCCESS; }
int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state) { if(keyval) *keyval=1; return MPI_SUCCESS; }
int MPI_Keyval_free(int *keyval) { if(keyval) *keyval=0; return MPI_SUCCESS; }
int MPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count) { return MPI_SUCCESS; }
int MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent) { if(lb) *lb = 0; if(extent) *extent = get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent) { return MPI_Type_get_extent_x(datatype, true_lb, true_extent); }
int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size) { if(size) *size = get_type_size(datatype); return MPI_SUCCESS; }

/* =========================================================================
 * A.5 Fortran Bindings (Name Mangling: Lowercase + Trailing Underscore)
 * ========================================================================= */
#define F_FUNC(name) mpi_##name##_

void F_FUNC(init)(MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(finalize)(MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(initialized)(MPI_Fint *flag, MPI_Fint *ierr) { *flag = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(finalized)(MPI_Fint *flag, MPI_Fint *ierr) { *flag = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(abort)(MPI_Fint *comm, MPI_Fint *errorcode, MPI_Fint *ierr) { exit(*errorcode); }

void F_FUNC(comm_size)(MPI_Fint *comm, MPI_Fint *size, MPI_Fint *ierr) { *size = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(comm_rank)(MPI_Fint *comm, MPI_Fint *rank, MPI_Fint *ierr) { *rank = 0; *ierr = MPI_SUCCESS; }

void F_FUNC(barrier)(MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(bcast)(void *buffer, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }

void F_FUNC(allreduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *ierr) {
    *ierr = MPI_Allreduce(sendbuf, recvbuf, *count, MPI_Type_f2c(*datatype), MPI_Op_f2c(*op), MPI_Comm_f2c(*comm));
}

void F_FUNC(reduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) {
    *ierr = MPI_Reduce(sendbuf, recvbuf, *count, MPI_Type_f2c(*datatype), MPI_Op_f2c(*op), *root, MPI_Comm_f2c(*comm));
}

void F_FUNC(gather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) {
    *ierr = MPI_Gather(sendbuf, *sendcount, MPI_Type_f2c(*sendtype), recvbuf, *recvcount, MPI_Type_f2c(*recvtype), *root, MPI_Comm_f2c(*comm));
}

void F_FUNC(scatter)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) {
    *ierr = MPI_Scatter(sendbuf, *sendcount, MPI_Type_f2c(*sendtype), recvbuf, *recvcount, MPI_Type_f2c(*recvtype), *root, MPI_Comm_f2c(*comm));
}

void F_FUNC(allgather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *ierr) {
    *ierr = MPI_Allgather(sendbuf, *sendcount, MPI_Type_f2c(*sendtype), recvbuf, *recvcount, MPI_Type_f2c(*recvtype), MPI_Comm_f2c(*comm));
}