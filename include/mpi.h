#ifndef MPI_STUB_H
#define MPI_STUB_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * CHAPTER 20: APPLICATION BINARY INTERFACE (ABI)
 * ========================================================================= */

#define MPI_ABI_VERSION 1
#define MPI_ABI_SUBVERSION 0

/* 20.3.1 The Status Object */
typedef struct {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int MPI_internal[5]; /* Strictly 5 ints per ABI standard */
} MPI_Status;

/* 20.3.2 Opaque Handles (Incomplete struct pointers for type safety) */
typedef struct MPI_ABI_Comm* MPI_Comm;
typedef struct MPI_ABI_Datatype* MPI_Datatype;
typedef struct MPI_ABI_Errhandler* MPI_Errhandler;
typedef struct MPI_ABI_File* MPI_File;
typedef struct MPI_ABI_Group* MPI_Group;
typedef struct MPI_ABI_Info* MPI_Info;
typedef struct MPI_ABI_Message* MPI_Message;
typedef struct MPI_ABI_Op* MPI_Op;
typedef struct MPI_ABI_Request* MPI_Request;
typedef struct MPI_ABI_Session* MPI_Session;
typedef struct MPI_ABI_Win* MPI_Win;

/* 20.3.5 Integer Types */
typedef intptr_t MPI_Aint;
typedef int64_t  MPI_Offset;
typedef int64_t  MPI_Count;
typedef int      MPI_Fint;

/* =========================================================================
 * APPENDIX A.1: DEFINED VALUES AND HANDLES
 * ========================================================================= */

/* Error Classes */
#define MPI_SUCCESS                  0
#define MPI_ERR_BUFFER               1
#define MPI_ERR_COUNT                2
#define MPI_ERR_TYPE                 3
#define MPI_ERR_TAG                  4
#define MPI_ERR_COMM                 5
#define MPI_ERR_RANK                 6
#define MPI_ERR_REQUEST              7
#define MPI_ERR_ROOT                 8
#define MPI_ERR_GROUP                9
#define MPI_ERR_OP                   10
#define MPI_ERR_TOPOLOGY             11
#define MPI_ERR_DIMS                 12
#define MPI_ERR_ARG                  13
#define MPI_ERR_UNKNOWN              14
#define MPI_ERR_TRUNCATE             15
#define MPI_ERR_OTHER                16
#define MPI_ERR_INTERN               17
#define MPI_ERR_LASTCODE             16383

/* Buffer Address Constants */
#define MPI_BOTTOM           ((void*)0)
#define MPI_IN_PLACE         ((void*)1)
#define MPI_BUFFER_AUTOMATIC ((void*)2)

/* Ignored Inputs */
#define MPI_ARGVS_NULL        ((char***)0)
#define MPI_ARGV_NULL         ((char**)0)
#define MPI_ERRCODES_IGNORE   ((int*)0)
#define MPI_STATUSES_IGNORE   ((MPI_Status*)0)
#define MPI_STATUS_IGNORE     ((MPI_Status*)0)

/* String Limits */
#define MPI_MAX_DATAREP_STRING         128
#define MPI_MAX_ERROR_STRING           512
#define MPI_MAX_INFO_KEY               256
#define MPI_MAX_INFO_VAL               1024
#define MPI_MAX_LIBRARY_VERSION_STRING 8192
#define MPI_MAX_OBJECT_NAME            128
#define MPI_MAX_PORT_NAME              1024
#define MPI_MAX_PROCESSOR_NAME         256

/* Mode Constants */
#define MPI_MODE_APPEND             1
#define MPI_MODE_CREATE             2
#define MPI_MODE_DELETE_ON_CLOSE    4
#define MPI_MODE_EXCL               8
#define MPI_MODE_RDONLY             16
#define MPI_MODE_RDWR               32
#define MPI_MODE_SEQUENTIAL         64
#define MPI_MODE_UNIQUE_OPEN        128
#define MPI_MODE_WRONLY             256
#define MPI_MODE_NOCHECK            1024
#define MPI_MODE_NOPRECEDE          2048
#define MPI_MODE_NOPUT              4096
#define MPI_MODE_NOSTORE            8192
#define MPI_MODE_NOSUCCEED          16384

/* Assorted Constants */
#define MPI_ANY_SOURCE     (-1)
#define MPI_ANY_TAG        (-2)
#define MPI_PROC_NULL      (-3)
#define MPI_ROOT           (-4)
#define MPI_UNDEFINED      (-32766)

/* Thread Constants */
#define MPI_THREAD_SINGLE     0
#define MPI_THREAD_FUNNELED   1024
#define MPI_THREAD_SERIALIZED 2048
#define MPI_THREAD_MULTIPLE   4096

