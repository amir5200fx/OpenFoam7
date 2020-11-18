/* -*- Mode: C; c-basic-offset:4 ; -*- */
/* 
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */

/* user include file for MPI-IO programs */

#ifndef MPIO_INCLUDE
#define MPIO_INCLUDE

#include "mpi.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef MPIO_IMPORT
#  if defined(_WIN32) && !defined(MPI_hpux)
#    define MPIO_IMPORT __declspec(dllimport)
#    define MPIO_API __stdcall
#  else
#    define MPIO_IMPORT
#    define MPIO_API
#  endif
#endif

#define ROMIO_VERSION 126 /* version 1.2.6 */

/* define MPI-IO datatypes and constants */

#ifndef MPI_FILE_DEFINED
typedef struct ADIOI_FileD *MPI_File;
#endif

#define HAVE_MPI_GREQUEST 1
#ifndef HAVE_MPI_GREQUEST
typedef struct ADIOI_RequestD *MPIO_Request;  
#else
#define MPIO_Request MPI_Request
#define MPIO_USES_MPI_REQUEST
/* Also rename the MPIO routines to get the MPI versions */
#define MPIO_Wait MPI_Wait
#define MPIO_Test MPI_Test
#define PMPIO_Wait PMPI_Wait
#define PMPIO_Test PMPI_Test
#endif
#define MPIO_REQUEST_DEFINED

#ifndef HAVE_MPI_OFFSET
typedef long long MPI_Offset;
/* If we needed to define MPI_Offset, then we also need to make
   this definition. */
#ifndef HAVE_MPI_DATAREP_FUNCTIONS
#define HAVE_MPI_DATAREP_FUNCTIONS
typedef int (MPI_Datarep_conversion_function)(void *, MPI_Datatype, int, 
             void *, MPI_Offset, void *);
typedef int (MPI_Datarep_extent_function)(MPI_Datatype datatype, MPI_Aint *,
					  void *);
#endif
#endif

#ifndef NEEDS_MPI_FINT

#endif
#ifdef NEEDS_MPI_FINT
typedef int MPI_Fint; 
#endif

#ifndef HAVE_MPI_INFO
#define HAVE_MPI_INFO
#endif
#ifndef HAVE_MPI_INFO
  typedef struct MPIR_Info *MPI_Info;
# define MPI_INFO_NULL         ((MPI_Info) 0)
# define MPI_MAX_INFO_KEY       255
# define MPI_MAX_INFO_VAL      1024
#endif

#define MPI_MODE_RDONLY              2  /* ADIO_RDONLY */
#define MPI_MODE_RDWR                8  /* ADIO_RDWR  */
#define MPI_MODE_WRONLY              4  /* ADIO_WRONLY  */
#define MPI_MODE_CREATE              1  /* ADIO_CREATE */ 
#define MPI_MODE_EXCL               64  /* ADIO_EXCL */
#define MPI_MODE_DELETE_ON_CLOSE    16  /* ADIO_DELETE_ON_CLOSE */
#define MPI_MODE_UNIQUE_OPEN        32  /* ADIO_UNIQUE_OPEN */
#define MPI_MODE_APPEND            128  /* ADIO_APPEND */
#define MPI_MODE_SEQUENTIAL        256  /* ADIO_SEQUENTIAL */

#define MPI_DISPLACEMENT_CURRENT   -54278278

#ifndef MPICH
/* FIXME: Make sure that we get a consistent definition of MPI_FILE_NULL
	in MPICH */
/* MPICH defines null object handles differently */
#define MPI_FILE_NULL           ((MPI_File) 0)
#endif
#define MPIO_REQUEST_NULL       ((MPIO_Request) 0)

#define MPI_SEEK_SET            600
#define MPI_SEEK_CUR            602
#define MPI_SEEK_END            604

/* Open MPI: don't define MPI_MAX_DATAREP_STRING here; it's defined in
   OMPI's mpi.h. */
#ifndef OPEN_MPI
#define MPI_MAX_DATAREP_STRING  128
#endif

#ifndef HAVE_MPI_DARRAY_SUBARRAY

#endif
#ifndef HAVE_MPI_DARRAY_SUBARRAY
#  define MPI_ORDER_C             56
#  define MPI_ORDER_FORTRAN       57
#  define MPI_DISTRIBUTE_BLOCK    121
#  define MPI_DISTRIBUTE_CYCLIC   122
#  define MPI_DISTRIBUTE_NONE     123
#  define MPI_DISTRIBUTE_DFLT_DARG -49767
#endif

