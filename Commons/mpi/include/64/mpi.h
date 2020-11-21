/*
 *	
 *	Copyright IBM corp. 1983-2010, 2012-2017
 *      US Government Users Restricted Rights:
 *          Use, duplication or disclosure restricted 
 *          by GSA ADP Schedule Contract with IBM Corp.
 *
 *	$Revision$
 *
 *	Function:	- MPI header file
 *
 *	Notice:		- IBM Platform MPI is based in parts on the contributions
 *			  of the following groups:
 *
 *	- MPICH (Argonne National Laboratory, Mississippi State University)
 *	  versions 1.0.11, 1.0.12
 *	  (c)Copyright 1993 University of Chicago
 *	  (c)Copyright 1993 Mississippi State University
 *
 *	- LAM (Ohio Supercomputer Center)
 *	  versions 6.0, 6.1
 *	  (c)Copyright 1995-1996 The Ohio State University
 *
 *	"@(#)IBM Platform MPI - Windows"
 */

#ifndef _MPI_H
#define _MPI_H

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

#ifndef HPAPIEXPORT
#ifdef _WIN32
#  define HPMPIAPI __stdcall
#  define HPAPIEXPORT __declspec(dllimport)
#  define HPDATEXPORT __declspec(dllimport)
#  define HPMPIIMPORT __declspec(dllimport)
#else
#  define HPMPIAPI
#  define HPAPIEXPORT
#  define HPDATEXPORT
#  define HPMPIIMPORT
#endif
#endif


/*****************************************************************
 * MPI Constants definition.
 *****************************************************************/
/*
 * MPI version
 */
#define MPI_VERSION	2
#define MPI_SUBVERSION	2

#define PLATFORM_MPI	0x09010404
#define HP_MPI		203
#define HP_MPI_MINOR	0

/*
 * user-visible MPI object
 */
typedef struct {
	int		MPI_SOURCE;
	int		MPI_TAG;
	int		MPI_ERROR;
        int             st_cancel;              /* opaque to user */
        long long       st_count;               /* opaque to user */
        int             st_pad[2];
} MPI_Status;

/*
 * MPI defined constants
 */
#define MPI_PROC_NULL		-1		/* rank of null process */
#define MPI_ANY_SOURCE		-2		/* match any source rank */
#define MPI_ROOT		-3		/* calling process is root */
#define MPI_ANY_TAG		-1		/* match any message tag */
#define MPI_MAX_PROCESSOR_NAME	256		/* max proc. name length */
#define MPI_MAX_OBJECT_NAME     64              /* max object name length */
#define MPI_MAX_ERROR_STRING	256		/* max error message length */
#define MPI_MAX_PORT_NAME	64              /* max port name length */
#define MPI_MAX_DATAREP_STRING 128 /* max length of data rep */
#define MPI_UNDEFINED		-32766		/* undefined stuff */
#define MPI_GRAPH		1		/* graph topology */
#define MPI_CART		2		/* cartesian topology */
#define MPI_DIST_GRAPH	3		/* distributed graph topology */
#define MPI_KEYVAL_INVALID	-1		/* invalid key value */
#define MPI_BSEND_OVERHEAD	64		/* bsend packing overhead */
#define MPI_TYPECLASS_INTEGER	1		/* integer datatype class */
#define MPI_TYPECLASS_REAL	2		/* real datatype class */
#define MPI_TYPECLASS_COMPLEX	3		/* complex datatype class */

#define MPI_IDENT		0		/* comparison result */
#define MPI_CONGRUENT		1		/* comparison result */
#define MPI_SIMILAR		2		/* comparison result */
#define MPI_UNEQUAL		3		/* comparison result */
#define MPI_MAX_INFO_KEY	256		/* max info key length */
#define MPI_MAX_INFO_VAL	16384		/* max info value length */
#define MPI_LOCK_EXCLUSIVE	1		/* exclusive lock */
#define MPI_LOCK_SHARED		2		/* shared lock */

#define MPI_THREAD_SINGLE	0		/* one thread only */
#define MPI_THREAD_FUNNELED	1		/* mthreaded, main only */
#define MPI_THREAD_SERIALIZED	2		/* mthreaded, one at a time */
#define MPI_THREAD_MULTIPLE	3		/* mthreaded, unrestricted */

/*
 * Predefined attribute keys.
 */
#define MPI_TAG_UB		0		/* max tag value can be used */
#define MPI_HOST		1		/* the host rank if exits */
#define MPI_IO			2		/* which rank accept input */
#define MPI_WTIME_IS_GLOBAL	3		/* if world is on same host */
#define IMPI_CLIENT_SIZE	4		/* client size in this comm */
#define IMPI_CLIENT_COLOR	5		/* the color of my client */
#define IMPI_HOST_SIZE		6		/* host size in this comm */
#define IMPI_HOST_COLOR		7		/* the color of my host */
#define MPI_WIN_BASE		8		/* the window base buffer */
#define MPI_WIN_SIZE		9		/* the window buffer size */
#define MPI_WIN_DISP_UNIT	10		/* the displace unit */
#define MPI_WIN_CREATE_FLAVOR	11              /* how the window was created */
#define MPI_WIN_MODEL 		12		/* memory model for window */
#define MPI_UNIVERSE_SIZE	13		/* universe size of job */
#define MPI_APPNUM		14		/* # of app. in the world */
#define MPI_LASTUSEDCODE	15		/* last used error code */

/*
 * Predefined reference constants
 */
/*
 * MPI_BOTTOM will depend on a flag (set via MPI_FLAGS=i), where the
 * default is to leave MPI_BOTTOM as "address zero" so we don't break
 * apps that depend on the old behavior, but if the MPI_FLAGS=i flag
 * is on, then it will instead use the same MPI_BOTTOM as fortran, to
 * allow language interoperability as required in section 4.12.10 of
 * the MPI-2 standard.
 */
HPDATEXPORT
extern int			hpmp_flinteroperate;
HPDATEXPORT
extern void			*hpmp_f_mpi_bottom;
HPDATEXPORT
extern void			*hpmp_f_mpi_in_place;

HPDATEXPORT
extern void			*MPI_F_STATUS_IGNORE;
HPDATEXPORT
extern void			*MPI_F_STATUSES_IGNORE;

#define MPI_BOTTOM  ((hpmp_flinteroperate)?(hpmp_f_mpi_bottom):((void *) 0))
#define MPI_STATUS_IGNORE	((MPI_Status *) 0)	/* status ignore */
#define MPI_STATUSES_IGNORE	((MPI_Status *) 0)	/* statuses ignore */
#define MPI_ERRCODES_IGNORE	((int *) 0)	/* error codes ignore */
#define MPI_ARGV_NULL		((char **) 0)	/* NULL spawn argument */
#define MPI_ARGVS_NULL		((char ***) 0)	/* NULL spawnmultiple arg */
#define MPI_IN_PLACE		(hpmp_f_mpi_in_place)/* collective in place */

#define MPI_UNWEIGHTED		((void*) 0)	/* NULL weight argument */

/*
 * error classes, also see file mpi_error.h & mperror.c
 */
#define MPI_SUCCESS		0		/* no errors */
#define MPI_ERR_BUFFER		1		/* invalid buffer */
#define MPI_ERR_COUNT		2		/* invalid count */
#define MPI_ERR_TYPE		3		/* invalid datatype */
#define MPI_ERR_TAG		4		/* invalid tag */
#define MPI_ERR_COMM		5		/* invalid communicator */
#define MPI_ERR_RANK		6		/* invalid rank */
#define MPI_ERR_ROOT		7		/* invalid root */
#define MPI_ERR_GROUP		8		/* invalid group */
#define MPI_ERR_OP		9		/* invalid operation */
#define MPI_ERR_TOPOLOGY	10		/* invalid topology */
#define MPI_ERR_DIMS		11		/* invalid dimension */
#define MPI_ERR_ARG		12		/* invalid argument */
#define MPI_ERR_UNKNOWN		13		/* unknown error */
#define MPI_ERR_TRUNCATE	14		/* message truncated */
#define MPI_ERR_OTHER		15		/* other known error */
#define MPI_ERR_INTERN		16		/* internal MPI error */
#define MPI_ERR_IN_STATUS	17		/* error code in status */
#define MPI_ERR_PENDING		18		/* pending request */
#define MPI_ERR_REQUEST		19		/* invalid request */
#define MPI_ERR_INFO		20		/* invalid info arg */
#define MPI_ERR_INFO_NOKEY	21		/* info key not defined */
#define MPI_ERR_INFO_KEY	22		/* invalid info key */
#define MPI_ERR_INFO_VALUE	23		/* invalid info value */
#define MPI_ERR_WIN		24		/* invalid window arg */
#define MPI_ERR_BASE		25		/* invalid window base */
#define MPI_ERR_SIZE		26		/* invalid window size */
#define MPI_ERR_DISP		27		/* invalid window unit disp. */
#define MPI_ERR_LOCKTYPE	28		/* invalid locktype arg */
#define MPI_ERR_ASSERT		29		/* invalid assert arg */
#define MPI_ERR_RMA_CONFLICT	30		/* conflicting access to win */
#define MPI_ERR_RMA_SYNC	31		/* invalid window sync */
#define MPI_ERR_NO_MEM		32		/* out of "special" memory */
#define MPI_ERR_KEYVAL		33		/* invalid key value */
#define MPI_ERR_SPAWN		34		/* spawn error */
#define MPI_ERR_PORT		51		/* invalid port name */
#define MPI_ERR_SERVICE		52		/* invalid service name */
#define MPI_ERR_NAME		53		/* nonexist service name */
#define MPI_ERR_EXITED		54		/* peer rank is exited */
#define MPI_ERR_CONNECT		55		/* OnDemand connect failed */
#define MPI_ERR_PROC_FAILED	56		/* target rank has exited */
#define MPI_ERR_REVOKED		57		/* Comm has been revoked */
#define MPI_ERR_LASTCODE	0x3FFFFFFF	/* last error code */

