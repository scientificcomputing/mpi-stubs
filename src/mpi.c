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
int MPI_Bsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Bsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Buffer_attach_c(void *buffer, MPI_Count size) { return MPI_SUCCESS; }
int MPI_Buffer_attach(void *buffer, int size) { return MPI_SUCCESS; }
int MPI_Buffer_detach_c(void *buffer_addr, MPI_Count *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Buffer_detach(void *buffer_addr, int *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Buffer_flush(void) { return MPI_SUCCESS; }
int MPI_Buffer_iflush(MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Cancel(MPI_Request *request) { return MPI_SUCCESS; }
int MPI_Comm_attach_buffer_c(MPI_Comm comm, void *buffer, MPI_Count size) { return MPI_SUCCESS; }
int MPI_Comm_attach_buffer(MPI_Comm comm, void *buffer, int size) { return MPI_SUCCESS; }
int MPI_Comm_detach_buffer_c(MPI_Comm comm, void *buffer_addr, MPI_Count *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Comm_detach_buffer(MPI_Comm comm, void *buffer_addr, int *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Comm_flush_buffer(MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Comm_iflush_buffer(MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Get_count_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count) { int c; MPI_Get_count(status, datatype, &c); if(count) *count=c; return MPI_SUCCESS; }
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count) { if(count && status && status!=MPI_STATUS_IGNORE) memcpy(count, &status->MPI_internal[0], sizeof(int)); return MPI_SUCCESS; }
int MPI_Ibsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Imrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Imrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Irecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Irsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request) { if(recvbuf!=sendbuf && sendbuf!=MPI_IN_PLACE) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, 
                         int dest, int sendtag, int source, int recvtag, 
                         MPI_Comm comm, MPI_Status *status) {
    /* In a serial stub, the buffer is already in place. Nothing to do. */
    if(status) {
        status->MPI_SOURCE = source;
        status->MPI_TAG = recvtag;
        status->MPI_ERROR = MPI_SUCCESS;
    }
    return MPI_SUCCESS;
}
int MPI_Isendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request) { if(recvbuf!=sendbuf && sendbuf!=MPI_IN_PLACE) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Issend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status) { if(message) *message=MPI_MESSAGE_NULL; return MPI_SUCCESS; }
int MPI_Mrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_Mrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_Recv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=0;status->MPI_TAG=tag;set_status_count(status,count);} return MPI_SUCCESS; }
int MPI_Recv_init_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=0;status->MPI_TAG=tag;set_status_count(status,count);} return MPI_SUCCESS; }
int MPI_Request_free(MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Request_get_status_all(int count, const MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Request_get_status_any(int count, const MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status) { if(flag) *flag=1; if(index) *index=0; return MPI_SUCCESS; }
int MPI_Request_get_status_some(int incount, const MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]) { if(outcount) *outcount=0; return MPI_SUCCESS; }
int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Rsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Rsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Send_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Send_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Sendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { if(recvbuf!=sendbuf && sendbuf!=MPI_IN_PLACE) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=source;status->MPI_TAG=recvtag;set_status_count(status,recvcount);} return MPI_SUCCESS; }
int MPI_Sendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=source;status->MPI_TAG=recvtag;set_status_count(status,count);} return MPI_SUCCESS; }
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { if(recvbuf!=sendbuf && sendbuf!=MPI_IN_PLACE) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); if(status!=MPI_STATUS_IGNORE){status->MPI_SOURCE=source;status->MPI_TAG=recvtag;set_status_count(status,recvcount);} return MPI_SUCCESS; }
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Session_attach_buffer_c(MPI_Session session, void *buffer, MPI_Count size) { return MPI_SUCCESS; }
int MPI_Session_attach_buffer(MPI_Session session, void *buffer, int size) { return MPI_SUCCESS; }
int MPI_Session_detach_buffer_c(MPI_Session session, void *buffer_addr, MPI_Count *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Session_detach_buffer(MPI_Session session, void *buffer_addr, int *size) { if(size) *size=0; return MPI_SUCCESS; }
int MPI_Session_flush_buffer(MPI_Session session) { return MPI_SUCCESS; }
int MPI_Session_iflush_buffer(MPI_Session session, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ssend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Ssend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Startall(int count, MPI_Request array_of_requests[]) { return MPI_SUCCESS; }
int MPI_Start(MPI_Request *request) { return MPI_SUCCESS; }
int MPI_Status_get_error(const MPI_Status *status, int *err) { if(err) *err=MPI_SUCCESS; return MPI_SUCCESS; }
int MPI_Status_get_source(const MPI_Status *status, int *source) { if(source) *source=0; return MPI_SUCCESS; }
int MPI_Status_get_tag(const MPI_Status *status, int *tag) { if(tag) *tag=0; return MPI_SUCCESS; }

int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) { if(flag) *flag=1; for(int i=0;i<count;i++) if(array_of_requests) array_of_requests[i]=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status) { if(flag) *flag=1; if(index) *index=0; if(array_of_requests && count>0) array_of_requests[0]=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]) { if(outcount) *outcount=0; return MPI_SUCCESS; }
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status) { if(flag) *flag=1; if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]) { for(int i=0;i<count;i++){ if(array_of_requests) array_of_requests[i]=MPI_REQUEST_NULL; if(array_of_statuses && array_of_statuses!=MPI_STATUSES_IGNORE) set_status_count(&array_of_statuses[i],0); } return MPI_SUCCESS; }
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status) { if(index) *index=0; if(array_of_requests && count>0) array_of_requests[0]=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]) { if(outcount) *outcount=0; return MPI_SUCCESS; }
int MPI_Wait(MPI_Request *request, MPI_Status *status) { if(request) *request=MPI_REQUEST_NULL; if(status!=MPI_STATUS_IGNORE) set_status_count(status,0); return MPI_SUCCESS; }

