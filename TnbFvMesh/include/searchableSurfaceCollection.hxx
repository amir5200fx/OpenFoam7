#pragma once
#ifndef _searchableSurfaceCollection_Header
#define _searchableSurfaceCollection_Header

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
	tnbLib::searchableSurfaceCollection

Description
	Set of transformed searchableSurfaces. Does not do boolean operations.
	So when meshing might find parts 'inside'.

SourceFiles
	searchableSurfaceCollection.C

\*---------------------------------------------------------------------------*/

#include <searchableSurface.hxx>
#include <treeBoundBox.hxx>
#include <coordinateSystem.hxx>
#include <UPtrList.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class searchableSurfaceCollection Declaration
	\*---------------------------------------------------------------------------*/

	class searchableSurfaceCollection
		:
		public searchableSurface
	{
		// Private Member Data

			// Per instance data

				//- Instance name
		wordList instance_;

		//- Scaling vector
		vectorField scale_;

		//- transformation
		PtrList<coordinateSystem> transform_;

		UPtrList<searchableSurface> subGeom_;

		Switch mergeSubRegions_;

		//- Offsets for indices coming from different surfaces
		//  (sized with size() of each surface)
		labelList indexOffset_;

		//- Region names
		mutable wordList regions_;

		//- From individual regions to collection regions
		mutable labelList regionOffset_;


		// Private Member Functions

			//- Inherit findNearest from searchableSurface
		using searchableSurface::findNearest;

		//- Find point nearest to sample. Updates minDistSqr. Sets nearestInfo
		//  and surface index
		FoamFvMesh_EXPORT void findNearest
		(
			const pointField& samples,
			scalarField& minDistSqr,
			List<pointIndexHit>& nearestInfo,
			labelList& nearestSurf
		) const;

		//- Sort hits into per-surface bins. Misses are rejected.
		//  Maintains map back to position
		FoamFvMesh_EXPORT void sortHits
		(
			const List<pointIndexHit>& info,
			List<List<pointIndexHit>>& surfInfo,
			labelListList& infoMap
		) const;


	public:

		//- Runtime type information
		/*TypeName("searchableSurfaceCollection");*/
		static const char* typeName_() { return "searchableSurfaceCollection"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary (used by searchableSurface)
		FoamFvMesh_EXPORT searchableSurfaceCollection
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT searchableSurfaceCollection
		(
			const searchableSurfaceCollection&
		) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchableSurfaceCollection();


		// Member Functions

			//- Scaling vector per subsurface
		const vectorField& scale() const
		{
			return scale_;
		}

		//- Scaling vector per subsurface
		vectorField& scale()
		{
			return scale_;
		}

		//- Coordinate system per subsurface
		const PtrList<coordinateSystem>& transform() const
		{
			return transform_;
		}

		//- Coordinate system per subsurface
		PtrList<coordinateSystem>& transform()
		{
			return transform_;
		}

		FoamFvMesh_EXPORT virtual const wordList& regions() const;

		//- Whether supports volume type below
		virtual bool hasVolumeType() const
		{
			return false;
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

		// Other

			//- Set bounds of surface. Bounds currently set as list of
			//  bounding boxes. The bounds are hints to the surface as for
			//  the range of queries it can expect. faceMap/pointMap can be
			//  set if the surface has done any redistribution.
		FoamFvMesh_EXPORT virtual void distribute
		(
			const List<treeBoundBox>&,
			const bool keepNonLocal,
			autoPtr<mapDistribute>& faceMap,
			autoPtr<mapDistribute>& pointMap
		);

		//- WIP. Store element-wise field.
		FoamFvMesh_EXPORT virtual void setField(const labelList& values);

		//- WIP. From a set of hits (points and
		//  indices) get the specified field. Misses do not get set. Return
		//  empty field if not supported.
		FoamFvMesh_EXPORT virtual void getField(const List<pointIndexHit>&, labelList&) const;

		// regIOobject implementation

		bool writeData(Ostream&) const
		{
			NotImplemented;
			return false;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const searchableSurfaceCollection&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_searchableSurfaceCollection_Header
