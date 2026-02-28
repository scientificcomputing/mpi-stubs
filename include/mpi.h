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
#define MPI_VERSION 5
#define MPI_SUBVERSION 0
#define MPI_ABI_VERSION 1
#define MPI_ABI_SUBVERSION 0

/* 20.3.1 The Status Object */
typedef struct {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int MPI_internal[5]; /* 0: count, 1: cancelled */
} MPI_Status;

typedef struct {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int MPI_internal[5];
} MPI_F08_status;

/* 20.3.2 Opaque Handles */
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

/* MPI_T Tool Interface Handles */
typedef struct MPI_ABI_T_enum* MPI_T_enum;
typedef struct MPI_ABI_T_cvar_handle* MPI_T_cvar_handle;
typedef struct MPI_ABI_T_pvar_handle* MPI_T_pvar_handle;
typedef struct MPI_ABI_T_pvar_session* MPI_T_pvar_session;
typedef struct MPI_ABI_T_event_instance* MPI_T_event_instance;
typedef struct MPI_ABI_T_event_registration* MPI_T_event_registration;

typedef int MPI_T_source_order;
typedef int MPI_T_cb_safety;

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
#define MPI_ERR_PENDING              18
#define MPI_ERR_IN_STATUS            19
#define MPI_ERR_ACCESS               20
#define MPI_ERR_AMODE                21
#define MPI_ERR_ASSERT               22
#define MPI_ERR_BAD_FILE             23
#define MPI_ERR_BASE                 24
#define MPI_ERR_CONVERSION           25
#define MPI_ERR_DISP                 26
#define MPI_ERR_DUP_DATAREP          27
#define MPI_ERR_FILE_EXISTS          28
#define MPI_ERR_FILE_IN_USE          29
#define MPI_ERR_FILE                 30
#define MPI_ERR_INFO_KEY             31
#define MPI_ERR_INFO_NOKEY           32
#define MPI_ERR_INFO_VALUE           33
#define MPI_ERR_INFO                 34
#define MPI_ERR_IO                   35
#define MPI_ERR_KEYVAL               36
#define MPI_ERR_LOCKTYPE             37
#define MPI_ERR_NAME                 38
#define MPI_ERR_NO_MEM               39
#define MPI_ERR_NOT_SAME             40
#define MPI_ERR_NO_SPACE             41
#define MPI_ERR_NO_SUCH_FILE         42
#define MPI_ERR_PORT                 43
#define MPI_ERR_QUOTA                44
#define MPI_ERR_READ_ONLY            45
#define MPI_ERR_RMA_ATTACH           46
#define MPI_ERR_RMA_CONFLICT         47
#define MPI_ERR_RMA_RANGE            48
#define MPI_ERR_RMA_SHARED           49
#define MPI_ERR_RMA_SYNC             50
#define MPI_ERR_SERVICE              51
#define MPI_ERR_SIZE                 52
#define MPI_ERR_SPAWN                53
#define MPI_ERR_UNSUPPORTED_DATAREP  54
#define MPI_ERR_UNSUPPORTED_OPERATION 55
#define MPI_ERR_WIN                  56
#define MPI_ERR_RMA_FLAVOR           57
#define MPI_ERR_PROC_ABORTED         58
#define MPI_ERR_VALUE_TOO_LARGE      59
#define MPI_ERR_SESSION              60
#define MPI_ERR_ERRHANDLER           61
#define MPI_ERR_ABI                  62
#define MPI_ERR_LASTCODE             16383

/* Buffer & Ignored Input Constants */
#define MPI_BOTTOM            ((void*)0)
#define MPI_IN_PLACE          ((void*)1)
#define MPI_BUFFER_AUTOMATIC  ((void*)2)
#define MPI_ARGVS_NULL        ((char***)0)
#define MPI_ARGV_NULL         ((char**)0)
#define MPI_ERRCODES_IGNORE   ((int*)0)
#define MPI_STATUSES_IGNORE   ((MPI_Status*)0)
#define MPI_STATUS_IGNORE     ((MPI_Status*)0)
#define MPI_UNWEIGHTED        ((int*)10)
#define MPI_WEIGHTS_EMPTY     ((int*)11)

/* String Limits */
#define MPI_MAX_DATAREP_STRING         128
#define MPI_MAX_ERROR_STRING           512
#define MPI_MAX_INFO_KEY               256
#define MPI_MAX_INFO_VAL               1024
#define MPI_MAX_LIBRARY_VERSION_STRING 8192
#define MPI_MAX_OBJECT_NAME            128
#define MPI_MAX_PORT_NAME              1024
#define MPI_MAX_PROCESSOR_NAME         256
#define MPI_MAX_STRINGTAG_LEN          1024
#define MPI_MAX_PSET_NAME_LEN          1024

/* Mode & Assorted Constants */
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

#define MPI_ANY_SOURCE     (-1)
#define MPI_ANY_TAG        (-2)
#define MPI_PROC_NULL      (-3)
#define MPI_ROOT           (-4)
#define MPI_UNDEFINED      (-32766)
#define MPI_BSEND_OVERHEAD 512

#define MPI_THREAD_SINGLE     0
#define MPI_THREAD_FUNNELED   1024
#define MPI_THREAD_SERIALIZED 2048
#define MPI_THREAD_MULTIPLE   4096

#define MPI_ORDER_C             12
#define MPI_ORDER_FORTRAN       15
#define MPI_DISTRIBUTE_NONE     16
#define MPI_DISTRIBUTE_BLOCK    17
#define MPI_DISTRIBUTE_CYCLIC   18
#define MPI_DISTRIBUTE_DFLT_DARG 19