/*
 *  MPIO related error codes.
 */
#define MPI_ERR_ACCESS          35              /* permission denied */
#define MPI_ERR_AMODE           36              /* amode error to open */
#define MPI_ERR_BAD_FILE        37              /* invalid file name */
#define MPI_ERR_CONVERSION      38              /* error in conversion func */
#define MPI_ERR_DUP_DATAREP     39              /* duplicated data rep. */
#define MPI_ERR_FILE            40              /* invalid file handle */
#define MPI_ERR_FILE_EXISTS     41              /* file exists */
#define MPI_ERR_FILE_IN_USE     42              /* file is used by other proc */
#define MPI_ERR_IO              43              /* other i/o error */
#define MPI_ERR_NO_SPACE        44              /* not enough space */
#define MPI_ERR_NO_SUCH_FILE    45              /* file doesn't exist */
#define MPI_ERR_NOT_SAME        46              /* arg. not idential */
#define MPI_ERR_QUOTA           47              /* quota exceeded */
#define MPI_ERR_READ_ONLY       48              /* file is read-only */
#define MPI_ERR_UNSUPPORTED_DATAREP 49          /* datarep is not supported */
#define MPI_ERR_UNSUPPORTED_OPERATION 50        /* operation is not supported */

#ifndef MPIO_USE_CONST
#define MPIO_CONST
#else
#define MPIO_CONST const
#endif

#ifndef MPI_hpux
/* MPI-IO function prototypes */

/* The compiler must support ANSI C style prototypes, otherwise 
   long long constants (e.g. 0) may get passed as ints. */

#ifndef HAVE_PRAGMA_HP_SEC_DEF

/* Section 9.2 */
/* Begin Prototypes */
MPIO_IMPORT extern int MPIO_API MPI_File_open(MPI_Comm comm, MPIO_CONST char *filename, int amode, MPI_Info info, MPI_File *fh);
MPIO_IMPORT extern int MPIO_API MPI_File_close(MPI_File *fh);
MPIO_IMPORT extern int MPIO_API MPI_File_delete(MPIO_CONST char *filename, MPI_Info info);
MPIO_IMPORT extern int MPIO_API MPI_File_set_size(MPI_File fh, MPI_Offset size);
MPIO_IMPORT extern int MPIO_API MPI_File_preallocate(MPI_File fh, MPI_Offset size);
MPIO_IMPORT extern int MPIO_API MPI_File_get_size(MPI_File fh, MPI_Offset *size);
MPIO_IMPORT extern int MPIO_API MPI_File_get_group(MPI_File fh, MPI_Group *group);
MPIO_IMPORT extern int MPIO_API MPI_File_get_amode(MPI_File fh, int *amode);
MPIO_IMPORT extern int MPIO_API MPI_File_set_info(MPI_File fh, MPI_Info info);
MPIO_IMPORT extern int MPIO_API MPI_File_get_info(MPI_File fh, MPI_Info *info_used);

/* Section 9.3 */
MPIO_IMPORT extern int MPIO_API MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype,
                      MPIO_CONST char *datarep, MPI_Info info);
MPIO_IMPORT extern int MPIO_API MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype,
                      char *datarep);

/* Section 9.4.2 */
MPIO_IMPORT extern int MPIO_API MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype,
                     MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count,
                         MPI_Datatype datatype, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_at(MPI_File fh, MPI_Offset offset, MPIO_CONST void * buf, int count,
                      MPI_Datatype datatype, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, MPIO_CONST void *buf, int count,
                          MPI_Datatype datatype, MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 
MPIO_IMPORT extern int MPIO_API MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype,
                      MPIO_Request *request);
MPIO_IMPORT extern int MPIO_API MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, MPIO_CONST void *buf, int count,
                       MPI_Datatype datatype, MPIO_Request *request);

/* Section 9.4.3 */
MPIO_IMPORT extern int MPIO_API MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                   MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_all(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                       MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

MPIO_IMPORT extern int MPIO_API MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request);
MPIO_IMPORT extern int MPIO_API MPI_File_iwrite(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                    MPIO_Request *request);

MPIO_IMPORT extern int MPIO_API MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
MPIO_IMPORT extern int MPIO_API MPI_File_get_position(MPI_File fh, MPI_Offset *offset);
MPIO_IMPORT extern int MPIO_API MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);

