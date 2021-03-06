#pragma once
#ifndef _triSurfaceRegionSearch_Header
#define _triSurfaceRegionSearch_Header

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
	tnbLib::triSurfaceRegionSearch

Description
	Helper class to search on triSurface. Creates an octree for each region of
	the surface and only searches on the specified regions.

SourceFiles
	triSurfaceRegionSearch.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <pointIndexHit.hxx>
#include <triSurfaceSearch.hxx>
#include <labelledTri.hxx>
#include <IndirectList.hxx>
#include <PtrList.hxx>
#include <indexedOctree.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class triSurfaceRegionSearch Declaration
	\*---------------------------------------------------------------------------*/

	class triSurfaceRegionSearch
		:
		public triSurfaceSearch
	{
		// Private Typedefs

		typedef PrimitivePatch<IndirectList<labelledTri>, const pointField&>
			indirectTriSurface;

		typedef treeDataPrimitivePatch<indirectTriSurface>
			treeDataIndirectTriSurface;

		typedef indexedOctree<treeDataIndirectTriSurface> treeType;


		// Private Data

			//- Surface is split into patches by region
		mutable PtrList<indirectTriSurface> indirectRegionPatches_;

		//- Search tree for each region
		mutable PtrList<treeType> treeByRegion_;


	public:

		// Constructors

			//- Construct from surface. Holds reference to surface!
		FoamFvMesh_EXPORT explicit triSurfaceRegionSearch(const triSurface&);

		//- Construct from surface and dictionary. Holds reference to surface!
		FoamFvMesh_EXPORT triSurfaceRegionSearch(const triSurface&, const dictionary& dict);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT triSurfaceRegionSearch(const triSurfaceRegionSearch&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT ~triSurfaceRegionSearch();

		//- Clear storage
		FoamFvMesh_EXPORT void clearOut();


		// Member Functions

			// Access

				//- Demand driven construction of octree for each region.
				//  Currently creates a tree for each region; could optimise
				//  by only constructing trees when they are in regionIndices
		FoamFvMesh_EXPORT const PtrList<treeType>& treeByRegion() const;

		// Query

			//- Find the nearest point on the surface out of the regions
			//  supplied in the list regionIndices. Ignores regions that are
			//  not specified
		FoamFvMesh_EXPORT void findNearest
		(
			const pointField& samples,
			const scalarField& nearestDistSqr,
			const labelList& regionIndices,
			List<pointIndexHit>& info
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const triSurfaceRegionSearch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_triSurfaceRegionSearch_Header