#define MPI_COMBINER_NAMED           101
#define MPI_COMBINER_DUP             102
#define MPI_COMBINER_CONTIGUOUS      103
#define MPI_COMBINER_VECTOR          104
#define MPI_COMBINER_HVECTOR         105
#define MPI_COMBINER_INDEXED         106
#define MPI_COMBINER_HINDEXED        107
#define MPI_COMBINER_INDEXED_BLOCK   108
#define MPI_COMBINER_HINDEXED_BLOCK  109
#define MPI_COMBINER_STRUCT          110
#define MPI_COMBINER_SUBARRAY        111
#define MPI_COMBINER_DARRAY          112
#define MPI_COMBINER_F90_REAL        113
#define MPI_COMBINER_F90_COMPLEX     114
#define MPI_COMBINER_F90_INTEGER     115
#define MPI_COMBINER_RESIZED         116
#define MPI_COMBINER_VALUE_INDEX     117

#define MPI_TYPECLASS_INTEGER 192
#define MPI_TYPECLASS_REAL    193
#define MPI_TYPECLASS_COMPLEX 194

#define MPI_IDENT     201
#define MPI_CONGRUENT 202
#define MPI_SIMILAR   203
#define MPI_UNEQUAL   204

#define MPI_CART       211
#define MPI_GRAPH      212
#define MPI_DIST_GRAPH 213

#define MPI_COMM_TYPE_SHARED          221
#define MPI_COMM_TYPE_HW_UNGUIDED     222
#define MPI_COMM_TYPE_HW_GUIDED       223
#define MPI_COMM_TYPE_RESOURCE_GUIDED 224

#define MPI_LOCK_EXCLUSIVE       301
#define MPI_LOCK_SHARED          302
#define MPI_WIN_FLAVOR_CREATE    311
#define MPI_WIN_FLAVOR_ALLOCATE  312
#define MPI_WIN_FLAVOR_DYNAMIC   313
#define MPI_WIN_FLAVOR_SHARED    314
#define MPI_WIN_UNIFIED          321
#define MPI_WIN_SEPARATE         322

#define MPI_SEEK_CUR 401
#define MPI_SEEK_END 402
#define MPI_SEEK_SET 403
#define MPI_DISPLACEMENT_CURRENT (-1)

#define MPI_KEYVAL_INVALID    0
#define MPI_TAG_UB            501
#define MPI_IO                502
#define MPI_HOST              503
#define MPI_WTIME_IS_GLOBAL   504
#define MPI_APPNUM            505
#define MPI_LASTUSEDCODE      506
#define MPI_UNIVERSE_SIZE     507
#define MPI_WIN_BASE          601
#define MPI_WIN_DISP_UNIT     602
#define MPI_WIN_SIZE          603
#define MPI_WIN_CREATE_FLAVOR 604
#define MPI_WIN_MODEL         605

/* Tool Interface (MPI_T) Constants */
#define MPI_T_ENUM_NULL            ((MPI_T_enum)0)
#define MPI_T_CVAR_HANDLE_NULL     ((MPI_T_cvar_handle)0)
#define MPI_T_PVAR_HANDLE_NULL     ((MPI_T_pvar_handle)0)
#define MPI_T_PVAR_SESSION_NULL    ((MPI_T_pvar_session)0)
#define MPI_T_PVAR_ALL_HANDLES     ((MPI_T_pvar_handle)1)

#define MPI_T_VERBOSITY_USER_BASIC    0x09
#define MPI_T_VERBOSITY_USER_DETAIL   0x0a
#define MPI_T_VERBOSITY_USER_ALL      0x0c
#define MPI_T_VERBOSITY_TUNER_BASIC   0x11
#define MPI_T_VERBOSITY_TUNER_DETAIL  0x12
#define MPI_T_VERBOSITY_TUNER_ALL     0x14
#define MPI_T_VERBOSITY_MPIDEV_BASIC  0x21
#define MPI_T_VERBOSITY_MPIDEV_DETAIL 0x22
#define MPI_T_VERBOSITY_MPIDEV_ALL    0x24

#define MPI_T_BIND_NO_OBJECT       1
#define MPI_T_BIND_MPI_COMM        2
#define MPI_T_BIND_MPI_DATATYPE    3
#define MPI_T_BIND_MPI_ERRHANDLER  4
#define MPI_T_BIND_MPI_FILE        5
#define MPI_T_BIND_MPI_GROUP       6
#define MPI_T_BIND_MPI_OP          7
#define MPI_T_BIND_MPI_REQUEST     8
#define MPI_T_BIND_MPI_WIN         9
#define MPI_T_BIND_MPI_MESSAGE     10
#define MPI_T_BIND_MPI_INFO        11
#define MPI_T_BIND_MPI_SESSION     12

#define MPI_T_SCOPE_CONSTANT       1
#define MPI_T_SCOPE_READONLY       2
#define MPI_T_SCOPE_LOCAL          3
#define MPI_T_SCOPE_GROUP          4
#define MPI_T_SCOPE_GROUP_EQ       5
#define MPI_T_SCOPE_ALL            6
#define MPI_T_SCOPE_ALL_EQ         7

#define MPI_T_PVAR_CLASS_STATE          1
#define MPI_T_PVAR_CLASS_LEVEL          2
#define MPI_T_PVAR_CLASS_SIZE           3
#define MPI_T_PVAR_CLASS_PERCENTAGE     4
#define MPI_T_PVAR_CLASS_HIGHWATERMARK  5
#define MPI_T_PVAR_CLASS_LOWWATERMARK   6
#define MPI_T_PVAR_CLASS_COUNTER        7
#define MPI_T_PVAR_CLASS_AGGREGATE      8
#define MPI_T_PVAR_CLASS_TIMER          9
#define MPI_T_PVAR_CLASS_GENERIC        10

