!
!       
! 	Copyright IBM corp. 1983-2010, 2012-2017
!       US Government Users Restricted Rights:
!           Use, duplication or disclosure restricted 
!           by GSA ADP Schedule Contract with IBM Corp.
!
!       Function:       - MPI Fortran header file
!
!       Notice:         - HP MPI is based in parts on the contributions
!                         of the following groups:
!
!       - MPICH (Argonne National Laboratory, Mississippi State University)
!         versions 1.0.11, 1.0.12
!         (c)Copyright 1993 University of Chicago
!         (c)Copyright 1993 Mississippi State University
!
!       - LAM (Ohio Supercomputer Center)
!         versions 6.0, 6.1
!         (c)Copyright 1995-1996 The Ohio State University
!
!       "@(#)HP MPI - Windows"
!

!
! MPI version
!
       integer MPI_VERSION, MPI_SUBVERSION

       parameter (MPI_VERSION=2)
       parameter (MPI_SUBVERSION=2)

      integer PLATFORM_MPI, HP_MPI, HP_MPI_MINOR
      parameter (PLATFORM_MPI=Z'09010404')
      parameter (HP_MPI=203)
      parameter (HP_MPI_MINOR=0)
!
! MPI_Status object size
!
       integer MPI_SOURCE, MPI_TAG, MPI_ERROR
       parameter (MPI_SOURCE=1)
       parameter (MPI_TAG=2)
       parameter (MPI_ERROR=3)
       integer MPI_STATUS_SIZE
       parameter (MPI_STATUS_SIZE=8)
!
! MPI defined constants
!
       integer MPI_PROC_NULL, MPI_ANY_SOURCE, MPI_ROOT, MPI_ANY_TAG
       integer MPI_MAX_PROCESSOR_NAME, MPI_MAX_OBJECT_NAME
       integer MPI_MAX_ERROR_STRING, MPI_MAX_PORT_NAME
       integer MPI_MAX_DATAREP_STRING
       integer MPI_UNDEFINED, MPI_GRAPH, MPI_CART, MPI_DIST_GRAPH
       integer MPI_KEYVAL_INVALID, MPI_BSEND_OVERHEAD
       integer MPI_TYPECLASS_INTEGER, MPI_TYPECLASS_REAL
       integer MPI_TYPECLASS_COMPLEX
       parameter (MPI_PROC_NULL=-1)
       parameter (MPI_ANY_SOURCE=-2)
       parameter (MPI_ROOT=-3)
       parameter (MPI_ANY_TAG=-1)
       parameter (MPI_MAX_PROCESSOR_NAME=255)
       parameter (MPI_MAX_OBJECT_NAME=63)
       parameter (MPI_MAX_DATAREP_STRING=127)
       parameter (MPI_MAX_ERROR_STRING=255)
       parameter (MPI_MAX_PORT_NAME=63)
       parameter (MPI_UNDEFINED=-32766)
       parameter (MPI_GRAPH=1)
       parameter (MPI_CART=2)
       parameter (MPI_DIST_GRAPH=3)
       parameter (MPI_KEYVAL_INVALID=-1)
       parameter (MPI_BSEND_OVERHEAD=64)
       parameter (MPI_TYPECLASS_INTEGER=1)
       parameter (MPI_TYPECLASS_REAL=2)
       parameter (MPI_TYPECLASS_COMPLEX=3)

       integer MPI_IDENT, MPI_CONGRUENT, MPI_SIMILAR, MPI_UNEQUAL
       integer MPI_MAX_INFO_KEY, MPI_MAX_INFO_VAL
       integer MPI_LOCK_EXCLUSIVE, MPI_LOCK_SHARED
       parameter (MPI_IDENT=0)
       parameter (MPI_CONGRUENT=1)
       parameter (MPI_SIMILAR=2)
       parameter (MPI_UNEQUAL=3)
       parameter (MPI_MAX_INFO_KEY=255)
       parameter (MPI_MAX_INFO_VAL=16383)
       parameter (MPI_LOCK_EXCLUSIVE=1)
       parameter (MPI_LOCK_SHARED=2)

       integer MPI_THREAD_SINGLE, MPI_THREAD_FUNNELED
       integer MPI_THREAD_SERIALIZED, MPI_THREAD_MULTIPLE
       parameter (MPI_THREAD_SINGLE=0)
       parameter (MPI_THREAD_FUNNELED=1)
       parameter (MPI_THREAD_SERIALIZED=2)
       parameter (MPI_THREAD_MULTIPLE=3)