/* --- A.3.2 Partitioned Communication --- */
int MPI_Parrived(MPI_Request request, int partition, int *flag) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Pready_list(int length, const int array_of_partitions[], MPI_Request request) { return MPI_SUCCESS; }
int MPI_Pready_range(int partition_low, int partition_high, MPI_Request request) { return MPI_SUCCESS; }
int MPI_Pready(int partition, MPI_Request request) { return MPI_SUCCESS; }
int MPI_Precv_init(void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Psend_init(const void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }

/* --- A.3.3 Datatypes --- */
int MPI_Get_address(const void *location, MPI_Aint *address) { if(address) *address=(MPI_Aint)location; return MPI_SUCCESS; }
int MPI_Get_elements_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count) { int c; MPI_Get_count(status, datatype, &c); if(count) *count=c; return MPI_SUCCESS; }
int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count) { return MPI_Get_count(status, datatype, count); }
int MPI_Pack_c(const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Pack_external_c(const char datarep[], const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position) { return MPI_SUCCESS; }
int MPI_Pack_external_size_c(const char datarep[], MPI_Count incount, MPI_Datatype datatype, MPI_Count *size) { if(size) *size = incount * get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size) { if(size) *size = incount * get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position) { return MPI_SUCCESS; }
int MPI_Pack_size_c(MPI_Count incount, MPI_Datatype datatype, MPI_Comm comm, MPI_Count *size) { if(size) *size = incount * get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size) { if(size) *size = incount * get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Type_commit(MPI_Datatype *datatype) { return MPI_SUCCESS; }
int MPI_Type_contiguous_c(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_contiguous_c(count, oldtype, newtype); }
int MPI_Type_create_darray_c(int size, int rank, int ndims, const MPI_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype = oldtype; return MPI_SUCCESS; }
int MPI_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype = oldtype; return MPI_SUCCESS; }
int MPI_Type_create_hindexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * blocklength * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_block_c(count, blocklength, NULL, oldtype, newtype); }
int MPI_Type_create_hindexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * (array_of_blocklengths ? array_of_blocklengths[0] : 1) * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_c(count, NULL, NULL, oldtype, newtype); }
int MPI_Type_create_hvector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = count * blocklength * get_type_size(oldtype); } return MPI_SUCCESS; }
int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hvector_c(count, blocklength, 0, oldtype, newtype); }
int MPI_Type_create_indexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype); }
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_block_c(count, blocklength, NULL, oldtype, newtype); }
int MPI_Type_create_resized_c(MPI_Datatype oldtype, MPI_Count lb, MPI_Count extent, MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = extent; } return MPI_SUCCESS; }
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype) { return MPI_Type_create_resized_c(oldtype, lb, extent, newtype); }
int MPI_Type_create_struct_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype) { if(newtype) { *newtype = (MPI_Datatype)(intptr_t)next_type_id++; custom_type_sizes[(int)(intptr_t)*newtype - 2000] = get_type_size(array_of_types[0]) * count; } return MPI_SUCCESS; }
int MPI_Type_create_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype) { return MPI_Type_create_struct_c(count, NULL, NULL, array_of_types, newtype); }
int MPI_Type_create_subarray_c(int ndims, const MPI_Count array_of_sizes[], const MPI_Count array_of_subsizes[], const MPI_Count array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype = oldtype; return MPI_SUCCESS; }
int MPI_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype = oldtype; return MPI_SUCCESS; }
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype) { if(newtype) *newtype=oldtype; return MPI_SUCCESS; }
int MPI_Type_free(MPI_Datatype *datatype) { if(datatype) *datatype=MPI_DATATYPE_NULL; return MPI_SUCCESS; }
int MPI_Type_get_contents_c(MPI_Datatype datatype, MPI_Count max_integers, MPI_Count max_addresses, MPI_Count max_large_counts, MPI_Count max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[]) { return MPI_SUCCESS; }
int MPI_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]) { return MPI_SUCCESS; }
int MPI_Type_get_envelope_c(MPI_Datatype datatype, MPI_Count *num_integers, MPI_Count *num_addresses, MPI_Count *num_large_counts, MPI_Count *num_datatypes, int *combiner) { if(num_integers) *num_integers=0; if(num_addresses) *num_addresses=0; if(num_large_counts) *num_large_counts=0; if(num_datatypes) *num_datatypes=0; if(combiner) *combiner=MPI_COMBINER_NAMED; return MPI_SUCCESS; }
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner) { if(num_integers) *num_integers=0; if(num_addresses) *num_addresses=0; if(num_datatypes) *num_datatypes=0; if(combiner) *combiner=MPI_COMBINER_NAMED; return MPI_SUCCESS; }
int MPI_Type_get_extent_c(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent) { if(lb) *lb=0; if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent) { if(lb) *lb=0; if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_get_true_extent_c(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent) { return MPI_Type_get_extent_c(datatype, true_lb, true_extent); }
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent) { return MPI_Type_get_extent(datatype, true_lb, true_extent); }
int MPI_Type_indexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype); }
int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hindexed_c(count, NULL, NULL, oldtype, newtype); }
int MPI_Type_size_c(MPI_Datatype datatype, MPI_Count *size) { if(size) *size=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_size(MPI_Datatype datatype, int *size) { if(size) *size=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_vector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hvector_c(count, blocklength, stride, oldtype, newtype); }
int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { return MPI_Type_create_hvector_c(count, blocklength, stride, oldtype, newtype); }
int MPI_Unpack_c(const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Unpack_external_c(const char datarep[], const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm) { return MPI_SUCCESS; }

/* --- A.3.4 Collective Communication --- */
int MPI_Allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_Gather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, 0, comm); }
int MPI_Allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy((char*)recvbuf + displs[0]*get_type_size(recvtype), sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy((char*)recvbuf + displs[0]*get_type_size(recvtype), sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, 0, comm); }
int MPI_Allreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_Reduce_c(sendbuf, recvbuf, count, datatype, op, 0, comm); }
int MPI_Allreduce_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_Reduce(sendbuf, recvbuf, count, datatype, op, 0, comm); }
int MPI_Alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Barrier_init(MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Barrier(MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Bcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Bcast_init_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Bcast_init(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Exscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Exscan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Exscan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Gather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Gather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Gather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Gatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm) { return MPI_Allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Gatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Gatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm) { return MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, sendcount*get_type_size(sendtype)); return MPI_SUCCESS; }
int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ibcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request) { 
    if(request) *request = MPI_REQUEST_NULL; 
    return MPI_SUCCESS; 
}
int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request) { 
    if(request) *request = MPI_REQUEST_NULL; 
    return MPI_SUCCESS; 
}
/* --- Missing Non-Blocking Collectives (MPI-3) --- */
int MPI_Iallgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm); }
int MPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm); }
int MPI_Iallgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm); }
int MPI_Iallreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allreduce_c(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Ialltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm); }
int MPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm); }
int MPI_Ialltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm); }
int MPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm); }
int MPI_Ialltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm); }
int MPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm); }
int MPI_Iexscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Exscan_c(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Exscan(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Igather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Gather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Igatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Gatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm); }
int MPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm); }
int MPI_Ireduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Reduce_c(sendbuf, recvbuf, count, datatype, op, root, comm); }
int MPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm); }
int MPI_Iscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scan_c(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scan(sendbuf, recvbuf, count, datatype, op, comm); }
int MPI_Iscatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Iscatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_Scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm); }
int MPI_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op) { if(op) *op=(MPI_Op)(intptr_t)next_op_id++; return MPI_SUCCESS; }
int MPI_Op_free(MPI_Op *op) { if(op) *op=MPI_OP_NULL; return MPI_SUCCESS; }
int MPI_Reduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce_local_c(const void *inbuf, void *inoutbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op) { return MPI_SUCCESS; }
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op) { return MPI_SUCCESS; }
int MPI_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcounts[0]*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcounts[0]*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Scan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Scan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, count*get_type_size(datatype)); return MPI_SUCCESS; }
int MPI_Scatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Scatter_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scatter_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, (char*)sendbuf + displs[0]*get_type_size(sendtype), recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Scatterv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, (char*)sendbuf + displs[0]*get_type_size(sendtype), recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { if(sendbuf!=MPI_IN_PLACE && sendbuf!=recvbuf) memcpy(recvbuf, sendbuf, recvcount*get_type_size(recvtype)); return MPI_SUCCESS; }
int MPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) {
    if(request) *request = MPI_REQUEST_NULL;
    return MPI_SUCCESS;
}

int MPI_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) {
    if(request) *request = MPI_REQUEST_NULL;
    return MPI_SUCCESS;
}

/* --- A.3.5 Groups, Contexts, Communicators, and Caching --- */
#define MAX_COMM_ATTRS 2048
static struct {
    int comm;
    int keyval;
    void *attr_val;
} comm_attrs[MAX_COMM_ATTRS];
static int num_comm_attrs = 0;