/* Section 9.4.4 */
MPIO_IMPORT extern int MPIO_API MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                         MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_shared(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                          MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                          MPIO_Request *request);
MPIO_IMPORT extern int MPIO_API MPI_File_iwrite_shared(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                           MPIO_Request *request);
MPIO_IMPORT extern int MPIO_API MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype,
                          MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_ordered(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype,
                           MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence);
MPIO_IMPORT extern int MPIO_API MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset);

/* Section 9.4.5 */
MPIO_IMPORT extern int MPIO_API MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count,
                               MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, MPIO_CONST void *buf, int count,
                                MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_write_at_all_end(MPI_File fh, MPIO_CONST void *buf, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_all_begin(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_write_all_end(MPI_File fh, MPIO_CONST void *buf, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
MPIO_IMPORT extern int MPIO_API MPI_File_write_ordered_begin(MPI_File fh, MPIO_CONST void *buf, int count, MPI_Datatype datatype);
MPIO_IMPORT extern int MPIO_API MPI_File_write_ordered_end(MPI_File fh, MPIO_CONST void *buf, MPI_Status *status);

/* Section 9.5.1 */
MPIO_IMPORT extern int MPIO_API MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent);

/* Section 9.5.3 */
MPIO_IMPORT extern int MPIO_API MPI_Register_datarep(MPIO_CONST char *datarep, MPI_Datarep_conversion_function *read_conversion_fn,
			 MPI_Datarep_conversion_function *write_conversion_fn,
			 MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);

/* Section 9.6.1 */
MPIO_IMPORT extern int MPIO_API MPI_File_set_atomicity(MPI_File fh, int flag);
MPIO_IMPORT extern int MPIO_API MPI_File_get_atomicity(MPI_File fh, int *flag);
MPIO_IMPORT extern int MPIO_API MPI_File_sync(MPI_File fh);

/* Section 4.13.3 */
#ifndef MPICH
/* MPICH provides these definitions */
MPIO_IMPORT extern int MPIO_API MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler);
MPIO_IMPORT extern int MPIO_API MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler);
#endif
/* End Prototypes */

#ifndef HAVE_MPI_DARRAY_SUBARRAY
/* Section 4.14.4 */
MPIO_IMPORT extern int MPIO_API MPI_Type_create_subarray(int ndims, MPIO_CONST int array_of_sizes[], MPIO_CONST int array_of_subsizes[],
                             MPIO_CONST int array_of_starts[], int order, MPI_Datatype oldtype,
                             MPI_Datatype *newtype);

/* Section 4.14.5 */
MPIO_IMPORT extern int MPIO_API MPI_Type_create_darray(int size, int rank, int ndims, MPIO_CONST int array_of_gsizes[],
                           MPIO_CONST int array_of_distribs[], MPIO_CONST int array_of_dargs[],
                           MPIO_CONST int array_of_psizes[], int order, MPI_Datatype oldtype,
                           MPI_Datatype *newtype);
#endif

/* The globus2 device has to rename MPI_ symbols in order to use the vendor
   MPI as one of its transport mechanisms.  Therefore, the following undefines
   should only happen if MPICH_RENAMING_MPI_FUNCS is not defined. */
/* Section 4.12.4 */
#if !defined(MPICH_RENAMING_MPI_FUNCS)
#ifdef MPI_File_f2c
#undef MPI_File_f2c
#endif
#ifdef MPI_File_c2f
#undef MPI_File_c2f
#endif
#endif
/* above needed for some versions of mpi.h in MPICH!! */
MPIO_IMPORT extern MPI_File MPIO_API MPI_File_f2c(MPI_Fint file);
MPIO_IMPORT extern MPI_Fint MPIO_API MPI_File_c2f(MPI_File file);


#ifndef HAVE_MPI_GREQUEST
/* The following functions are required if generalized requests are not
   available, because in that case, an MPIO_Request object
   is currently used for nonblocking I/O. */
int MPIO_Test(MPIO_Request *request, int *flag, MPI_Status *status);
int MPIO_Wait(MPIO_Request *request, MPI_Status *status);
int MPIO_Testall(int count, MPIO_Request array_of_requests[], int *flag,
                 MPI_Status array_of_statuses[]);
int MPIO_Waitall(int count, MPIO_Request array_of_requests[], MPI_Status array_of_statuses[]);
int MPIO_Testany(int count, MPIO_Request array_of_requests[], int *indx, int *flag,
                 MPI_Status *status);