!
! Predefined attribute keys.
!
       integer MPI_TAG_UB, MPI_HOST, MPI_IO, MPI_WTIME_IS_GLOBAL
       integer IMPI_CLIENT_SIZE, IMPI_CLIENT_COLOR
       integer IMPI_HOST_SIZE, IMPI_HOST_COLOR
       integer MPI_WIN_BASE, MPI_WIN_SIZE, MPI_WIN_DISP_UNIT
       integer MPI_WIN_CREATE_FLAVOR, MPI_WIN_MODEL
       integer MPI_UNIVERSE_SIZE, MPI_APPNUM, MPI_LASTUSEDCODE
       parameter (MPI_TAG_UB=0)
       parameter (MPI_HOST=1)
       parameter (MPI_IO=2)
       parameter (MPI_WTIME_IS_GLOBAL=3)
       parameter (IMPI_CLIENT_SIZE=4)
       parameter (IMPI_CLIENT_COLOR=5)
       parameter (IMPI_HOST_SIZE=6)
       parameter (IMPI_HOST_COLOR=7)
       parameter (MPI_WIN_BASE=8)
       parameter (MPI_WIN_SIZE=9)
       parameter (MPI_WIN_DISP_UNIT=10)
       parameter (MPI_WIN_CREATE_FLAVOR=11)
       parameter (MPI_WIN_MODEL=12)
       parameter (MPI_UNIVERSE_SIZE=13)
       parameter (MPI_APPNUM=14)
       parameter (MPI_LASTUSEDCODE=15)
!
! Predefined reference constants
!
       integer*4 MPI_BOTTOM
       common/mpi_f_bottom/MPI_BOTTOM
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_bottom/
       save /mpi_f_bottom/
       integer*4 MPI_STATUS_IGNORE
       common/mpi_f_status_ignore/MPI_STATUS_IGNORE
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_status_ignore/
       save /mpi_f_status_ignore/
       integer*4 MPI_STATUSES_IGNORE(1)
       common/mpi_f_statuses_ignore/MPI_STATUSES_IGNORE
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_statuses_ignore/
       save /mpi_f_statuses_ignore/
       integer*4 MPI_ERRCODES_IGNORE(1)
       common/mpi_f_errcodes_ignore/MPI_ERRCODES_IGNORE
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_errcodes_ignore/
       save /mpi_f_errcodes_ignore/
       integer*4 MPI_ARGV_NULL(1)
       common/mpi_f_argv_null/MPI_ARGV_NULL
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_argv_null/
       save /mpi_f_argv_null/
       integer*4 MPI_ARGVS_NULL(1,1)
       common/mpi_f_argvs_null/MPI_ARGVS_NULL
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_argvs_null/
       save /mpi_f_argvs_null/
       integer*4 MPI_IN_PLACE
       common/mpi_f_in_place/MPI_IN_PLACE
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_in_place/
       save /mpi_f_in_place/
       integer*4 MPI_UNWEIGHTED
       common/mpi_f_unweighted/MPI_UNWEIGHTED
!DEC$ ATTRIBUTES DLLIMPORT :: /mpi_f_unweighted/
       save /mpi_f_unweighted/