int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val) { 
    int c = (int)(intptr_t)comm;
    int free_slot = -1;
    for (int i=0; i<num_comm_attrs; i++) {
        if (comm_attrs[i].comm == c && comm_attrs[i].keyval == comm_keyval) {
            comm_attrs[i].attr_val = attribute_val;
            return MPI_SUCCESS;
        }
        if (comm_attrs[i].comm == 0 && free_slot == -1) free_slot = i;
    }
    if (free_slot != -1) {
        comm_attrs[free_slot].comm = c;
        comm_attrs[free_slot].keyval = comm_keyval;
        comm_attrs[free_slot].attr_val = attribute_val;
    } else if (num_comm_attrs < MAX_COMM_ATTRS) {
        comm_attrs[num_comm_attrs].comm = c;
        comm_attrs[num_comm_attrs].keyval = comm_keyval;
        comm_attrs[num_comm_attrs].attr_val = attribute_val;
        num_comm_attrs++;
    }
    return MPI_SUCCESS; 
}

int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag) {
    static int tag_ub = 32767;
    static int host = MPI_PROC_NULL;
    static int io = MPI_ANY_SOURCE;
    static int wtime_is_global = 1;

    if (comm_keyval == MPI_TAG_UB) { *(void**)attribute_val = &tag_ub; *flag = 1; return MPI_SUCCESS; }
    if (comm_keyval == MPI_HOST) { *(void**)attribute_val = &host; *flag = 1; return MPI_SUCCESS; }
    if (comm_keyval == MPI_IO) { *(void**)attribute_val = &io; *flag = 1; return MPI_SUCCESS; }
    if (comm_keyval == MPI_WTIME_IS_GLOBAL) { *(void**)attribute_val = &wtime_is_global; *flag = 1; return MPI_SUCCESS; }

    int c = (int)(intptr_t)comm;
    for (int i=0; i<num_comm_attrs; i++) {
        if (comm_attrs[i].comm == c && comm_attrs[i].keyval == comm_keyval) {
            *(void**)attribute_val = comm_attrs[i].attr_val;
            *flag = 1;
            return MPI_SUCCESS;
        }
    }
    *flag = 0;
    return MPI_SUCCESS;
}

int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval) { 
    int c = (int)(intptr_t)comm;
    for (int i=0; i<num_comm_attrs; i++) {
        if (comm_attrs[i].comm == c && comm_attrs[i].keyval == comm_keyval) {
            comm_attrs[i].comm = 0; /* Mark slot as free */
            return MPI_SUCCESS;
        }
    }
    return MPI_SUCCESS; 
}

int MPI_Comm_free(MPI_Comm *comm) { 
    if(comm && *comm != MPI_COMM_NULL) {
        int c = (int)(intptr_t)*comm;
        for (int i=0; i<num_comm_attrs; i++) {
            if (comm_attrs[i].comm == c) {
                comm_attrs[i].comm = 0; /* Clear all attrs for this comm */
            }
        }
        *comm = MPI_COMM_NULL;
    }
    return MPI_SUCCESS; 
}
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result) { if(result) *result=(comm1==comm2)?MPI_IDENT:MPI_UNEQUAL; return MPI_SUCCESS; }
int MPI_Comm_create_from_group(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state) { if(comm_keyval) *comm_keyval=next_keyval++; return MPI_SUCCESS; }
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
// int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval) { return MPI_SUCCESS; }
int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_free_keyval(int *comm_keyval) { if(comm_keyval) *comm_keyval=MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
// int MPI_Comm_free(MPI_Comm *comm) { if(comm) *comm=MPI_COMM_NULL; return MPI_SUCCESS; }
// int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag) {
//     /* The MPI Standard requires these attributes to exist. */
//     static int tag_ub = 32767;      /* Minimum required max tag */
//     static int host = MPI_PROC_NULL;
//     static int io = MPI_ANY_SOURCE;
//     static int wtime_is_global = 1;

//     if (comm_keyval == MPI_TAG_UB) {
//         *(int**)attribute_val = &tag_ub;
//         *flag = 1;
//     } else if (comm_keyval == MPI_HOST) {
//         *(int**)attribute_val = &host;
//         *flag = 1;
//     } else if (comm_keyval == MPI_IO) {
//         *(int**)attribute_val = &io;
//         *flag = 1;
//     } else if (comm_keyval == MPI_WTIME_IS_GLOBAL) {
//         *(int**)attribute_val = &wtime_is_global;
//         *flag = 1;
//     } else {
//         *flag = 0;
//     }
//     return MPI_SUCCESS;
// }
int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen) { const char* name="MPI_STUB_COMM"; if(comm_name) strncpy(comm_name, name, MPI_MAX_OBJECT_NAME); if(resultlen) *resultlen=strlen(name); return MPI_SUCCESS; }
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group) { if(group) *group=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Comm_idup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Comm_rank(MPI_Comm comm, int *rank) { if(rank) *rank=0; return MPI_SUCCESS; }
int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group) { if(group) *group=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Comm_remote_size(MPI_Comm comm, int *size) { if(size) *size=1; return MPI_SUCCESS; }
// int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info) { return MPI_SUCCESS; }
int MPI_Comm_set_name(MPI_Comm comm, const char *comm_name) { return MPI_SUCCESS; }
int MPI_Comm_size(MPI_Comm comm, int *size) { if(size) *size=1; return MPI_SUCCESS; }
int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_test_inter(MPI_Comm comm, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result) { if(result) *result=(group1==group2)?MPI_IDENT:MPI_UNEQUAL; return MPI_SUCCESS; }
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=MPI_GROUP_EMPTY; return MPI_SUCCESS; }
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_free(MPI_Group *group) { if(group) *group=MPI_GROUP_NULL; return MPI_SUCCESS; }
int MPI_Group_from_session_pset(MPI_Session session, const char *pset_name, MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=group1; return MPI_SUCCESS; }
int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup) { if(newgroup) *newgroup=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Group_rank(MPI_Group group, int *rank) { if(rank) *rank=0; return MPI_SUCCESS; }
int MPI_Group_size(MPI_Group group, int *size) { if(size) *size=1; return MPI_SUCCESS; }
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]) { if(ranks1 && ranks2){for(int i=0;i<n;i++) ranks2[i]=ranks1[i];} return MPI_SUCCESS; }
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { if(newgroup) *newgroup=group1; return MPI_SUCCESS; }
int MPI_Intercomm_create_from_groups(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm) { if(newintercomm) *newintercomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm) { if(newintercomm) *newintercomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm) { if(newintracomm) *newintracomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state) { if(type_keyval) *type_keyval=next_keyval++; return MPI_SUCCESS; }
int MPI_Type_delete_attr(MPI_Datatype datatype, int type_keyval) { return MPI_SUCCESS; }
int MPI_Type_free_keyval(int *type_keyval) { if(type_keyval) *type_keyval=MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
int MPI_Type_get_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Type_get_name(MPI_Datatype datatype, char *type_name, int *resultlen) { const char* name="MPI_STUB_TYPE"; if(type_name) strncpy(type_name, name, MPI_MAX_OBJECT_NAME); if(resultlen) *resultlen=strlen(name); return MPI_SUCCESS; }
int MPI_Type_set_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Type_set_name(MPI_Datatype datatype, const char *type_name) { return MPI_SUCCESS; }
int MPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state) { if(win_keyval) *win_keyval=next_keyval++; return MPI_SUCCESS; }
int MPI_Win_delete_attr(MPI_Win win, int win_keyval) { return MPI_SUCCESS; }
int MPI_Win_free_keyval(int *win_keyval) { if(win_keyval) *win_keyval=MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
int MPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen) { const char* name="MPI_STUB_WIN"; if(win_name) strncpy(win_name, name, MPI_MAX_OBJECT_NAME); if(resultlen) *resultlen=strlen(name); return MPI_SUCCESS; }
int MPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Win_set_name(MPI_Win win, const char *win_name) { return MPI_SUCCESS; }