/* Comparison Results */
#define MPI_IDENT     201
#define MPI_CONGRUENT 202
#define MPI_SIMILAR   203
#define MPI_UNEQUAL   204

/* Window Locks and Flavors */
#define MPI_LOCK_EXCLUSIVE       301
#define MPI_LOCK_SHARED          302
#define MPI_WIN_FLAVOR_CREATE    311
#define MPI_WIN_FLAVOR_ALLOCATE  312
#define MPI_WIN_FLAVOR_DYNAMIC   313
#define MPI_WIN_FLAVOR_SHARED    314
#define MPI_WIN_UNIFIED          321
#define MPI_WIN_SEPARATE         322

/* Attributes */
#define MPI_KEYVAL_INVALID    0
#define MPI_TAG_UB            501
#define MPI_IO                502
#define MPI_HOST              503
#define MPI_WTIME_IS_GLOBAL   504

/* Predefined Opaque Handles (Cast to struct pointers per ABI) */
#define MPI_COMM_NULL  ((MPI_Comm)(intptr_t)256)
#define MPI_COMM_WORLD ((MPI_Comm)(intptr_t)257)
#define MPI_COMM_SELF  ((MPI_Comm)(intptr_t)258)

#define MPI_GROUP_NULL  ((MPI_Group)(intptr_t)264)
#define MPI_GROUP_EMPTY ((MPI_Group)(intptr_t)265)

#define MPI_REQUEST_NULL ((MPI_Request)(intptr_t)384)
#define MPI_FILE_NULL    ((MPI_File)(intptr_t)280)
#define MPI_INFO_NULL    ((MPI_Info)(intptr_t)304)
#define MPI_WIN_NULL     ((MPI_Win)(intptr_t)272)
#define MPI_ERRHANDLER_NULL ((MPI_Errhandler)(intptr_t)320)
#define MPI_MESSAGE_NULL    ((MPI_Message)(intptr_t)296)

#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)(intptr_t)321)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)(intptr_t)323)

/* Predefined Datatypes */
#define MPI_DATATYPE_NULL      ((MPI_Datatype)(intptr_t)512)
#define MPI_AINT               ((MPI_Datatype)(intptr_t)513)
#define MPI_COUNT              ((MPI_Datatype)(intptr_t)514)
#define MPI_OFFSET             ((MPI_Datatype)(intptr_t)515)
#define MPI_PACKED             ((MPI_Datatype)(intptr_t)519)
#define MPI_SHORT              ((MPI_Datatype)(intptr_t)520)
#define MPI_INT                ((MPI_Datatype)(intptr_t)521)
#define MPI_LONG               ((MPI_Datatype)(intptr_t)522)
#define MPI_LONG_LONG_INT      ((MPI_Datatype)(intptr_t)523)
#define MPI_LONG_LONG          ((MPI_Datatype)(intptr_t)523)
#define MPI_UNSIGNED_SHORT     ((MPI_Datatype)(intptr_t)524)
#define MPI_UNSIGNED           ((MPI_Datatype)(intptr_t)525)
#define MPI_UNSIGNED_LONG      ((MPI_Datatype)(intptr_t)526)
#define MPI_UNSIGNED_LONG_LONG ((MPI_Datatype)(intptr_t)527)
#define MPI_FLOAT              ((MPI_Datatype)(intptr_t)528)
#define MPI_C_COMPLEX          ((MPI_Datatype)(intptr_t)530)
#define MPI_C_FLOAT_COMPLEX    ((MPI_Datatype)(intptr_t)530)
#define MPI_DOUBLE             ((MPI_Datatype)(intptr_t)532)
#define MPI_C_DOUBLE_COMPLEX   ((MPI_Datatype)(intptr_t)534)
#define MPI_LONG_DOUBLE        ((MPI_Datatype)(intptr_t)544)
#define MPI_C_LONG_DOUBLE_COMPLEX ((MPI_Datatype)(intptr_t)548)
#define MPI_C_BOOL             ((MPI_Datatype)(intptr_t)568)
#define MPI_INT8_T             ((MPI_Datatype)(intptr_t)576)
#define MPI_UINT8_T            ((MPI_Datatype)(intptr_t)577)
#define MPI_CHAR               ((MPI_Datatype)(intptr_t)579)
#define MPI_SIGNED_CHAR        ((MPI_Datatype)(intptr_t)580)
#define MPI_UNSIGNED_CHAR      ((MPI_Datatype)(intptr_t)581)
#define MPI_BYTE               ((MPI_Datatype)(intptr_t)583)
#define MPI_INT16_T            ((MPI_Datatype)(intptr_t)584)
#define MPI_UINT16_T           ((MPI_Datatype)(intptr_t)585)
#define MPI_INT32_T            ((MPI_Datatype)(intptr_t)592)
#define MPI_UINT32_T           ((MPI_Datatype)(intptr_t)593)
#define MPI_INT64_T            ((MPI_Datatype)(intptr_t)600)
#define MPI_UINT64_T           ((MPI_Datatype)(intptr_t)601)