!
! error classes
!
       integer MPI_SUCCESS, MPI_ERR_BUFFER, MPI_ERR_COUNT
       integer MPI_ERR_TYPE, MPI_ERR_TAG, MPI_ERR_COMM
       integer MPI_ERR_RANK, MPI_ERR_ROOT, MPI_ERR_GROUP
       integer MPI_ERR_OP, MPI_ERR_TOPOLOGY, MPI_ERR_DIMS
       integer MPI_ERR_ARG, MPI_ERR_UNKNOWN, MPI_ERR_TRUNCATE
       integer MPI_ERR_OTHER, MPI_ERR_INTERN, MPI_ERR_IN_STATUS
       integer MPI_ERR_PENDING, MPI_ERR_REQUEST, MPI_ERR_INFO
       integer MPI_ERR_INFO_NOKEY, MPI_ERR_INFO_KEY, MPI_ERR_INFO_VALUE
       integer MPI_ERR_WIN, MPI_ERR_BASE, MPI_ERR_SIZE, MPI_ERR_DISP
       integer MPI_ERR_LOCKTYPE, MPI_ERR_ASSERT, MPI_ERR_RMA_CONFLICT
       integer MPI_ERR_RMA_SYNC, MPI_ERR_NO_MEM, MPI_ERR_KEYVAL
       integer MPI_ERR_SPAWN, MPI_ERR_PORT
       integer MPI_ERR_SERVICE, MPI_ERR_NAME
       integer MPI_ERR_LASTCODE

       parameter (MPI_SUCCESS=0)
       parameter (MPI_ERR_BUFFER=1)
       parameter (MPI_ERR_COUNT=2)
       parameter (MPI_ERR_TYPE=3)
       parameter (MPI_ERR_TAG=4)
       parameter (MPI_ERR_COMM=5)
       parameter (MPI_ERR_RANK=6)
       parameter (MPI_ERR_ROOT=7)
       parameter (MPI_ERR_GROUP=8)
       parameter (MPI_ERR_OP=9)
       parameter (MPI_ERR_TOPOLOGY=10)
       parameter (MPI_ERR_DIMS=11)
       parameter (MPI_ERR_ARG=12)
       parameter (MPI_ERR_UNKNOWN=13)
       parameter (MPI_ERR_TRUNCATE=14)
       parameter (MPI_ERR_OTHER=15)
       parameter (MPI_ERR_INTERN=16)
       parameter (MPI_ERR_IN_STATUS=17)
       parameter (MPI_ERR_PENDING=18)
       parameter (MPI_ERR_REQUEST=19)
       parameter (MPI_ERR_INFO=20)
       parameter (MPI_ERR_INFO_NOKEY=21)
       parameter (MPI_ERR_INFO_KEY=22)
       parameter (MPI_ERR_INFO_VALUE=23)
       parameter (MPI_ERR_WIN=24)
       parameter (MPI_ERR_BASE=25)
       parameter (MPI_ERR_SIZE=26)
       parameter (MPI_ERR_DISP=27)
       parameter (MPI_ERR_LOCKTYPE=28)
       parameter (MPI_ERR_ASSERT=29)
       parameter (MPI_ERR_RMA_CONFLICT=30)
       parameter (MPI_ERR_RMA_SYNC=31)
       parameter (MPI_ERR_NO_MEM=32)
       parameter (MPI_ERR_KEYVAL=33)
       parameter (MPI_ERR_SPAWN=34)
       parameter (MPI_ERR_PORT=51)
       parameter (MPI_ERR_SERVICE=52)
       parameter (MPI_ERR_NAME=53)
       parameter (MPI_ERR_LASTCODE=1073741823)
!
! one-sided assert flags
!
       integer MPI_MODE_NOCHECK, MPI_MODE_NOSTORE, MPI_MODE_NOPUT
       integer MPI_MODE_NOPRECEDE, MPI_MODE_NOSUCCEED
       integer MPI_COMM_TYPE_SHARED

       parameter (MPI_MODE_NOCHECK=1)
       parameter (MPI_MODE_NOSTORE=2)
       parameter (MPI_MODE_NOPUT=4)
       parameter (MPI_MODE_NOPRECEDE=8)
       parameter (MPI_MODE_NOSUCCEED=16)
       parameter (MPI_COMM_TYPE_SHARED=32)
