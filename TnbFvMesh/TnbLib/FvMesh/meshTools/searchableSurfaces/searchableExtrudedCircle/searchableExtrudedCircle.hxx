#pragma once
#ifndef _searchableExtrudedCircle_Header
#define _searchableExtrudedCircle_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::searchableExtrudedCircle

Description
	Searching on edgemesh with constant radius

SourceFiles
	searchableExtrudedCircle.C

\*---------------------------------------------------------------------------*/

#include <treeBoundBox.hxx>
#include <searchableSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class edgeMesh;
	class treeDataEdge;
	template <class Type> class indexedOctree;

	/*---------------------------------------------------------------------------*\
					  Class searchableExtrudedCircle Declaration
	\*---------------------------------------------------------------------------*/

	class searchableExtrudedCircle
		:
		public searchableSurface
	{
		// Private Member Data

			//- Feature
		autoPtr<edgeMesh> eMeshPtr_;

		//- Search structure
		autoPtr<indexedOctree<treeDataEdge>> edgeTree_;

		//- Radius
		const scalar radius_;

		//- Names of regions
		mutable wordList regions_;


	public:

		//- Runtime type information
		/*TypeName("searchableExtrudedCircle");*/
		static const char* typeName_() { return "searchableExtrudedCircle"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary (used by searchableSurface)
		FoamFvMesh_EXPORT searchableExtrudedCircle
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchableExtrudedCircle(const searchableExtrudedCircle&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchableExtrudedCircle();


		// Member Functions

		FoamFvMesh_EXPORT virtual const wordList& regions() const;

		//- Whether supports volume type below
		virtual bool hasVolumeType() const
		{
			return true;
		}

		//- Range of local indices that can be returned.
		FoamFvMesh_EXPORT virtual label size() const;

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
		virtual tmp<pointField> points() const
		{
			return coordinates();
		}

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

		//- Unique to parametric geometry: given points find
		//  an interpolated (along the curve) point on the surface.
		//  The lambdas[0] is equivalent for start, lambdas.last()
		//  is equivalent for end.
		FoamFvMesh_EXPORT virtual void findParametricNearest
		(
			const point& start,
			const point& end,
			const scalarField& lambdas,
			const scalarField& nearestDistSqr,
			List<pointIndexHit>&
		) const;

		virtual void findLine
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const
		{
			NotImplemented;
		}

		virtual void findLineAny
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const
		{
			NotImplemented;
		}

		//- Get all intersections in order from start to end.
		virtual void findLineAll
		(
			const pointField& start,
			const pointField& end,
			List<List<pointIndexHit>>&
		) const
		{
			NotImplemented;
		}

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
		virtual void getVolumeType
		(
			const pointField&,
			List<volumeType>&
		) const
		{
			NotImplemented;
		}

		bool writeData(Ostream&) const
		{
			NotImplemented;
			return false;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const searchableExtrudedCircle&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_searchableExtrudedCircle_Header