/* Datatypes for reduction functions */
#define MPI_FLOAT_INT          ((MPI_Datatype)(intptr_t)552)
#define MPI_DOUBLE_INT         ((MPI_Datatype)(intptr_t)553)
#define MPI_LONG_INT           ((MPI_Datatype)(intptr_t)554)
#define MPI_2INT               ((MPI_Datatype)(intptr_t)555)
#define MPI_SHORT_INT          ((MPI_Datatype)(intptr_t)556)
#define MPI_LONG_DOUBLE_INT    ((MPI_Datatype)(intptr_t)557)
#define MPI_2REAL              ((MPI_Datatype)(intptr_t)560)
#define MPI_2DOUBLE_PRECISION  ((MPI_Datatype)(intptr_t)561)
#define MPI_2INTEGER           ((MPI_Datatype)(intptr_t)562)

/* Predefined Operators */
#define MPI_OP_NULL ((MPI_Op)(intptr_t)32)
#define MPI_SUM     ((MPI_Op)(intptr_t)33)
#define MPI_MIN     ((MPI_Op)(intptr_t)34)
#define MPI_MAX     ((MPI_Op)(intptr_t)35)
#define MPI_PROD    ((MPI_Op)(intptr_t)36)
#define MPI_BAND    ((MPI_Op)(intptr_t)40)
#define MPI_BOR     ((MPI_Op)(intptr_t)41)
#define MPI_BXOR    ((MPI_Op)(intptr_t)42)
#define MPI_LAND    ((MPI_Op)(intptr_t)48)
#define MPI_LOR     ((MPI_Op)(intptr_t)49)
#define MPI_LXOR    ((MPI_Op)(intptr_t)50)
#define MPI_MINLOC  ((MPI_Op)(intptr_t)56)
#define MPI_MAXLOC  ((MPI_Op)(intptr_t)57)
#define MPI_REPLACE ((MPI_Op)(intptr_t)60)
#define MPI_NO_OP   ((MPI_Op)(intptr_t)61)

/* Combiner Types */
#define MPI_COMBINER_NAMED 101

/* Callback Prototypes */
typedef void MPI_User_function(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype);
typedef int MPI_Comm_copy_attr_function(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Comm_delete_attr_function(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef void MPI_Comm_errhandler_function(MPI_Comm *, int *, ...);
typedef MPI_Comm_errhandler_function MPI_Comm_errhandler_fn;

/* Deprecated Callbacks (Crucial for HDF5 / PETSc Legacy Support) */
typedef void (MPI_Handler_function)(MPI_Comm *, int *, ...);
typedef int (MPI_Copy_function)(MPI_Comm, int, void *, void *, void *, int *);
typedef int (MPI_Delete_function)(MPI_Comm, int, void *, void *);

#define MPI_COMM_NULL_COPY_FN ((MPI_Comm_copy_attr_function*)0)
#define MPI_COMM_NULL_DELETE_FN ((MPI_Comm_delete_attr_function*)0)

/* =========================================================================
 * APPENDIX A.3: C BINDINGS
 * ========================================================================= */

/* --- A.3.1 Point-to-Point Communication --- */
int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Cancel(MPI_Request *request);
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Request_free(MPI_Request *request);
int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status);
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Start(MPI_Request *request);
int MPI_Startall(int count, MPI_Request array_of_requests[]);
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
int MPI_Wait(MPI_Request *request, MPI_Status *status);
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status);

/* --- A.3.3 Datatypes --- */
int MPI_Get_address(const void *location, MPI_Aint *address);
int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count);
int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
int MPI_Type_commit(MPI_Datatype *datatype);
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
int MPI_Type_create_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_free(MPI_Datatype *datatype);
int MPI_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]);
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent);
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
int MPI_Type_size(MPI_Datatype datatype, int *size);
int MPI_Type_struct(int count, const int *array_of_blocklengths, const MPI_Aint *array_of_displacements, const MPI_Datatype *array_of_types, MPI_Datatype *newtype);
int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);

/* --- A.3.4 Collective Communication --- */
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Barrier(MPI_Comm comm);
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request);
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op);
int MPI_Op_free(MPI_Op *op);
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

/* --- A.3.5 Groups, Contexts, Communicators, and Caching --- */
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_free(MPI_Comm *comm);
int MPI_Comm_free_keyval(int *comm_keyval);
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_free(MPI_Group *group);
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_rank(MPI_Group group, int *rank);
int MPI_Group_size(MPI_Group group, int *size);
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]);
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);