/*
 * one-sided assert flags
 */
#define MPI_MODE_NOCHECK	0x01		/* no synchronization check */
#define MPI_MODE_NOSTORE	0x02		/* no previous local stores */
#define MPI_MODE_NOPUT		0x04		/* no following put/acc. */
#define MPI_MODE_NOPRECEDE	0x08		/* no previous local RMA */
#define MPI_MODE_NOSUCCEED	0x10		/* no following local RMA */

#define MPI_COMM_TYPE_SHARED	0x20

/*
 * datatype decoding combiners
 */
#define MPI_COMBINER_NAMED		0	/* predefined datatype */
#define MPI_COMBINER_DUP		1	/* Type_dup */
#define MPI_COMBINER_CONTIGUOUS		2	/* Type_contiguous */
#define MPI_COMBINER_VECTOR		3	/* Type_vector */
#define MPI_COMBINER_HVECTOR_INTEGER	4	/* f77 Type_hvector */
#define MPI_COMBINER_HVECTOR		5	/* Type_hvector */
#define MPI_COMBINER_INDEXED		6	/* Type_indexed */
#define MPI_COMBINER_HINDEXED_INTEGER	7	/* f77 Type_hindexed */
#define MPI_COMBINER_HINDEXED		8	/* Type_hindexed */
#define MPI_COMBINER_INDEXED_BLOCK	9	/* Type_create_indexed_block */
#define MPI_COMBINER_STRUCT_INTEGER	10	/* f77 MPI_Type_struct */
#define MPI_COMBINER_STRUCT		11	/* Type_struct */
#define MPI_COMBINER_SUBARRAY		12	/* Type_create_subarray */
#define MPI_COMBINER_DARRAY		13	/* Type_create_darray */
#define MPI_COMBINER_F90_REAL		14	/* Type_create_f90_real */
#define MPI_COMBINER_F90_COMPLEX	15	/* Type_create_f90_complex */
#define MPI_COMBINER_F90_INTEGER	16	/* Type_create_f90_integer */
#define MPI_COMBINER_RESIZED		17	/* Type_create_resized */

/*****************************************************************
 * MPI Objects definition.
 *****************************************************************/
#if !defined(MPI_hpux) || defined(HPMP_BUILD_CXXBINDING)
    typedef void* voidptr;
#   define HPMP_COMM_T voidptr
#   define HPMP_DTYPE_T voidptr
#   define HPMP_GROUP_T voidptr
#   define HPMP_OP_T voidptr
#   define HPMP_ERR_T voidptr
#   define HPMP_REQ_T voidptr
#   define HPMP_INFO_T voidptr
#   define HPMP_WIN_T voidptr
#   define HPMP_MSG_T voidptr
#   define HPMP_REQC_T voidptr
#else
#   define HPMP_COMM_T struct hpmp_comm_s
#   define HPMP_DTYPE_T struct hpmp_dtype_s
#   define HPMP_GROUP_T struct hpmp_group_s
#   define HPMP_OP_T struct hpmp_op_s
#   define HPMP_REQ_T struct hpmp_req_s
#   define HPMP_ERR_T struct hpmp_err_s
#   define HPMP_INFO_T struct hpmp_info_s
#   define HPMP_WIN_T struct hpmp_win_s
#   define HPMP_MSG_T struct hpmp_message_s
#   define HPMP_REQC_T struct hpmp_greqx_class_s
#endif

/*
 * MPI object typedefs.
 */
typedef HPMP_COMM_T		*MPI_Comm;	/* communicator object */
typedef HPMP_DTYPE_T		*MPI_Datatype;	/* datatype object */
typedef HPMP_GROUP_T		*MPI_Group;	/* group object */
typedef HPMP_OP_T		*MPI_Op;	/* operation object */
typedef HPMP_REQ_T		*MPI_Request;	/* request object */
typedef HPMP_ERR_T		*MPI_Errhandler;/* error handler object */
typedef HPMP_INFO_T		*MPI_Info;	/* info object */
typedef HPMP_WIN_T		*MPI_Win;	/* window object */
typedef HPMP_MSG_T		*MPI_Message;	/* request object */
#ifdef _WIN64
typedef __int64			MPI_Aint;	/* address-sized integer */
#else
typedef long			MPI_Aint;	/* address-sized integer */
#endif
typedef int			MPI_Fint;	/* fortran integer */
typedef long long	MPI_Count;
typedef HPMP_REQC_T            *MPIX_Grequest_class; /* gen-req class */

/*
 * User function typedefs
 */
#if defined(__STDC__) || defined(c_plusplus) || defined(__cplusplus) || defined(_WIN32)
typedef int		(MPI_Copy_function)(MPI_Comm, int, void *,
						void *, void *, int *);
typedef int		(MPI_Delete_function)(MPI_Comm, int, void *, void *);
typedef void		(MPI_Handler_function)(MPI_Comm *, int *, ...);
typedef void		(MPI_User_function)(void *, void *, int *,
						MPI_Datatype *);
typedef void	(MPI_Comm_errhandler_function)(MPI_Comm *, int *, ...);
typedef int		(MPI_Comm_copy_attr_function)(MPI_Comm,
				int, void *, void *, void *, int *);
typedef int		(MPI_Comm_delete_attr_function)(MPI_Comm,
				int, void *, void *);
typedef int		(MPI_Grequest_query_function)(void *, MPI_Status*);
typedef int		(MPI_Grequest_free_function)(void *);
typedef int		(MPI_Grequest_cancel_function)(void *, int);
typedef int		(MPIX_Grequest_poll_fn)(void *, MPI_Status *);
typedef int		(MPIX_Grequest_wait_fn)(int,void*, double, MPI_Status*);
typedef void	(MPI_Win_errhandler_function)(MPI_Win *, int *, ...);
typedef int		(MPI_Win_copy_attr_function)(MPI_Win, int,
				void *, void *, void *, int *);
typedef int		(MPI_Win_delete_attr_function)(MPI_Win, int,
				void *, void *);
typedef int		(MPI_Type_copy_attr_function)(MPI_Datatype, int,
				void *, void *, void *, int *);
typedef int		(MPI_Type_delete_attr_function)(MPI_Datatype, int,
				void *, void *);
#else
typedef int		(MPI_Copy_function)();
typedef int		(MPI_Delete_function)();
typedef void	(MPI_Handler_function)();
typedef void	(MPI_User_function)();
typedef void	(MPI_Comm_errhandler_function)();
typedef int		(MPI_Comm_copy_attr_function)();
typedef int		(MPI_Comm_delete_attr_function)();
typedef int		(MPI_Grequest_query_function)();
typedef int		(MPI_Grequest_free_function)();
typedef int		(MPI_Grequest_cancel_function)();
typedef int		(MPIX_Grequest_poll_fn)();
typedef int		(MPIX_Grequest_wait_fn)();
typedef void	(MPI_Win_errhandler_function)();
typedef int		(MPI_Win_copy_attr_function)();
typedef int		(MPI_Win_delete_attr_function)();
typedef int		(MPI_Type_copy_attr_function)();
typedef int		(MPI_Type_delete_attr_function)();
#endif
/* names that were added in MPI-2.0 and deprecated in MPI-2.2 */
typedef MPI_Comm_errhandler_function MPI_Comm_errhandler_fn;
typedef MPI_Win_errhandler_function MPI_Win_errhandler_fn;

/*
 * NULL handles
 */
#define MPI_COMM_NULL		((MPI_Comm) 0)
#define MPI_DATATYPE_NULL	((MPI_Datatype) 0)
#define MPI_ERRHANDLER_NULL	((MPI_Errhandler) 0)
#define MPI_GROUP_NULL		((MPI_Group) 0)
#define MPI_OP_NULL		((MPI_Op) 0)
#define MPI_INFO_NULL		((MPI_Info) 0)
#define MPI_WIN_NULL		((MPI_Win) 0)
#define MPI_REQUEST_NULL	((MPI_Request) 0)

#define MPI_NULL_COPY_FN	((MPI_Copy_function *) 0)
#define MPI_NULL_DELETE_FN	((MPI_Delete_function *) 0)
#define MPI_COMM_NULL_COPY_FN	((MPI_Comm_copy_attr_function *) 0)
#define MPI_COMM_NULL_DELETE_FN	((MPI_Comm_delete_attr_function *) 0)
#define MPI_WIN_NULL_COPY_FN	((MPI_Win_copy_attr_function *) 0)
#define MPI_WIN_NULL_DELETE_FN	((MPI_Win_delete_attr_function *) 0)
#define MPI_TYPE_NULL_COPY_FN	((MPI_Type_copy_attr_function *) 0)
#define MPI_TYPE_NULL_DELETE_FN	((MPI_Type_delete_attr_function *) 0)

