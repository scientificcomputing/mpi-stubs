#ifndef MPI_STUB_H
#define MPI_STUB_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Chapter 2: MPI Terms and Conventions
 * ========================================================================= */

/* MPICH-style integer handle ABI */
typedef int MPI_Comm;
typedef int MPI_Datatype;
typedef int MPI_Op;
typedef int MPI_Request;
typedef int MPI_Group;
typedef int MPI_Info;
typedef int MPI_Errhandler;
typedef int MPI_Win;
typedef int MPI_Fint;
typedef int MPI_File;

/* MPI 5.0 Memory, I/O, and Large Count types */
typedef ptrdiff_t MPI_Aint;
typedef int64_t   MPI_Offset;
typedef int64_t   MPI_Count;

/* Status Object */
typedef struct {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int _cancelled;
    size_t _count;
} MPI_Status;

/* Return Codes and String Limits */
#define MPI_SUCCESS      0
#define MPI_ERR_OTHER    1
#define MPI_ERR_UNKNOWN  2
#define MPI_ERR_INTERN   3
#define MPI_ERR_COUNT    4
#define MPI_ERR_LASTCODE 5

#define MPI_MAX_LIBRARY_VERSION_STRING 256
#define MPI_MAX_ERROR_STRING 512
#define MPI_MAX_OBJECT_NAME  128
#define MPI_MAX_INFO_KEY     255
#define MPI_MAX_INFO_VAL     1024

/* Threading Levels */
#define MPI_THREAD_SINGLE     0
#define MPI_THREAD_FUNNELED   1
#define MPI_THREAD_SERIALIZED 2
#define MPI_THREAD_MULTIPLE   3

/* Predefined Communicators and Groups */
#define MPI_COMM_NULL   ((MPI_Comm)0)
#define MPI_COMM_WORLD  ((MPI_Comm)1)
#define MPI_COMM_SELF   ((MPI_Comm)2)
#define MPI_GROUP_NULL  ((MPI_Group)0)
#define MPI_GROUP_EMPTY ((MPI_Group)1)

/* Predefined Datatypes */
#define MPI_DATATYPE_NULL ((MPI_Datatype)0)
#define MPI_CHAR          ((MPI_Datatype)1)
#define MPI_INT           ((MPI_Datatype)2)
#define MPI_LONG          ((MPI_Datatype)3)
#define MPI_FLOAT         ((MPI_Datatype)4)
#define MPI_DOUBLE        ((MPI_Datatype)5)
#define MPI_COMPLEX       ((MPI_Datatype)6)
#define MPI_DOUBLE_COMPLEX ((MPI_Datatype)7)
#define MPI_BYTE          ((MPI_Datatype)8)
#define MPI_UNSIGNED_CHAR ((MPI_Datatype)9)
#define MPI_C_BOOL        ((MPI_Datatype)10)
#define MPI_UNSIGNED_LONG ((MPI_Datatype)11)
#define MPI_AINT          ((MPI_Datatype)12)
#define MPI_LONG_LONG_INT ((MPI_Datatype)13)
#define MPI_2DOUBLE_PRECISION ((MPI_Datatype)14)
#define MPI_2INT              ((MPI_Datatype)15)
#define MPI_C_DOUBLE_COMPLEX  ((MPI_Datatype)16)
#define MPI_C_FLOAT_COMPLEX   ((MPI_Datatype)17)
#define MPI_UNSIGNED          ((MPI_Datatype)18)
#define MPI_UNSIGNED_LONG_LONG ((MPI_Datatype)19)
#define MPI_SHORT             ((MPI_Datatype)20)
#define MPI_INT32_T           ((MPI_Datatype)21)
#define MPI_INT64_T           ((MPI_Datatype)22)
#define MPI_UNSIGNED_SHORT    ((MPI_Datatype)23)
#define MPI_SIGNED_CHAR       ((MPI_Datatype)24)
#define MPI_COUNT             ((MPI_Datatype)25)
#define MPI_OFFSET            ((MPI_Datatype)26)
#define MPI_UINT64_T          ((MPI_Datatype)27)
#define MPI_INT8_T            ((MPI_Datatype)28)
#define MPI_UINT8_T           ((MPI_Datatype)29)
#define MPI_INT16_T           ((MPI_Datatype)30)
#define MPI_UINT16_T          ((MPI_Datatype)31)
#define MPI_UINT32_T          ((MPI_Datatype)32)

