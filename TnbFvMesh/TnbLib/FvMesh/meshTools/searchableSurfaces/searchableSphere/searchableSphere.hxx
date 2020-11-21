#pragma once
#ifndef _searchableSphere_Header
#define _searchableSphere_Header

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
	tnbLib::searchableSphere

Description
	Searching on sphere

SourceFiles
	searchableSphere.C

\*---------------------------------------------------------------------------*/

#include <treeBoundBox.hxx>
#include <searchableSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	/*---------------------------------------------------------------------------*\
							   Class searchableSphere Declaration
	\*---------------------------------------------------------------------------*/

	class searchableSphere
		:
		public searchableSurface
	{
		// Private Member Data

			//- Centre point
		const point centre_;

		//- Radius
		const scalar radius_;

		//- Names of regions
		mutable wordList regions_;


		// Private Member Functions

			//- Inherit findNearest from searchableSurface
		using searchableSurface::findNearest;

		//- Find nearest point on sphere.
		FoamFvMesh_EXPORT pointIndexHit findNearest
		(
			const point& sample,
			const scalar nearestDistSqr
		) const;

		//- Find intersection with sphere
		FoamFvMesh_EXPORT void findLineAll
		(
			const point& start,
			const point& end,
			pointIndexHit& near,
			pointIndexHit& far
		) const;


	public:

		//- Runtime type information
		/*TypeName("searchableSphere");*/
		static const char* typeName_() { return "searchableSphere"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT searchableSphere(const IOobject& io, const point&, const scalar radius);

		//- Construct from dictionary (used by searchableSurface)
		FoamFvMesh_EXPORT searchableSphere
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchableSphere(const searchableSphere&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchableSphere();


		// Member Functions

		FoamFvMesh_EXPORT virtual const wordList& regions() const;

		//- Whether supports volume type below
		virtual bool hasVolumeType() const
		{
			return true;
		}

		//- Range of local indices that can be returned.
		virtual label size() const
		{
			return 1;
		}

		//- Get representative set of element coordinates
		//  Usually the element centres (should be of length size()).
		virtual tmp<pointField> coordinates() const
		{
			tmp<pointField> tCtrs(new pointField(1, centre_));
			return tCtrs;
		}

		//- Get bounding spheres (centre and radius squared), one per element.
		//  Any point on element is guaranteed to be inside.
		FoamFvMesh_EXPORT virtual void boundingSpheres
		(
			pointField& centres,
			scalarField& radiusSqr
		) const;

		//- Get the points that define the surface.
		virtual tmp<pointField> points() const
		{
			return coordinates();
		}

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


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const searchableSphere&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_searchableSphere_Header