/* --- A.3.6 Virtual Topologies --- */
int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[]) { return MPI_SUCCESS; }
int MPI_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart) { if(comm_cart) *comm_cart=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[]) { return MPI_SUCCESS; }
int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank) { if(newrank) *newrank=0; return MPI_SUCCESS; }
int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank) { if(rank) *rank=0; return MPI_SUCCESS; }
int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest) { if(rank_source) *rank_source=0; if(rank_dest) *rank_dest=0; return MPI_SUCCESS; }
int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Cartdim_get(MPI_Comm comm, int *ndims) { if(ndims) *ndims=0; return MPI_SUCCESS; }
int MPI_Dims_create(int nnodes, int ndims, int dims[]) { return MPI_SUCCESS; }
int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph) { if(comm_dist_graph) *comm_dist_graph=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph) { if(comm_dist_graph) *comm_dist_graph=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int *indegree, int *outdegree, int *weighted) { if(indegree) *indegree=0; if(outdegree) *outdegree=0; if(weighted) *weighted=0; return MPI_SUCCESS; }
int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[]) { return MPI_SUCCESS; }
int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph) { if(comm_graph) *comm_graph=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[]) { return MPI_SUCCESS; }
int MPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank) { if(newrank) *newrank=0; return MPI_SUCCESS; }
int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors) { if(nneighbors) *nneighbors=0; return MPI_SUCCESS; }
int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[]) { return MPI_SUCCESS; }
int MPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges) { if(nnodes) *nnodes=0; if(nedges) *nedges=0; return MPI_SUCCESS; }
int MPI_Ineighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { return MPI_SUCCESS; }
int MPI_Topo_test(MPI_Comm comm, int *status) { if(status) *status=MPI_UNDEFINED; return MPI_SUCCESS; }

