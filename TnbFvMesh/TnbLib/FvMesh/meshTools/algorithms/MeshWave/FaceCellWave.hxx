#pragma once
#ifndef _FaceCellWave_Header
#define _FaceCellWave_Header

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
	tnbLib::FaceCellWave

Description
	Wave propagation of information through grid. Every iteration
	information goes through one layer of cells. Templated on information
	that is transferred.

	Handles parallel and cyclics and non-parallel cyclics.

	Note: whether to propagate depends on the return value of Type::update
	which returns true (i.e. propagate) if the value changes by more than a
	certain tolerance.
	This tolerance can be very strict for normal face-cell and parallel
	cyclics (we use a value of 0.01 just to limit propagation of small changes)
	but for non-parallel cyclics this tolerance can be critical and if chosen
	too small can lead to non-convergence.

SourceFiles
	FaceCellWave.C

\*---------------------------------------------------------------------------*/

#include <PackedBoolList.hxx>
#include <DynamicList.hxx>
#include <primitiveFieldsFwd.hxx>
#include <labelPair.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class polyPatch;
	class vectorTensorTransform;

	/*---------------------------------------------------------------------------*\
							Class FaceCellWaveName Declaration
	\*---------------------------------------------------------------------------*/

	//TemplateName(FaceCellWave);
	class FaceCellWaveName
	{
	public:
		FaceCellWaveName()
		{
		}

		static const char* typeName_() { return "FaceCellWave"; }
		static const FoamFvMesh_EXPORT word typeName;
		static FoamFvMesh_EXPORT int debug;
	};


	/*---------------------------------------------------------------------------*\
							   Class FaceCellWave Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type, class TrackingData = int>
	class FaceCellWave
		:
		public FaceCellWaveName
	{
	protected:

		// Protected data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Optional boundary faces that information should travel through
		const labelPairList explicitConnections_;

		//- Information for all faces
		UList<Type>& allFaceInfo_;

		//- Information for all cells
		UList<Type>& allCellInfo_;

		//- Additional data to be passed into container
		TrackingData& td_;

		//- Has face changed
		PackedBoolList changedFace_;

		//- List of changed faces
		DynamicList<label> changedFaces_;

		//- Has cell changed
		PackedBoolList changedCell_;

		// Cells that have changed
		DynamicList<label> changedCells_;


		//- Contains cyclics
		const bool hasCyclicPatches_;

		//- Contains cyclicAMI
		const bool hasCyclicAMIPatches_;

		//- Number of evaluations
		label nEvals_;

		//- Number of unvisited cells/faces
		label nUnvisitedCells_;
		label nUnvisitedFaces_;


		//- Updates cellInfo with information from neighbour. Updates all
		//  statistics.
		FoamFvMesh_EXPORT bool updateCell
		(
			const label celli,
			const label neighbourFacei,
			const Type& neighbourInfo,
			const scalar tol,
			Type& cellInfo
		);

		//- Updates faceInfo with information from neighbour. Updates all
		//  statistics.
		FoamFvMesh_EXPORT bool updateFace
		(
			const label facei,
			const label neighbourCelli,
			const Type& neighbourInfo,
			const scalar tol,
			Type& faceInfo
		);

		//- Updates faceInfo with information from same face. Updates all
		//  statistics.
		FoamFvMesh_EXPORT bool updateFace
		(
			const label facei,
			const Type& neighbourInfo,
			const scalar tol,
			Type& faceInfo
		);


		// Parallel, cyclic

			//- Debugging: check info on both sides of cyclic
		FoamFvMesh_EXPORT void checkCyclic(const polyPatch& pPatch) const;

		//- Has cyclic patch?
		template<class PatchType>
		bool hasPatch() const;

		//- Merge received patch data into global data
		FoamFvMesh_EXPORT void mergeFaceInfo
		(
			const polyPatch& patch,
			const label nFaces,
			const labelList&,
			const List<Type>&
		);

		//- Extract info for single patch only
		FoamFvMesh_EXPORT label getChangedPatchFaces
		(
			const polyPatch& patch,
			const label startFacei,
			const label nFaces,
			labelList& changedPatchFaces,
			List<Type>& changedPatchFacesInfo
		) const;

		//- Handle leaving domain. Implementation referred to Type
		FoamFvMesh_EXPORT void leaveDomain
		(
			const polyPatch& patch,
			const label nFaces,
			const labelList& faceLabels,
			List<Type>& faceInfo
		) const;

		//- Handle leaving domain. Implementation referred to Type
		FoamFvMesh_EXPORT void enterDomain
		(
			const polyPatch& patch,
			const label nFaces,
			const labelList& faceLabels,
			List<Type>& faceInfo
		) const;

		//- Offset face labels by constant value
		static FoamFvMesh_EXPORT void offset
		(
			const polyPatch& patch,
			const label off,
			const label nFaces,
			labelList& faces
		);

		//- Apply transformation to Type
		FoamFvMesh_EXPORT void transform
		(
			const tensorField& rotTensor,
			const label nFaces,
			List<Type>& faceInfo
		);

		//- Apply transformation to Type
		FoamFvMesh_EXPORT void transform
		(
			const vectorTensorTransform& trans,
			const label nFaces,
			List<Type>& faceInfo
		);

		//- Merge data from across processor boundaries
		FoamFvMesh_EXPORT void handleProcPatches();

		//- Merge data from across cyclics
		FoamFvMesh_EXPORT void handleCyclicPatches();

		//- Merge data from across AMI cyclics
		FoamFvMesh_EXPORT void handleAMICyclicPatches();

		//- Merge data across explicitly provided local connections (usually
		//  baffles)
		FoamFvMesh_EXPORT void handleExplicitConnections();


		// Protected static data

		static FoamFvMesh_EXPORT const scalar geomTol_;
		static FoamFvMesh_EXPORT scalar propagationTol_;

		//- Used as default trackdata value to satisfy default template
		//  argument.
		static FoamFvMesh_EXPORT int dummyTrackData_;


	public:

		// Static Functions

			//- Access to tolerance
		static scalar propagationTol()
		{
			return propagationTol_;
		}

		//- Change tolerance
		static void setPropagationTol(const scalar tol)
		{
			propagationTol_ = tol;
		}


		// Constructors

			// Construct from mesh. Use setFaceInfo and iterate() to do actual
			// calculation.
		FoamFvMesh_EXPORT FaceCellWave
		(
			const polyMesh&,
			UList<Type>& allFaceInfo,
			UList<Type>& allCellInfo,
			TrackingData& td = dummyTrackData_
		);

		//- Construct from mesh and list of changed faces with the Type
		//  for these faces. Iterates until nothing changes or maxIter reached.
		//  (maxIter can be 0)
		FoamFvMesh_EXPORT FaceCellWave
		(
			const polyMesh&,
			const labelList& initialChangedFaces,
			const List<Type>& changedFacesInfo,
			UList<Type>& allFaceInfo,
			UList<Type>& allCellInfo,
			const label maxIter,
			TrackingData& td = dummyTrackData_
		);

		//- Construct from mesh and explicitly connected boundary faces
		//  and list of changed faces with the Type
		//  for these faces. Iterates until nothing changes or maxIter reached.
		//  (maxIter can be 0)
		FoamFvMesh_EXPORT FaceCellWave
		(
			const polyMesh&,
			const labelPairList& explicitConnections,
			const bool handleCyclicAMI,
			const labelList& initialChangedFaces,
			const List<Type>& changedFacesInfo,
			UList<Type>& allFaceInfo,
			UList<Type>& allCellInfo,
			const label maxIter,
			TrackingData& td = dummyTrackData_
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT FaceCellWave(const FaceCellWave&) = delete;


		//- Destructor
		virtual ~FaceCellWave()
		{}


		// Member Functions

			// Access

				//- Access allFaceInfo
		UList<Type>& allFaceInfo()
		{
			return allFaceInfo_;
		}

		//- Access allCellInfo
		UList<Type>& allCellInfo()
		{
			return allCellInfo_;
		}

		//- Additional data to be passed into container
		const TrackingData& data() const
		{
			return td_;
		}

		//- Access mesh
		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Get number of unvisited cells, i.e. cells that were not (yet)
		//  reached from walking across mesh. This can happen from
		//  - not enough iterations done
		//  - a disconnected mesh
		//  - a mesh without walls in it
		FoamFvMesh_EXPORT label getUnsetCells() const;

		//- Get number of unvisited faces
		FoamFvMesh_EXPORT label getUnsetFaces() const;


		// Edit

			//- Set initial changed faces
		FoamFvMesh_EXPORT void setFaceInfo
		(
			const labelList& changedFaces,
			const List<Type>& changedFacesInfo
		);

		//- Propagate from face to cell. Returns total number of cells
		//  (over all processors) changed.
		FoamFvMesh_EXPORT virtual label faceToCell();

		//- Propagate from cell to face. Returns total number of faces
		//  (over all processors) changed. (Faces on processorpatches are
		//  counted double)
		FoamFvMesh_EXPORT virtual label cellToFace();

		//- Iterate until no changes or maxIter reached.  Returns actual
		//  number of iterations.
		FoamFvMesh_EXPORT virtual label iterate(const label maxIter);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const FaceCellWave&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <FaceCellWaveI.hxx>

//#ifdef NoRepository
//#include <FaceCellWave.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_FaceCellWave_Header
