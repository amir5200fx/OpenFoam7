#pragma once
#ifndef _treeDataPoint_Header
#define _treeDataPoint_Header

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
	tnbLib::treeDataPoint

Description
	Holds (reference to) pointField. Encapsulation of data needed for
	octree searches.
	Used for searching for nearest point. No bounding boxes around points.
	Only overlaps and calcNearest are implemented, rest makes little sense.

	Optionally works on subset of points.

SourceFiles
	treeDataPoint.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <treeBoundBox.hxx>
#include <linePointRef.hxx>
#include <volumeType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	template<class Type> class indexedOctree;

	/*---------------------------------------------------------------------------*\
							   Class treeDataPoint Declaration
	\*---------------------------------------------------------------------------*/

	class treeDataPoint
	{
		// Private Data

		const pointField& points_;

		//- Subset of points to work on (or empty)
		const labelList pointLabels_;

		const bool useSubset_;

	public:


		class findNearestOp
		{
			const indexedOctree<treeDataPoint>& tree_;

		public:

			FoamFvMesh_EXPORT findNearestOp(const indexedOctree<treeDataPoint>& tree);

			FoamFvMesh_EXPORT void operator()
				(
					const labelUList& indices,
					const point& sample,

					scalar& nearestDistSqr,
					label& minIndex,
					point& nearestPoint
					) const;

			FoamFvMesh_EXPORT void operator()
				(
					const labelUList& indices,
					const linePointRef& ln,

					treeBoundBox& tightest,
					label& minIndex,
					point& linePoint,
					point& nearestPoint
					) const;
		};


		class findIntersectOp
		{
		public:

			FoamFvMesh_EXPORT findIntersectOp(const indexedOctree<treeDataPoint>& tree);

			//- Calculate intersection of triangle with ray. Sets result
			//  accordingly
			FoamFvMesh_EXPORT bool operator()
				(
					const label index,
					const point& start,
					const point& end,
					point& intersectionPoint
					) const;
		};


		// Declare name of the class and its debug switch
		/*ClassName("treeDataPoint");*/
		static const char* typeName_() { return "treeDataPoint"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct from pointField. Holds reference!
		FoamFvMesh_EXPORT treeDataPoint(const pointField&);

		//- Construct from subset of pointField. Holds reference!
		FoamFvMesh_EXPORT treeDataPoint(const pointField&, const labelList&);


		// Member Functions

			// Access

		inline label size() const
		{
			return
				(
					useSubset_
					? pointLabels_.size()
					: points_.size()
					);
		}

		inline const labelList& pointLabels() const
		{
			return pointLabels_;
		}

		const pointField& points() const
		{
			return points_;
		}

		bool useSubset() const
		{
			return useSubset_;
		}

		//- Get representative point cloud for all shapes inside
		//  (one point per shape)
		FoamFvMesh_EXPORT pointField shapePoints() const;


		// Search

			//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
			//  Only makes sense for closed surfaces.
		FoamFvMesh_EXPORT volumeType getVolumeType
		(
			const indexedOctree<treeDataPoint>&,
			const point&
		) const;

		//- Does (bb of) shape at index overlap bb
		FoamFvMesh_EXPORT bool overlaps
		(
			const label index,
			const treeBoundBox& sampleBb
		) const;

		//- Does shape at index overlap the sphere
		FoamFvMesh_EXPORT bool overlaps
		(
			const label index,
			const point& centre,
			const scalar radiusSqr
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_treeDataPoint_Header