!
! datatype decoding combiners
!
       integer MPI_COMBINER_NAMED, MPI_COMBINER_DUP
       integer MPI_COMBINER_CONTIGUOUS, MPI_COMBINER_VECTOR
       integer MPI_COMBINER_HVECTOR_INTEGER, MPI_COMBINER_HVECTOR
       integer MPI_COMBINER_INDEXED, MPI_COMBINER_HINDEXED_INTEGER
       integer MPI_COMBINER_HINDEXED, MPI_COMBINER_INDEXED_BLOCK
       integer MPI_COMBINER_STRUCT_INTEGER, MPI_COMBINER_STRUCT
       integer MPI_COMBINER_SUBARRAY, MPI_COMBINER_DARRAY
       integer MPI_COMBINER_F90_REAL, MPI_COMBINER_F90_COMPLEX
       integer MPI_COMBINER_F90_INTEGER, MPI_COMBINER_RESIZED

       parameter (MPI_COMBINER_NAMED=0)
       parameter (MPI_COMBINER_DUP=1)
       parameter (MPI_COMBINER_CONTIGUOUS=2)
       parameter (MPI_COMBINER_VECTOR=3)
       parameter (MPI_COMBINER_HVECTOR_INTEGER=4)
       parameter (MPI_COMBINER_HVECTOR=5)
       parameter (MPI_COMBINER_INDEXED=6)
       parameter (MPI_COMBINER_HINDEXED_INTEGER=7)
       parameter (MPI_COMBINER_HINDEXED=8)
       parameter (MPI_COMBINER_INDEXED_BLOCK=9)
       parameter (MPI_COMBINER_STRUCT_INTEGER=10)
       parameter (MPI_COMBINER_STRUCT=11)
       parameter (MPI_COMBINER_SUBARRAY=12)
       parameter (MPI_COMBINER_DARRAY=13)
       parameter (MPI_COMBINER_F90_REAL=14)
       parameter (MPI_COMBINER_F90_COMPLEX=15)
       parameter (MPI_COMBINER_F90_INTEGER=16)
       parameter (MPI_COMBINER_RESIZED=17)
!
! NULL handles.
!
       integer MPI_COMM_NULL, MPI_DATATYPE_NULL, MPI_ERRHANDLER_NULL
       integer MPI_GROUP_NULL, MPI_OP_NULL, MPI_INFO_NULL
       integer MPI_WIN_NULL, MPI_REQUEST_NULL
       parameter (MPI_COMM_NULL=-1)
       parameter (MPI_DATATYPE_NULL=-1)
       parameter (MPI_ERRHANDLER_NULL=-1)
       parameter (MPI_GROUP_NULL=-1)
       parameter (MPI_OP_NULL=-1)
       parameter (MPI_INFO_NULL=-1)
       parameter (MPI_WIN_NULL=-1)
       parameter (MPI_REQUEST_NULL=-1)
!
! Predefined NULL copy/delete/dup callback routines.
!
       external MPI_NULL_COPY_FN, MPI_NULL_DELETE_FN, MPI_DUP_FN
       external MPI_COMM_NULL_COPY_FN, MPI_COMM_NULL_DELETE_FN
       external MPI_COMM_DUP_FN
       external MPI_WIN_NULL_COPY_FN, MPI_WIN_NULL_DELETE_FN
       external MPI_WIN_DUP_FN
       external MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN
       external MPI_TYPE_DUP_FN
!
! Global debugging variable.
!
       integer*4 MPI_DEBUG_CONT
       common/mpi_debug_cont/MPI_DEBUG_CONT
       save /mpi_debug_cont/

!
! Predefined communicator objects: (0 - 2)
!
       integer MPI_COMM_WORLD, MPI_COMM_SELF
       integer MPI_GROUP_EMPTY
       parameter (MPI_COMM_WORLD=0)
       parameter (MPI_COMM_SELF=1)
       parameter (MPI_GROUP_EMPTY=2)
!
! Predefined operator objects: (3 - 14)
!
       integer MPI_MAX, MPI_MIN, MPI_SUM, MPI_PROD, MPI_LAND
       integer MPI_BAND, MPI_LOR, MPI_BOR, MPI_LXOR, MPI_BXOR
       integer MPI_MAXLOC, MPI_MINLOC
       parameter (MPI_MAX=3)
       parameter (MPI_MIN=4)
       parameter (MPI_SUM=5)
       parameter (MPI_PROD=6)
       parameter (MPI_LAND=7)
       parameter (MPI_BAND=8)
       parameter (MPI_LOR=9)
       parameter (MPI_BOR=10)
       parameter (MPI_LXOR=11)
       parameter (MPI_BXOR=12)
       parameter (MPI_MAXLOC=13)
       parameter (MPI_MINLOC=14)
