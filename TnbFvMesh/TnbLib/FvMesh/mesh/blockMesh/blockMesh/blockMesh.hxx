#pragma once
#ifndef _blockMesh_Header
#define _blockMesh_Header

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
	tnbLib::blockMesh

Description
	A multi-block mesh generator

Note
	The vertices, cells and patches for filling the blocks are demand-driven.

SourceFiles
	blockMesh.C
	blockMeshCheck.C
	blockMeshCreate.C
	blockMeshMerge.C
	blockMeshTopology.C

\*---------------------------------------------------------------------------*/

#include <blockList.hxx>
#include <searchableSurfaces.hxx>
#include <polyMesh.hxx>
#include <IOdictionary.hxx>
#include <blockVertexList.hxx>
#include <blockEdgeList.hxx>
#include <blockFaceList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class blockMesh Declaration
	\*---------------------------------------------------------------------------*/

	class blockMesh
		:
		public blockList
	{
		// Private Data

			//- Reference to mesh dictionary
		const IOdictionary& meshDict_;

		//- Switch for verbose output
		bool verboseOutput;

		//- Switch checking face consistency (defaults to true)
		bool checkFaceCorrespondence_;

		//- Optional searchable geometry to project face-points to
		searchableSurfaces geometry_;

		//- The scaling factor to convert to meters
		scalar scaleFactor_;

		//- The list of block vertices
		blockVertexList blockVertices_;

		//- The list of block vertex positions
		pointField vertices_;

		//- The list of curved edges
		blockEdgeList edges_;

		//- The list of curved faces
		blockFaceList faces_;

		//- The blocks themselves (the topology) as a polyMesh
		polyMesh* topologyPtr_;

		label nPoints_;

		//- The sum of all cells in each block
		label nCells_;

		//- The point offset added to each block
		labelList blockOffsets_;

		//- The merge points information
		labelList mergeList_;

		mutable pointField points_;

		mutable cellShapeList cells_;

		mutable faceListList patches_;


		// Private Member Functions

		template<class Source>
		void checkPatchLabels
		(
			const Source& source,
			const word& patchName,
			const pointField& points,
			faceList& patchShapes
		) const;

		FoamFvMesh_EXPORT void readPatches
		(
			const dictionary& meshDescription,
			faceListList& tmpBlocksPatches,
			wordList& patchNames,
			wordList& patchTypes,
			wordList& nbrPatchNames
		);

		FoamFvMesh_EXPORT void readBoundary
		(
			const dictionary& meshDescription,
			wordList& patchNames,
			faceListList& tmpBlocksPatches,
			PtrList<dictionary>& patchDicts
		);

		FoamFvMesh_EXPORT void createCellShapes(cellShapeList& tmpBlockCells);

		FoamFvMesh_EXPORT polyMesh* createTopology(const IOdictionary&, const word& regionName);

		FoamFvMesh_EXPORT void check(const polyMesh&, const dictionary&) const;

		//- Determine the merge info and the final number of cells/points
		FoamFvMesh_EXPORT void calcMergeInfo();

		//- Determine the merge info and the final number of cells/points
		FoamFvMesh_EXPORT void calcMergeInfoFast();

		FoamFvMesh_EXPORT faceList createPatchFaces(const polyPatch& patchTopologyFaces) const;

		FoamFvMesh_EXPORT Pair<scalar> xCellSizes
		(
			const block& b,
			const pointField& blockPoints,
			const label j,
			const label k
		) const;

		FoamFvMesh_EXPORT Pair<scalar> yCellSizes
		(
			const block& b,
			const pointField& blockPoints,
			const label i,
			const label k
		) const;

		FoamFvMesh_EXPORT Pair<scalar> zCellSizes
		(
			const block& b,
			const pointField& blockPoints,
			const label i,
			const label j
		) const;

		FoamFvMesh_EXPORT void printCellSizeRange(const Pair<scalar>& cellSizes) const;

		FoamFvMesh_EXPORT void printCellSizeRanges
		(
			const direction d,
			const FixedList<Pair<scalar>, 4>& cellSizes
		) const;

		FoamFvMesh_EXPORT void createPoints() const;
		FoamFvMesh_EXPORT void createCells() const;
		FoamFvMesh_EXPORT void createPatches() const;

		//- As copy (not implemented)
		FoamFvMesh_EXPORT blockMesh(const blockMesh&);


	public:

		// Static Data Members

		//ClassName("blockMesh");
		static const char* typeName_() { return "blockMesh"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct from IOdictionary
		FoamFvMesh_EXPORT blockMesh(const IOdictionary&, const word& regionName);


		//- Destructor
		FoamFvMesh_EXPORT ~blockMesh();


		// Member Functions

			// Access

				//- Access to input dictionary
		const dictionary& meshDict() const
		{
			return meshDict_;
		}

		//- Optional searchable geometry to project face-points to
		const searchableSurfaces& geometry() const
		{
			return geometry_;
		}

		//- Reference to point field defining the blockMesh
		//  these points have not been scaled by scaleFactor
		FoamFvMesh_EXPORT const pointField& vertices() const;

		//- Return the blockMesh topology as a polyMesh
		FoamFvMesh_EXPORT const polyMesh& topology() const;

		//- Return the curved edges
		const blockEdgeList& edges() const
		{
			return edges_;
		}

		//- Return the curved faces
		const blockFaceList& faces() const
		{
			return faces_;
		}

		//- The scaling factor used to convert to meters
		FoamFvMesh_EXPORT scalar scaleFactor() const;

		//- The points for the entire mesh
		//  these points have been scaled by scaleFactor
		FoamFvMesh_EXPORT const pointField& points() const;

		//- Return cell shapes list
		FoamFvMesh_EXPORT const cellShapeList& cells() const;

		//- Return the patch face lists
		FoamFvMesh_EXPORT const faceListList& patches() const;

		//- Get patch information from the topology mesh
		FoamFvMesh_EXPORT PtrList<dictionary> patchDicts() const;

		//- Return patch names
		FoamFvMesh_EXPORT wordList patchNames() const;

		//- Number of blocks with specified zones
		FoamFvMesh_EXPORT label numZonedBlocks() const;


		// Edit

			//- Enable/disable verbose information about the progress
		FoamFvMesh_EXPORT void verbose(const bool on = true);


		// Write

			//- Writes edges of blockMesh in OBJ format.
		FoamFvMesh_EXPORT void writeTopology(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blockMesh_Header