/* --- A.3.7 MPI Environmental Management --- */
int MPI_Abort(MPI_Comm comm, int errorcode) { exit(errorcode); return MPI_SUCCESS; }
int MPI_Add_error_class(int *errorclass) { if(errorclass) *errorclass=100; return MPI_SUCCESS; }
int MPI_Add_error_code(int errorclass, int *errorcode) { if(errorcode) *errorcode=1000; return MPI_SUCCESS; }
int MPI_Add_error_string(int errorcode, const char *string) { return MPI_SUCCESS; }
int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr) { if(baseptr) *(void**)baseptr = malloc(size); return MPI_SUCCESS; }
int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode) { return MPI_SUCCESS; }
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=MPI_ERRHANDLER_NULL; return MPI_SUCCESS; }
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Errhandler_free(MPI_Errhandler *errhandler) { if(errhandler) *errhandler=MPI_ERRHANDLER_NULL; return MPI_SUCCESS; }
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Error_class(int errorcode, int *errorclass) { if(errorclass) *errorclass=errorcode; return MPI_SUCCESS; }
int MPI_Error_string(int errorcode, char *string, int *resultlen) { const char *msg="MPI_STUB_ERROR"; if(string) strncpy(string, msg, MPI_MAX_ERROR_STRING); if(resultlen) *resultlen=strlen(msg); return MPI_SUCCESS; }
int MPI_Free_mem(void *base) { free(base); return MPI_SUCCESS; }
int MPI_Get_hw_resource_info(MPI_Info *hw_info) { if(hw_info) *hw_info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Get_library_version(char *version, int *resultlen) { const char *ver="MPI Stub 1.0"; if(version) strncpy(version, ver, MPI_MAX_LIBRARY_VERSION_STRING); if(resultlen) *resultlen=strlen(ver); return MPI_SUCCESS; }
int MPI_Get_processor_name(char *name, int *resultlen) { const char* host="localhost"; if(name) strncpy(name, host, MPI_MAX_PROCESSOR_NAME); if(resultlen) *resultlen=strlen(host); return MPI_SUCCESS; }
int MPI_Get_version(int *version, int *subversion) { if(version) *version=5; if(subversion) *subversion=0; return MPI_SUCCESS; }
int MPI_Init(int *argc, char ***argv) { return MPI_SUCCESS; }
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided) { if(provided) *provided=required; return MPI_SUCCESS; }
int MPI_Initialized(int *flag) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Is_thread_main(int *flag) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Query_thread(int *provided) { if(provided) *provided=MPI_THREAD_SINGLE; return MPI_SUCCESS; }
int MPI_Remove_error_class(int errorclass) { return MPI_SUCCESS; }
int MPI_Remove_error_code(int errorcode) { return MPI_SUCCESS; }
int MPI_Remove_error_string(int errorcode) { return MPI_SUCCESS; }
int MPI_Session_call_errhandler(MPI_Session session, int errorcode) { return MPI_SUCCESS; }
int MPI_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Session_get_errhandler(MPI_Session session, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=MPI_ERRHANDLER_NULL; return MPI_SUCCESS; }
int MPI_Session_set_errhandler(MPI_Session session, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Win_call_errhandler(MPI_Win win, int errorcode) { return MPI_SUCCESS; }
int MPI_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=(MPI_Errhandler)(intptr_t)next_errhandler++; return MPI_SUCCESS; }
int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler) { if(errhandler) *errhandler=MPI_ERRHANDLER_NULL; return MPI_SUCCESS; }
int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler) { return MPI_SUCCESS; }
int MPI_Finalize(void) { return MPI_SUCCESS; }
int MPI_Finalized(int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
double MPI_Wtime(void) { struct timeval tv; gettimeofday(&tv, NULL); return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0; }
double MPI_Wtick(void) { return 0.000001; }

/* --- A.3.8 The Info Object --- */
int MPI_Info_create(MPI_Info *info) { if(info) *info=(MPI_Info)(intptr_t)next_info_id++; return MPI_SUCCESS; }
int MPI_Info_create_env(int argc, char *argv[], MPI_Info *info) { if(info) *info=(MPI_Info)(intptr_t)next_info_id++; return MPI_SUCCESS; }
int MPI_Info_delete(MPI_Info info, const char *key) { return MPI_SUCCESS; }
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo) { if(newinfo) *newinfo=info; return MPI_SUCCESS; }
int MPI_Info_free(MPI_Info *info) { if(info) *info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys) { if(nkeys) *nkeys=0; return MPI_SUCCESS; }
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key) { if(key) key[0]='\0'; return MPI_SUCCESS; }
int MPI_Info_get_string(MPI_Info info, const char *key, int *buflen, char *value, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag) { if(valuelen) *valuelen=0; if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_Info_set(MPI_Info info, const char *key, const char *value) { return MPI_SUCCESS; }

/* --- A.3.9 Process Creation and Management --- */
int MPI_Close_port(const char *port_name) { return MPI_SUCCESS; }
int MPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm) { if(newcomm) *newcomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_disconnect(MPI_Comm *comm) { if(comm) *comm=MPI_COMM_NULL; return MPI_SUCCESS; }
int MPI_Comm_get_parent(MPI_Comm *parent) { if(parent) *parent=MPI_COMM_NULL; return MPI_SUCCESS; }
int MPI_Comm_join(int fd, MPI_Comm *intercomm) { if(intercomm) *intercomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]) { if(intercomm) *intercomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MPI_Info array_of_info[], int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]) { if(intercomm) *intercomm=(MPI_Comm)(intptr_t)next_comm_id++; return MPI_SUCCESS; }
int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name) { return MPI_SUCCESS; }
int MPI_Open_port(MPI_Info info, char *port_name) { return MPI_SUCCESS; }
int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name) { return MPI_SUCCESS; }
int MPI_Session_finalize(MPI_Session *session) { if(session) *session=MPI_SESSION_NULL; return MPI_SUCCESS; }
int MPI_Session_get_info(MPI_Session session, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Session_get_nth_pset(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name) { if(pset_len) *pset_len=0; return MPI_SUCCESS; }
int MPI_Session_get_num_psets(MPI_Session session, MPI_Info info, int *npset_names) { if(npset_names) *npset_names=0; return MPI_SUCCESS; }
int MPI_Session_get_pset_info(MPI_Session session, const char *pset_name, MPI_Info *info) { if(info) *info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Session_init(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session) { if(session) *session=(MPI_Session)(intptr_t)1; return MPI_SUCCESS; }
int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name) { return MPI_SUCCESS; }

/* --- A.3.10 One-Sided Communications --- */
int MPI_Accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Put_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Raccumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rget_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rget_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rput_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Win_allocate_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { if(baseptr) *(void**)baseptr = malloc(size); if(win) *win=(MPI_Win)(intptr_t)next_win_id++; return MPI_SUCCESS; }
int MPI_Win_allocate_shared_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { return MPI_Win_allocate_c(size, disp_unit, info, comm, baseptr, win); }
int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { return MPI_Win_allocate_c(size, disp_unit, info, comm, baseptr, win); }
int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { return MPI_Win_allocate_c(size, disp_unit, info, comm, baseptr, win); }
int MPI_Win_attach(MPI_Win win, void *base, MPI_Aint size) { return MPI_SUCCESS; }
int MPI_Win_complete(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_create_c(void *base, MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win) { if(win) *win=(MPI_Win)(intptr_t)next_win_id++; return MPI_SUCCESS; }
int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win) { if(win) *win=(MPI_Win)(intptr_t)next_win_id++; return MPI_SUCCESS; }
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win) { if(win) *win=(MPI_Win)(intptr_t)next_win_id++; return MPI_SUCCESS; }
int MPI_Win_detach(MPI_Win win, const void *base) { return MPI_SUCCESS; }
int MPI_Win_fence(int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_flush_all(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_flush_local_all(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_flush_local(int rank, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_flush(int rank, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_free(MPI_Win *win) { if(win) *win=MPI_WIN_NULL; return MPI_SUCCESS; }
int MPI_Win_get_group(MPI_Win win, MPI_Group *group) { if(group) *group=(MPI_Group)(intptr_t)next_group_id++; return MPI_SUCCESS; }
int MPI_Win_get_info(MPI_Win win, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Win_lock_all(int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_set_info(MPI_Win win, MPI_Info info) { return MPI_SUCCESS; }
int MPI_Win_shared_query_c(MPI_Win win, int rank, MPI_Aint *size, MPI_Aint *disp_unit, void *baseptr) { if(size) *size=0; if(disp_unit) *disp_unit=1; if(baseptr) *(void**)baseptr=NULL; return MPI_SUCCESS; }
int MPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr) { if(size) *size=0; if(disp_unit) *disp_unit=1; if(baseptr) *(void**)baseptr=NULL; return MPI_SUCCESS; }
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_sync(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_test(MPI_Win win, int *flag) { if(flag) *flag=1; return MPI_SUCCESS; }
int MPI_Win_unlock_all(MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_unlock(int rank, MPI_Win win) { return MPI_SUCCESS; }
int MPI_Win_wait(MPI_Win win) { return MPI_SUCCESS; }

/* --- A.3.11 External Interfaces --- */
int MPI_Grequest_complete(MPI_Request request) { return MPI_SUCCESS; }
int MPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_SUCCESS; }
int MPI_Status_set_cancelled(MPI_Status *status, int flag) { if(status) status->MPI_internal[1]=flag; return MPI_SUCCESS; }
int MPI_Test_cancelled(const MPI_Status *status, int *flag) { if(flag) *flag = status ? status->MPI_internal[1] : 0; return MPI_SUCCESS; }
int MPI_Status_set_elements_c(MPI_Status *status, MPI_Datatype datatype, MPI_Count count) { set_status_count(status, count); return MPI_SUCCESS; }
int MPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count) { set_status_count(status, count); return MPI_SUCCESS; }
int MPI_Status_set_error(MPI_Status *status, int err) { if(status) status->MPI_ERROR=err; return MPI_SUCCESS; }
int MPI_Status_set_source(MPI_Status *status, int source) { if(status) status->MPI_SOURCE=source; return MPI_SUCCESS; }
int MPI_Status_set_tag(MPI_Status *status, int tag) { if(status) status->MPI_TAG=tag; return MPI_SUCCESS; }

/* --- A.3.12 I/O --- */
int MPI_File_close(MPI_File *fh) { if(fh && *fh != MPI_FILE_NULL) { close((int)(intptr_t)*fh); *fh = MPI_FILE_NULL; } return MPI_SUCCESS; }
int MPI_File_delete(const char *filename, MPI_Info info) { unlink(filename); return MPI_SUCCESS; }
int MPI_File_get_amode(MPI_File fh, int *amode) { if(amode) *amode=0; return MPI_SUCCESS; }
int MPI_File_get_atomicity(MPI_File fh, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp) { if(disp) *disp=offset; return MPI_SUCCESS; }
int MPI_File_get_group(MPI_File fh, MPI_Group *group) { if(group) *group=MPI_GROUP_NULL; return MPI_SUCCESS; }
int MPI_File_get_info(MPI_File fh, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset) { return MPI_File_get_position(fh, offset); }
int MPI_File_get_position(MPI_File fh, MPI_Offset *offset) { if(offset) *offset = lseek((int)(intptr_t)fh, 0, SEEK_CUR); return MPI_SUCCESS; }
int MPI_File_get_size(MPI_File fh, MPI_Offset *size) { struct stat st; if (fstat((int)(intptr_t)fh, &st) != 0) return MPI_ERR_OTHER; if (size) *size = st.st_size; return MPI_SUCCESS; }
int MPI_File_get_type_extent_c(MPI_File fh, MPI_Datatype datatype, MPI_Count *extent) { if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent) { if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep) { return MPI_SUCCESS; }
int MPI_File_iread_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_read(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write_at(fh, offset, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
int MPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { if(request) *request=MPI_REQUEST_NULL; return MPI_File_write(fh, buf, count, datatype, MPI_STATUS_IGNORE); }
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
int MPI_File_preallocate(MPI_File fh, MPI_Offset size) { return MPI_File_set_size(fh, size); }
int MPI_File_read_all_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_at_all_begin_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read_at(fh, offset, buf, count, datatype, status); }
int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read_at(fh, offset, buf, count, datatype, status); }
int MPI_File_read_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read_at(fh, offset, buf, count, datatype, status); }
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = pread((int)(intptr_t)fh, buf, (size_t)count * size, offset);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_read_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_ordered_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_read_ordered_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_read(fh, buf, count, datatype, status); }
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = read((int)(intptr_t)fh, buf, (size_t)count * size);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence) { return MPI_File_seek(fh, offset, whence); }
int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence) { lseek((int)(intptr_t)fh, offset, whence); return MPI_SUCCESS; }
int MPI_File_set_atomicity(MPI_File fh, int flag) { return MPI_SUCCESS; }
int MPI_File_set_info(MPI_File fh, MPI_Info info) { return MPI_SUCCESS; }
int MPI_File_set_size(MPI_File fh, MPI_Offset size) { if (ftruncate((int)(intptr_t)fh, size) != 0) return MPI_ERR_OTHER; return MPI_SUCCESS; }
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info) { return MPI_SUCCESS; }
int MPI_File_sync(MPI_File fh) { fsync((int)(intptr_t)fh); return MPI_SUCCESS; }
int MPI_File_write_all_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_at_all_begin_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write_at(fh, offset, buf, count, datatype, status); }
int MPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write_at(fh, offset, buf, count, datatype, status); }
int MPI_File_write_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write_at(fh, offset, buf, count, datatype, status); }
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = pwrite((int)(intptr_t)fh, buf, (size_t)count * size, offset);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_File_write_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_ordered_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype) { return MPI_SUCCESS; }
int MPI_File_write_ordered_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status) { return MPI_SUCCESS; }
int MPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { return MPI_File_write(fh, buf, count, datatype, status); }
int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) {
    int size = get_type_size(datatype);
    ssize_t bytes = write((int)(intptr_t)fh, buf, (size_t)count * size);
    if (status) set_status_count(status, bytes > 0 ? bytes / size : 0);
    return MPI_SUCCESS;
}
int MPI_Register_datarep_c(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state) { return MPI_SUCCESS; }
int MPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state) { return MPI_SUCCESS; }