#define MPI_T_SOURCE_ORDERED    1
#define MPI_T_SOURCE_UNORDERED  2

#define MPI_T_CB_REQUIRE_NONE              0x00
#define MPI_T_CB_REQUIRE_MPI_RESTRICTED    0x03
#define MPI_T_CB_REQUIRE_THREAD_SAFE       0x0F
#define MPI_T_CB_REQUIRE_ASYNC_SIGNAL_SAFE 0x3F

/* Predefined Opaque Handles */
#define MPI_COMM_NULL  ((MPI_Comm)(intptr_t)256)
#define MPI_COMM_WORLD ((MPI_Comm)(intptr_t)257)
#define MPI_COMM_SELF  ((MPI_Comm)(intptr_t)258)

#define MPI_GROUP_NULL  ((MPI_Group)(intptr_t)264)
#define MPI_GROUP_EMPTY ((MPI_Group)(intptr_t)265)

#define MPI_REQUEST_NULL ((MPI_Request)(intptr_t)384)
#define MPI_FILE_NULL    ((MPI_File)(intptr_t)280)
#define MPI_INFO_NULL    ((MPI_Info)(intptr_t)304)
#define MPI_INFO_ENV     ((MPI_Info)(intptr_t)305)
#define MPI_SESSION_NULL ((MPI_Session)(intptr_t)288)
#define MPI_WIN_NULL     ((MPI_Win)(intptr_t)272)
#define MPI_MESSAGE_NULL    ((MPI_Message)(intptr_t)296)
#define MPI_MESSAGE_NO_PROC ((MPI_Message)(intptr_t)297)

#define MPI_ERRHANDLER_NULL  ((MPI_Errhandler)(intptr_t)320)
#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)(intptr_t)321)
#define MPI_ERRORS_ABORT     ((MPI_Errhandler)(intptr_t)322)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)(intptr_t)323)

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
#define MPI_CXX_FLOAT_COMPLEX  ((MPI_Datatype)(intptr_t)531)
#define MPI_DOUBLE             ((MPI_Datatype)(intptr_t)532)
#define MPI_C_DOUBLE_COMPLEX   ((MPI_Datatype)(intptr_t)534)
#define MPI_CXX_DOUBLE_COMPLEX ((MPI_Datatype)(intptr_t)535)
#define MPI_LOGICAL            ((MPI_Datatype)(intptr_t)536)
#define MPI_INTEGER            ((MPI_Datatype)(intptr_t)537)
#define MPI_REAL               ((MPI_Datatype)(intptr_t)538)
#define MPI_COMPLEX            ((MPI_Datatype)(intptr_t)539)
#define MPI_DOUBLE_PRECISION   ((MPI_Datatype)(intptr_t)540)
#define MPI_DOUBLE_COMPLEX     ((MPI_Datatype)(intptr_t)541)
#define MPI_CHARACTER          ((MPI_Datatype)(intptr_t)542)
#define MPI_LONG_DOUBLE        ((MPI_Datatype)(intptr_t)544)
#define MPI_C_LONG_DOUBLE_COMPLEX ((MPI_Datatype)(intptr_t)548)
#define MPI_CXX_LONG_DOUBLE_COMPLEX ((MPI_Datatype)(intptr_t)549)
#define MPI_FLOAT_INT          ((MPI_Datatype)(intptr_t)552)
#define MPI_DOUBLE_INT         ((MPI_Datatype)(intptr_t)553)
#define MPI_LONG_INT           ((MPI_Datatype)(intptr_t)554)
#define MPI_2INT               ((MPI_Datatype)(intptr_t)555)
#define MPI_SHORT_INT          ((MPI_Datatype)(intptr_t)556)
#define MPI_LONG_DOUBLE_INT    ((MPI_Datatype)(intptr_t)557)
#define MPI_2REAL              ((MPI_Datatype)(intptr_t)560)
#define MPI_2DOUBLE_PRECISION  ((MPI_Datatype)(intptr_t)561)
#define MPI_2INTEGER           ((MPI_Datatype)(intptr_t)562)
#define MPI_C_BOOL             ((MPI_Datatype)(intptr_t)568)
#define MPI_CXX_BOOL           ((MPI_Datatype)(intptr_t)569)
#define MPI_WCHAR              ((MPI_Datatype)(intptr_t)572)
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

/* Fortran Optional Types */
#define MPI_LOGICAL1           ((MPI_Datatype)(intptr_t)704)
#define MPI_INTEGER1           ((MPI_Datatype)(intptr_t)705)
#define MPI_LOGICAL2           ((MPI_Datatype)(intptr_t)712)
#define MPI_INTEGER2           ((MPI_Datatype)(intptr_t)713)
#define MPI_REAL2              ((MPI_Datatype)(intptr_t)714)
#define MPI_LOGICAL4           ((MPI_Datatype)(intptr_t)720)
#define MPI_INTEGER4           ((MPI_Datatype)(intptr_t)721)
#define MPI_REAL4              ((MPI_Datatype)(intptr_t)722)
#define MPI_COMPLEX4           ((MPI_Datatype)(intptr_t)723)
#define MPI_LOGICAL8           ((MPI_Datatype)(intptr_t)728)
#define MPI_INTEGER8           ((MPI_Datatype)(intptr_t)729)
#define MPI_REAL8              ((MPI_Datatype)(intptr_t)730)
#define MPI_COMPLEX8           ((MPI_Datatype)(intptr_t)731)
#define MPI_LOGICAL16          ((MPI_Datatype)(intptr_t)736)
#define MPI_INTEGER16          ((MPI_Datatype)(intptr_t)737)
#define MPI_REAL16             ((MPI_Datatype)(intptr_t)738)
#define MPI_COMPLEX16          ((MPI_Datatype)(intptr_t)739)
#define MPI_COMPLEX32          ((MPI_Datatype)(intptr_t)747)

