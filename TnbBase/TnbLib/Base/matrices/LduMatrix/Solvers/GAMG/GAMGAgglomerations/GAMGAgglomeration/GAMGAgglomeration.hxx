#pragma once
#ifndef _GAMGAgglomeration_Header
#define _GAMGAgglomeration_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::GAMGAgglomeration

Description
	Geometric agglomerated algebraic multigrid agglomeration class.

SourceFiles
	GAMGAgglomeration.C
	GAMGAgglomerationTemplates.C
	GAMGAgglomerateLduAddressing.C

\*---------------------------------------------------------------------------*/

#include <MeshObject.hxx>
#include <lduPrimitiveMesh.hxx>
#include <lduInterfacePtrsList.hxx>
#include <primitiveFields.hxx>
#include <runTimeSelectionTables.hxx>

#include <boolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class lduMesh;
	class lduMatrix;
	class mapDistribute;
	class GAMGProcAgglomeration;

	/*---------------------------------------------------------------------------*\
						Class GAMGAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class GAMGAgglomeration
		:
		public MeshObject<lduMesh, GeometricMeshObject, GAMGAgglomeration>
	{
	protected:

		// Protected data

			//- Max number of levels
		const label maxLevels_;

		//- Number of cells in coarsest level
		const label nCellsInCoarsestLevel_;

		//- Cached mesh interfaces
		const lduInterfacePtrsList meshInterfaces_;

		autoPtr<GAMGProcAgglomeration> procAgglomeratorPtr_;

		//- The number of cells in each level
		labelList nCells_;

		//- Cell restriction addressing array.
		//  Maps from the finer to the coarser level.
		PtrList<labelField> restrictAddressing_;

		//- The number of (coarse) faces in each level.
		//  max(faceRestrictAddressing)+1.
		labelList nFaces_;

		//- Face restriction addressing array.
		//  Maps from the finer to the coarser level.
		//  Positive indices map the finer faces which form part of the boundary
		//  of the coarser cells to the corresponding coarser cell face.
		//  Negative indices map the finer faces which are internal to the
		//  coarser cells to minus the corresponding coarser cell index minus 1.
		PtrList<labelList> faceRestrictAddressing_;

		//- Face flip: for faces mapped to internal faces stores whether
		//  the face is reversed or not. This is used to avoid having
		//  to access the coarse mesh at all when mapping
		PtrList<boolList> faceFlipMap_;

		//- The number of (coarse) patch faces in each level.
		//  max(patchFaceRestrictAddressing_)+1.
		PtrList<labelList> nPatchFaces_;

		//- Patch-local face restriction addressing array.
		//  Maps from the finer to the coarser level. Always positive.
		//  Extracted from GAMGInterfaces after agglomeration.
		PtrList<labelListList> patchFaceRestrictAddressing_;

		//- Hierarchy of mesh addressing
		PtrList<lduPrimitiveMesh> meshLevels_;


		// Processor agglomeration

			//- Per level, per processor the processor it agglomerates into
		mutable PtrList<labelList> procAgglomMap_;

		//- Per level the set of processors to agglomerate. Element 0 is
		//  the 'master' of the cluster.
		mutable PtrList<labelList> agglomProcIDs_;

		//- Communicator for given level
		mutable labelList procCommunicator_;

		//- Mapping from processor to procMeshLevel cells
		mutable PtrList<labelList> procCellOffsets_;

		//- Mapping from processor to procMeshLevel face
		mutable PtrList<labelListList> procFaceMap_;

		//- Mapping from processor to procMeshLevel boundary
		mutable PtrList<labelListList> procBoundaryMap_;

		//- Mapping from processor to procMeshLevel boundary face
		mutable PtrList<labelListListList> procBoundaryFaceMap_;


		// Protected Member Functions

			//- Assemble coarse mesh addressing
		FoamBase_EXPORT void agglomerateLduAddressing(const label fineLevelIndex);

		//- Combine a level with the previous one
		FoamBase_EXPORT void combineLevels(const label curLevel);

		//- Shrink the number of levels to that specified
		FoamBase_EXPORT void compactLevels(const label nCreatedLevels);

		//- Check the need for further agglomeration
		FoamBase_EXPORT bool continueAgglomerating
		(
			const label nCells,
			const label nCoarseCells
		) const;

		//- Gather value from all procIDs onto procIDs[0]
		template<class Type>
		static void gatherList
		(
			const label comm,
			const labelList& procIDs,

			const Type& myVal,
			List<Type>& allVals,
			const int tag = Pstream::msgType()
		);

		FoamBase_EXPORT void clearLevel(const label leveli);


		// Processor agglomeration

			//- Collect and combine processor meshes into allMesh:
			//
			//    - allMeshComm   : communicator for combined mesh.
			//    - procAgglomMap : per processor the new agglomerated
			//        processor (rank in allMeshComm!). Global information.
			//    - procIDs       : local information: same for all in
			//        agglomerated processor.
		FoamBase_EXPORT void procAgglomerateLduAddressing
		(
			const label comm,
			const labelList& procAgglomMap,
			const labelList& procIDs,
			const label allMeshComm,
			const label levelIndex
		);

		//- Collect and combine basic restriction addressing:
		//
		//    - nCells_
		//    - restrictAddressing_
		FoamBase_EXPORT void procAgglomerateRestrictAddressing
		(
			const label comm,
			const labelList& procIDs,
			const label levelIndex
		);


	public:

		//- Declare friendship with GAMGProcAgglomeration
		friend class GAMGProcAgglomeration;

		//- Runtime type information
		//TypeName("GAMGAgglomeration");
		static const char* typeName_() { return "GAMGAgglomeration"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

			//- Runtime selection table for pure geometric agglomerators
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGAgglomeration,
			lduMesh,
			(
				const lduMesh& mesh,
				const dictionary& controlDict
				),
				(
					mesh,
					controlDict
					)
		);*/

		typedef autoPtr<GAMGAgglomeration> (*lduMeshConstructorPtr)(const lduMesh& mesh, const dictionary& controlDict);
		typedef HashTable<lduMeshConstructorPtr, word, string::hash> lduMeshConstructorTable;
		static FoamBase_EXPORT lduMeshConstructorTable* lduMeshConstructorTablePtr_;
		static FoamBase_EXPORT void constructlduMeshConstructorTables();
		static FoamBase_EXPORT void destroylduMeshConstructorTables();

		template <class GAMGAgglomerationType>
		class addlduMeshConstructorToTable
		{
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMesh& mesh, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(mesh, controlDict));
			}

			addlduMeshConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName)
			{
				constructlduMeshConstructorTables();
				if (!lduMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGAgglomeration" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addlduMeshConstructorToTable() { destroylduMeshConstructorTables(); }
		};

		template <class GAMGAgglomerationType>
		class addRemovablelduMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMesh& mesh, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(mesh, controlDict));
			}

			addRemovablelduMeshConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName) : lookup_(lookup)
			{
				constructlduMeshConstructorTables();
				lduMeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablelduMeshConstructorToTable()
			{
				if (lduMeshConstructorTablePtr_) { lduMeshConstructorTablePtr_->erase(lookup_); }
			}
		};;

		//- Runtime selection table for matrix or mixed geometric/matrix
		//  agglomerators
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGAgglomeration,
			lduMatrix,
			(
				const lduMatrix& matrix,
				const dictionary& controlDict
				),
				(
					matrix,
					controlDict
					)
		);*/

		typedef autoPtr<GAMGAgglomeration> (*lduMatrixConstructorPtr)(const lduMatrix& matrix, const dictionary& controlDict);
		typedef HashTable<lduMatrixConstructorPtr, word, string::hash> lduMatrixConstructorTable;
		static FoamBase_EXPORT lduMatrixConstructorTable* lduMatrixConstructorTablePtr_;
		static FoamBase_EXPORT void constructlduMatrixConstructorTables();
		static FoamBase_EXPORT void destroylduMatrixConstructorTables();

		template <class GAMGAgglomerationType>
		class addlduMatrixConstructorToTable
		{
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMatrix& matrix, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(matrix, controlDict));
			}

			addlduMatrixConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName)
			{
				constructlduMatrixConstructorTables();
				if (!lduMatrixConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGAgglomeration" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addlduMatrixConstructorToTable() { destroylduMatrixConstructorTables(); }
		};

		template <class GAMGAgglomerationType>
		class addRemovablelduMatrixConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMatrix& matrix, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(matrix, controlDict));
			}

			addRemovablelduMatrixConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName) : lookup_(lookup)
			{
				constructlduMatrixConstructorTables();
				lduMatrixConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablelduMatrixConstructorToTable()
			{
				if (lduMatrixConstructorTablePtr_) { lduMatrixConstructorTablePtr_->erase(lookup_); }
			}
		};;

		//- Runtime selection table for matrix or mixed geometric/matrix
		//  agglomerators
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGAgglomeration,
			geometry,
			(
				const lduMesh& mesh,
				const scalarField& cellVolumes,
				const vectorField& faceAreas,
				const dictionary& controlDict
				),
				(
					mesh,
					cellVolumes,
					faceAreas,
					controlDict
					)
		);*/

		typedef autoPtr<GAMGAgglomeration> (*geometryConstructorPtr)(const lduMesh& mesh, const scalarField& cellVolumes,
		                                                             const vectorField& faceAreas,
		                                                             const dictionary& controlDict);
		typedef HashTable<geometryConstructorPtr, word, string::hash> geometryConstructorTable;
		static FoamBase_EXPORT geometryConstructorTable* geometryConstructorTablePtr_;
		static FoamBase_EXPORT void constructgeometryConstructorTables();
		static FoamBase_EXPORT void destroygeometryConstructorTables();

		template <class GAMGAgglomerationType>
		class addgeometryConstructorToTable
		{
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMesh& mesh, const scalarField& cellVolumes,
			                                      const vectorField& faceAreas, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(mesh, cellVolumes, faceAreas, controlDict));
			}

			addgeometryConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName)
			{
				constructgeometryConstructorTables();
				if (!geometryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGAgglomeration" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addgeometryConstructorToTable() { destroygeometryConstructorTables(); }
		};

		template <class GAMGAgglomerationType>
		class addRemovablegeometryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGAgglomeration> New(const lduMesh& mesh, const scalarField& cellVolumes,
			                                      const vectorField& faceAreas, const dictionary& controlDict)
			{
				return autoPtr<GAMGAgglomeration>(new GAMGAgglomerationType(mesh, cellVolumes, faceAreas, controlDict));
			}

			addRemovablegeometryConstructorToTable(const word& lookup = GAMGAgglomerationType::typeName) : lookup_(lookup)
			{
				constructgeometryConstructorTables();
				geometryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablegeometryConstructorToTable()
			{
				if (geometryConstructorTablePtr_) { geometryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct given mesh and controls
		FoamBase_EXPORT GAMGAgglomeration
		(
			const lduMesh& mesh,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT GAMGAgglomeration(const GAMGAgglomeration&) = delete;


		// Selectors

			//- Return the selected geometric agglomerator
		static FoamBase_EXPORT const GAMGAgglomeration& New
		(
			const lduMesh& mesh,
			const dictionary& controlDict
		);

		//- Return the selected matrix agglomerator
		static FoamBase_EXPORT const GAMGAgglomeration& New
		(
			const lduMatrix& matrix,
			const dictionary& controlDict
		);

		//- Return the selected geometric agglomerator
		static FoamBase_EXPORT autoPtr<GAMGAgglomeration> New
		(
			const lduMesh& mesh,
			const scalarField& cellVolumes,
			const vectorField& faceAreas,
			const dictionary& controlDict
		);


		//- Destructor
		FoamBase_EXPORT ~GAMGAgglomeration();


		// Member Functions

			// Access

		label size() const
		{
			return meshLevels_.size();
		}

		//- Return LDU mesh of given level
		FoamBase_EXPORT const lduMesh& meshLevel(const label leveli) const;

		//- Do we have mesh for given level?
		FoamBase_EXPORT bool hasMeshLevel(const label leveli) const;

		//- Return LDU interface addressing of given level
		FoamBase_EXPORT const lduInterfacePtrsList& interfaceLevel
		(
			const label leveli
		) const;

		//- Return cell restrict addressing of given level
		const labelField& restrictAddressing(const label leveli) const
		{
			return restrictAddressing_[leveli];
		}

		//- Return face restrict addressing of given level
		const labelList& faceRestrictAddressing(const label leveli) const
		{
			return faceRestrictAddressing_[leveli];
		}

		const labelListList& patchFaceRestrictAddressing(const label leveli)
			const
		{
			return patchFaceRestrictAddressing_[leveli];
		}

		//- Return face flip map of given level
		const boolList& faceFlipMap(const label leveli) const
		{
			return faceFlipMap_[leveli];
		}

		//- Return number of coarse cells (before processor agglomeration)
		label nCells(const label leveli) const
		{
			return nCells_[leveli];
		}

		//- Return number of coarse faces (before processor agglomeration)
		label nFaces(const label leveli) const
		{
			return nFaces_[leveli];
		}

		//- Return number of coarse patch faces (before processor
		//  agglomeration)
		const labelList& nPatchFaces(const label leveli) const
		{
			return nPatchFaces_[leveli];
		}


		// Restriction and prolongation

			//- Restrict (integrate by summation) cell field
		template<class Type>
		void restrictField
		(
			Field<Type>& cf,
			const Field<Type>& ff,
			const label fineLevelIndex,
			const bool procAgglom
		) const;

		//- Restrict (integrate by summation) face field
		template<class Type>
		void restrictFaceField
		(
			Field<Type>& cf,
			const Field<Type>& ff,
			const label fineLevelIndex
		) const;

		//- Restrict (integrate by summation) cell field
		template<class Type>
		void restrictField
		(
			Field<Type>& cf,
			const Field<Type>& ff,
			const labelList& fineToCoarse
		) const;

		//- Prolong (interpolate by injection) cell field
		template<class Type>
		void prolongField
		(
			Field<Type>& ff,
			const Field<Type>& cf,
			const label coarseLevelIndex,
			const bool procAgglom
		) const;


		// Procesor agglomeration. Note that the mesh and agglomeration is
		// stored per fineLevel (even though it is the coarse level mesh that
		// has been agglomerated). This is just for convenience and consistency
		// with GAMGSolver notation.

			//- Given fine to coarse processor map determine:
			//
			//    - for each coarse processor a master (minimum of the fine
			//        processors)
			//    - for each coarse processor the set of fine processors
			//        (element 0 is the master processor)
		static FoamBase_EXPORT void calculateRegionMaster
		(
			const label comm,
			const labelList& procAgglomMap,
			labelList& masterProcs,
			List<label>& agglomProcIDs
		);

		//- Whether to agglomerate across processors
		bool processorAgglomerate() const
		{
			return procAgglomeratorPtr_.valid();
		}

		//- Mapping from processor to agglomerated processor (global, all
		//  processors have the same information). Note that level is
		//  the fine, not the coarse, level index. This is to be
		//  consistent with the way the restriction is stored
		FoamBase_EXPORT const labelList& procAgglomMap(const label fineLeveli) const;

		//- Set of processors to agglomerate. Element 0 is the
		//  master processor. (local, same only on those processors that
		//  agglomerate)
		FoamBase_EXPORT const labelList& agglomProcIDs(const label fineLeveli) const;

		//- Check that level has combined mesh
		FoamBase_EXPORT bool hasProcMesh(const label fineLeveli) const;

		//- Communicator for current level or -1
		FoamBase_EXPORT label procCommunicator(const label fineLeveli) const;

		//- Mapping from processor to procMesh cells
		FoamBase_EXPORT const labelList& cellOffsets(const label fineLeveli) const;

		//- Mapping from processor to procMesh face
		FoamBase_EXPORT const labelListList& faceMap(const label fineLeveli) const;

		//- Mapping from processor to procMesh boundary
		FoamBase_EXPORT const labelListList& boundaryMap(const label fineLeveli) const;

		//- Mapping from processor to procMesh boundary face
		FoamBase_EXPORT const labelListListList& boundaryFaceMap(const label fineLeveli)
			const;

		//- Given restriction determines if coarse cells are connected.
		//  Return ok is so, otherwise creates new restriction that is
		static FoamBase_EXPORT bool checkRestriction
		(
			labelList& newRestrict,
			label& nNewCoarse,
			const lduAddressing& fineAddressing,
			const labelUList& restrict,
			const label nCoarse
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const GAMGAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GAMGAgglomerationTemplatesI.hxx>

//#ifdef NoRepository
//#include <GAMGAgglomerationTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GAMGAgglomeration_Header