/* --- A.3.13 Language Bindings --- */
int MPI_Status_c2f08(const MPI_Status *c_status, MPI_F08_status *f08_status) { if(c_status && f08_status) memcpy(f08_status, c_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Status_c2f(const MPI_Status *c_status, MPI_Fint *f_status) { if(c_status && f_status) memcpy(f_status, c_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Status_f082c(const MPI_F08_status *f08_status, MPI_Status *c_status) { if(c_status && f08_status) memcpy(c_status, f08_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Status_f082f(const MPI_F08_status *f08_status, MPI_Fint *f_status) { if(f_status && f08_status) memcpy(f_status, f08_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Status_f2c(const MPI_Fint *f_status, MPI_Status *c_status) { if(c_status && f_status) memcpy(c_status, f_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Status_f2f08(const MPI_Fint *f_status, MPI_F08_status *f08_status) { if(f_status && f08_status) memcpy(f08_status, f_status, sizeof(MPI_Status)); return MPI_SUCCESS; }
int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype) { if(newtype) *newtype=MPI_COMPLEX; return MPI_SUCCESS; }
int MPI_Type_create_f90_integer(int r, MPI_Datatype *newtype) { if(newtype) *newtype=MPI_INTEGER; return MPI_SUCCESS; }
int MPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype) { if(newtype) *newtype=MPI_REAL; return MPI_SUCCESS; }
int MPI_Type_match_size(int typeclass, int size, MPI_Datatype *datatype) { if(datatype) *datatype=MPI_DATATYPE_NULL; return MPI_SUCCESS; }

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
MPI_Message MPI_Message_f2c(MPI_Fint message) { return (MPI_Message)(intptr_t)message; }
MPI_Fint MPI_Message_c2f(MPI_Message message) { return (MPI_Fint)(intptr_t)message; }
MPI_Session MPI_Session_f2c(MPI_Fint session) { return (MPI_Session)(intptr_t)session; }
MPI_Fint MPI_Session_c2f(MPI_Session session) { return (MPI_Fint)(intptr_t)session; }

/* --- A.3.14 Application Binary Interface (ABI) --- */
int MPI_Abi_get_version(int *abi_major, int *abi_minor) { if(abi_major) *abi_major=MPI_ABI_VERSION; if(abi_minor) *abi_minor=MPI_ABI_SUBVERSION; return MPI_SUCCESS; }
int MPI_Abi_get_info(MPI_Info *info) { if(info) *info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Abi_get_fortran_info(MPI_Info *info) { if(info) *info=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_Abi_set_fortran_info(MPI_Info info) { return MPI_SUCCESS; }
int MPI_Abi_get_fortran_booleans(int logical_size, void *logical_true, void *logical_false, int *is_set) { if(is_set) *is_set=0; return MPI_SUCCESS; }
int MPI_Abi_set_fortran_booleans(int logical_size, void *logical_true, void *logical_false) { return MPI_SUCCESS; }
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
int MPI_Message_toint(MPI_Message message) { return (int)(intptr_t)message; }
MPI_Message MPI_Message_fromint(int message) { return (MPI_Message)(intptr_t)message; }
int MPI_Session_toint(MPI_Session session) { return (int)(intptr_t)session; }
MPI_Session MPI_Session_fromint(int session) { return (MPI_Session)(intptr_t)session; }

/* --- A.3.15 Tools / Profiling Interface --- */
int MPI_Pcontrol(const int level, ...) { return MPI_SUCCESS; }

/* --- A.3.16 Tools / MPI Tool Information Interface --- */
int MPI_T_category_changed(int *update_number) { if(update_number) *update_number=0; return MPI_SUCCESS; }
int MPI_T_category_get_categories(int cat_index, int len, int indices[]) { return MPI_SUCCESS; }
int MPI_T_category_get_cvars(int cat_index, int len, int indices[]) { return MPI_SUCCESS; }
int MPI_T_category_get_events(int cat_index, int len, int indices[]) { return MPI_SUCCESS; }
int MPI_T_category_get_index(const char *name, int *cat_index) { if(cat_index) *cat_index=0; return MPI_SUCCESS; }
int MPI_T_category_get_info(int cat_index, char *name, int *name_len, char *desc, int *desc_len, int *num_cvars, int *num_pvars, int *num_categories) { return MPI_SUCCESS; }
int MPI_T_category_get_num_events(int cat_index, int *num_events) { if(num_events) *num_events=0; return MPI_SUCCESS; }
int MPI_T_category_get_num(int *num_cat) { if(num_cat) *num_cat=0; return MPI_SUCCESS; }
int MPI_T_category_get_pvars(int cat_index, int len, int indices[]) { return MPI_SUCCESS; }
int MPI_T_cvar_get_index(const char *name, int *cvar_index) { if(cvar_index) *cvar_index=0; return MPI_SUCCESS; }
int MPI_T_cvar_get_info(int cvar_index, char *name, int *name_len, int *verbosity, MPI_Datatype *datatype, MPI_T_enum *enumtype, char *desc, int *desc_len, int *bind, int *scope) { return MPI_SUCCESS; }
int MPI_T_cvar_get_num(int *num_cvar) { if(num_cvar) *num_cvar=0; return MPI_SUCCESS; }
int MPI_T_cvar_handle_alloc(int cvar_index, void *obj_handle, MPI_T_cvar_handle *handle, int *count) { if(handle) *handle=MPI_T_CVAR_HANDLE_NULL; if(count) *count=1; return MPI_SUCCESS; }
int MPI_T_cvar_handle_free(MPI_T_cvar_handle *handle) { if(handle) *handle=MPI_T_CVAR_HANDLE_NULL; return MPI_SUCCESS; }
int MPI_T_cvar_read(MPI_T_cvar_handle handle, void *buf) { return MPI_SUCCESS; }
int MPI_T_cvar_write(MPI_T_cvar_handle handle, const void *buf) { return MPI_SUCCESS; }
int MPI_T_enum_get_info(MPI_T_enum enumtype, int *num, char *name, int *name_len) { if(num) *num=0; return MPI_SUCCESS; }
int MPI_T_enum_get_item(MPI_T_enum enumtype, int index, int *value, char *name, int *name_len) { if(value) *value=0; return MPI_SUCCESS; }
int MPI_T_event_callback_get_info(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_T_event_callback_set_info(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info info) { return MPI_SUCCESS; }
int MPI_T_event_copy(MPI_T_event_instance event_instance, void *buffer) { return MPI_SUCCESS; }
int MPI_T_event_get_index(const char *name, int *event_index) { if(event_index) *event_index=0; return MPI_SUCCESS; }
int MPI_T_event_get_info(int event_index, char *name, int *name_len, int *verbosity, MPI_Datatype array_of_datatypes[], MPI_Aint array_of_displacements[], int *num_elements, MPI_T_enum *enumtype, MPI_Info info, char *desc, int *desc_len, int *bind) { return MPI_SUCCESS; }
int MPI_T_event_get_num(int *num_events) { if(num_events) *num_events=0; return MPI_SUCCESS; }
int MPI_T_event_get_source(MPI_T_event_instance event_instance, int *source_index) { if(source_index) *source_index=0; return MPI_SUCCESS; }
int MPI_T_event_get_timestamp(MPI_T_event_instance event_instance, MPI_Count *event_timestamp) { if(event_timestamp) *event_timestamp=0; return MPI_SUCCESS; }
int MPI_T_event_handle_alloc(int event_index, void *obj_handle, MPI_Info info, MPI_T_event_registration *event_registration) { if(event_registration) *event_registration=0; return MPI_SUCCESS; }
int MPI_T_event_handle_free(MPI_T_event_registration event_registration, void *user_data, MPI_T_event_free_cb_function free_cb_function) { return MPI_SUCCESS; }
int MPI_T_event_handle_get_info(MPI_T_event_registration event_registration, MPI_Info *info_used) { if(info_used) *info_used=MPI_INFO_NULL; return MPI_SUCCESS; }
int MPI_T_event_handle_set_info(MPI_T_event_registration event_registration, MPI_Info info) { return MPI_SUCCESS; }
int MPI_T_event_read(MPI_T_event_instance event_instance, int element_index, void *buffer) { return MPI_SUCCESS; }
int MPI_T_event_register_callback(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info info, void *user_data, MPI_T_event_cb_function event_cb_function) { return MPI_SUCCESS; }
int MPI_T_event_set_dropped_handler(MPI_T_event_registration event_registration, MPI_T_event_dropped_cb_function dropped_cb_function) { return MPI_SUCCESS; }
int MPI_T_finalize(void) { return MPI_SUCCESS; }
int MPI_T_init_thread(int required, int *provided) { if(provided) *provided=required; return MPI_SUCCESS; }
int MPI_T_pvar_get_index(const char *name, int var_class, int *pvar_index) { if(pvar_index) *pvar_index=0; return MPI_SUCCESS; }
int MPI_T_pvar_get_info(int pvar_index, char *name, int *name_len, int *verbosity, int *var_class, MPI_Datatype *datatype, MPI_T_enum enumtype, char *desc, int *desc_len, int *bind, int *readonly, int *continuous, int *atomic) { return MPI_SUCCESS; }
int MPI_T_pvar_get_num(int *num_pvar) { if(num_pvar) *num_pvar=0; return MPI_SUCCESS; }
int MPI_T_pvar_handle_alloc(MPI_T_pvar_session pe_session, int pvar_index, void *obj_handle, MPI_T_pvar_handle handle, int *count) { if(count) *count=1; return MPI_SUCCESS; }
int MPI_T_pvar_handle_free(MPI_T_pvar_session pe_session, MPI_T_pvar_handle *handle) { if(handle) *handle=MPI_T_PVAR_HANDLE_NULL; return MPI_SUCCESS; }
int MPI_T_pvar_readreset(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, void *buf) { return MPI_SUCCESS; }
int MPI_T_pvar_read(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, void *buf) { return MPI_SUCCESS; }
int MPI_T_pvar_reset(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle) { return MPI_SUCCESS; }
int MPI_T_pvar_session_create(MPI_T_pvar_session *pe_session) { if(pe_session) *pe_session=MPI_T_PVAR_SESSION_NULL; return MPI_SUCCESS; }
int MPI_T_pvar_session_free(MPI_T_pvar_session *pe_session) { if(pe_session) *pe_session=MPI_T_PVAR_SESSION_NULL; return MPI_SUCCESS; }
int MPI_T_pvar_start(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle) { return MPI_SUCCESS; }
int MPI_T_pvar_stop(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle) { return MPI_SUCCESS; }
int MPI_T_pvar_write(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, const void *buf) { return MPI_SUCCESS; }
int MPI_T_source_get_info(int source_index, char *name, int *name_len, char *desc, int *desc_len, MPI_T_source_order *ordering, MPI_Count *ticks_per_second, MPI_Count *max_ticks, MPI_Info info) { return MPI_SUCCESS; }
int MPI_T_source_get_num(int *num_sources) { if(num_sources) *num_sources=0; return MPI_SUCCESS; }
int MPI_T_source_get_timestamp(int source_index, MPI_Count timestamp) { return MPI_SUCCESS; }

/* --- A.3.17 Deprecated C Bindings --- */
// int MPI_Attr_delete(MPI_Comm comm, int keyval) { return MPI_SUCCESS; }
// int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag) { if(flag) *flag=0; return MPI_SUCCESS; }
// int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val) { return MPI_SUCCESS; }
int MPI_Attr_delete(MPI_Comm comm, int keyval) { return MPI_Comm_delete_attr(comm, keyval); }
int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag) { return MPI_Comm_get_attr(comm, keyval, attribute_val, flag); }
int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val) { return MPI_Comm_set_attr(comm, keyval, attribute_val); }
int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count) { int c; MPI_Get_count(status, datatype, &c); if(count) *count=c; return MPI_SUCCESS; }
int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state) { if(keyval) *keyval=next_keyval++; return MPI_SUCCESS; }
int MPI_Keyval_free(int *keyval) { if(keyval) *keyval=MPI_KEYVAL_INVALID; return MPI_SUCCESS; }
int MPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count) { set_status_count(status, count); return MPI_SUCCESS; }
int MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent) { if(lb) *lb=0; if(extent) *extent=get_type_size(datatype); return MPI_SUCCESS; }
int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent) { return MPI_Type_get_extent_x(datatype, true_lb, true_extent); }
int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size) { if(size) *size=get_type_size(datatype); return MPI_SUCCESS; }

/* Legacy MPI-1 Aliases for SuperLU_DIST and MUMPS */
int MPI_Type_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype) {
    return MPI_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}
int MPI_Type_extent(MPI_Datatype datatype, MPI_Aint *extent) {
    MPI_Aint lb;
    return MPI_Type_get_extent(datatype, &lb, extent);
}
int MPI_Type_lb(MPI_Datatype datatype, MPI_Aint *displacement) {
    if(displacement) *displacement = 0;
    return MPI_SUCCESS;
}
int MPI_Type_ub(MPI_Datatype datatype, MPI_Aint *displacement) {
    if(displacement) *displacement = get_type_size(datatype);
    return MPI_SUCCESS;
}
int MPI_Address(void *location, MPI_Aint *address) {
    return MPI_Get_address(location, address);
}
int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler) {
    if(errhandler) *errhandler = MPI_ERRHANDLER_NULL;
    return MPI_SUCCESS;
}
int MPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype) {
    return MPI_Type_create_hvector(count, blocklength, stride, oldtype, newtype);
}
int MPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) {
    return MPI_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

MPI_Aint MPI_Aint_add(MPI_Aint base, MPI_Aint disp) { return base + disp; }
MPI_Aint MPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2) { return addr1 - addr2; }