/* Callbacks & User Functions */
typedef void MPI_User_function(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype);
typedef void MPI_User_function_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype *datatype);
typedef int MPI_Comm_copy_attr_function(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Comm_delete_attr_function(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int MPI_Win_copy_attr_function(MPI_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Win_delete_attr_function(MPI_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int MPI_Type_copy_attr_function(MPI_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Type_delete_attr_function(MPI_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void MPI_Comm_errhandler_function(MPI_Comm *comm, int *error_code, ...);
typedef void MPI_Win_errhandler_function(MPI_Win *win, int *error_code, ...);
typedef void MPI_File_errhandler_function(MPI_File *file, int *error_code, ...);
typedef void MPI_Session_errhandler_function(MPI_Session session, int *error_code, ...);
typedef int MPI_Grequest_query_function(void *extra_state, MPI_Status *status);
typedef int MPI_Grequest_free_function(void *extra_state);
typedef int MPI_Grequest_cancel_function(void *extra_state, int complete);
typedef int MPI_Datarep_extent_function(MPI_Datatype datatype, MPI_Aint *extent, void *extra_state);
typedef int MPI_Datarep_conversion_function(void *userbuf, MPI_Datatype datatype, int count, void *filebuf, MPI_Offset position, void *extra_state);
typedef int MPI_Datarep_conversion_function_c(void *userbuf, MPI_Datatype datatype, MPI_Count count, void *filebuf, MPI_Offset position, void *extra_state);
typedef void MPI_T_event_cb_function(MPI_T_event_instance event_instance, MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, void *user_data);
typedef void MPI_T_event_free_cb_function(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, void *user_data);
typedef void MPI_T_event_dropped_cb_function(MPI_Count count, MPI_T_event_registration event_registration, int source_index, MPI_T_cb_safety cb_safety, void *user_data);

/* Deprecated Callbacks */
typedef void (MPI_Handler_function)(MPI_Comm *, int *, ...);
typedef int (MPI_Copy_function)(MPI_Comm, int, void *, void *, void *, int *);
typedef int (MPI_Delete_function)(MPI_Comm, int, void *, void *);
/* --- FIX: Backwards compatibility aliases required by PETSc --- */
typedef MPI_Comm_errhandler_function MPI_Comm_errhandler_fn;
typedef MPI_File_errhandler_function MPI_File_errhandler_fn;
typedef MPI_Win_errhandler_function MPI_Win_errhandler_fn;

#define MPI_COMM_NULL_COPY_FN ((MPI_Comm_copy_attr_function*)0)
#define MPI_COMM_NULL_DELETE_FN ((MPI_Comm_delete_attr_function*)0)
#define MPI_COMM_DUP_FN ((MPI_Comm_copy_attr_function*)1)
#define MPI_WIN_NULL_COPY_FN ((MPI_Win_copy_attr_function*)0)
#define MPI_WIN_NULL_DELETE_FN ((MPI_Win_delete_attr_function*)0)
#define MPI_WIN_DUP_FN ((MPI_Win_copy_attr_function*)1)
#define MPI_TYPE_NULL_COPY_FN ((MPI_Type_copy_attr_function*)0)
#define MPI_TYPE_NULL_DELETE_FN ((MPI_Type_delete_attr_function*)0)
#define MPI_TYPE_DUP_FN ((MPI_Type_copy_attr_function*)1)
#define MPI_CONVERSION_FN_NULL ((MPI_Datarep_conversion_function*)0)
#define MPI_CONVERSION_FN_NULL_C ((MPI_Datarep_conversion_function_c*)0)

/* =========================================================================
 * APPENDIX A.3: C BINDINGS (ALL FUNCTIONS)
 * ========================================================================= */

/* --- A.3.1 Point-to-Point Communication --- */
int MPI_Bsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Bsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Buffer_attach_c(void *buffer, MPI_Count size);
int MPI_Buffer_attach(void *buffer, int size);
int MPI_Buffer_detach_c(void *buffer_addr, MPI_Count *size);
int MPI_Buffer_detach(void *buffer_addr, int *size);
int MPI_Buffer_flush(void);
int MPI_Buffer_iflush(MPI_Request *request);
int MPI_Cancel(MPI_Request *request);
int MPI_Comm_attach_buffer_c(MPI_Comm comm, void *buffer, MPI_Count size);
int MPI_Comm_attach_buffer(MPI_Comm comm, void *buffer, int size);
int MPI_Comm_detach_buffer_c(MPI_Comm comm, void *buffer_addr, MPI_Count *size);
int MPI_Comm_detach_buffer(MPI_Comm comm, void *buffer_addr, int *size);
int MPI_Comm_flush_buffer(MPI_Comm comm);
int MPI_Comm_iflush_buffer(MPI_Comm comm, MPI_Request *request);
int MPI_Get_count_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);
int MPI_Ibsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status);
int MPI_Imrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request);
int MPI_Imrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request);
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
int MPI_Irecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Isend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Isendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int MPI_Isendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int MPI_Isendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int MPI_Isendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Issend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status);
int MPI_Mrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status);
int MPI_Mrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status);
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Recv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Recv_init_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Request_free(MPI_Request *request);
int MPI_Request_get_status_all(int count, const MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
int MPI_Request_get_status_any(int count, const MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
int MPI_Request_get_status_some(int incount, const MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status);
int MPI_Rsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Rsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Rsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Send_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Send_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Sendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int MPI_Sendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, 
                         int dest, int sendtag, int source, int recvtag, 
                         MPI_Comm comm, MPI_Status *status);
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Session_attach_buffer_c(MPI_Session session, void *buffer, MPI_Count size);
int MPI_Session_attach_buffer(MPI_Session session, void *buffer, int size);
int MPI_Session_detach_buffer_c(MPI_Session session, void *buffer_addr, MPI_Count *size);
int MPI_Session_detach_buffer(MPI_Session session, void *buffer_addr, int *size);
int MPI_Session_flush_buffer(MPI_Session session);
int MPI_Session_iflush_buffer(MPI_Session session, MPI_Request *request);
int MPI_Ssend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Ssend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Startall(int count, MPI_Request array_of_requests[]);
int MPI_Start(MPI_Request *request);
int MPI_Status_get_error(const MPI_Status *status, int *err);
int MPI_Status_get_source(const MPI_Status *status, int *source);
int MPI_Status_get_tag(const MPI_Status *status, int *tag);
int MPI_Test_cancelled(const MPI_Status *status, int *flag);
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status);
int MPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
int MPI_Wait(MPI_Request *request, MPI_Status *status);