/*
 * HP MPI global debugging variable
 */
HPDATEXPORT
extern volatile int		MPI_DEBUG_CONT;
HPDATEXPORT
extern volatile int		mpi_debug_cont;

/*
 * external variables
 */
HPDATEXPORT
extern HPMP_COMM_T	hpmp_comm_world, hpmp_comm_self;
HPDATEXPORT
extern HPMP_GROUP_T	hpmp_group_empty;

HPDATEXPORT
extern HPMP_OP_T	hpmp_max, hpmp_min, hpmp_sum, hpmp_prod;
HPDATEXPORT
extern HPMP_OP_T	hpmp_land, hpmp_band, hpmp_lor, hpmp_bor;
HPDATEXPORT
extern HPMP_OP_T	hpmp_lxor, hpmp_bxor, hpmp_maxloc, hpmp_minloc;
HPDATEXPORT
extern HPMP_OP_T	hpmp_replace;

HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_ub, hpmp_lb;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_packed, hpmp_byte;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_char, hpmp_wchar;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_signed_char, hpmp_unsigned_char;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_short, hpmp_unsigned_short;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_int, hpmp_unsigned;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_long, hpmp_unsigned_long;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_int8, hpmp_uint8;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_float, hpmp_double, hpmp_long_double;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_2int, hpmp_2float, hpmp_2double;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_short_int, hpmp_long_int;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_int8_int;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_float_int, hpmp_double_int;
HPDATEXPORT
extern HPMP_DTYPE_T	hpmp_longdouble_int;

/*
	Datatypes introduced in mpi 2.2
*/
HPDATEXPORT extern HPMP_DTYPE_T hpmp_aint;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_offset;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_bool;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_int8_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_int16_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_int32_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_int64_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_uint8_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_uint16_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_uint32_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_uint64_t;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_float_complex;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_double_complex;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_long_double_complex;

HPDATEXPORT extern HPMP_DTYPE_T hpmp_real;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_integer;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_doubleprec;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_complex;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_logic;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_character;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_doublecomplex;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_integer1;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_integer2;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_integer4;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_integer8;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_real4;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_real8;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_real16;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_2integer;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_2real;
HPDATEXPORT extern HPMP_DTYPE_T hpmp_2doubleprec;



HPDATEXPORT
extern HPMP_ERR_T	hpmp_errors_are_fatal;
HPDATEXPORT
extern HPMP_ERR_T	hpmp_errors_return;

/*
 * predefined communicator objects
 */
#define MPI_COMM_WORLD		((MPI_Comm) &hpmp_comm_world)
#define MPI_COMM_SELF		((MPI_Comm) &hpmp_comm_self)
#define MPI_GROUP_EMPTY		((MPI_Group) &hpmp_group_empty)

/*
 * Predefined operator objects.
 */
#define MPI_MAX			((MPI_Op) &hpmp_max)
#define MPI_MIN			((MPI_Op) &hpmp_min)
#define MPI_SUM			((MPI_Op) &hpmp_sum)
#define MPI_PROD		((MPI_Op) &hpmp_prod)
#define MPI_LAND		((MPI_Op) &hpmp_land)
#define MPI_BAND		((MPI_Op) &hpmp_band)
#define MPI_LOR			((MPI_Op) &hpmp_lor)
#define MPI_BOR			((MPI_Op) &hpmp_bor)
#define MPI_LXOR		((MPI_Op) &hpmp_lxor)
#define MPI_BXOR		((MPI_Op) &hpmp_bxor)
#define MPI_MAXLOC		((MPI_Op) &hpmp_maxloc)
#define MPI_MINLOC		((MPI_Op) &hpmp_minloc)
#define MPI_REPLACE		((MPI_Op) &hpmp_replace)

/*
 * Predefined datatype objects.
 */
#define MPI_LB			((MPI_Datatype) &hpmp_lb)
#define MPI_UB			((MPI_Datatype) &hpmp_ub)

#define MPI_PACKED		((MPI_Datatype) &hpmp_packed)
#define MPI_BYTE		((MPI_Datatype) &hpmp_byte)
#define MPI_CHAR		((MPI_Datatype) &hpmp_char)
#define MPI_WCHAR		((MPI_Datatype) &hpmp_wchar)
#define MPI_SIGNED_CHAR		((MPI_Datatype) &hpmp_signed_char)
#define MPI_SHORT		((MPI_Datatype) &hpmp_short)
#define MPI_INT			((MPI_Datatype) &hpmp_int)
#define MPI_INT4		MPI_INT
#define MPI_INT8		((MPI_Datatype) &hpmp_int8)
#define MPI_LONG		((MPI_Datatype) &hpmp_long)
#define MPI_LONG_LONG		MPI_INT8
#define MPI_LONG_LONG_INT	MPI_INT8
#define MPI_FLOAT		((MPI_Datatype) &hpmp_float)
#define MPI_DOUBLE		((MPI_Datatype) &hpmp_double)
#define MPI_LONG_DOUBLE		((MPI_Datatype) &hpmp_long_double)

#define MPI_UNSIGNED_CHAR	((MPI_Datatype) &hpmp_unsigned_char)
#define MPI_UNSIGNED_SHORT	((MPI_Datatype) &hpmp_unsigned_short)
#define MPI_UNSIGNED		((MPI_Datatype) &hpmp_unsigned)
#define MPI_UINT4		MPI_UNSIGNED
#define MPI_UINT8		((MPI_Datatype) &hpmp_uint8)
#define MPI_UNSIGNED_LONG	((MPI_Datatype) &hpmp_unsigned_long)
#define MPI_UNSIGNED_LONG_LONG	MPI_UINT8

#define MPI_2INT		((MPI_Datatype) &hpmp_2int)
#define MPI_2FLOAT		((MPI_Datatype) &hpmp_2float)
#define MPI_2DOUBLE		((MPI_Datatype) &hpmp_2double)

#define MPI_SHORT_INT		((MPI_Datatype) &hpmp_short_int)
#define MPI_INT_INT		MPI_2INT
#define MPI_LONG_INT		((MPI_Datatype) &hpmp_long_int)
#define MPI_INT8_INT		((MPI_Datatype) &hpmp_int8_int)
#define MPI_FLOAT_INT		((MPI_Datatype) &hpmp_float_int)
#define MPI_DOUBLE_INT		((MPI_Datatype) &hpmp_double_int)
#define MPI_LONG_DOUBLE_INT	((MPI_Datatype) &hpmp_longdouble_int)
/*
	Datatypes introduced in mpi 2.2
*/
#define MPI_AINT     ((MPI_Datatype) &hpmp_aint)
#define MPI_OFFSET   ((MPI_Datatype) &hpmp_offset)
#define MPI_C_BOOL   ((MPI_Datatype) &hpmp_bool)
#define MPI_INT8_T   ((MPI_Datatype) &hpmp_int8_t)
#define MPI_INT16_T  ((MPI_Datatype) &hpmp_int16_t)
#define MPI_INT32_T  ((MPI_Datatype) &hpmp_int32_t)
#define MPI_INT64_T  ((MPI_Datatype) &hpmp_int64_t)
#define MPI_UINT8_T  ((MPI_Datatype) &hpmp_uint8_t)
#define MPI_UINT16_T ((MPI_Datatype) &hpmp_uint16_t)
#define MPI_UINT32_T ((MPI_Datatype) &hpmp_uint32_t)
#define MPI_UINT64_T ((MPI_Datatype) &hpmp_uint64_t)
#define MPI_C_COMPLEX ((MPI_Datatype) &hpmp_float_complex)
#define MPI_C_FLOAT_COMPLEX MPI_C_COMPLEX
#define MPI_C_DOUBLE_COMPLEX ((MPI_Datatype) &hpmp_double_complex)
#define MPI_C_LONG_DOUBLE_COMPLEX ((MPI_Datatype) &hpmp_long_double_complex)

/*
 * Predefined error handlers
 */
#define MPI_ERRORS_ARE_FATAL	((MPI_Errhandler) &hpmp_errors_are_fatal)
#define MPI_ERRORS_RETURN	((MPI_Errhandler) &hpmp_errors_return)

/*
 * These Fortran datatypes are included
 * for GLOBUS compatability.    We provide macros named after
 * standard MPI types to provide transparent conversion from Fortran
 * (integer value) to usable 'C' datatypes.
 */
#define MPIF_INTEGER            15
#define MPIF_REAL               16
#define MPIF_DOUBLE_PRECISION   17
#define MPIF_COMPLEX            18
#define MPIF_LOGICAL            19
#define MPIF_CHARACTER          20
#define MPIF_BYTE               21
#define MPIF_PACKED             22
#define MPIF_UB                 23
#define MPIF_LB                 24
#define MPIF_2REAL              25
#define MPIF_2DOUBLE_PRECISION  26
#define MPIF_2INTEGER           27
#define MPIF_INTEGER1           28
#define MPIF_INTEGER2           29
#define MPIF_INTEGER4           30
#define MPIF_REAL4              31
#define MPIF_REAL8              32
#define MPIF_DOUBLE_COMPLEX     33

/*
 *  Make the fortran types directly available from C
 */
