#pragma once
#ifndef _snappyRefineDriver_Header
#define _snappyRefineDriver_Header

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
	tnbLib::snappyRefineDriver

Description

SourceFiles
	snappyRefineDriver.C

\*---------------------------------------------------------------------------*/

#include <treeBoundBox.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class refinementParameters;
	class snapParameters;

	class meshRefinement;
	class decompositionMethod;
	class fvMeshDistribute;

	/*---------------------------------------------------------------------------*\
							   Class snappyRefineDriver Declaration
	\*---------------------------------------------------------------------------*/

	class snappyRefineDriver
	{
		// Private Data

			//- Mesh+surface
		meshRefinement& meshRefiner_;

		//- Reference to decomposition method
		decompositionMethod& decomposer_;

		//- Reference to mesh distribution engine
		fvMeshDistribute& distributor_;

		//- From surface region to patch
		const labelList globalToMasterPatch_;

		//- From surface region to patch
		const labelList globalToSlavePatch_;


		// Private Member Functions

			//- Refine all cells pierced by explicit feature edges
		FoamSnappyHexMesh_EXPORT label featureEdgeRefine
		(
			const refinementParameters& refineParams,
			const label maxIter,
			const label minRefine
		);

		//- Refine all cells interacting with the surface
		FoamSnappyHexMesh_EXPORT label surfaceOnlyRefine
		(
			const refinementParameters& refineParams,
			const label maxIter
		);

		//- Refine all cells in small gaps
		FoamSnappyHexMesh_EXPORT label gapOnlyRefine
		(
			const refinementParameters& refineParams,
			const label maxIter
		);

		//- Refine cells with almost all sides refined
		FoamSnappyHexMesh_EXPORT label danglingCellRefine
		(
			const refinementParameters& refineParams,
			const label nFaces,
			const label maxIter
		);

		//- Remove all cells within intersected region
		FoamSnappyHexMesh_EXPORT void removeInsideCells
		(
			const refinementParameters& refineParams,
			const label nBufferLayers
		);

		//- Remove all cells inside/outside shell
		FoamSnappyHexMesh_EXPORT label shellRefine
		(
			const refinementParameters& refineParams,
			const label maxIter
		);

		//- Add baffles and remove unreachable cells
		FoamSnappyHexMesh_EXPORT void baffleAndSplitMesh
		(
			const refinementParameters& refineParams,
			const snapParameters& snapParams,
			const bool handleSnapProblems,
			const dictionary& motionDict
		);

		//- Add zones
		FoamSnappyHexMesh_EXPORT void zonify(const refinementParameters& refineParams);

		FoamSnappyHexMesh_EXPORT void splitAndMergeBaffles
		(
			const refinementParameters& refineParams,
			const snapParameters& snapParams,
			const bool handleSnapProblems,
			const dictionary& motionDict
		);

		//- Merge refined boundary faces (from exposing coarser cell)
		FoamSnappyHexMesh_EXPORT void mergePatchFaces
		(
			const refinementParameters& refineParams,
			const dictionary& motionDict
		);


	public:

		//- Runtime type information
		//ClassName("snappyRefineDriver");
		static const char* typeName_() { return "snappyRefineDriver"; }
		static FoamSnappyHexMesh_EXPORT const ::tnbLib::word typeName;
		static FoamSnappyHexMesh_EXPORT int debug;


		// Constructors

			//- Construct from components
		FoamSnappyHexMesh_EXPORT snappyRefineDriver
		(
			meshRefinement& meshRefiner,
			decompositionMethod& decomposer,
			fvMeshDistribute& distributor,
			const labelList& globalToMasterPatch,
			const labelList& globalToSlavePatch
		);

		//- Disallow default bitwise copy construction
		FoamSnappyHexMesh_EXPORT snappyRefineDriver(const snappyRefineDriver&) = delete;


		// Member Functions

			//- Do all the refinement
		FoamSnappyHexMesh_EXPORT void doRefine
		(
			const dictionary& refineDict,
			const refinementParameters& refineParams,
			const snapParameters& snapParams,
			const bool prepareForSnapping,
			const dictionary& motionDict
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSnappyHexMesh_EXPORT void operator=(const snappyRefineDriver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_snappyRefineDriver_Header