/* --- A.3.7 MPI Environmental Management --- */
int MPI_Abort(MPI_Comm comm, int errorcode);
int MPI_Add_error_class(int *errorclass);
int MPI_Add_error_code(int errorclass, int *errorcode);
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_fn *function, MPI_Errhandler *errhandler);
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler);
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler);
int MPI_Errhandler_free(MPI_Errhandler *errhandler);
int MPI_Error_class(int errorcode, int *errorclass);
int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_Get_library_version(char *version, int *resultlen);
int MPI_Get_processor_name(char *name, int *resultlen);
int MPI_Get_version(int *version, int *subversion);
int MPI_Init(int *argc, char ***argv);
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
int MPI_Initialized(int *flag);
int MPI_Finalize(void);
int MPI_Finalized(int *flag);
double MPI_Wtime(void);

/* --- A.3.8 The Info Object --- */
int MPI_Info_create(MPI_Info *info);
int MPI_Info_delete(MPI_Info info, const char *key);
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
int MPI_Info_free(MPI_Info *info);
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag);
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag);
int MPI_Info_set(MPI_Info info, const char *key, const char *value);

/* --- A.3.10 One-Sided Communications --- */
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Win_complete(MPI_Win win);
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_fence(int assert, MPI_Win win);
int MPI_Win_free(MPI_Win *win);
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_unlock(int rank, MPI_Win win);
int MPI_Win_wait(MPI_Win win);

/* --- A.3.12 I/O --- */
int MPI_File_close(MPI_File *fh);
int MPI_File_delete(const char *filename, MPI_Info info);
int MPI_File_get_atomicity(MPI_File fh, int *flag);
int MPI_File_get_info(MPI_File fh, MPI_Info *info_used);
int MPI_File_get_size(MPI_File fh, MPI_Offset *size);
int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh);
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_set_atomicity(MPI_File fh, int flag);
int MPI_File_set_size(MPI_File fh, MPI_Offset size);
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info);
int MPI_File_sync(MPI_File fh);
int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);

/* --- A.3.13 Language Bindings --- */
MPI_Comm MPI_Comm_f2c(MPI_Fint comm);
MPI_Fint MPI_Comm_c2f(MPI_Comm comm);
MPI_Errhandler MPI_Errhandler_f2c(MPI_Fint errhandler);
MPI_Fint MPI_Errhandler_c2f(MPI_Errhandler errhandler);
MPI_Group MPI_Group_f2c(MPI_Fint group);
MPI_Fint MPI_Group_c2f(MPI_Group group);
MPI_Info MPI_Info_f2c(MPI_Fint info);
MPI_Fint MPI_Info_c2f(MPI_Info info);
MPI_Op MPI_Op_f2c(MPI_Fint op);
MPI_Fint MPI_Op_c2f(MPI_Op op);
MPI_Request MPI_Request_f2c(MPI_Fint request);
MPI_Fint MPI_Request_c2f(MPI_Request request);
MPI_Datatype MPI_Type_f2c(MPI_Fint datatype);
MPI_Fint MPI_Type_c2f(MPI_Datatype datatype);
MPI_Win MPI_Win_f2c(MPI_Fint win);
MPI_Fint MPI_Win_c2f(MPI_Win win);

/* --- A.3.14 Application Binary Interface (ABI) --- */
int MPI_Abi_get_version(int *abi_major, int *abi_minor);
int MPI_Comm_toint(MPI_Comm comm);
MPI_Comm MPI_Comm_fromint(int comm);
int MPI_Type_toint(MPI_Datatype datatype);
MPI_Datatype MPI_Type_fromint(int datatype);
int MPI_Group_toint(MPI_Group group);
MPI_Group MPI_Group_fromint(int group);
int MPI_Request_toint(MPI_Request request);
MPI_Request MPI_Request_fromint(int request);
int MPI_File_toint(MPI_File file);
MPI_File MPI_File_fromint(int file);
int MPI_Win_toint(MPI_Win win);
MPI_Win MPI_Win_fromint(int win);
int MPI_Op_toint(MPI_Op op);
MPI_Op MPI_Op_fromint(int op);
int MPI_Info_toint(MPI_Info info);
MPI_Info MPI_Info_fromint(int info);
int MPI_Errhandler_toint(MPI_Errhandler errhandler);
MPI_Errhandler MPI_Errhandler_fromint(int errhandler);

/* --- A.3.17 Deprecated C Bindings --- */
int MPI_Attr_delete(MPI_Comm comm, int keyval);
int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag);
int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val);
int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state);
int MPI_Keyval_free(int *keyval);
int MPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count);
int MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent);
int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent);
int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size);

#ifdef __cplusplus
}
#endif

#endif /* MPI_STUB_H */