#define MPI_REAL               ((MPI_Datatype) &hpmp_real)
#define MPI_INTEGER            ((MPI_Datatype) &hpmp_integer)
#define MPI_DOUBLE_PRECISION   ((MPI_Datatype) &hpmp_doubleprec)
#define MPI_COMPLEX            ((MPI_Datatype) &hpmp_complex)
#define MPI_LOGICAL            ((MPI_Datatype) &hpmp_logic)
#define MPI_CHARACTER          ((MPI_Datatype) &hpmp_character)
#define MPI_DOUBLE_COMPLEX     ((MPI_Datatype) &hpmp_doublecomplex)
#define MPI_INTEGER1           ((MPI_Datatype) &hpmp_integer1)
#define MPI_INTEGER2           ((MPI_Datatype) &hpmp_integer2)
#define MPI_INTEGER4           ((MPI_Datatype) &hpmp_integer4)
#define MPI_INTEGER8           ((MPI_Datatype) &hpmp_integer8)
#define MPI_REAL4              ((MPI_Datatype) &hpmp_real4)
#define MPI_REAL8              ((MPI_Datatype) &hpmp_real8)
#define MPI_REAL16             ((MPI_Datatype) &hpmp_real16)
#define MPI_COMPLEX8           ((MPI_Datatype) &hpmp_float_complex)
#define MPI_COMPLEX16          ((MPI_Datatype) &hpmp_double_complex)
#define MPI_COMPLEX32          ((MPI_Datatype) &hpmp_long_double_complex)
#define MPI_2INTEGER           ((MPI_Datatype) &hpmp_2integer)
#define MPI_2REAL              ((MPI_Datatype) &hpmp_2real)
#define MPI_2DOUBLE_PRECISION  ((MPI_Datatype) &hpmp_2doubleprec)

/*****************************************************************
 * MPI function prototypes
 *****************************************************************/
#if defined(__STDC__) || defined(c_plusplus) || defined(__cplusplus) || defined(_WIN32)

#if !defined(MPI_hpux) || defined(_WIN32)

/*
 * Function prototype only for users or internal Windows build.
 */
