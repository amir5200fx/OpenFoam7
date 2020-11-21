#pragma once
#ifndef _searchablePlate_Header
#define _searchablePlate_Header

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
	tnbLib::searchablePlate

Description
	Searching on finite plate. Plate has to be aligned with coordinate
	axes.
	Plate defined as origin and span. One of the components of span has
	to be 0 which defines the normal direction. E.g.

	span    = (Sx Sy 0)     // plate in x-y plane
	origin  = (Ox Oy Oz)

	now plane is from (Ox Oy Oz) to (Ox+Sx Oy+Sy Oz)

SourceFiles
	searchablePlate.C

\*---------------------------------------------------------------------------*/

#include <searchableSurface.hxx>
#include <treeBoundBox.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	/*---------------------------------------------------------------------------*\
						   Class searchablePlate Declaration
	\*---------------------------------------------------------------------------*/

	class searchablePlate
		:
		public searchableSurface
	{
		// Private Member Data

		const point origin_;

		const vector span_;

		//- Coordinate direction which is normal
		const direction normalDir_;

		mutable wordList regions_;


		// Private Member Functions

			//- Calculate normal direction from span
		static FoamFvMesh_EXPORT direction calcNormal(const point&);

		//- Inherit findNearest from searchableSurface
		using searchableSurface::findNearest;

		FoamFvMesh_EXPORT pointIndexHit findNearest
		(
			const point& sample,
			const scalar nearestDistSqr
		) const;

		FoamFvMesh_EXPORT pointIndexHit findLine
		(
			const point& start,
			const point& end
		) const;

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchablePlate(const searchablePlate&) = delete;

		//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const searchablePlate&) = delete;


	public:

		//- Runtime type information
		/*TypeName("searchablePlate");*/
		static const char* typeName_() { return "searchablePlate"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT searchablePlate
		(
			const IOobject& io,
			const point& origin,
			const vector& span
		);

		//- Construct from dictionary (used by searchableSurface)
		FoamFvMesh_EXPORT searchablePlate
		(
			const IOobject& io,
			const dictionary& dict
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchablePlate();


		// Member Functions

		FoamFvMesh_EXPORT virtual const wordList& regions() const;

		//- Whether supports volume type below
		virtual bool hasVolumeType() const
		{
			return false;
		}

		//- Range of local indices that can be returned.
		virtual label size() const
		{
			return 1;
		}

		//- Get representative set of element coordinates
		//  Usually the element centres (should be of length size()).
		FoamFvMesh_EXPORT virtual tmp<pointField> coordinates() const;

		//- Get bounding spheres (centre and radius squared), one per element.
		//  Any point on element is guaranteed to be inside.
		FoamFvMesh_EXPORT virtual void boundingSpheres
		(
			pointField& centres,
			scalarField& radiusSqr
		) const;

		//- Get the points that define the surface.
		FoamFvMesh_EXPORT virtual tmp<pointField> points() const;

		//- Does any part of the surface overlap the supplied bound box?
		FoamFvMesh_EXPORT virtual bool overlaps(const boundBox& bb) const;


		// Multiple point queries.

		FoamFvMesh_EXPORT virtual void findNearest
		(
			const pointField& sample,
			const scalarField& nearestDistSqr,
			List<pointIndexHit>&
		) const;

		FoamFvMesh_EXPORT virtual void findLine
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const;

		FoamFvMesh_EXPORT virtual void findLineAny
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const;

		//- Get all intersections in order from start to end.
		FoamFvMesh_EXPORT virtual void findLineAll
		(
			const pointField& start,
			const pointField& end,
			List<List<pointIndexHit>>&
		) const;

		//- From a set of points and indices get the region
		FoamFvMesh_EXPORT virtual void getRegion
		(
			const List<pointIndexHit>&,
			labelList& region
		) const;

		//- From a set of points and indices get the normal
		FoamFvMesh_EXPORT virtual void getNormal
		(
			const List<pointIndexHit>&,
			vectorField& normal
		) const;

		//- Determine type (inside/outside/mixed) for point. unknown if
		//  cannot be determined (e.g. non-manifold surface)
		FoamFvMesh_EXPORT virtual void getVolumeType
		(
			const pointField&,
			List<volumeType>&
		) const;


		// regIOobject implementation

		bool writeData(Ostream&) const
		{
			NotImplemented;
			return false;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_searchablePlate_Header