/* Predefined Operations */
#define MPI_OP_NULL ((MPI_Op)0)
#define MPI_MAX     ((MPI_Op)1)
#define MPI_MIN     ((MPI_Op)2)
#define MPI_SUM     ((MPI_Op)3)
#define MPI_PROD    ((MPI_Op)4)
#define MPI_REPLACE ((MPI_Op)5)
#define MPI_LOR     ((MPI_Op)6)
#define MPI_LAND    ((MPI_Op)7)
#define MPI_MAXLOC  ((MPI_Op)8)
#define MPI_MINLOC  ((MPI_Op)9)
#define MPI_BAND    ((MPI_Op)10)
#define MPI_BOR     ((MPI_Op)11)
#define MPI_LXOR    ((MPI_Op)12)
#define MPI_BXOR    ((MPI_Op)13)

/* Requests, Windows, Statuses, and Error Handlers */
#define MPI_REQUEST_NULL    ((MPI_Request)0)
#define MPI_WIN_NULL        ((MPI_Win)0)
#define MPI_INFO_NULL       ((MPI_Info)0)
#define MPI_STATUS_IGNORE   ((MPI_Status *)0)
#define MPI_STATUSES_IGNORE ((MPI_Status *)0)

#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)1)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)2)

/* Constants for Collectives and P2P */
#define MPI_ANY_SOURCE (-1)
#define MPI_ANY_TAG    (-1)
#define MPI_PROC_NULL  (-2)
#define MPI_UNDEFINED  (-3)
#define MPI_IN_PLACE   ((void *)1)
#define MPI_COMBINER_NAMED 1

/* Communicator Comparison Results */
#define MPI_IDENT     0
#define MPI_CONGRUENT 1
#define MPI_SIMILAR   2
#define MPI_UNEQUAL   3

/* RMA Lock / Mode Constants */
#define MPI_LOCK_EXCLUSIVE 1
#define MPI_LOCK_SHARED    2
#define MPI_MODE_NOCHECK   1
#define MPI_MODE_NOPUT     2
#define MPI_MODE_NOPRECEDE 4
#define MPI_MODE_NOSTORE   8
#define MPI_MODE_NOSUCCEED 16

/* MPI-IO Modes */
#define MPI_FILE_NULL ((MPI_File)0)
#define MPI_MODE_RDONLY              2
#define MPI_MODE_RDWR                8
#define MPI_MODE_WRONLY              4
#define MPI_MODE_CREATE              1
#define MPI_MODE_EXCL               64
#define MPI_MODE_DELETE_ON_CLOSE    16
#define MPI_MODE_UNIQUE_OPEN        32
#define MPI_MODE_APPEND            128
#define MPI_MODE_SEQUENTIAL        256

/* Attributes / Keyvals */
#define MPI_KEYVAL_INVALID 0
#define MPI_TAG_UB           1
#define MPI_HOST             2
#define MPI_IO               3
#define MPI_WTIME_IS_GLOBAL  4

typedef int MPI_Comm_copy_attr_function(MPI_Comm, int, void *, void *, void *, int *);
typedef int MPI_Comm_delete_attr_function(MPI_Comm, int, void *, void *);
#define MPI_COMM_NULL_COPY_FN ((MPI_Comm_copy_attr_function*)0)
#define MPI_COMM_NULL_DELETE_FN ((MPI_Comm_delete_attr_function*)0)

/* Callbacks */
typedef void (MPI_Handler_function)(MPI_Comm *, int *, ...);
typedef void (MPI_Comm_errhandler_function)(MPI_Comm *, int *, ...);
typedef MPI_Comm_errhandler_function MPI_Comm_errhandler_fn;
typedef void (MPI_User_function)(void *, void *, int *, MPI_Datatype *);

/* =========================================================================
 * Chapter 3: Point-to-Point Communication
 * ========================================================================= */
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);
int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Startall(int count, MPI_Request array_of_requests[]);
int MPI_Wait(MPI_Request *request, MPI_Status *status);
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status);
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
int MPI_Cancel(MPI_Request *request);
int MPI_Request_free(MPI_Request *request);
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);