HPAPIEXPORT extern
int HPMPIAPI MPI_Abort(MPI_Comm, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Address(void *, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Allgather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Allgatherv(void *, int, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Allreduce(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Alltoall(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Alltoallv(void *, int *, int *, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Alltoallw(void *, int *, int *, MPI_Datatype*, void *,
			int *, int *, MPI_Datatype*, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Attr_delete(MPI_Comm, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Attr_get(MPI_Comm, int, void *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Attr_put(MPI_Comm, int, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Barrier(MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Bcast(void *, int, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Bsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Bsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Buffer_attach(void *, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Buffer_detach(void *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cancel(MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_coords(MPI_Comm, int, int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_get(MPI_Comm, int, int *, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_map(MPI_Comm, int, int *, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_rank(MPI_Comm, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_shift(MPI_Comm, int, int, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cart_sub(MPI_Comm, int *, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Cartdim_get(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_compare(MPI_Comm, MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_create(MPI_Comm, MPI_Group, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_create_group(MPI_Comm, MPI_Group, int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_dup(MPI_Comm, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_free(MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_group(MPI_Comm, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_rank(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_remote_group(MPI_Comm, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_remote_size(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_size(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_split(MPI_Comm, int, int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_split_type(MPI_Comm, int, int, MPI_Info, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_test_inter(MPI_Comm, int *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Comm_dup_with_info(MPI_Comm, MPI_Info, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_idup(MPI_Comm, MPI_Comm *, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Comm_get_info(MPI_Comm, MPI_Info *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Comm_set_info(MPI_Comm, MPI_Info);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_get_parent(MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_spawn(char *, char **, int, MPI_Info, int,
			MPI_Comm, MPI_Comm *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_spawn_multiple(int, char **, char ***, int *,
			MPI_Info *, int, MPI_Comm, MPI_Comm *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_accept(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_connect(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_join(int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_disconnect(MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Open_port(MPI_Info, char*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Close_port(char*);
/*
HPAPIEXPORT extern
int HPMPIAPI MPI_Publish_name(char*, MPI_Info, char*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Unpublish_name(char*, MPI_Info, char*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Lookup_name(char*, MPI_Info, char*);
*/
HPAPIEXPORT extern
int HPMPIAPI MPI_Dims_create(int, int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Errhandler_create(MPI_Handler_function *,
			MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Errhandler_free(MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Errhandler_get(MPI_Comm, MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Errhandler_set(MPI_Comm, MPI_Errhandler);
HPAPIEXPORT extern
int HPMPIAPI MPI_Error_class(int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Error_string(int, char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Add_error_class(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Add_error_code(int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Add_error_string(int, char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Finalize(void);
HPAPIEXPORT extern
int HPMPIAPI MPI_Finalized(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Gather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Gatherv(void *, int, MPI_Datatype, void *, int *,
			int *, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_count(MPI_Status *, MPI_Datatype, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_elements_x(MPI_Status *, MPI_Datatype, MPI_Count *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_processor_name(char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_version(int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_library_version(char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graph_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graph_get(MPI_Comm, int, int, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graph_map(MPI_Comm, int, int *, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graph_neighbors(MPI_Comm, int, int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graph_neighbors_count(MPI_Comm, int, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Graphdims_get(MPI_Comm, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Neighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_allgatherv(void *, int, MPI_Datatype, 
			void *, int *, int *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, MPI_Datatype *, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Dist_graph_create(MPI_Comm, int, int*, int*,
			int*, int*,	MPI_Info, int, MPI_Comm*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Dist_graph_create_adjacent(MPI_Comm, int, int*, int*,
			int, int*, int*,	MPI_Info, int, MPI_Comm*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Dist_graph_neighbors_count(MPI_Comm, int*, int*, int*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Dist_graph_neighbors(MPI_Comm, int, int*, int*,
			int, int*, int*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_compare(MPI_Group, MPI_Group, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_difference(MPI_Group, MPI_Group, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_excl(MPI_Group, int, int *, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_free(MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_incl(MPI_Group, int, int *, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_intersection(MPI_Group, MPI_Group, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_range_excl(MPI_Group, int, int [][3], MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_range_incl(MPI_Group, int, int [][3], MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_rank(MPI_Group, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_size(MPI_Group, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_translate_ranks(MPI_Group, int, int *,
			MPI_Group, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Group_union(MPI_Group, MPI_Group, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ibsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_allgatherv(void *, int, MPI_Datatype, 
			void *, int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Init(int *, char ***);
HPAPIEXPORT extern
int HPMPIAPI MPI_Initialized(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Intercomm_create(MPI_Comm, int, MPI_Comm, int,
			int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Intercomm_merge(MPI_Comm, int, MPI_Comm *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iprobe(int, int, MPI_Comm, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Irecv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Irsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Isend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Issend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Keyval_create(MPI_Copy_function *,
			MPI_Delete_function *, int *, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Keyval_free(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Op_create(MPI_User_function *, int, MPI_Op *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Op_free(MPI_Op *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Op_commutative(MPI_Op, int*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Pack(void *, int, MPI_Datatype, void *, int,
			int *, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Pack_external(char *, void *, int, MPI_Datatype, void *,
                        MPI_Aint, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Pack_size(int, MPI_Datatype, MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Pack_external_size(char *, int, MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Pcontrol(const int level, ...);
HPAPIEXPORT extern
int HPMPIAPI MPI_Probe(int, int, MPI_Comm, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Mprobe(int, int, MPI_Comm, MPI_Message *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Improbe(int, int, MPI_Comm, int *, MPI_Message *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Recv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Mrecv(void *, int, MPI_Datatype, MPI_Message *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Imrecv(void *, int, MPI_Datatype, MPI_Message *, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Recv_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Reduce(void *, void *, int, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Reduce_local(void *, void *, int, MPI_Datatype,
			MPI_Op);
HPAPIEXPORT extern
int HPMPIAPI MPI_Reduce_scatter(void *, void *, int *,
 			MPI_Datatype, MPI_Op, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Reduce_scatter_block(void *, void *, int,
			MPI_Datatype, MPI_Op, MPI_Comm);

HPAPIEXPORT extern
int HPMPIAPI MPI_Ibcast(void *, int, MPI_Datatype, int,
		    MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ibarrier(MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Igather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Igatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iscatter(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iscatterv(void *, int *, int *, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iallgather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iallgatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ialltoall(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ialltoallv(void *, int *, int *, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ialltoallw(void *, int *, int *, MPI_Datatype *, void *, int *,
		    int *, MPI_Datatype *, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ireduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iallreduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ireduce_scatter(void *, void *, int *,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ireduce_scatter_block(void *, void *, int,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Iexscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Request_free(MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Request_get_status(MPI_Request, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Grequest_start(MPI_Grequest_query_function*,
			MPI_Grequest_free_function*,
			MPI_Grequest_cancel_function*, void*, MPI_Request*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Grequest_complete(MPI_Request);
HPAPIEXPORT extern
int HPMPIAPI MPIX_Grequest_class_create(MPI_Grequest_query_function *,
                       MPI_Grequest_free_function *,
                       MPI_Grequest_cancel_function *, MPIX_Grequest_poll_fn *,
                       MPIX_Grequest_wait_fn *, MPIX_Grequest_class *);
HPAPIEXPORT extern
int HPMPIAPI MPIX_Grequest_class_allocate(MPIX_Grequest_class greq_class,
                       void *extra_state, MPI_Request *request);
HPAPIEXPORT extern
int HPMPIAPI MPI_Rsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Rsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Scan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Exscan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Scatter(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Scatterv(void *, int *, int *, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Send(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Send_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Sendrecv(void *, int, MPI_Datatype, int, int,
			void *, int, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Sendrecv_replace(void *, int, MPI_Datatype, int, int,
			int, int, MPI_Comm, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ssend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Ssend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Start(MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Startall(int, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Test(MPI_Request *, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Test_cancelled(MPI_Status *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Testall(int, MPI_Request *, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Topo_test(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_commit(MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_extent(MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_free(MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_contents(MPI_Datatype, int, int, int,
			int [], MPI_Aint [], MPI_Datatype []);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_envelope(MPI_Datatype, int *, int *,
			int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_extent(MPI_Datatype, MPI_Aint *, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_extent_x(MPI_Datatype, MPI_Count *, MPI_Count *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_true_extent(MPI_Datatype, MPI_Aint *,
			MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_true_extent_x(MPI_Datatype, MPI_Count *,
			MPI_Count *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_hvector(int, int, MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_indexed(int, int *, int *, MPI_Datatype,
			MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_lb(MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_size(MPI_Datatype, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_size_x(MPI_Datatype, MPI_Count *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_ub(MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_vector(int, int, int, MPI_Datatype,
			MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Unpack(void *, int, int *, void *, int,
			MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_Unpack_external(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, int, MPI_Datatype);
HPAPIEXPORT extern
int HPMPIAPI MPI_Wait(MPI_Request *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Waitall(int, MPI_Request *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPAPIEXPORT extern
double HPMPIAPI MPI_Wtick(void);
HPAPIEXPORT extern
double HPMPIAPI MPI_Wtime(void);

HPAPIEXPORT extern
int MPI_DUP_FN(MPI_Comm, int, void *, void *, void *, int*);
HPAPIEXPORT extern
int MPI_COMM_DUP_FN(MPI_Comm, int, void *, void *, void *, int*);
HPAPIEXPORT extern
int MPI_TYPE_DUP_FN(MPI_Datatype, int, void *, void *, void *, int*);
HPAPIEXPORT extern
int MPI_WIN_DUP_FN(MPI_Win, int, void *, void *, void *, int*);

HPAPIEXPORT extern
MPI_Comm HPMPIAPI MPI_Comm_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Datatype HPMPIAPI MPI_Type_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Group HPMPIAPI MPI_Group_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Op HPMPIAPI MPI_Op_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Request HPMPIAPI MPI_Request_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Win HPMPIAPI MPI_Win_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Info HPMPIAPI MPI_Info_f2c(MPI_Fint);
HPAPIEXPORT extern
MPI_Errhandler HPMPIAPI MPI_Errhandler_f2c(MPI_Fint);

HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Comm_c2f(MPI_Comm);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Type_c2f(MPI_Datatype);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Group_c2f(MPI_Group);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Op_c2f(MPI_Op);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Request_c2f(MPI_Request);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Win_c2f(MPI_Win);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Info_c2f(MPI_Info);
HPAPIEXPORT extern
MPI_Fint HPMPIAPI MPI_Errhandler_c2f(MPI_Errhandler);

HPAPIEXPORT extern
int HPMPIAPI MPI_Status_f2c(void *, MPI_Status *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Status_c2f(MPI_Status *, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Status_set_cancelled(MPI_Status *, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Status_set_elements(MPI_Status *, MPI_Datatype, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Status_set_elements_x(MPI_Status *, MPI_Datatype, MPI_Count);

HPAPIEXPORT extern
int HPMPIAPI MPI_Info_create(MPI_Info *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_delete(MPI_Info, const char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_dup(MPI_Info, MPI_Info *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_free(MPI_Info *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_get(MPI_Info, const char *, int, char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_get_nkeys(MPI_Info, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_get_nthkey(MPI_Info, int, char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_get_valuelen(MPI_Info, const char *, int *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Info_set(MPI_Info, const char *, const char *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Win_create(void *, MPI_Aint, int,
			MPI_Info, MPI_Comm, MPI_Win *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_allocate(MPI_Aint, int, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_allocate_shared(MPI_Aint, int, MPI_Info, 
			MPI_Comm, void *, MPI_Win *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_fence(int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_free(MPI_Win *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_get_group(MPI_Win, MPI_Group *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_attach(MPI_Win, void *, MPI_Aint);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_detach(MPI_Win, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_create_dynamic(MPI_Info, MPI_Comm, MPI_Win *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_flush(int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_flush_all(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_flush_local(int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_flush_local_all(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_get_info(MPI_Win, MPI_Info *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_set_info(MPI_Win, MPI_Info);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_sync(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_lock(int, int, int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_unlock(int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_lock_all(int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_unlock_all(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_shared_query(MPI_Win, int, MPI_Aint *, int *, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_start(MPI_Group, int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_post(MPI_Group, int, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_complete(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_wait(MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_test(MPI_Win, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_create_errhandler(MPI_Win_errhandler_function *,
			MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_set_errhandler(MPI_Win, MPI_Errhandler);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_get_errhandler(MPI_Win, MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_call_errhandler(MPI_Win, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_create_keyval(MPI_Win_copy_attr_function *,
			MPI_Win_delete_attr_function *, int *, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_free_keyval(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_set_attr(MPI_Win, int, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_get_attr(MPI_Win, int, void *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_delete_attr(MPI_Win, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Put(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Accumulate(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Op, MPI_Win);

HPAPIEXPORT extern
int HPMPIAPI MPI_Compare_and_swap(void *, void *, void *,
			MPI_Datatype, int, MPI_Aint, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Fetch_and_op(void *, void *, MPI_Datatype,
			int, MPI_Aint, MPI_Op, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win);
HPAPIEXPORT extern
int HPMPIAPI MPI_Raccumulate(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Rget_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Rget(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Rput(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Alloc_mem(MPI_Aint, MPI_Info, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Free_mem(void *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Is_thread_main(int *flag);
HPAPIEXPORT extern
int HPMPIAPI MPI_Init_thread(int *, char ***, int , int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Query_thread(int *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_set_name(MPI_Comm, char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_get_name(MPI_Comm, char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_set_name(MPI_Datatype, char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_name(MPI_Datatype, char *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_set_name(MPI_Win, char *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Win_get_name(MPI_Win, char *, int *);

HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_delete_attr(MPI_Comm, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_set_attr(MPI_Comm, int, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_get_attr(MPI_Comm, int, void *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *,
			MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_get_errhandler(MPI_Comm, MPI_Errhandler *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_set_errhandler(MPI_Comm, MPI_Errhandler);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *,
			MPI_Comm_delete_attr_function *, int *, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_free_keyval(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Comm_call_errhandler(MPI_Comm, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Get_address(void *, MPI_Aint *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_indexed_block(int, int, int *,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_hvector(int, int, MPI_Aint,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_dup(MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_resized(MPI_Datatype, MPI_Aint, MPI_Aint,
			MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_keyval(MPI_Type_copy_attr_function *,
			MPI_Type_delete_attr_function *, int*, void*);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_free_keyval(int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_set_attr(MPI_Datatype, int, void *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_get_attr(MPI_Datatype, int, void *, int *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_delete_attr(MPI_Datatype, int);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_f90_real(int, int, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_f90_complex(int, int, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_f90_integer(int, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_match_size(int, int, MPI_Datatype *);


/*
 * HP MPI extensions
 */
HPAPIEXPORT extern
int HPMPIAPI MPIHP_Comm_id(MPI_Comm, int *);
HPAPIEXPORT extern
int HPMPIAPI MPIHP_Type_id(MPI_Datatype, int *);
HPAPIEXPORT extern
int HPMPIAPI MPIHP_Trace_on(void);
HPAPIEXPORT extern
int HPMPIAPI MPIHP_Trace_off(void);

#endif /* !defined(MPI_hpux) || defined(_WIN32) */

#if !defined(MPI_hpux) || defined(HPMP_BUILD_DLIB) || defined(HPMP_BUILD_CXXBINDING)
/*
 * Profiling prototypes, for both users and internal building.
 */
HPMPIIMPORT extern int HPMPIAPI PMPI_Abort(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Address(void *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Allgather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Allgatherv(void *, int, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Allreduce(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Alltoall(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Alltoallv(void *, int *, int *, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Alltoallw(void *, int *, int *, MPI_Datatype*, void *,
			int *, int *, MPI_Datatype*, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Attr_delete(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Attr_get(MPI_Comm, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Attr_put(MPI_Comm, int, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Barrier(MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Bcast(void *, int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Bsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Bsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Buffer_attach(void *, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Buffer_detach(void *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cancel(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_coords(MPI_Comm, int, int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_get(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_map(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_rank(MPI_Comm, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_shift(MPI_Comm, int, int, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cart_sub(MPI_Comm, int *, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Cartdim_get(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_compare(MPI_Comm, MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_create(MPI_Comm, MPI_Group, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_create_group(MPI_Comm, MPI_Group, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_dup(MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_free(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_group(MPI_Comm, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_rank(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_remote_group(MPI_Comm, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_remote_size(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_size(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_split(MPI_Comm, int, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_split_type(MPI_Comm, int, int, MPI_Info, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_test_inter(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_dup_with_info(MPI_Comm, MPI_Info, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_idup(MPI_Comm, MPI_Comm *, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_get_info(MPI_Comm, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_set_info(MPI_Comm, MPI_Info);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_get_parent(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_spawn(char *, char **, int, MPI_Info, int,
			MPI_Comm, MPI_Comm *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_spawn_multiple(int, char **, char ***, int *,
			MPI_Info *, int, MPI_Comm, MPI_Comm *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_accept(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_connect(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_join(int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_disconnect(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Open_port(MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Close_port(char*);
/*
HPMPIIMPORT extern int HPMPIAPI PMPI_Publish_name(char*, MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Unpublish_name(char*, MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Lookup_name(char*, MPI_Info, char*);
*/
HPMPIIMPORT extern int HPMPIAPI PMPI_Dims_create(int, int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Errhandler_create(MPI_Handler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Errhandler_free(MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Errhandler_get(MPI_Comm, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Errhandler_set(MPI_Comm, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI PMPI_Error_class(int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Error_string(int, char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Add_error_class(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Add_error_code(int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Add_error_string(int, char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Finalize(void);
HPMPIIMPORT extern int HPMPIAPI PMPI_Finalized(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Gather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Gatherv(void *, int, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_count(MPI_Status *, MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_elements_x(MPI_Status *, MPI_Datatype, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_processor_name(char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_version(int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_library_version(char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graph_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graph_get(MPI_Comm, int, int, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graph_map(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graph_neighbors(MPI_Comm, int, int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graph_neighbors_count(MPI_Comm, int, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Graphdims_get(MPI_Comm, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_allgatherv(void *, int, MPI_Datatype, 
			void *, int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, MPI_Datatype *, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Dist_graph_create(MPI_Comm, int, int*, int*,
			int*, int*,	MPI_Info, int, MPI_Comm*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Dist_graph_create_adjacent(MPI_Comm, int, int*, int*,
			int, int*, int*,	MPI_Info, int, MPI_Comm*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Dist_graph_neighbors_count(MPI_Comm, int*, int*, int*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Dist_graph_neighbors(MPI_Comm, int, int*, int*,
			int, int*, int*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_compare(MPI_Group, MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_difference(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_excl(MPI_Group, int, int *, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_free(MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_incl(MPI_Group, int, int *, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_intersection(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_range_excl(MPI_Group, int, int [][3], MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_range_incl(MPI_Group, int, int [][3], MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_rank(MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_size(MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_translate_ranks(MPI_Group, int, int *,
			MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Group_union(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ibsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_allgatherv(void *, int, MPI_Datatype, 
			void *, int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Init(int *, char ***);
HPMPIIMPORT extern int HPMPIAPI PMPI_Initialized(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Intercomm_create(MPI_Comm, int, MPI_Comm, int,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Intercomm_merge(MPI_Comm, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iprobe(int, int, MPI_Comm, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Irecv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Irsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Isend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Issend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Keyval_create(MPI_Copy_function *,
			MPI_Delete_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Keyval_free(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Op_create(MPI_User_function *, int, MPI_Op *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Op_free(MPI_Op *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Op_commutative(MPI_Op, int*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Pack(void *, int, MPI_Datatype, void *, int,
			int *, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Pack_external(char *, void *, int, MPI_Datatype, void *,
                        MPI_Aint, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Pack_size(int, MPI_Datatype, MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Pack_external_size(char *, int, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Pcontrol(const int level, ...);
HPMPIIMPORT extern int HPMPIAPI PMPI_Probe(int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Mprobe(int, int, MPI_Comm, MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Improbe(int, int, MPI_Comm, int *, MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Recv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Mrecv(void *, int, MPI_Datatype, MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Imrecv(void *, int, MPI_Datatype, MPI_Message *, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Recv_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Reduce(void *, void *, int, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Reduce_local(void *, void *, int, MPI_Datatype,
			MPI_Op);
HPMPIIMPORT extern int HPMPIAPI PMPI_Reduce_scatter(void *, void *, int *,
 			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Reduce_scatter_block(void *, void *, int,
			MPI_Datatype, MPI_Op, MPI_Comm);

HPMPIIMPORT extern int HPMPIAPI PMPI_Ibcast(void *, int, MPI_Datatype, int,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ibarrier(MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Igather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Igatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iscatter(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iscatterv(void *, int *, int *, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iallgather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iallgatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ialltoall(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ialltoallv(void *, int *, int *, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ialltoallw(void *, int *, int *, MPI_Datatype *, 
			void *, int *, int *, MPI_Datatype *, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ireduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iallreduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ireduce_scatter(void *, void *, int *,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ireduce_scatter_block(void *, void *, int,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Iexscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Request_free(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Request_get_status(MPI_Request, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Grequest_start(MPI_Grequest_query_function*,
			MPI_Grequest_free_function*,
			MPI_Grequest_cancel_function*, void*, MPI_Request*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Grequest_complete(MPI_Request);
HPMPIIMPORT extern int HPMPIAPI PMPIX_Grequest_class_create(MPI_Grequest_query_function *,
                       MPI_Grequest_free_function *,
                       MPI_Grequest_cancel_function *, MPIX_Grequest_poll_fn *,
                       MPIX_Grequest_wait_fn *, MPIX_Grequest_class *);
HPMPIIMPORT extern int HPMPIAPI PMPIX_Grequest_class_allocate(MPIX_Grequest_class greq_class,
                       void *extra_state, MPI_Request *request);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Scan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Exscan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Scatter(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Scatterv(void *, int *, int *, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Send(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Send_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Sendrecv(void *, int, MPI_Datatype, int, int,
			void *, int, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Sendrecv_replace(void *, int, MPI_Datatype, int, int,
			int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ssend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ssend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Start(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Startall(int, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Test(MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Test_cancelled(MPI_Status *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Testall(int, MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Topo_test(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_commit(MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_extent(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_free(MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_contents(MPI_Datatype, int, int, int,
			int [], MPI_Aint [], MPI_Datatype []);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_envelope(MPI_Datatype, int *, int *,
			int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_extent(MPI_Datatype, MPI_Aint *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_extent_x(MPI_Datatype, MPI_Count *, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_true_extent(MPI_Datatype, MPI_Aint *,
			MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_true_extent_x(MPI_Datatype, MPI_Count *,
			MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_hvector(int, int, MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_indexed(int, int *, int *, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_lb(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_size(MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_size_x(MPI_Datatype, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_ub(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_vector(int, int, int, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Unpack(void *, int, int *, void *, int,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Unpack_external(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, int, MPI_Datatype);
HPMPIIMPORT extern int HPMPIAPI PMPI_Wait(MPI_Request *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Waitall(int, MPI_Request *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern double HPMPIAPI PMPI_Wtick(void);
HPMPIIMPORT extern double HPMPIAPI PMPI_Wtime(void);

HPMPIIMPORT extern MPI_Comm HPMPIAPI PMPI_Comm_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Datatype HPMPIAPI PMPI_Type_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Group HPMPIAPI PMPI_Group_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Op HPMPIAPI PMPI_Op_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Request HPMPIAPI PMPI_Request_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Win HPMPIAPI PMPI_Win_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Info HPMPIAPI PMPI_Info_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Errhandler HPMPIAPI PMPI_Errhandler_f2c(MPI_Fint);

HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Comm_c2f(MPI_Comm);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Type_c2f(MPI_Datatype);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Group_c2f(MPI_Group);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Op_c2f(MPI_Op);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Request_c2f(MPI_Request);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Win_c2f(MPI_Win);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Info_c2f(MPI_Info);
HPMPIIMPORT extern MPI_Fint HPMPIAPI PMPI_Errhandler_c2f(MPI_Errhandler);

HPMPIIMPORT extern int HPMPIAPI PMPI_Status_f2c(void *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Status_c2f(MPI_Status *, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Status_set_cancelled(MPI_Status *, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Status_set_elements(MPI_Status *, MPI_Datatype, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Status_set_elements_x(MPI_Status *, MPI_Datatype, MPI_Count);

HPMPIIMPORT extern int HPMPIAPI PMPI_Info_create(MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_delete(MPI_Info, const char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_dup(MPI_Info, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_free(MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_get(MPI_Info, const char *, int, char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_get_nkeys(MPI_Info, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_get_nthkey(MPI_Info, int, char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_get_valuelen(MPI_Info, const char *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Info_set(MPI_Info, const char *, const char *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Win_create(void *, MPI_Aint, int,
			MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_allocate(MPI_Aint, int, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_allocate_shared(MPI_Aint, int, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_fence(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_free(MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_get_group(MPI_Win, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_attach(MPI_Win, void *, MPI_Aint);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_detach(MPI_Win, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_create_dynamic(MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_flush(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_flush_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_flush_local(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_flush_local_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_get_info(MPI_Win, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_set_info(MPI_Win, MPI_Info);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_sync(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_lock(int, int, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_unlock(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_lock_all(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_unlock_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_shared_query(MPI_Win, int, MPI_Aint *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_start(MPI_Group, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_post(MPI_Group, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_complete(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_wait(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_test(MPI_Win, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_create_errhandler(MPI_Win_errhandler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_set_errhandler(MPI_Win, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_get_errhandler(MPI_Win, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_call_errhandler(MPI_Win, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_create_keyval(MPI_Win_copy_attr_function *,
			MPI_Win_delete_attr_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_set_attr(MPI_Win, int, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_get_attr(MPI_Win, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_delete_attr(MPI_Win, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Put(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Accumulate(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Op, MPI_Win);

HPMPIIMPORT extern int HPMPIAPI PMPI_Compare_and_swap(void *, void *, void *,
			MPI_Datatype, int, MPI_Aint, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Fetch_and_op(void *, void *, MPI_Datatype,
			int, MPI_Aint, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Raccumulate(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rget_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rget(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rput(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Alloc_mem(MPI_Aint, MPI_Info, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Free_mem(void *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Is_thread_main(int *flag);
HPMPIIMPORT extern int HPMPIAPI PMPI_Init_thread(int *, char ***, int , int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Query_thread(int *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_set_name(MPI_Comm, char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_get_name(MPI_Comm, char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_set_name(MPI_Datatype, char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_name(MPI_Datatype, char *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_set_name(MPI_Win, char *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_get_name(MPI_Win, char *, int *);

HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_delete_attr(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_set_attr(MPI_Comm, int, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_get_attr(MPI_Comm, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_get_errhandler(MPI_Comm, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_set_errhandler(MPI_Comm, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *,
			MPI_Comm_delete_attr_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Comm_call_errhandler(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_address(void *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_indexed_block(int, int, int *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_hvector(int, int, MPI_Aint,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_dup(MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_resized(MPI_Datatype, MPI_Aint, MPI_Aint,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_keyval(MPI_Type_copy_attr_function *,
			MPI_Type_delete_attr_function *, int*, void*);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_set_attr(MPI_Datatype, int, void *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_get_attr(MPI_Datatype, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_delete_attr(MPI_Datatype, int);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_f90_real(int, int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_f90_complex(int, int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_create_f90_integer(int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Type_match_size(int, int, MPI_Datatype *);

#endif /* !defined(MPI_hpux) || defined(HPMP_BUILD_DLIB) */

/*
 * Prototypes, for HPMPI entrypoints, only needed
 * for internal building.
 */
HPMPIIMPORT extern int HPMPIAPI HPMPI_Abort(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Address(void *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Allgather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Allgatherv(void *, int, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Allreduce(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Alltoall(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Alltoallv(void *, int *, int *, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Alltoallw(void *, int *, int *, MPI_Datatype*, void *,
			int *, int *, MPI_Datatype*, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Attr_delete(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Attr_get(MPI_Comm, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Attr_put(MPI_Comm, int, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Barrier(MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Bcast(void *, int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Bsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Bsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Buffer_attach(void *, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Buffer_detach(void *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cancel(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_coords(MPI_Comm, int, int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_get(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_map(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_rank(MPI_Comm, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_shift(MPI_Comm, int, int, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cart_sub(MPI_Comm, int *, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Cartdim_get(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_compare(MPI_Comm, MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_create(MPI_Comm, MPI_Group, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_create_group(MPI_Comm, MPI_Group, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_dup(MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_free(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_group(MPI_Comm, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_rank(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_remote_group(MPI_Comm, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_remote_size(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_size(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_split(MPI_Comm, int, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_split_type(MPI_Comm, int, int, MPI_Info, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_test_inter(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_dup_with_info(MPI_Comm, MPI_Info, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_idup(MPI_Comm, MPI_Comm *, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_get_info(MPI_Comm, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_set_info(MPI_Comm, MPI_Info);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_get_parent(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_spawn(char *, char **, int, MPI_Info, int,
			MPI_Comm, MPI_Comm *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_spawn_multiple(int, char **, char ***, int *,
			MPI_Info *, int, MPI_Comm, MPI_Comm *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_accept(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_connect(char*, MPI_Info, int, MPI_Comm, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_join(int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_disconnect(MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Open_port(MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Close_port(char*);
/*
HPMPIIMPORT extern int HPMPIAPI HPMPI_Publish_name(char*, MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Unpublish_name(char*, MPI_Info, char*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Lookup_name(char*, MPI_Info, char*);
*/
HPMPIIMPORT extern int HPMPIAPI HPMPI_Dims_create(int, int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Errhandler_create(MPI_Handler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Errhandler_free(MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Errhandler_get(MPI_Comm, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Errhandler_set(MPI_Comm, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Error_class(int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Error_string(int, char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Add_error_class(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Add_error_code(int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Add_error_string(int, char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Finalize(void);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Finalized(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Gather(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Gatherv(void *, int, MPI_Datatype, void *,
			int *, int *, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_count(MPI_Status *, MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_elements_x(MPI_Status *, MPI_Datatype, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_processor_name(char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_version(int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_library_version(char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graph_create(MPI_Comm, int, int *, int *,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graph_get(MPI_Comm, int, int, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graph_map(MPI_Comm, int, int *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graph_neighbors(MPI_Comm, int, int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graph_neighbors_count(MPI_Comm, int, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Graphdims_get(MPI_Comm, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_allgatherv(void *, int, MPI_Datatype, 
			void *, int *, int *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, 
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, 
			MPI_Datatype *, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Dist_graph_create(MPI_Comm, int, int*, int*,
			int*, int*,	MPI_Info, int, MPI_Comm*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Dist_graph_create_adjacent(MPI_Comm, int, int*, int*,
			int, int*, int*,	MPI_Info, int, MPI_Comm*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Dist_graph_neighbors_count(MPI_Comm, int*, int*, int*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Dist_graph_neighbors(MPI_Comm, int, int*, int*,
			int, int*, int*);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_compare(MPI_Group, MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_difference(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_excl(MPI_Group, int, int *, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_free(MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_incl(MPI_Group, int, int *, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_intersection(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_range_excl(MPI_Group, int, int [][3], MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_range_incl(MPI_Group, int, int [][3], MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_rank(MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_size(MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_translate_ranks(MPI_Group, int, int *,
			MPI_Group, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Group_union(MPI_Group, MPI_Group, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ibsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_allgather(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_allgatherv(void *, int, MPI_Datatype,
			void *, int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoall(void *, int, MPI_Datatype, 
			void *, int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoallv(void *, int *, int *, 
			MPI_Datatype, void *, int *, int *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoallw(void *, int *, MPI_Aint *, 
			MPI_Datatype *, void *, int *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Init(int *, char ***);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Initialized(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Intercomm_create(MPI_Comm, int, MPI_Comm, int,
			int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Intercomm_merge(MPI_Comm, int, MPI_Comm *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iprobe(int, int, MPI_Comm, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Irecv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Irsend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Isend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Issend(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Keyval_create(MPI_Copy_function *,
			MPI_Delete_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Keyval_free(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Op_create(MPI_User_function *, int, MPI_Op *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Op_free(MPI_Op *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Op_commutative(MPI_Op, int*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Pack(void *, int, MPI_Datatype, void *, int,
			int *, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Pack_external(char *, void *, int, MPI_Datatype, void *,
                        MPI_Aint, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Pack_size(int, MPI_Datatype, MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Pack_external_size(char *, int, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Pcontrol(const int level, ...);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Probe(int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Mprobe(int, int, MPI_Comm, MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Improbe(int, int, MPI_Comm, int *, MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Recv(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Mrecv(void *, int, MPI_Datatype, 
			MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Imrecv(void *, int, MPI_Datatype, 
			MPI_Message *, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Recv_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Reduce(void *, void *, int, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Reduce_local(void *, void *, int, MPI_Datatype,
			MPI_Op);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Reduce_scatter(void *, void *, int *,
 			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Reduce_scatter_block(void *, void *, int,
			MPI_Datatype, MPI_Op, MPI_Comm);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Ibcast(void *, int, MPI_Datatype, int,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ibarrier(MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Igather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Igatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iscatter(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iscatterv(void *, int *, int *, MPI_Datatype, void *,
		    int, MPI_Datatype, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iallgather(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iallgatherv(void *, int, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ialltoall(void *, int, MPI_Datatype, void *,
		    int, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ialltoallv(void *, int *, int *, MPI_Datatype, void *,
		    int *, int *, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ialltoallw(void *, int *, int *, MPI_Datatype *, 
			void *, int *, int *, MPI_Datatype *, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ireduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iallreduce(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ireduce_scatter(void *, void *, int *,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ireduce_scatter_block(void *, void *, int,
		    MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Iexscan(void *, void *, int, MPI_Datatype, MPI_Op,
		    MPI_Comm, MPI_Request *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Request_free(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Request_get_status(MPI_Request, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Grequest_start(MPI_Grequest_query_function*,
			MPI_Grequest_free_function*,
			MPI_Grequest_cancel_function*, void*, MPI_Request*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Grequest_complete(MPI_Request);
HPMPIIMPORT extern int HPMPIAPI HPMPIX_Grequest_class_create(MPI_Grequest_query_function *,
                       MPI_Grequest_free_function *,
                       MPI_Grequest_cancel_function *, MPIX_Grequest_poll_fn *,
                       MPIX_Grequest_wait_fn *, MPIX_Grequest_class *);
HPMPIIMPORT extern int HPMPIAPI HPMPIX_Grequest_class_allocate(MPIX_Grequest_class greq_class,
                       void *extra_state, MPI_Request *request);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rsend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rsend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Scan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Exscan(void *, void *, int, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Scatter(void *, int, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Scatterv(void *, int *, int *, MPI_Datatype, void *,
			int, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Send(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Send_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Sendrecv(void *, int, MPI_Datatype, int, int,
			void *, int, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Sendrecv_replace(void *, int, MPI_Datatype, int, int,
			int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ssend(void *, int, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ssend_init(void *, int, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Start(MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Startall(int, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Test(MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Test_cancelled(MPI_Status *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Testall(int, MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Topo_test(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_commit(MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_extent(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_free(MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_contents(MPI_Datatype, int, int, int,
			int [], MPI_Aint [], MPI_Datatype []);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_envelope(MPI_Datatype, int *, int *,
			int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_extent(MPI_Datatype, MPI_Aint *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_extent_x(MPI_Datatype, MPI_Count *, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_true_extent(MPI_Datatype, MPI_Aint *,
			MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_true_extent_x(MPI_Datatype, MPI_Count *,
			MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_hvector(int, int, MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_indexed(int, int *, int *, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_lb(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_size(MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_size_x(MPI_Datatype, MPI_Count *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_ub(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_vector(int, int, int, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Unpack(void *, int, int *, void *, int,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Unpack_external(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, int, MPI_Datatype);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Wait(MPI_Request *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Waitall(int, MPI_Request *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
HPMPIIMPORT extern double HPMPIAPI HPMPI_Wtick(void);
HPMPIIMPORT extern double HPMPIAPI HPMPI_Wtime(void);

HPMPIIMPORT extern MPI_Comm HPMPIAPI HPMPI_Comm_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Datatype HPMPIAPI HPMPI_Type_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Group HPMPIAPI HPMPI_Group_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Op HPMPIAPI HPMPI_Op_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Request HPMPIAPI HPMPI_Request_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Win HPMPIAPI HPMPI_Win_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Info HPMPIAPI HPMPI_Info_f2c(MPI_Fint);
HPMPIIMPORT extern MPI_Errhandler HPMPIAPI HPMPI_Errhandler_f2c(MPI_Fint);

HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Comm_c2f(MPI_Comm);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Type_c2f(MPI_Datatype);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Group_c2f(MPI_Group);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Op_c2f(MPI_Op);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Request_c2f(MPI_Request);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Win_c2f(MPI_Win);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Info_c2f(MPI_Info);
HPMPIIMPORT extern MPI_Fint HPMPIAPI HPMPI_Errhandler_c2f(MPI_Errhandler);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Status_f2c(void *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Status_c2f(MPI_Status *, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Status_set_cancelled(MPI_Status *, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Status_set_elements(MPI_Status *, MPI_Datatype, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Status_set_elements_x(MPI_Status *, MPI_Datatype, MPI_Count);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_create(MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_delete(MPI_Info, const char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_dup(MPI_Info, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_free(MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_get(MPI_Info, const char *, int, char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_get_nkeys(MPI_Info, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_get_nthkey(MPI_Info, int, char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_get_valuelen(MPI_Info, const char *, int *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Info_set(MPI_Info, const char *, const char *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_create(void *, MPI_Aint, int,
			MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_allocate(MPI_Aint, int, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_allocate_shared(MPI_Aint, int, MPI_Info,
			MPI_Info, MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_fence(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_free(MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_get_group(MPI_Win, MPI_Group *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_attach(MPI_Win, void *, MPI_Aint);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_detach(MPI_Win, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_create_dynamic(MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_flush(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_flush_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_flush_local(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_flush_local_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_get_info(MPI_Win, MPI_Info *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_set_info(MPI_Win, MPI_Info);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_sync(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_lock(int, int, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_unlock(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_lock_all(int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_unlock_all(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_shared_query(MPI_Win, int, MPI_Aint *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_start(MPI_Group, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_post(MPI_Group, int, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_complete(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_wait(MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_test(MPI_Win, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_create_errhandler(MPI_Win_errhandler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_set_errhandler(MPI_Win, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_get_errhandler(MPI_Win, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_call_errhandler(MPI_Win, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_create_keyval(MPI_Win_copy_attr_function *,
			MPI_Win_delete_attr_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_set_attr(MPI_Win, int, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_get_attr(MPI_Win, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_delete_attr(MPI_Win, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Put(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Accumulate(void *, int, MPI_Datatype, int, MPI_Aint,
			int, MPI_Datatype, MPI_Op, MPI_Win);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Compare_and_swap(void *, void *, void *,
			MPI_Datatype, int, MPI_Aint, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Fetch_and_op(void *, void *, MPI_Datatype,
			int, MPI_Aint, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Raccumulate(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rget_accumulate(void *, int, MPI_Datatype,
			void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rget(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rput(void *, int, MPI_Datatype,
			int, MPI_Aint, int, MPI_Datatype, MPI_Win,
			MPI_Request *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Alloc_mem(MPI_Aint, MPI_Info, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Free_mem(void *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Is_thread_main(int *flag);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Init_thread(int *, char ***, int , int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Query_thread(int *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_set_name(MPI_Comm, char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_get_name(MPI_Comm, char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_set_name(MPI_Datatype, char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_name(MPI_Datatype, char *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_set_name(MPI_Win, char *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_get_name(MPI_Win, char *, int *);

HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_delete_attr(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_set_attr(MPI_Comm, int, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_get_attr(MPI_Comm, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *,
			MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_get_errhandler(MPI_Comm, MPI_Errhandler *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_set_errhandler(MPI_Comm, MPI_Errhandler);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *,
			MPI_Comm_delete_attr_function *, int *, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Comm_call_errhandler(MPI_Comm, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_address(void *, MPI_Aint *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_indexed_block(int, int, int *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_hindexed(int, int *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_hvector(int, int, MPI_Aint,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_struct(int, int *, MPI_Aint *,
			MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_dup(MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_resized(MPI_Datatype, MPI_Aint, MPI_Aint,
			MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_keyval(MPI_Type_copy_attr_function *,
			MPI_Type_delete_attr_function *, int*, void*);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_free_keyval(int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_set_attr(MPI_Datatype, int, void *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_get_attr(MPI_Datatype, int, void *, int *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_delete_attr(MPI_Datatype, int);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_f90_real(int, int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_f90_complex(int, int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_create_f90_integer(int, MPI_Datatype *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Type_match_size(int, int, MPI_Datatype *);

/*
 * HP MPI extensions
 */
HPMPIIMPORT extern int HPMPIAPI PMPIHP_Comm_id(MPI_Comm, int *);
HPMPIIMPORT extern int HPMPIAPI PMPIHP_Type_id(MPI_Datatype, int *);
HPMPIIMPORT extern int HPMPIAPI PMPIHP_Trace_on(void);
HPMPIIMPORT extern int HPMPIAPI PMPIHP_Trace_off(void);

#else /* !defined(__STDC__) && !defined(c_plusplus) && !defined(__cplusplus) && !defined(_WIN32)*/

/*
 * All functions DO NOT return an integer.
 */

#if !defined(MPI_hpux) || defined(HPMP_BUILD_CXXBINDING)

/*
 * Function prototype only for users.
 */
extern double MPI_Wtick();
extern double MPI_Wtime();

extern MPI_Comm MPI_Comm_f2c();
extern MPI_Datatype MPI_Type_f2c();
extern MPI_Group MPI_Group_f2c();
extern MPI_Op MPI_Op_f2c();
extern MPI_Request MPI_Request_f2c();
extern MPI_Win MPI_Win_f2c();
extern MPI_Info MPI_Info_f2c();
extern MPI_Errhandler MPI_Errhandler_f2c();

extern MPI_Fint MPI_Comm_c2f();
extern MPI_Fint MPI_Type_c2f();
extern MPI_Fint MPI_Group_c2f();
extern MPI_Fint MPI_Op_c2f();
extern MPI_Fint MPI_Request_c2f();
extern MPI_Fint MPI_Win_c2f();
extern MPI_Fint MPI_Info_c2f();
extern MPI_Fint MPI_Errhandler_c2f();

#endif /* MPI_hpux */

/*
 * Profiling prototypes, for both users and internal building.
 */
extern double PMPI_Wtick();
extern double PMPI_Wtime();

extern MPI_Comm PMPI_Comm_f2c();
extern MPI_Datatype PMPI_Type_f2c();
extern MPI_Group PMPI_Group_f2c();
extern MPI_Op PMPI_Op_f2c();
extern MPI_Request PMPI_Request_f2c();
extern MPI_Win PMPI_Win_f2c();
extern MPI_Info PMPI_Info_f2c();
extern MPI_Errhandler PMPI_Errhandler_f2c();

extern MPI_Fint PMPI_Comm_c2f();
extern MPI_Fint PMPI_Type_c2f();
extern MPI_Fint PMPI_Group_c2f();
extern MPI_Fint PMPI_Op_c2f();
extern MPI_Fint PMPI_Request_c2f();
extern MPI_Fint PMPI_Win_c2f();
extern MPI_Fint PMPI_Info_c2f();
extern MPI_Fint PMPI_Errhandler_c2f();

#endif /* defined(__STDC__) || defined(c_plusplus) || defined(__cplusplus) */

#ifndef HP_MPI_NOIO
#include <mpio.h>
#endif	/* HP_MPI_NOIO */

#ifdef HPMPI_LONG_EXTENTIONS
#ifdef MPI_hpux
/* internal building */
#include <mpiLONG.h>
#else
#include <mpiL.h>
#endif
#endif

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif
#if !defined(_WIN32)
/* Windows does not support  C++-bindings */
#if defined(c_plusplus) || defined(__cplusplus)
#include <mpiCC.h>
#endif
#endif

#endif	/* _MPI_H */
