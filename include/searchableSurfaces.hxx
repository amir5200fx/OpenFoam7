#pragma once
#ifndef _searchableSurfaces_Header
#define _searchableSurfaces_Header

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
	tnbLib::searchableSurfaces

Description
	Container for searchableSurfaces.

SourceFiles
	searchableSurfaces.C

\*---------------------------------------------------------------------------*/

#include <searchableSurface.hxx>
#include <labelPair.hxx>
#include <writer.hxx>

#include <PtrList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurface;

	/*---------------------------------------------------------------------------*\
							   Class searchableSurfaces Declaration
	\*---------------------------------------------------------------------------*/

	class searchableSurfaces
		:
		public PtrList<searchableSurface>
	{
		// Private Data

			//- Surface names
		wordList names_;

		//- Region names per surface
		List<wordList> regionNames_;

		////- From global region name to surface and region on surface
		// HashTable<labelPair> regionNames_;

		//- Indices of all surfaces. Precalculated and stored.
		labelList allSurfaces_;


		// Private Member Functions

			//- Is edge on face
		static FoamFvMesh_EXPORT bool connected
		(
			const triSurface& s,
			const label edgeI,
			const pointIndexHit& hit
		);


	public:

		/*ClassName("searchableSurfaces");*/
		static const char* typeName_() { return "searchableSurfaces"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct with length specified. Fill later.
		FoamFvMesh_EXPORT explicit searchableSurfaces(const label);


		////- Construct from list of dictionaries
		// searchableSurfaces(const IOobject&, const PtrList<dictionary>&);

		//- Construct from dictionary and whether to construct names always
		//  as surfaceName "_" regionName (singleRegionName false) or
		//  for single region surfaces as surfaceName only (singleRegionName
		//  true)
		FoamFvMesh_EXPORT searchableSurfaces
		(
			const IOobject&,
			const dictionary&,
			const bool singleRegionName
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchableSurfaces(const searchableSurfaces&) = delete;


		// Member Functions

		const wordList& names() const
		{
			return names_;
		}

		wordList& names()
		{
			return names_;
		}

		const List<wordList>& regionNames() const
		{
			return regionNames_;
		}

		List<wordList>& regionNames()
		{
			return regionNames_;
		}


		////- If adding surfaces 'by hand'
		// HashTable<labelPair>& regionNames()
		//{
		//    return regionNames_;
		//}
		////- Get surface and region for a name
		// const labelPair& surfaceRegion(const word& globalRegion) const
		//{
		//    return regionNames_[globalRegion];
		//}

		//- Find index of surface. Return -1 if not found.
		FoamFvMesh_EXPORT label findSurfaceID(const word& name) const;

		FoamFvMesh_EXPORT label findSurfaceRegionID
		(
			const word& surfaceName,
			const word& regionName
		) const;

		// Multiple point queries.

			//- Find any intersection. Return hit point information and
			//  surface number. If multiple surfaces hit the first surface
			//  is returned, not necessarily the nearest (to start).
		FoamFvMesh_EXPORT void findAnyIntersection
		(
			const pointField& start,
			const pointField& end,
			labelList& surfaces,
			List<pointIndexHit>&
		) const;

		//- Find all intersections in order from start to end. Returns for
		//  every hit the surface and the hit info.
		FoamFvMesh_EXPORT void findAllIntersections
		(
			const pointField& start,
			const pointField& end,
			labelListList& surfaces,
			List<List<pointIndexHit>>&
		) const;

		// Find intersections of edge nearest to both endpoints.
		FoamFvMesh_EXPORT void findNearestIntersection
		(
			const pointField& start,
			const pointField& end,
			labelList& surface1,
			List<pointIndexHit>& hit1,
			labelList& surface2,
			List<pointIndexHit>& hit2
		) const;

		//- Find nearest. Return -1 (and a miss()) or surface and nearest
		//  point.
		FoamFvMesh_EXPORT void findNearest
		(
			const pointField&,
			const scalarField& nearestDistSqr,
			labelList& surfaces,
			List<pointIndexHit>&
		) const;

		FoamFvMesh_EXPORT void findNearest
		(
			const pointField& samples,
			const scalarField& nearestDistSqr,
			const labelList& regionIndices,
			labelList& nearestSurfaces,
			List<pointIndexHit>& nearestInfo
		) const;

		//- Calculate bounding box
		FoamFvMesh_EXPORT boundBox bounds() const;

		// Checking

			//- Are all surfaces closed and manifold
		FoamFvMesh_EXPORT bool checkClosed(const bool report) const;

		//- Are all (triangulated) surfaces consistent normal orientation
		FoamFvMesh_EXPORT bool checkNormalOrientation(const bool report) const;

		//- Are all bounding boxes of similar size
		FoamFvMesh_EXPORT bool checkSizes(const scalar maxRatio, const bool report) const;

		//- Do surfaces self-intersect or intersect others
		FoamFvMesh_EXPORT bool checkIntersection
		(
			const scalar tol,
			const autoPtr<writer<scalar>>&,
			const bool report
		) const;

		//- Check triangle quality
		FoamFvMesh_EXPORT bool checkQuality
		(
			const scalar minQuality,
			const bool report
		) const;

		//- All topological checks. Return number of failed checks
		FoamFvMesh_EXPORT label checkTopology(const bool report) const;

		//- All geometric checks. Return number of failed checks
		FoamFvMesh_EXPORT label checkGeometry
		(
			const scalar maxRatio,
			const scalar tolerance,
			const autoPtr<writer<scalar>>& setWriter,
			const scalar minQuality,
			const bool report
		) const;

		//- Write some stats
		FoamFvMesh_EXPORT void writeStats(const List<wordList>&, Ostream&) const;


		// Member Operators

			//- Return const and non-const reference to searchableSurface by index.
		using PtrList<searchableSurface>::operator[];

		//- Return const reference to searchableSurface by name.
		FoamFvMesh_EXPORT const searchableSurface& operator[](const word&) const;

		//- Return reference to searchableSurface by name.
		FoamFvMesh_EXPORT searchableSurface& operator[](const word&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const searchableSurfaces&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_searchableSurfaces_Header