/* --- A.3.2 Partitioned Communication --- */
int MPI_Parrived(MPI_Request request, int partition, int *flag);
int MPI_Pready_list(int length, const int array_of_partitions[], MPI_Request request);
int MPI_Pready_range(int partition_low, int partition_high, MPI_Request request);
int MPI_Pready(int partition, MPI_Request request);
int MPI_Precv_init(void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Psend_init(const void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request);

/* --- A.3.3 Datatypes --- */
int MPI_Get_address(const void *location, MPI_Aint *address);
int MPI_Get_elements_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count);
int MPI_Pack_c(const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position, MPI_Comm comm);
int MPI_Pack_external_c(const char datarep[], const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position);
int MPI_Pack_external_size_c(const char datarep[], MPI_Count incount, MPI_Datatype datatype, MPI_Count *size);
int MPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size);
int MPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position);
int MPI_Pack_size_c(MPI_Count incount, MPI_Datatype datatype, MPI_Comm comm, MPI_Count *size);
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
int MPI_Type_commit(MPI_Datatype *datatype);
int MPI_Type_contiguous_c(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_darray_c(int size, int rank, int ndims, const MPI_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hvector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_indexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_resized_c(MPI_Datatype oldtype, MPI_Count lb, MPI_Count extent, MPI_Datatype *newtype);
int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
int MPI_Type_create_struct_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int MPI_Type_create_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int MPI_Type_create_subarray_c(int ndims, const MPI_Count array_of_sizes[], const MPI_Count array_of_subsizes[], const MPI_Count array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_free(MPI_Datatype *datatype);
int MPI_Type_get_contents_c(MPI_Datatype datatype, MPI_Count max_integers, MPI_Count max_addresses, MPI_Count max_large_counts, MPI_Count max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[]);
int MPI_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]);
int MPI_Type_get_envelope_c(MPI_Datatype datatype, MPI_Count *num_integers, MPI_Count *num_addresses, MPI_Count *num_large_counts, MPI_Count *num_datatypes, int *combiner);
int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
int MPI_Type_get_extent_c(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent);
int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent);
int MPI_Type_get_true_extent_c(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent);
int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
int MPI_Type_indexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_size_c(MPI_Datatype datatype, MPI_Count *size);
int MPI_Type_size(MPI_Datatype datatype, int *size);
int MPI_Type_vector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Unpack_c(const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype, MPI_Comm comm);
int MPI_Unpack_external_c(const char datarep[], const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype);
int MPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype);
int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);

/* --- A.3.4 Collective Communication --- */
int MPI_Allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Allreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Allreduce_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int MPI_Alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Barrier_init(MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Barrier(MPI_Comm comm);
int MPI_Bcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm);
int MPI_Bcast_init_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Bcast_init(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int MPI_Exscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Exscan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Exscan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Gather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Gather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Gatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Gatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Iallgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Iallgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Iallreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int MPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request);
int MPI_Ibcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Iexscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Igather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Igatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Iscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int MPI_Iscatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Iscatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int MPI_Op_commutative(MPI_Op op, int *commute);
int MPI_Op_create_c(MPI_User_function_c *user_fn, int commute, MPI_Op *op);
int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op);
int MPI_Op_free(MPI_Op *op);
int MPI_Reduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int MPI_Reduce_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_local_c(const void *inbuf, void *inoutbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op);
int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);
int MPI_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int MPI_Scan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Scan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int MPI_Scatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Scatter_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scatter_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Scatterv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

/* --- A.3.5 Groups, Contexts, Communicators, and Caching --- */
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
int MPI_Comm_create_from_group(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm);
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm);
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm);
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_free_keyval(int *comm_keyval);
int MPI_Comm_free(MPI_Comm *comm);
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used);
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_idup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request);
int MPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_remote_size(MPI_Comm comm, int *size);
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info);
int MPI_Comm_set_name(MPI_Comm comm, const char *comm_name);
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int MPI_Comm_test_inter(MPI_Comm comm, int *flag);
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_free(MPI_Group *group);
int MPI_Group_from_session_pset(MPI_Session session, const char *pset_name, MPI_Group *newgroup);
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int MPI_Group_rank(MPI_Group group, int *rank);
int MPI_Group_size(MPI_Group group, int *size);
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]);
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Intercomm_create_from_groups(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm);
int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
int MPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state);
int MPI_Type_delete_attr(MPI_Datatype datatype, int type_keyval);
int MPI_Type_free_keyval(int *type_keyval);
int MPI_Type_get_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val, int *flag);
int MPI_Type_get_name(MPI_Datatype datatype, char *type_name, int *resultlen);
int MPI_Type_set_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val);
int MPI_Type_set_name(MPI_Datatype datatype, const char *type_name);
int MPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state);
int MPI_Win_delete_attr(MPI_Win win, int win_keyval);
int MPI_Win_free_keyval(int *win_keyval);
int MPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag);
int MPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen);
int MPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val);
int MPI_Win_set_name(MPI_Win win, const char *win_name);

