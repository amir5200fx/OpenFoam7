#pragma once
#ifndef _meshSearch_Header
#define _meshSearch_Header

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
	tnbLib::meshSearch

Description
	Various (local, not parallel) searches on polyMesh;
	uses (demand driven) octree to search.

SourceFiles
	meshSearch.C

\*---------------------------------------------------------------------------*/

#include <pointIndexHit.hxx>
#include <pointField.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class treeDataCell;
	class treeDataFace;
	template<class Type> class indexedOctree;
	class treeBoundBox;

	/*---------------------------------------------------------------------------*\
							   Class meshSearch Declaration
	\*---------------------------------------------------------------------------*/

	class meshSearch
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Whether to use cell decomposition for all geometric tests
		const polyMesh::cellDecomposition cellDecompMode_;

		//- Data bounding box
		mutable autoPtr<treeBoundBox> overallBbPtr_;

		//- Demand driven octrees
		mutable autoPtr<indexedOctree<treeDataFace>> boundaryTreePtr_;
		mutable autoPtr<indexedOctree<treeDataCell>> cellTreePtr_;


		// Private Member Functions

			//- Updates nearestI, nearestDistSqr from any closer ones.
		static FoamFvMesh_EXPORT bool findNearer
		(
			const point& sample,
			const pointField& points,
			label& nearestI,
			scalar& nearestDistSqr
		);

		//- Updates nearestI, nearestDistSqr from any selected closer ones.
		static FoamFvMesh_EXPORT bool findNearer
		(
			const point& sample,
			const pointField& points,
			const labelList& indices,
			label& nearestI,
			scalar& nearestDistSqr
		);


		// Cells

			//- Nearest cell centre using octree
		FoamFvMesh_EXPORT label findNearestCellTree(const point&) const;

		//- Nearest cell centre going through all cells
		FoamFvMesh_EXPORT label findNearestCellLinear(const point&) const;

		//- Walk from seed. Does not 'go around' boundary, just returns
		//  last cell before boundary.
		FoamFvMesh_EXPORT label findNearestCellWalk(const point&, const label) const;

		//- Cell containing location. Linear search.
		FoamFvMesh_EXPORT label findCellLinear(const point&) const;

		//- Walk from seed. Does not 'go around' boundary, just returns
		//  last cell before boundary.
		FoamFvMesh_EXPORT label findCellWalk(const point&, const label) const;


		// Faces

		FoamFvMesh_EXPORT label findNearestFaceTree(const point&) const;

		FoamFvMesh_EXPORT label findNearestFaceLinear(const point&) const;

		FoamFvMesh_EXPORT label findNearestFaceWalk(const point&, const label) const;



		// Boundary faces

			//- Walk from seed to find nearest boundary face. Gets stuck in
			//  local minimum.
		FoamFvMesh_EXPORT label findNearestBoundaryFaceWalk
		(
			const point& location,
			const label seedFacei
		) const;


	public:

		// Declare name of the class and its debug switch
		/*ClassName("meshSearch");*/
		static const char* typeName_() { return "meshSearch"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Static Data Members

			//- Tolerance on linear dimensions
		static FoamFvMesh_EXPORT scalar tol_;


		// Constructors

			//- Construct from components. Constructs bb slightly bigger than
			//  mesh points bb.
		FoamFvMesh_EXPORT meshSearch
		(
			const polyMesh& mesh,
			const polyMesh::cellDecomposition = polyMesh::CELL_TETS
		);

		//- Construct with a custom bounding box. Any mesh element outside
		//  bb will not be found. Up to user to make sure bb
		//  extends slightly beyond wanted elements.
		FoamFvMesh_EXPORT meshSearch
		(
			const polyMesh& mesh,
			const treeBoundBox& bb,
			const polyMesh::cellDecomposition = polyMesh::CELL_TETS
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT meshSearch(const meshSearch&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT ~meshSearch();


		// Member Functions

			// Access

		const polyMesh& mesh() const
		{
			return mesh_;
		}

		polyMesh::cellDecomposition decompMode() const
		{
			return cellDecompMode_;
		}

		//- Get (demand driven) reference to octree holding all
		//  boundary faces
		FoamFvMesh_EXPORT const indexedOctree<treeDataFace>& boundaryTree() const;

		//- Get (demand driven) reference to octree holding all cells
		FoamFvMesh_EXPORT const indexedOctree<treeDataCell>& cellTree() const;


		// Queries

			//- Find nearest cell in terms of cell centre.
			//  Options:
			//  - use octree
			//  - use linear search
			//  - if seed is provided walk. (uses findNearestCellWalk;
			//    does not handle holes in domain)
		FoamFvMesh_EXPORT label findNearestCell
		(
			const point& location,
			const label seedCelli = -1,
			const bool useTreeSearch = true
		) const;

		FoamFvMesh_EXPORT label findNearestFace
		(
			const point& location,
			const label seedFacei = -1,
			const bool useTreeSearch = true
		) const;

		//- Find cell containing location.
		//  If seed provided walks and falls back to linear/tree search.
		//  (so handles holes correctly)s
		//  Returns -1 if not in domain.
		FoamFvMesh_EXPORT label findCell
		(
			const point& location,
			const label seedCelli = -1,
			const bool useTreeSearch = true
		) const;

		//- Find nearest boundary face
		//  If seed provided walks but then does not pass local minima
		//  in distance. Also does not jump from one connected region to
		//  the next.
		FoamFvMesh_EXPORT label findNearestBoundaryFace
		(
			const point& location,
			const label seedFacei = -1,
			const bool useTreeSearch = true
		) const;

		//- Find first intersection of boundary in segment [pStart, pEnd]
		//  (so inclusive of endpoints). Always octree for now
		FoamFvMesh_EXPORT pointIndexHit intersection(const point& pStart, const point& pEnd)
			const;

		//- Find all intersections of boundary within segment pStart .. pEnd
		//  Always octree for now
		FoamFvMesh_EXPORT List<pointIndexHit> intersections
		(
			const point& pStart,
			const point& pEnd
		) const;

		//- Determine inside/outside status
		FoamFvMesh_EXPORT bool isInside(const point&) const;


		//- Delete all storage
		FoamFvMesh_EXPORT void clearOut();

		//- Correct for mesh geom/topo changes
		FoamFvMesh_EXPORT void correct();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const meshSearch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshSearch_Header