!
! Predefined datatype objects: (15 - 33)
!
       integer MPI_INTEGER, MPI_REAL, MPI_DOUBLE_PRECISION
       integer MPI_COMPLEX, MPI_LOGICAL, MPI_CHARACTER
       integer MPI_BYTE, MPI_PACKED, MPI_UB, MPI_LB, MPI_2REAL
       integer MPI_2DOUBLE_PRECISION, MPI_2INTEGER
       integer MPI_INTEGER1, MPI_INTEGER2, MPI_INTEGER4
       integer MPI_REAL4, MPI_REAL8, MPI_DOUBLE_COMPLEX
       parameter (MPI_INTEGER=15)
       parameter (MPI_REAL=16)
       parameter (MPI_DOUBLE_PRECISION=17)
       parameter (MPI_COMPLEX=18)
       parameter (MPI_LOGICAL=19)
       parameter (MPI_CHARACTER=20)
       parameter (MPI_BYTE=21)
       parameter (MPI_PACKED=22)
       parameter (MPI_UB=23)
       parameter (MPI_LB=24)
       parameter (MPI_2REAL=25)
       parameter (MPI_2DOUBLE_PRECISION=26)
       parameter (MPI_2INTEGER=27)
       parameter (MPI_INTEGER1=28)
       parameter (MPI_INTEGER2=29)
       parameter (MPI_INTEGER4=30)
       parameter (MPI_REAL4=31)
       parameter (MPI_REAL8=32)
       parameter (MPI_DOUBLE_COMPLEX=33)
!
! Predefined error handlers: (34 - 35)
!
       integer MPI_ERRORS_ARE_FATAL, MPI_ERRORS_RETURN
       parameter (MPI_ERRORS_ARE_FATAL=34)
       parameter (MPI_ERRORS_RETURN=35)
!
! Newly added datatypes: (36 - 37)
!
       integer MPI_INTEGER8, MPI_REAL16
       parameter (MPI_INTEGER8=36)
       parameter (MPI_REAL16=37)
!
! Newly added operator: (38)
!
       integer MPI_REPLACE
       parameter (MPI_REPLACE=38)
!
! new mpi 2.2 Datatypes
!
       integer MPI_AINT, MPI_OFFSET
       parameter (MPI_AINT=41)
       parameter (MPI_OFFSET=42)
