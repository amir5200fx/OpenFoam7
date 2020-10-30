#pragma once
#ifndef _searchableCylinder_Header
#define _searchableCylinder_Header

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
	tnbLib::searchableCylinder

Description
	Searching on cylinder

SourceFiles
	searchableCylinder.C

\*---------------------------------------------------------------------------*/

#include <treeBoundBox.hxx>
#include <searchableSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	/*---------------------------------------------------------------------------*\
							   Class searchableCylinder Declaration
	\*---------------------------------------------------------------------------*/

	class searchableCylinder
		:
		public searchableSurface
	{
		// Private Member Data

			//- 'left' point
		const point point1_;

		//- 'right' point
		const point point2_;

		//- Length of vector point2-point1
		const scalar magDir_;

		//- Normalised vector point2-point1
		const vector unitDir_;

		//- Radius squared
		const scalar radius_;

		//- Names of regions
		mutable wordList regions_;


		// Private Member Functions

			//- Inherit findNearest from searchableSurface
		using searchableSurface::findNearest;

		//- Find nearest point on cylinder.
		FoamFvMesh_EXPORT pointIndexHit findNearest
		(
			const point& sample,
			const scalar nearestDistSqr
		) const;

		FoamFvMesh_EXPORT scalar radius2(const point& pt) const;

		//- Find intersection with cylinder
		FoamFvMesh_EXPORT void findLineAll
		(
			const point& start,
			const point& end,
			pointIndexHit& near,
			pointIndexHit& far
		) const;

		//- Return the boundBox of the cylinder
		FoamFvMesh_EXPORT boundBox calcBounds() const;


	public:

		//- Runtime type information
		/*TypeName("searchableCylinder");*/
		static const char* typeName_() { return "searchableCylinder"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT searchableCylinder
		(
			const IOobject& io,
			const point&,
			const point&,
			const scalar radius
		);

		//- Construct from dictionary (used by searchableSurface)
		FoamFvMesh_EXPORT searchableCylinder
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchableCylinder(const searchableCylinder&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchableCylinder();


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
		virtual bool overlaps(const boundBox& bb) const
		{
			NotImplemented;

			return false;
		}


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
		FoamFvMesh_EXPORT void operator=(const searchableCylinder&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_searchableCylinder_Header