/* =========================================================================
 * Core Fortran Interceptors (Crucial for Linker Resolution)
 * ========================================================================= */
#define F_FUNC(name) mpi_##name##_

/* Environmental Management */
void F_FUNC(init)(MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(finalize)(MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(initialized)(MPI_Fint *flag, MPI_Fint *ierr) { *flag = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(finalized)(MPI_Fint *flag, MPI_Fint *ierr) { *flag = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(abort)(MPI_Fint *comm, MPI_Fint *errorcode, MPI_Fint *ierr) { exit(*errorcode); }
double F_FUNC(wtime)(void) { return MPI_Wtime(); }
double F_FUNC(wtick)(void) { return MPI_Wtick(); }
void F_FUNC(get_processor_name)(char *name, MPI_Fint *resultlen, MPI_Fint *ierr, size_t name_len) { 
    if(name && name_len > 0) name[0] = 'A'; 
    *resultlen = 1; 
    *ierr = MPI_SUCCESS; 
}

/* Communicators */
void F_FUNC(comm_size)(MPI_Fint *comm, MPI_Fint *size, MPI_Fint *ierr) { *size = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(comm_rank)(MPI_Fint *comm, MPI_Fint *rank, MPI_Fint *ierr) { *rank = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(comm_dup)(MPI_Fint *comm, MPI_Fint *newcomm, MPI_Fint *ierr) { *newcomm = *comm; *ierr = MPI_SUCCESS; }
void F_FUNC(comm_split)(MPI_Fint *comm, MPI_Fint *color, MPI_Fint *key, MPI_Fint *newcomm, MPI_Fint *ierr) { *newcomm = *comm; *ierr = MPI_SUCCESS; }
void F_FUNC(comm_free)(MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }

/* Point-to-Point */
void F_FUNC(send)(void *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *dest, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(recv)(void *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *source, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *status, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(isend)(void *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *dest, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(irecv)(void *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *source, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(probe)(MPI_Fint *source, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *status, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(iprobe)(MPI_Fint *source, MPI_Fint *tag, MPI_Fint *comm, MPI_Fint *flag, MPI_Fint *status, MPI_Fint *ierr) { *flag = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(get_count)(MPI_Fint *status, MPI_Fint *datatype, MPI_Fint *count, MPI_Fint *ierr) { *count = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(sendrecv_replace)(void *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *dest, MPI_Fint *sendtag, MPI_Fint *source, MPI_Fint *recvtag, MPI_Fint *comm, MPI_Fint *status, MPI_Fint *ierr) { 
    *ierr = MPI_SUCCESS; 
}
/* Requests */
void F_FUNC(wait)(MPI_Fint *request, MPI_Fint *status, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(waitany)(MPI_Fint *count, MPI_Fint *array_of_requests, MPI_Fint *index, MPI_Fint *status, MPI_Fint *ierr) { *index = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(waitall)(MPI_Fint *count, MPI_Fint *array_of_requests, MPI_Fint *array_of_statuses, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(test)(MPI_Fint *request, MPI_Fint *flag, MPI_Fint *status, MPI_Fint *ierr) { *flag = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(testany)(MPI_Fint *count, MPI_Fint *array_of_requests, MPI_Fint *index, MPI_Fint *flag, MPI_Fint *status, MPI_Fint *ierr) { *flag = 1; *index = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(cancel)(MPI_Fint *request, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(request_free)(MPI_Fint *request, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }

/* Collectives */
void F_FUNC(barrier)(MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(bcast)(void *buffer, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(allreduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(reduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(gather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(scatter)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(allgather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(alltoall)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(reduce_scatter)(void *sendbuf, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(ibcast)(void *buffer, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ireduce_scatter)(void *sendbuf, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { 
    *request = 0; 
    *ierr = MPI_SUCCESS; 
}
/* Packing */
void F_FUNC(pack)(void *inbuf, MPI_Fint *incount, MPI_Fint *datatype, void *outbuf, MPI_Fint *outsize, MPI_Fint *position, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(unpack)(void *inbuf, MPI_Fint *insize, MPI_Fint *position, void *outbuf, MPI_Fint *outcount, MPI_Fint *datatype, MPI_Fint *comm, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(pack_size)(MPI_Fint *incount, MPI_Fint *datatype, MPI_Fint *comm, MPI_Fint *size, MPI_Fint *ierr) { *size = 0; *ierr = MPI_SUCCESS; }

/* Types */
void F_FUNC(type_contiguous)(MPI_Fint *count, MPI_Fint *oldtype, MPI_Fint *newtype, MPI_Fint *ierr) { *newtype = *oldtype; *ierr = MPI_SUCCESS; }
void F_FUNC(type_commit)(MPI_Fint *datatype, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }
void F_FUNC(type_free)(MPI_Fint *datatype, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }

/* Ops */
void F_FUNC(op_create)(void *user_fn, MPI_Fint *commute, MPI_Fint *op, MPI_Fint *ierr) { *op = 1; *ierr = MPI_SUCCESS; }
void F_FUNC(op_free)(MPI_Fint *op, MPI_Fint *ierr) { *ierr = MPI_SUCCESS; }

void F_FUNC(iallgather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iallgatherv)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *displs, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iallreduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ialltoall)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ialltoallv)(void *sendbuf, MPI_Fint *sendcounts, MPI_Fint *sdispls, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *rdispls, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ialltoallw)(void *sendbuf, MPI_Fint *sendcounts, MPI_Fint *sdispls, MPI_Fint *sendtypes, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *rdispls, MPI_Fint *recvtypes, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iexscan)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(igather)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(igatherv)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcounts, MPI_Fint *displs, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ireduce)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iscan)(void *sendbuf, void *recvbuf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iscatter)(void *sendbuf, MPI_Fint *sendcount, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(iscatterv)(void *sendbuf, MPI_Fint *sendcounts, MPI_Fint *displs, MPI_Fint *sendtype, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *recvtype, MPI_Fint *root, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ibarrier)(MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }
void F_FUNC(ireduce_scatter_block)(void *sendbuf, void *recvbuf, MPI_Fint *recvcount, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, MPI_Fint *request, MPI_Fint *ierr) { *request = 0; *ierr = MPI_SUCCESS; }