!
! Make the C datatypes available from Fortran
!
       integer MPI_CHAR, MPI_WCHAR, MPI_SIGNED_CHAR, MPI_SHORT
       integer MPI_INT, MPI_LONG, MPI_LONG_LONG, MPI_LONG_LONG_INT
       integer MPI_FLOAT, MPI_DOUBLE, MPI_LONG_DOUBLE
       integer MPI_UNSIGNED_CHAR, MPI_UNSIGNED_SHORT, MPI_UNSIGNED
       integer MPI_UNSIGNED_LONG, MPI_UNSIGNED_LONG_LONG, MPI_C_BOOL
       integer MPI_INT8_T, MPI_INT16_T, MPI_INT32_T, MPI_INT64_T
       integer MPI_UINT8_T, MPI_UINT16_T, MPI_UINT32_T, MPI_UINT64_T
       integer MPI_C_COMPLEX, MPI_C_FLOAT_COMPLEX
       integer MPI_C_DOUBLE_COMPLEX, MPI_C_LONG_DOUBLE_COMPLEX
       integer MPI_COMPLEX8, MPI_COMPLEX16, MPI_COMPLEX32
       integer MPI_FLOAT_INT, MPI_DOUBLE_INT, MPI_LONG_INT, MPI_2INT
       integer MPI_SHORT_INT, MPI_LONG_DOUBLE_INT
       integer MPI_INT8, MPI_UINT8

       parameter (MPI_CHAR=43)
       parameter (MPI_WCHAR=44)
       parameter (MPI_SIGNED_CHAR=45)
       parameter (MPI_SHORT=46)
       parameter (MPI_INT=47)
       parameter (MPI_LONG=48)
       parameter (MPI_LONG_LONG=74)
       parameter (MPI_LONG_LONG_INT=74)
       parameter (MPI_FLOAT=49)
       parameter (MPI_DOUBLE=50)
       parameter (MPI_LONG_DOUBLE=51)
       parameter (MPI_UNSIGNED_CHAR=52)
       parameter (MPI_UNSIGNED_SHORT=53)
       parameter (MPI_UNSIGNED=54)
       parameter (MPI_UNSIGNED_LONG=55)
       parameter (MPI_UNSIGNED_LONG_LONG=75)
       parameter (MPI_C_BOOL=56)
       parameter (MPI_INT8_T=57)
       parameter (MPI_INT16_T=58)
       parameter (MPI_INT32_T=59)
       parameter (MPI_INT64_T=60)
       parameter (MPI_UINT8_T=61)
       parameter (MPI_UINT16_T=62)
       parameter (MPI_UINT32_T=63)
       parameter (MPI_UINT64_T=64)
       parameter (MPI_C_COMPLEX=65)
       parameter (MPI_C_FLOAT_COMPLEX=65)
       parameter (MPI_C_DOUBLE_COMPLEX=66)
       parameter (MPI_C_LONG_DOUBLE_COMPLEX=67)
       parameter (MPI_COMPLEX8=65)
       parameter (MPI_COMPLEX16=66)
       parameter (MPI_COMPLEX32=67)
       parameter (MPI_FLOAT_INT=68)
       parameter (MPI_DOUBLE_INT=69)
       parameter (MPI_LONG_INT=70)
       parameter (MPI_2INT=71)
       parameter (MPI_SHORT_INT=72)
       parameter (MPI_LONG_DOUBLE_INT=73)
       parameter (MPI_INT8=74)
       parameter (MPI_UINT8=75)
!
! Double precision functions
!
       real*8 MPI_WTIME, MPI_WTICK
       real*8 PMPI_WTIME, PMPI_WTICK
       external MPI_WTIME, MPI_WTICK
       external PMPI_WTIME, PMPI_WTICK
!
! Address KIND parameters
!
       integer MPI_INTEGER_KIND
       parameter (MPI_INTEGER_KIND=4)

       integer MPI_ADDRESS_KIND
       parameter (MPI_ADDRESS_KIND=4)

!
! Constants for Fortran MPI-IO programs
!

       include 'mpiof.h'

!
! Certain MPI routines need to inform the compiler that they
! access memory which the compiler doesn't know about, so it
! won't optimize too agressively and break those calls.
!

       external MPI_START, MPI_STARTALL
       external MPI_WAIT, MPI_WAITALL, MPI_WAITANY, MPI_WAITSOME
       external MPI_TEST, MPI_TESTALL, MPI_TESTANY, MPI_TESTSOME
       external MPI_WIN_START, MPI_WIN_COMPLETE, MPI_WIN_POST
       external MPI_WIN_WAIT, MPI_WIN_TEST

!$dir  sync_routine(MPI_START)
!$dir  sync_routine(MPI_STARTALL)
!$dir  sync_routine(MPI_WAIT)
!$dir  sync_routine(MPI_WAITALL)
!$dir  sync_routine(MPI_WAITANY)
!$dir  sync_routine(MPI_WAITSOME)
!$dir  sync_routine(MPI_TEST)
!$dir  sync_routine(MPI_TESTALL)
!$dir  sync_routine(MPI_TESTANY)
!$dir  sync_routine(MPI_TESTSOME)
!$dir  sync_routine(MPI_WIN_START)
!$dir  sync_routine(MPI_WIN_COMPLETE)
!$dir  sync_routine(MPI_WIN_POST)
!$dir  sync_routine(MPI_WIN_WAIT)
!$dir  sync_routine(MPI_WIN_TEST)