/* --- A.3.6 Virtual Topologies --- */
int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[]);
int MPI_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart);
int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[]);
int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank);
int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank);
int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest);
int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *newcomm);
int MPI_Cartdim_get(MPI_Comm comm, int *ndims);
int MPI_Dims_create(int nnodes, int ndims, int dims[]);
int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph);
int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph);
int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int *indegree, int *outdegree, int *weighted);
int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[]);
int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph);
int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[]);
int MPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank);
int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors);
int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[]);
int MPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges);
int MPI_Ineighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int MPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int MPI_Neighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Neighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int MPI_Neighbor_alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int MPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int MPI_Topo_test(MPI_Comm comm, int *status);

/* --- A.3.7 MPI Environmental Management --- */
int MPI_Abort(MPI_Comm comm, int errorcode);
int MPI_Add_error_class(int *errorclass);
int MPI_Add_error_code(int errorclass, int *errorcode);
int MPI_Add_error_string(int errorcode, const char *string);
int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr);
int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode);
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *errhandler);
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
int MPI_Errhandler_free(MPI_Errhandler *errhandler);
int MPI_Error_class(int errorcode, int *errorclass);
int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_File_call_errhandler(MPI_File fh, int errorcode);
int MPI_File_create_errhandler(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler);
int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler);
int MPI_Free_mem(void *base);
int MPI_Get_hw_resource_info(MPI_Info *hw_info);
int MPI_Get_library_version(char *version, int *resultlen);
int MPI_Get_processor_name(char *name, int *resultlen);
int MPI_Get_version(int *version, int *subversion);
int MPI_Init(int *argc, char ***argv);
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
int MPI_Initialized(int *flag);
int MPI_Is_thread_main(int *flag);
int MPI_Query_thread(int *provided);
int MPI_Remove_error_class(int errorclass);
int MPI_Remove_error_code(int errorcode);
int MPI_Remove_error_string(int errorcode);
int MPI_Session_call_errhandler(MPI_Session session, int errorcode);
int MPI_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Session_get_errhandler(MPI_Session session, MPI_Errhandler *errhandler);
int MPI_Session_set_errhandler(MPI_Session session, MPI_Errhandler errhandler);
int MPI_Win_call_errhandler(MPI_Win win, int errorcode);
int MPI_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler);
int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler);
int MPI_Finalize(void);
int MPI_Finalized(int *flag);
double MPI_Wtime(void);
double MPI_Wtick(void);

/* --- A.3.8 The Info Object --- */
int MPI_Info_create(MPI_Info *info);
int MPI_Info_create_env(int argc, char *argv[], MPI_Info *info);
int MPI_Info_delete(MPI_Info info, const char *key);
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
int MPI_Info_free(MPI_Info *info);
int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag);
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
int MPI_Info_get_string(MPI_Info info, const char *key, int *buflen, char *value, int *flag);
int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag);
int MPI_Info_set(MPI_Info info, const char *key, const char *value);

/* --- A.3.9 Process Creation and Management --- */
int MPI_Close_port(const char *port_name);
int MPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_disconnect(MPI_Comm *comm);
int MPI_Comm_get_parent(MPI_Comm *parent);
int MPI_Comm_join(int fd, MPI_Comm *intercomm);
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]);
int MPI_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MPI_Info array_of_info[], int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]);
int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name);
int MPI_Open_port(MPI_Info info, char *port_name);
int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name);
int MPI_Session_finalize(MPI_Session *session);
int MPI_Session_get_info(MPI_Session session, MPI_Info *info_used);
int MPI_Session_get_nth_pset(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name);
int MPI_Session_get_num_psets(MPI_Session session, MPI_Info info, int *npset_names);
int MPI_Session_get_pset_info(MPI_Session session, const char *pset_name, MPI_Info *info);
int MPI_Session_init(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session);
int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name);

/* --- A.3.10 One-Sided Communications --- */
int MPI_Accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int MPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win);
int MPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win);
int MPI_Get_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int MPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int MPI_Get_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Put_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Raccumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int MPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int MPI_Rget_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int MPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int MPI_Rget_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int MPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int MPI_Rput_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int MPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int MPI_Win_allocate_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int MPI_Win_allocate_shared_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int MPI_Win_attach(MPI_Win win, void *base, MPI_Aint size);
int MPI_Win_complete(MPI_Win win);
int MPI_Win_create_c(void *base, MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_detach(MPI_Win win, const void *base);
int MPI_Win_fence(int assert, MPI_Win win);
int MPI_Win_flush_all(MPI_Win win);
int MPI_Win_flush_local_all(MPI_Win win);
int MPI_Win_flush_local(int rank, MPI_Win win);
int MPI_Win_flush(int rank, MPI_Win win);
int MPI_Win_free(MPI_Win *win);
int MPI_Win_get_group(MPI_Win win, MPI_Group *group);
int MPI_Win_get_info(MPI_Win win, MPI_Info *info_used);
int MPI_Win_lock_all(int assert, MPI_Win win);
int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);
int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_set_info(MPI_Win win, MPI_Info info);
int MPI_Win_shared_query_c(MPI_Win win, int rank, MPI_Aint *size, MPI_Aint *disp_unit, void *baseptr);
int MPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr);
int MPI_Win_start(MPI_Group group, int assert, MPI_Win win);
int MPI_Win_sync(MPI_Win win);
int MPI_Win_test(MPI_Win win, int *flag);
int MPI_Win_unlock_all(MPI_Win win);
int MPI_Win_unlock(int rank, MPI_Win win);
int MPI_Win_wait(MPI_Win win);