/* =========================================================================
 * Chapter 5: Datatypes
 * ========================================================================= */
int MPI_Type_size(MPI_Datatype datatype, int *size);
int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size);
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_commit(MPI_Datatype *datatype);
int MPI_Type_free(MPI_Datatype *datatype);
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent);
int MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent);
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
int MPI_Type_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype);
int MPI_Type_create_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype);
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Get_address(const void *location, MPI_Aint *address);

/* =========================================================================
 * Chapter 6: Collective Communication
 * ========================================================================= */
int MPI_Barrier(MPI_Comm comm);
int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request);
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op);
int MPI_Op_free(MPI_Op *op);

/* =========================================================================
 * Chapter 7: Groups, Contexts, Communicators, and Caching
 * ========================================================================= */
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_free(MPI_Comm *comm);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Group_size(MPI_Group group, int *size);
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]);
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_free(MPI_Group *group);
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int MPI_Comm_free_keyval(int *comm_keyval);
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);

/* =========================================================================
 * Chapter 9: MPI Environmental Management
 * ========================================================================= */
int MPI_Get_library_version(char *version, int *resultlen);
double MPI_Wtime(void);
int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_Add_error_class(int *errorclass);
int MPI_Add_error_code(int errorclass, int *errorcode);
int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler);
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler);
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_fn *function, MPI_Errhandler *errhandler);
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);

/* =========================================================================
 * Chapter 10: The Info Object
 * ========================================================================= */
int MPI_Info_create(MPI_Info *info);
int MPI_Info_free(MPI_Info *info);
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag);
int MPI_Info_set(MPI_Info info, const char *key, const char *value);
int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag);

/* =========================================================================
 * Chapter 11: Process Initialization, Creation, and Management
 * ========================================================================= */
int MPI_Init(int *argc, char ***argv);
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
int MPI_Finalize(void);
int MPI_Initialized(int *flag);
int MPI_Finalized(int *flag);
int MPI_Abort(MPI_Comm comm, int errorcode);

/* =========================================================================
 * Chapter 12: One-Sided Communications
 * ========================================================================= */
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_free(MPI_Win *win);
int MPI_Win_fence(int assert, MPI_Win win);
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);
int MPI_Win_unlock(int rank, MPI_Win win);
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_complete(MPI_Win win);
int MPI_Win_wait(MPI_Win win);
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);

/* =========================================================================
 * Chapter 14: I/O
 * ========================================================================= */
int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh);
int MPI_File_close(MPI_File *fh);
int MPI_File_delete(const char *filename, MPI_Info info);
int MPI_File_set_size(MPI_File fh, MPI_Offset size);
int MPI_File_get_size(MPI_File fh, MPI_Offset *size);
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info);
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_sync(MPI_File fh);
int MPI_File_get_info(MPI_File fh, MPI_Info *info_used);
int MPI_File_set_atomicity(MPI_File fh, int flag);
int MPI_File_get_atomicity(MPI_File fh, int *flag);

/* =========================================================================
 * Chapter 19: Language Bindings
 * ========================================================================= */
MPI_Datatype MPI_Type_f2c(MPI_Fint datatype);
MPI_Fint MPI_Type_c2f(MPI_Datatype datatype);
MPI_Comm MPI_Comm_f2c(MPI_Fint comm);
MPI_Fint MPI_Comm_c2f(MPI_Comm comm);
MPI_Op MPI_Op_f2c(MPI_Fint op);
MPI_Fint MPI_Op_c2f(MPI_Op op);
MPI_Request MPI_Request_f2c(MPI_Fint request);
MPI_Fint MPI_Request_c2f(MPI_Request request);
MPI_Win MPI_Win_f2c(MPI_Fint win);
MPI_Fint MPI_Win_c2f(MPI_Win win);
MPI_Info MPI_Info_f2c(MPI_Fint info);
MPI_Fint MPI_Info_c2f(MPI_Info info);
MPI_Group MPI_Group_f2c(MPI_Fint group);
MPI_Fint MPI_Group_c2f(MPI_Group group);
MPI_Errhandler MPI_Errhandler_f2c(MPI_Fint errhandler);
MPI_Fint MPI_Errhandler_c2f(MPI_Errhandler errhandler);

#ifdef __cplusplus
}
#endif

#endif /* MPI_STUB_H */