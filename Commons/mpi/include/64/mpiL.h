/*
 *	
 *	Copyright Platform Computing Inc., an IBM company, 1983-2008, 2012
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
 */

#ifndef _MPIL_H
#define _MPIL_H


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
 * MPI function prototypes
 ****************************************************************/
#if defined(__STDC__) || defined(c_plusplus) || defined(__cplusplus) || defined(_WIN32)

typedef void (MPI_User_functionL)(void *, void *, 
			MPI_Aint *, MPI_Datatype *);
#if !defined(MPI_hpux) || defined(_WIN32)

/*
 * Function prototype only for users or internal Windows build.
 */
HPAPIEXPORT extern 
int HPMPIAPI MPI_AllgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AllgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AllreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AlltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AlltoallvL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AlltoallwL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype*, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype*, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_BcastL(void *, MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_BsendL(void *, MPI_Aint, MPI_Datatype, int, int, 
			MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Bsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Buffer_attachL(void *, MPI_Aint);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Buffer_detachL(void *, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_GatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_GathervL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Get_countL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Get_elementsL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IbcastL(void *, MPI_Aint, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IscatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IscattervL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IallgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IallgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IalltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IalltoallvL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IalltoallwL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype *, void *, MPI_Aint *,
			MPI_Aint *, MPI_Datatype *, MPI_Comm,
			MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IallreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ireduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ireduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IexscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IbsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IrecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IrsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_IssendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Op_createL(MPI_User_functionL *, int, MPI_Op *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_PackL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint, MPI_Aint *, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Pack_externalL(char *, void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Pack_sizeL(MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Pack_external_sizeL(char *, MPI_Aint, MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_RecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Recv_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ReduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Reduce_localL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op);
HPAPIEXPORT extern
int HPMPIAPI MPI_Reduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Reduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPAPIEXPORT extern
int HPMPIAPI MPI_RsendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Rsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ScanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ExscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ScatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ScattervL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_SendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Send_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_SendrecvL(void *, MPI_Aint, MPI_Datatype, int, int,
			void *, MPI_Aint, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Sendrecv_replaceL(void *, MPI_Aint, MPI_Datatype, 
			int, int, int, int, MPI_Comm, MPI_Status *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_SsendL(void *, MPI_Aint, MPI_Datatype, int, int, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ssend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Status_set_elementsL(MPI_Status *status,
			MPI_Datatype dtype, MPI_Aint nelem);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_contiguousL(MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_create_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_create_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_create_indexed_blockL(MPI_Aint, MPI_Aint, 
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_create_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_indexedL(MPI_Aint, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_sizeL(MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Type_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI MPI_Type_vectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_UnpackL(void *, MPI_Aint, MPI_Aint *, void *, MPI_Aint,
			MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Unpack_externalL(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, MPI_Aint, MPI_Datatype);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Win_createL(void *, MPI_Aint, MPI_Aint,
			MPI_Info, MPI_Comm, MPI_Win *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Win_create_dynamicL(MPI_Info, MPI_Comm, MPI_Win *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_GetL(void *, MPI_Aint, MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win);
HPAPIEXPORT extern 
int HPMPIAPI MPI_PutL(void *, MPI_Aint, MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win);
HPAPIEXPORT extern 
int HPMPIAPI MPI_AccumulateL(void *, MPI_Aint, MPI_Datatype, int,
			MPI_Aint, MPI_Aint, MPI_Datatype, MPI_Op, MPI_Win);

HPAPIEXPORT extern 
int HPMPIAPI MPI_Compare_and_swapL(void *, void *, void *,
				MPI_Datatype, int, MPI_Aint, MPI_Win);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Fetch_and_opL(void *, void *, MPI_Datatype,
				int, MPI_Aint, MPI_Op, MPI_Win);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Get_accumulateL(void *, MPI_Aint, MPI_Datatype,
				void *, MPI_Aint, MPI_Datatype,
				int, MPI_Aint, MPI_Aint, MPI_Datatype,
				MPI_Op, MPI_Win);
HPAPIEXPORT extern 
int HPMPIAPI MPI_RaccumulateL(void *, MPI_Aint, MPI_Datatype,
				int, MPI_Aint, MPI_Aint, MPI_Datatype,
				MPI_Op, MPI_Win, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Rget_accumulateL(void *, MPI_Aint, MPI_Datatype,
				void *, MPI_Aint, MPI_Datatype,
				int, MPI_Aint, MPI_Aint, MPI_Datatype,
				MPI_Op, MPI_Win, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_RgetL(void *, MPI_Aint, MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_RputL(void *, MPI_Aint, MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Win_allocateL(MPI_Aint, MPI_Aint, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Win_allocate_sharedL(MPI_Aint, MPI_Aint, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Ineighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPAPIEXPORT extern 
int HPMPIAPI MPI_Neighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm);

HPAPIEXPORT extern 
int HPMPIAPI MPI_MrecvL(void *, MPI_Aint, MPI_Datatype,
			MPI_Message *, MPI_Status *);
HPAPIEXPORT extern 
int HPMPIAPI MPI_ImrecvL(void *, MPI_Aint, MPI_Datatype,
			MPI_Message *, MPI_Request *);

#endif /* !defined(MPI_hpux) || defined(_WIN32) */





#if !defined(MPI_hpux) || defined(HPMP_BUILD_DLIB)

/*
 * Profiling prototypes, for both users and internal building.
 */
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AllgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AllgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AllreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AlltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AlltoallvL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_AlltoallwL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype*, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype*, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_BcastL(void *, MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_BsendL(void *, MPI_Aint, MPI_Datatype, int, int, 
			MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Bsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Buffer_attachL(void *, MPI_Aint);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Buffer_detachL(void *, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_GatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_GathervL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Get_countL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Get_elementsL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IbcastL(void *, MPI_Aint, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IscatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IscattervL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IallgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IallgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IalltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IalltoallvL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IalltoallwL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype *, void *, MPI_Aint *,
			MPI_Aint *, MPI_Datatype *, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IallreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Ireduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Ireduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IexscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IbsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IrecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IrsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_IssendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern
int HPMPIAPI PMPI_Op_createL(MPI_User_functionL *, int, MPI_Op *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_PackL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint, MPI_Aint *, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Pack_externalL(char *, void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Pack_sizeL(MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Pack_external_sizeL(char *, MPI_Aint, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_RecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Recv_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_ReduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Reduce_localL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op);
HPMPIIMPORT extern
int HPMPIAPI PMPI_Reduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Reduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern
int HPMPIAPI PMPI_RsendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Rsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_ScanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_ExscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_ScatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_ScattervL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_SendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Send_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_SendrecvL(void *, MPI_Aint, MPI_Datatype, int, int,
			void *, MPI_Aint, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Sendrecv_replaceL(void *, MPI_Aint, MPI_Datatype, 
			int, int, int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_SsendL(void *, MPI_Aint, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Ssend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern
int HPMPIAPI PMPI_Status_set_elementsL(MPI_Status *status,
			MPI_Datatype dtype, MPI_Aint nelem);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_contiguousL(MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_create_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI PMPI_Type_create_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_create_indexed_blockL(MPI_Aint, MPI_Aint, 
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_create_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI PMPI_Type_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_indexedL(MPI_Aint, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_sizeL(MPI_Datatype, MPI_Aint *);
HPAPIEXPORT extern 
int HPMPIAPI PMPI_Type_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPAPIEXPORT extern
int HPMPIAPI PMPI_Type_vectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_UnpackL(void *, MPI_Aint, MPI_Aint *, void *, MPI_Aint,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI PMPI_Unpack_externalL(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, MPI_Aint, MPI_Datatype);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_createL(void *, MPI_Aint, 
			MPI_Aint, MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_create_dynamicL(MPI_Info, 
			MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_GetL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_PutL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_AccumulateL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Compare_and_swapL(void *, void *, void *,
			MPI_Datatype, int, MPI_Aint, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Fetch_and_opL(void *, void *, MPI_Datatype,
			int, MPI_Aint, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_Get_accumulateL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI PMPI_RaccumulateL(void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Rget_accumulateL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_RgetL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_RputL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_allocateL(MPI_Aint, MPI_Aint,
			MPI_Info, MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Win_allocate_sharedL(MPI_Aint,
			MPI_Aint, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Ineighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI PMPI_Neighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm);

HPMPIIMPORT extern int HPMPIAPI PMPI_MrecvL(void *, MPI_Aint, MPI_Datatype, 
			MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI PMPI_ImrecvL(void *, MPI_Aint, MPI_Datatype, 
			MPI_Message *, MPI_Request *);

#endif /* !defined(MPI_hpux) || defined(HPMP_BUILD_DLIB) */





/*
 * Prototypes, for HPMPI entrypoints, only needed
 * for internal building.
 */
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AllgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AllgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AllreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AlltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AlltoallvL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_AlltoallwL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype*, void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype*, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_BcastL(void *, MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_BsendL(void *, MPI_Aint, MPI_Datatype, int, int, 
			MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Bsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Buffer_attachL(void *, MPI_Aint);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Buffer_detachL(void *, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_GatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_GathervL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Get_countL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Get_elementsL(MPI_Status *, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IbcastL(void *, MPI_Aint, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, int,
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IscatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IscattervL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IallgatherL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IallgathervL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IalltoallL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IalltoallvL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, void *,
			MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IalltoallwL(void *, MPI_Aint *, MPI_Aint *,
			MPI_Datatype *, void *, MPI_Aint *,
			MPI_Aint *, MPI_Datatype *, MPI_Comm,
			MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IallreduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Ireduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Ireduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IexscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IbsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IrecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IrsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IsendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_IssendL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_Op_createL(MPI_User_functionL *, int, MPI_Op *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_PackL(void *, MPI_Aint, MPI_Datatype, void *, 
			MPI_Aint, MPI_Aint *, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Pack_externalL(char *, void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Pack_sizeL(MPI_Aint, MPI_Datatype, MPI_Comm, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Pack_external_sizeL(char *, MPI_Aint, MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_RecvL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Recv_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_ReduceL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, int, MPI_Comm);
int HPMPIAPI HPMPI_Reduce_localL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Reduce_scatterL(void *, void *, MPI_Aint *,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Reduce_scatter_blockL(void *, void *, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Comm);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_RsendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Rsend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_ScanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_ExscanL(void *, void *, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_ScatterL(void *, MPI_Aint, MPI_Datatype, void *,
			MPI_Aint, MPI_Datatype, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_ScattervL(void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_SendL(void *, MPI_Aint, MPI_Datatype, int, 
			int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Send_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_SendrecvL(void *, MPI_Aint, MPI_Datatype, int, int,
			void *, MPI_Aint, MPI_Datatype, int, int,
			MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Sendrecv_replaceL(void *, MPI_Aint, MPI_Datatype, 
			int, int, int, int, MPI_Comm, MPI_Status *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_SsendL(void *, MPI_Aint, MPI_Datatype, int, int, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Ssend_initL(void *, MPI_Aint, MPI_Datatype, int,
			int, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_Status_set_elementsL(MPI_Status *status,
			MPI_Datatype dtype, MPI_Aint nelem);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_contiguousL(MPI_Aint, MPI_Datatype,
			MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_create_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_Type_create_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_create_indexed_blockL(MPI_Aint, MPI_Aint, 
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_create_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_hindexedL(MPI_Aint, MPI_Aint *,
			MPI_Aint *, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_Type_hvectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_indexedL(MPI_Aint, MPI_Aint *, MPI_Aint *,
			MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_sizeL(MPI_Datatype, MPI_Aint *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Type_structL(MPI_Aint, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
HPMPIIMPORT extern
int HPMPIAPI HPMPI_Type_vectorL(MPI_Aint, MPI_Aint, 
			MPI_Aint, MPI_Datatype, MPI_Datatype *);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_UnpackL(void *, MPI_Aint, MPI_Aint *, void *, MPI_Aint,
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern 
int HPMPIAPI HPMPI_Unpack_externalL(char *, void *, MPI_Aint, MPI_Aint *,
                        void *, MPI_Aint, MPI_Datatype);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_createL(void *, MPI_Aint, 
			MPI_Aint, MPI_Info, MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_create_dynamicL(MPI_Info, 
			MPI_Comm, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_GetL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_PutL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_AccumulateL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint, MPI_Aint,
			MPI_Datatype, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Compare_and_swapL(void *, void *, void *,
			MPI_Datatype, int, MPI_Aint, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Fetch_and_opL(void *, void *, MPI_Datatype,
			int, MPI_Aint, MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Get_accumulateL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win);
HPMPIIMPORT extern int HPMPIAPI HPMPI_RaccumulateL(void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Rget_accumulateL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype,
			int, MPI_Aint, MPI_Aint, MPI_Datatype,
			MPI_Op, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_RgetL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_RputL(void *, MPI_Aint,
			MPI_Datatype, int, MPI_Aint,
			MPI_Aint, MPI_Datatype, MPI_Win, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_allocateL(MPI_Aint, MPI_Aint,
			MPI_Info, MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Win_allocate_sharedL(MPI_Aint,
			MPI_Aint, MPI_Info,
			MPI_Comm, void *, MPI_Win *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Ineighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm, MPI_Request *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_allgatherL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_allgathervL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoallL(void *, MPI_Aint, 
			MPI_Datatype, void *, MPI_Aint, MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoallvL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype, void *, MPI_Aint *, MPI_Aint *, 
			MPI_Datatype, MPI_Comm);
HPMPIIMPORT extern int HPMPIAPI HPMPI_Neighbor_alltoallwL(void *, MPI_Aint *, 
			MPI_Aint *, MPI_Datatype *, void *, MPI_Aint *, MPI_Aint *, MPI_Datatype *, 
			MPI_Comm);

HPMPIIMPORT extern int HPMPIAPI HPMPI_MrecvL(void *, MPI_Aint, MPI_Datatype,
			MPI_Message *, MPI_Status *);
HPMPIIMPORT extern int HPMPIAPI HPMPI_ImrecvL(void *, MPI_Aint, MPI_Datatype,
			MPI_Message *, MPI_Request *);

#endif /* defined(__STDC__) || defined(c_plusplus) || defined(__cplusplus) */


#if defined(c_plusplus) || defined(__cplusplus) 
}
#endif


#endif	/* _MPIL_H */