/* --- A.3.11 External Interfaces --- */
int MPI_Grequest_complete(MPI_Request request);
int MPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request);
int MPI_Status_set_cancelled(MPI_Status *status, int flag);
int MPI_Status_set_elements_c(MPI_Status *status, MPI_Datatype datatype, MPI_Count count);
int MPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count);
int MPI_Status_set_error(MPI_Status *status, int err);
int MPI_Status_set_source(MPI_Status *status, int source);
int MPI_Status_set_tag(MPI_Status *status, int tag);

/* --- A.3.12 I/O --- */
int MPI_File_close(MPI_File *fh);
int MPI_File_delete(const char *filename, MPI_Info info);
int MPI_File_get_amode(MPI_File fh, int *amode);
int MPI_File_get_atomicity(MPI_File fh, int *flag);
int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);
int MPI_File_get_group(MPI_File fh, MPI_Group *group);
int MPI_File_get_info(MPI_File fh, MPI_Info *info_used);
int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset);
int MPI_File_get_position(MPI_File fh, MPI_Offset *offset);
int MPI_File_get_size(MPI_File fh, MPI_Offset *size);
int MPI_File_get_type_extent_c(MPI_File fh, MPI_Datatype datatype, MPI_Count *extent);
int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent);
int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep);
int MPI_File_iread_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh);
int MPI_File_preallocate(MPI_File fh, MPI_Offset size);
int MPI_File_read_all_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
int MPI_File_read_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status);
int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_all_begin_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
int MPI_File_read_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_ordered_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
int MPI_File_read_ordered_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
int MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence);
int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
int MPI_File_set_atomicity(MPI_File fh, int flag);
int MPI_File_set_info(MPI_File fh, MPI_Info info);
int MPI_File_set_size(MPI_File fh, MPI_Offset size);
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info);
int MPI_File_sync(MPI_File fh);
int MPI_File_write_all_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype);
int MPI_File_write_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status);
int MPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at_all_begin_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype);
int MPI_File_write_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status);
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_ordered_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype);
int MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype);
int MPI_File_write_ordered_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status);
int MPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_Register_datarep_c(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
int MPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);

/* --- A.3.13 Language Bindings --- */
int MPI_Status_c2f08(const MPI_Status *c_status, MPI_F08_status *f08_status);
int MPI_Status_c2f(const MPI_Status *c_status, MPI_Fint *f_status);
int MPI_Status_f082c(const MPI_F08_status *f08_status, MPI_Status *c_status);
int MPI_Status_f082f(const MPI_F08_status *f08_status, MPI_Fint *f_status);
int MPI_Status_f2c(const MPI_Fint *f_status, MPI_Status *c_status);
int MPI_Status_f2f08(const MPI_Fint *f_status, MPI_F08_status *f08_status);
int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype);
int MPI_Type_create_f90_integer(int r, MPI_Datatype *newtype);
int MPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype);
int MPI_Type_match_size(int typeclass, int size, MPI_Datatype *datatype);

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
MPI_Message MPI_Message_f2c(MPI_Fint message);
MPI_Fint MPI_Message_c2f(MPI_Message message);
MPI_Session MPI_Session_f2c(MPI_Fint session);
MPI_Fint MPI_Session_c2f(MPI_Session session);

/* --- A.3.14 Application Binary Interface (ABI) --- */
int MPI_Abi_get_version(int *abi_major, int *abi_minor);
int MPI_Abi_get_info(MPI_Info *info);
int MPI_Abi_get_fortran_info(MPI_Info *info);
int MPI_Abi_set_fortran_info(MPI_Info info);
int MPI_Abi_get_fortran_booleans(int logical_size, void *logical_true, void *logical_false, int *is_set);
int MPI_Abi_set_fortran_booleans(int logical_size, void *logical_true, void *logical_false);
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
int MPI_Message_toint(MPI_Message message);
MPI_Message MPI_Message_fromint(int message);
int MPI_Session_toint(MPI_Session session);
MPI_Session MPI_Session_fromint(int session);

/* --- A.3.15 Tools / Profiling Interface --- */
int MPI_Pcontrol(const int level, ...);

