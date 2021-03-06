#pragma once
#ifndef _triSurfaceSearch_Header
#define _triSurfaceSearch_Header

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
	tnbLib::triSurfaceSearch

Description
	Helper class to search on triSurface.

SourceFiles
	triSurfaceSearch.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <boolList.hxx>
#include <pointIndexHit.hxx>
#include <indexedOctree.hxx>
#include <treeDataTriSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurface;

	/*---------------------------------------------------------------------------*\
						  Class triSurfaceSearch Declaration
	\*---------------------------------------------------------------------------*/

	class triSurfaceSearch
	{
		// Private Data

			//- Reference to surface to work on
		const triSurface& surface_;

		//- Optional tolerance to use in searches
		scalar tolerance_;

		//- Optional max tree depth of octree
		label maxTreeDepth_;

		//- Octree for searches
		mutable autoPtr<indexedOctree<treeDataTriSurface>> treePtr_;


		// Private Member Functions

			//- Check whether the current hit on the surface which lies on lineVec
			//  is unique.
			//  point : return 1 unique hit
			//  edge  : return 1 hit if in the cone of the edge faces
			//        : return 2 hits if outside or on the cone.
		FoamFvMesh_EXPORT bool checkUniqueHit
		(
			const pointIndexHit& currHit,
			const DynamicList<pointIndexHit, 1, 1>& hits,
			const vector& lineVec
		) const;


	public:

		// Constructors

			//- Construct from surface. Holds reference to surface!
		FoamFvMesh_EXPORT explicit triSurfaceSearch(const triSurface&);

		//- Construct from surface and dictionary.
		FoamFvMesh_EXPORT triSurfaceSearch(const triSurface&, const dictionary& dict);

		//- Construct from components
		FoamFvMesh_EXPORT triSurfaceSearch
		(
			const triSurface& surface,
			const scalar tolerance,
			const label maxTreeDepth
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT triSurfaceSearch(const triSurfaceSearch&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT ~triSurfaceSearch();


		// Member Functions

			//- Clear storage
		FoamFvMesh_EXPORT void clearOut();

		//- Demand driven construction of the octree
		FoamFvMesh_EXPORT const indexedOctree<treeDataTriSurface>& tree() const;

		//- Return reference to the surface.
		const triSurface& surface() const
		{
			return surface_;
		}

		//- Return tolerance to use in searches
		scalar tolerance() const
		{
			return tolerance_;
		}

		//- Return max tree depth of octree
		label maxTreeDepth() const
		{
			return maxTreeDepth_;
		}

		//- Calculate for each searchPoint inside/outside status.
		FoamFvMesh_EXPORT boolList calcInside(const pointField& searchPoints) const;

		FoamFvMesh_EXPORT void findNearest
		(
			const pointField& samples,
			const scalarField& nearestDistSqr,
			List<pointIndexHit>& info
		) const;

		//- Calculate nearest point on surface for single searchPoint. Returns
		//  in pointIndexHit:
		//  - hit()      : whether nearest point found within bounding box
		//  - hitPoint() : coordinate of nearest point
		//  - index()    : surface triangle label
		FoamFvMesh_EXPORT pointIndexHit nearest(const point&, const vector& span) const;

		FoamFvMesh_EXPORT void findLine
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>& info
		) const;

		FoamFvMesh_EXPORT void findLineAny
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>& info
		) const;

		//- Calculate all intersections from start to end
		FoamFvMesh_EXPORT void findLineAll
		(
			const pointField& start,
			const pointField& end,
			List<List<pointIndexHit>>& info
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const triSurfaceSearch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurfaceSearch_Header