int MPIO_Waitany(int count, MPIO_Request array_of_requests[], int *indx, MPI_Status *status);
int MPIO_Waitsome(int incount, MPIO_Request array_of_requests[], int *outcount,
                  int array_of_indices[], MPI_Status array_of_statuses[]);
int MPIO_Testsome(int incount, MPIO_Request array_of_requests[], int *outcount,
                  int array_of_indices[], MPI_Status array_of_statuses[]);

MPI_Fint MPIO_Request_c2f(MPIO_Request request);
MPIO_Request MPIO_Request_f2c(MPI_Fint request);
#endif /* HAVE_MPI_GREQUEST */

/* info functions if not defined in the MPI implementation */
#ifndef HAVE_MPI_INFO

MPIO_IMPORT extern int MPIO_API MPI_Info_create(MPI_Info *info);
MPIO_IMPORT extern int MPIO_API MPI_Info_set(MPI_Info info, MPIO_CONST char *key, MPIO_CONST char *value);
MPIO_IMPORT extern int MPIO_API MPI_Info_delete(MPI_Info info, MPIO_CONST char *key);
MPIO_IMPORT extern int MPIO_API MPI_Info_get(MPI_Info info, MPIO_CONST char *key, int valuelen, char *value, int *flag);
MPIO_IMPORT extern int MPIO_API MPI_Info_get_valuelen(MPI_Info info, MPIO_CONST char *key, int *valuelen, int *flag);
MPIO_IMPORT extern int MPIO_API MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
MPIO_IMPORT extern int MPIO_API MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
MPIO_IMPORT extern int MPIO_API MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
MPIO_IMPORT extern int MPIO_API MPI_Info_free(MPI_Info *info);

/* The globus2 device has to rename MPI_ symbols in order to use the vendor
   MPI as one of its transport mechanisms.  Therefore, the following undefines
   should only happen if MPICH_RENAMING_MPI_FUNCS is not defined. */
#if !defined(MPICH_RENAMING_MPI_FUNCS)
#ifdef MPI_Info_f2c
#undef MPI_Info_f2c
#endif
#ifdef MPI_Info_c2f
#undef MPI_Info_c2f
#endif
#endif
/* above needed for some versions of mpi.h in MPICH!! */
MPIO_IMPORT extern MPI_Fint MPIO_API MPI_Info_c2f(MPI_Info info);
MPIO_IMPORT extern MPI_Info MPIO_API MPI_Info_f2c(MPI_Fint info);
#endif

#endif   /* HAVE_PRAGMA_HP_SEC_DEF */


/**************** BINDINGS FOR THE PROFILING INTERFACE ***************/


/* Section 9.2 */
MPIO_IMPORT extern int MPIO_API PMPI_File_open(MPI_Comm, MPIO_CONST char *, int, MPI_Info, MPI_File *);
MPIO_IMPORT extern int MPIO_API PMPI_File_close(MPI_File *);
MPIO_IMPORT extern int MPIO_API PMPI_File_delete(MPIO_CONST char *, MPI_Info);
MPIO_IMPORT extern int MPIO_API PMPI_File_set_size(MPI_File, MPI_Offset);
MPIO_IMPORT extern int MPIO_API PMPI_File_preallocate(MPI_File, MPI_Offset);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_size(MPI_File, MPI_Offset *);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_group(MPI_File, MPI_Group *);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_amode(MPI_File, int *);
MPIO_IMPORT extern int MPIO_API PMPI_File_set_info(MPI_File, MPI_Info);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_info(MPI_File, MPI_Info *);

/* Section 9.3 */
MPIO_IMPORT extern int MPIO_API PMPI_File_set_view(MPI_File, MPI_Offset, 
    MPI_Datatype, MPI_Datatype, MPIO_CONST char *, MPI_Info);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_view(MPI_File, MPI_Offset *, 
      MPI_Datatype *, MPI_Datatype *, char *);