/* --- A.3.16 Tools / MPI Tool Information Interface --- */
int MPI_T_category_changed(int *update_number);
int MPI_T_category_get_categories(int cat_index, int len, int indices[]);
int MPI_T_category_get_cvars(int cat_index, int len, int indices[]);
int MPI_T_category_get_events(int cat_index, int len, int indices[]);
int MPI_T_category_get_index(const char *name, int *cat_index);
int MPI_T_category_get_info(int cat_index, char *name, int *name_len, char *desc, int *desc_len, int *num_cvars, int *num_pvars, int *num_categories);
int MPI_T_category_get_num_events(int cat_index, int *num_events);
int MPI_T_category_get_num(int *num_cat);
int MPI_T_category_get_pvars(int cat_index, int len, int indices[]);
int MPI_T_cvar_get_index(const char *name, int *cvar_index);
int MPI_T_cvar_get_info(int cvar_index, char *name, int *name_len, int *verbosity, MPI_Datatype *datatype, MPI_T_enum *enumtype, char *desc, int *desc_len, int *bind, int *scope);
int MPI_T_cvar_get_num(int *num_cvar);
int MPI_T_cvar_handle_alloc(int cvar_index, void *obj_handle, MPI_T_cvar_handle *handle, int *count);
int MPI_T_cvar_handle_free(MPI_T_cvar_handle *handle);
int MPI_T_cvar_read(MPI_T_cvar_handle handle, void *buf);
int MPI_T_cvar_write(MPI_T_cvar_handle handle, const void *buf);
int MPI_T_enum_get_info(MPI_T_enum enumtype, int *num, char *name, int *name_len);
int MPI_T_enum_get_item(MPI_T_enum enumtype, int index, int *value, char *name, int *name_len);
int MPI_T_event_callback_get_info(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info *info_used);
int MPI_T_event_callback_set_info(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info info);
int MPI_T_event_copy(MPI_T_event_instance event_instance, void *buffer);
int MPI_T_event_get_index(const char *name, int *event_index);
int MPI_T_event_get_info(int event_index, char *name, int *name_len, int *verbosity, MPI_Datatype array_of_datatypes[], MPI_Aint array_of_displacements[], int *num_elements, MPI_T_enum *enumtype, MPI_Info info, char *desc, int *desc_len, int *bind);
int MPI_T_event_get_num(int *num_events);
int MPI_T_event_get_source(MPI_T_event_instance event_instance, int *source_index);
int MPI_T_event_get_timestamp(MPI_T_event_instance event_instance, MPI_Count *event_timestamp);
int MPI_T_event_handle_alloc(int event_index, void *obj_handle, MPI_Info info, MPI_T_event_registration *event_registration);
int MPI_T_event_handle_free(MPI_T_event_registration event_registration, void *user_data, MPI_T_event_free_cb_function free_cb_function);
int MPI_T_event_handle_get_info(MPI_T_event_registration event_registration, MPI_Info *info_used);
int MPI_T_event_handle_set_info(MPI_T_event_registration event_registration, MPI_Info info);
int MPI_T_event_read(MPI_T_event_instance event_instance, int element_index, void *buffer);
int MPI_T_event_register_callback(MPI_T_event_registration event_registration, MPI_T_cb_safety cb_safety, MPI_Info info, void *user_data, MPI_T_event_cb_function event_cb_function);
int MPI_T_event_set_dropped_handler(MPI_T_event_registration event_registration, MPI_T_event_dropped_cb_function dropped_cb_function);
int MPI_T_finalize(void);
int MPI_T_init_thread(int required, int *provided);
int MPI_T_pvar_get_index(const char *name, int var_class, int *pvar_index);
int MPI_T_pvar_get_info(int pvar_index, char *name, int *name_len, int *verbosity, int *var_class, MPI_Datatype *datatype, MPI_T_enum enumtype, char *desc, int *desc_len, int *bind, int *readonly, int *continuous, int *atomic);
int MPI_T_pvar_get_num(int *num_pvar);
int MPI_T_pvar_handle_alloc(MPI_T_pvar_session pe_session, int pvar_index, void *obj_handle, MPI_T_pvar_handle handle, int *count);
int MPI_T_pvar_handle_free(MPI_T_pvar_session pe_session, MPI_T_pvar_handle *handle);
int MPI_T_pvar_readreset(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, void *buf);
int MPI_T_pvar_read(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, void *buf);
int MPI_T_pvar_reset(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle);
int MPI_T_pvar_session_create(MPI_T_pvar_session *pe_session);
int MPI_T_pvar_session_free(MPI_T_pvar_session *pe_session);
int MPI_T_pvar_start(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle);
int MPI_T_pvar_stop(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle);
int MPI_T_pvar_write(MPI_T_pvar_session pe_session, MPI_T_pvar_handle handle, const void *buf);
int MPI_T_source_get_info(int source_index, char *name, int *name_len, char *desc, int *desc_len, MPI_T_source_order *ordering, MPI_Count *ticks_per_second, MPI_Count *max_ticks, MPI_Info info);
int MPI_T_source_get_num(int *num_sources);
int MPI_T_source_get_timestamp(int source_index, MPI_Count timestamp);

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
/* Legacy MPI-1 Aliases for SuperLU_DIST and MUMPS */
int MPI_Type_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int MPI_Type_extent(MPI_Datatype datatype, MPI_Aint *extent);
int MPI_Type_lb(MPI_Datatype datatype, MPI_Aint *displacement);
int MPI_Type_ub(MPI_Datatype datatype, MPI_Aint *displacement);
int MPI_Address(void *location, MPI_Aint *address);
int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler);
int MPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int MPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);

/* --- MPI-3.1 Address Arithmetic (Required by HDF5) --- */
MPI_Aint MPI_Aint_add(MPI_Aint base, MPI_Aint disp);
MPI_Aint MPI_Aint_diff(MPI_Aint addr1, MPI_Aint addr2);

/* --- FIX: Backwards compatibility aliases required by PETSc --- */
typedef void MPI_Comm_errhandler_fn(MPI_Comm *comm, int *error_code, ...);
typedef void MPI_File_errhandler_fn(MPI_File *file, int *error_code, ...);
typedef void MPI_Win_errhandler_fn(MPI_Win *win, int *error_code, ...);

#define MPI_LB ((MPI_Datatype)(intptr_t)516)
#define MPI_UB ((MPI_Datatype)(intptr_t)517)



#ifdef __cplusplus
}
#endif

#endif /* MPI_STUB_H */