/* Section 9.4.2 */
MPIO_IMPORT extern int MPIO_API PMPI_File_read_at(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_at_all(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_at(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_at_all(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPI_Status *);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

MPIO_IMPORT extern int MPIO_API PMPI_File_iread_at(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPIO_Request *);
MPIO_IMPORT extern int MPIO_API PMPI_File_iwrite_at(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPIO_Request *);

/* Section 9.4.3 */
MPIO_IMPORT extern int MPIO_API PMPI_File_read(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_all(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_all(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

MPIO_IMPORT extern int MPIO_API PMPI_File_iread(MPI_File, void *, int, MPI_Datatype, MPIO_Request *);
MPIO_IMPORT extern int MPIO_API PMPI_File_iwrite(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPIO_Request *);

MPIO_IMPORT extern int MPIO_API PMPI_File_seek(MPI_File, MPI_Offset, int);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_position(MPI_File, MPI_Offset *);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_byte_offset(MPI_File, MPI_Offset, MPI_Offset *);

/* Section 9.4.4 */
MPIO_IMPORT extern int MPIO_API PMPI_File_read_shared(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_shared(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_iread_shared(MPI_File, void *, int, 
			   MPI_Datatype, MPIO_Request *);
MPIO_IMPORT extern int MPIO_API PMPI_File_iwrite_shared(MPI_File, MPIO_CONST void *, int,
			    MPI_Datatype, MPIO_Request *);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_ordered(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_ordered(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_seek_shared(MPI_File, MPI_Offset, int);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_position_shared(MPI_File, MPI_Offset *);

/* Section 9.4.5 */
MPIO_IMPORT extern int MPIO_API PMPI_File_read_at_all_begin(MPI_File, MPI_Offset, void *,
                               int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_at_all_end(MPI_File, void *, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_at_all_begin(MPI_File, MPI_Offset, MPIO_CONST void *,
                                 int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_at_all_end(MPI_File, MPIO_CONST void *, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_all_begin(MPI_File, void *, int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_all_end(MPI_File, void *, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_all_begin(MPI_File, MPIO_CONST void *, int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_all_end(MPI_File, MPIO_CONST void *, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_ordered_begin(MPI_File, void *, int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_read_ordered_end(MPI_File, void *, MPI_Status *);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_ordered_begin(MPI_File, MPIO_CONST void *, int, MPI_Datatype);
MPIO_IMPORT extern int MPIO_API PMPI_File_write_ordered_end(MPI_File, MPIO_CONST void *, MPI_Status *);

/* Section 9.5.1 */
MPIO_IMPORT extern int MPIO_API PMPI_File_get_type_extent(MPI_File, MPI_Datatype, MPI_Aint *);

/* Section 9.5.3 */
MPIO_IMPORT extern int MPIO_API PMPI_Register_datarep(MPIO_CONST char *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_extent_function *,
			 void *);

/* Section 9.6.1 */
MPIO_IMPORT extern int MPIO_API PMPI_File_set_atomicity(MPI_File, int);
MPIO_IMPORT extern int MPIO_API PMPI_File_get_atomicity(MPI_File, int *);
MPIO_IMPORT extern int MPIO_API PMPI_File_sync(MPI_File);

/* Section 4.13.3 */
#ifndef MPICH
/* MPICH provides these definitions */
MPIO_IMPORT extern int MPIO_API PMPI_File_set_errhandler( MPI_File, MPI_Errhandler );
MPIO_IMPORT extern int MPIO_API PMPI_File_get_errhandler( MPI_File, MPI_Errhandler * );
#endif

#ifndef HAVE_MPI_DARRAY_SUBARRAY
/* Section 4.14.4 */
MPIO_IMPORT extern int MPIO_API PMPI_Type_create_subarray(int, int *, int *, int *, int, 
                      MPI_Datatype, MPI_Datatype *);

/* Section 4.14.5 */
MPIO_IMPORT extern int MPIO_API PMPI_Type_create_darray(int, int, int, int *, int *, 
                    int *, int *, int, MPI_Datatype, MPI_Datatype *);
#endif

/* Section 4.12.4 */
MPIO_IMPORT extern MPI_File MPIO_API PMPI_File_f2c(MPI_Fint);
MPIO_IMPORT extern MPI_Fint MPIO_API PMPI_File_c2f(MPI_File);

#ifndef HAVE_MPI_GREQUEST
/* The following functions are required if generalized requests are not
   available, because in that case, an MPIO_Request object
   is currently used for nonblocking I/O. */
int PMPIO_Test(MPIO_Request *, int *, MPI_Status *);
int PMPIO_Wait(MPIO_Request *, MPI_Status *);
int PMPIO_Testall(int, MPIO_Request *, int *, MPI_Status *);
int PMPIO_Waitall(int, MPIO_Request *, MPI_Status *);
int PMPIO_Testany(int, MPIO_Request *, int *, int *, MPI_Status *);
int PMPIO_Waitany(int, MPIO_Request *, int *, MPI_Status *);
int PMPIO_Waitsome(int, MPIO_Request *, int *, int *, MPI_Status *);
int PMPIO_Testsome(int, MPIO_Request *, int *, int *, MPI_Status *);
MPI_Fint PMPIO_Request_c2f(MPIO_Request);
MPIO_Request PMPIO_Request_f2c(MPI_Fint);
#endif /* HAVE_MPI_GREQUEST */

/* info functions if not defined in the MPI implementation */
#ifndef HAVE_MPI_INFO

MPIO_IMPORT extern int MPIO_API PMPI_Info_create(MPI_Info *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_set(MPI_Info, char *, char *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_delete(MPI_Info, char *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_get(MPI_Info, char *, int, char *, int *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_get_valuelen(MPI_Info, char *, int *, int *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_get_nkeys(MPI_Info, int *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_get_nthkey(MPI_Info, int, char *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_dup(MPI_Info, MPI_Info *);
MPIO_IMPORT extern int MPIO_API PMPI_Info_free(MPI_Info *);

MPIO_IMPORT extern MPI_Fint MPIO_API PMPI_Info_c2f(MPI_Info);
MPIO_IMPORT extern MPI_Info MPIO_API PMPI_Info_f2c(MPI_Fint);
#endif
#endif

// Declarations for routines still in our romio build
typedef void (MPI_File_errhandler_function)(MPI_File *, int *, ...);
typedef MPI_File_errhandler_function MPI_File_errhandler_fn;
#ifndef MPI_hpux
MPIO_IMPORT extern int MPIO_API MPI_File_create_errhandler(
    MPI_File_errhandler_function *func, MPI_Errhandler *hdl);
MPIO_IMPORT extern int MPIO_API MPI_File_call_errhandler(
    MPI_File file, int errcode);
MPIO_IMPORT extern int MPIO_API PMPI_File_create_errhandler(
    MPI_File_errhandler_function *func, MPI_Errhandler *hdl);
MPIO_IMPORT extern int MPIO_API PMPI_File_call_errhandler(
    MPI_File file, int errcode);
#endif
MPIO_IMPORT extern int MPIO_API HPMPI_File_create_errhandler(
    MPI_File_errhandler_function *func, MPI_Errhandler *hdl);
MPIO_IMPORT extern int MPIO_API HPMPI_File_call_errhandler(
    MPI_File file, int errcode);

// ============ HPMPI_ declarations ===============

/* Section 9.2 */
int HPMPI_File_open(MPI_Comm, MPIO_CONST char *, int, MPI_Info, MPI_File *);
int HPMPI_File_close(MPI_File *);
int HPMPI_File_delete(MPIO_CONST char *, MPI_Info);
int HPMPI_File_set_size(MPI_File, MPI_Offset);
int HPMPI_File_preallocate(MPI_File, MPI_Offset);
int HPMPI_File_get_size(MPI_File, MPI_Offset *);
int HPMPI_File_get_group(MPI_File, MPI_Group *);
int HPMPI_File_get_amode(MPI_File, int *);
int HPMPI_File_set_info(MPI_File, MPI_Info);
int HPMPI_File_get_info(MPI_File, MPI_Info *);

/* Section 9.3 */
int HPMPI_File_set_view(MPI_File, MPI_Offset, 
    MPI_Datatype, MPI_Datatype, MPIO_CONST char *, MPI_Info);
int HPMPI_File_get_view(MPI_File, MPI_Offset *, 
      MPI_Datatype *, MPI_Datatype *, char *);

/* Section 9.4.2 */
int HPMPI_File_read_at(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPI_Status *);
int HPMPI_File_read_at_all(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write_at(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write_at_all(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPI_Status *);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

int HPMPI_File_iread_at(MPI_File, MPI_Offset, void *,
	      int, MPI_Datatype, MPIO_Request *);
int HPMPI_File_iwrite_at(MPI_File, MPI_Offset, MPIO_CONST void *,
	      int, MPI_Datatype, MPIO_Request *);

/* Section 9.4.3 */
int HPMPI_File_read(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_read_all(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write_all(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

int HPMPI_File_iread(MPI_File, void *, int, MPI_Datatype, MPIO_Request *);
int HPMPI_File_iwrite(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPIO_Request *);

int HPMPI_File_seek(MPI_File, MPI_Offset, int);
int HPMPI_File_get_position(MPI_File, MPI_Offset *);
int HPMPI_File_get_byte_offset(MPI_File, MPI_Offset, MPI_Offset *);

/* Section 9.4.4 */
int HPMPI_File_read_shared(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write_shared(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_iread_shared(MPI_File, void *, int, 
			   MPI_Datatype, MPIO_Request *);
int HPMPI_File_iwrite_shared(MPI_File, MPIO_CONST void *, int,
			    MPI_Datatype, MPIO_Request *);
int HPMPI_File_read_ordered(MPI_File, void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_write_ordered(MPI_File, MPIO_CONST void *, int, MPI_Datatype, MPI_Status *);
int HPMPI_File_seek_shared(MPI_File, MPI_Offset, int);
int HPMPI_File_get_position_shared(MPI_File, MPI_Offset *);

/* Section 9.4.5 */
int HPMPI_File_read_at_all_begin(MPI_File, MPI_Offset, void *,
                               int, MPI_Datatype);
int HPMPI_File_read_at_all_end(MPI_File, void *, MPI_Status *);
int HPMPI_File_write_at_all_begin(MPI_File, MPI_Offset, MPIO_CONST void *,
                                 int, MPI_Datatype);
int HPMPI_File_write_at_all_end(MPI_File, MPIO_CONST void *, MPI_Status *);
int HPMPI_File_read_all_begin(MPI_File, void *, int, MPI_Datatype);
int HPMPI_File_read_all_end(MPI_File, void *, MPI_Status *);
int HPMPI_File_write_all_begin(MPI_File, MPIO_CONST void *, int, MPI_Datatype);
int HPMPI_File_write_all_end(MPI_File, MPIO_CONST void *, MPI_Status *);
int HPMPI_File_read_ordered_begin(MPI_File, void *, int, MPI_Datatype);
int HPMPI_File_read_ordered_end(MPI_File, void *, MPI_Status *);
int HPMPI_File_write_ordered_begin(MPI_File, MPIO_CONST void *, int, MPI_Datatype);
int HPMPI_File_write_ordered_end(MPI_File, MPIO_CONST void *, MPI_Status *);

/* Section 9.5.1 */
int HPMPI_File_get_type_extent(MPI_File, MPI_Datatype, MPI_Aint *);

/* Section 9.5.3 */
int HPMPI_Register_datarep(MPIO_CONST char *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_extent_function *,
			 void *);

/* Section 9.6.1 */
int HPMPI_File_set_atomicity(MPI_File, int);
int HPMPI_File_get_atomicity(MPI_File, int *);
int HPMPI_File_sync(MPI_File);

/* Section 4.13.3 */
#ifndef MPICH
/* MPICH provides these definitions */
int HPMPI_File_set_errhandler( MPI_File, MPI_Errhandler );
int HPMPI_File_get_errhandler( MPI_File, MPI_Errhandler * );
#endif

#ifndef HAVE_MPI_DARRAY_SUBARRAY
/* Section 4.14.4 */
int HPMPI_Type_create_subarray(int, int *, int *, int *, int, 
                      MPI_Datatype, MPI_Datatype *);

/* Section 4.14.5 */
int HPMPI_Type_create_darray(int, int, int, int *, int *, 
                    int *, int *, int, MPI_Datatype, MPI_Datatype *);
#endif

/* Section 4.12.4 */
MPI_File HPMPI_File_f2c(MPI_Fint);
MPI_Fint HPMPI_File_c2f(MPI_File);

/* info functions if not defined in the MPI implementation */
#ifndef HAVE_MPI_INFO

int HPMPI_Info_create(MPI_Info *);
int HPMPI_Info_set(MPI_Info, char *, char *);
int HPMPI_Info_delete(MPI_Info, char *);
int HPMPI_Info_get(MPI_Info, char *, int, char *, int *);
int HPMPI_Info_get_valuelen(MPI_Info, char *, int *, int *);
int HPMPI_Info_get_nkeys(MPI_Info, int *);
int HPMPI_Info_get_nthkey(MPI_Info, int, char *);
int HPMPI_Info_dup(MPI_Info, MPI_Info *);
int HPMPI_Info_free(MPI_Info *);

MPI_Fint HPMPI_Info_c2f(MPI_Info);
MPI_Info HPMPI_Info_f2c(MPI_Fint);
#endif

#if defined(__cplusplus)
}
#endif

#endif
