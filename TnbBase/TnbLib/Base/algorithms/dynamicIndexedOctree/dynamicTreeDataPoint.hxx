#pragma once
#ifndef _dynamicTreeDataPoint_Header
#define _dynamicTreeDataPoint_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::dynamicTreeDataPoint

Description
	Holds (reference to) pointField. Encapsulation of data needed for
	octree searches.
	Used for searching for nearest point. No bounding boxes around points.
	Only overlaps and calcNearest are implemented, rest makes little sense.

	Optionally works on subset of points.

SourceFiles
	dynamicTreeDataPoint.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <treeBoundBox.hxx>
#include <linePointRef.hxx>
#include <volumeType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	template<class Type> class dynamicIndexedOctree;

	/*---------------------------------------------------------------------------*\
							   Class dynamicTreeDataPoint Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicTreeDataPoint
	{
		// Private Data

		const DynamicList<point>& points_;

	public:

		// Declare name of the class and its debug switch
		//ClassName("dynamicTreeDataPoint");
		static const char* typeName_() { return "dynamicTreeDataPoint"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct from List. Holds reference!
		FoamBase_EXPORT dynamicTreeDataPoint(const DynamicList<point>& points);


		// Member Functions

			// Access

		inline label size() const
		{
			return points_.size();
		}

		//- Get representative point cloud for all shapes inside
		//  (one point per shape)
		FoamBase_EXPORT const DynamicList<point>& shapePoints() const;


		// Search

			//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
			//  Only makes sense for closed surfaces.
		FoamBase_EXPORT volumeType getVolumeType
		(
			const dynamicIndexedOctree<dynamicTreeDataPoint>&,
			const point&
		) const;

		//- Does (bb of) shape at index overlap bb
		FoamBase_EXPORT bool overlaps
		(
			const label index,
			const treeBoundBox& sampleBb
		) const;

		//- Check if any point on shape is inside sphere.
		FoamBase_EXPORT bool overlaps
		(
			const label index,
			const point& centre,
			const scalar radiusSqr
		) const;

		//- Calculates nearest (to sample) point in shape.
		//  Returns actual point and distance (squared)
		FoamBase_EXPORT void findNearest
		(
			const labelUList& indices,
			const point& sample,

			scalar& nearestDistSqr,
			label& nearestIndex,
			point& nearestPoint
		) const;

		//- Calculates nearest (to line) point in shape.
		//  Returns point and distance (squared)
		FoamBase_EXPORT void findNearest
		(
			const labelUList& indices,
			const linePointRef& ln,

			treeBoundBox& tightest,
			label& minIndex,
			point& linePoint,
			point& nearestPoint
		) const;

		//- Calculate intersection of shape with ray. Sets result
		//  accordingly
		bool intersects
		(
			const label index,
			const point& start,
			const point& end,
			point& result
		) const
		{
			NotImplemented;
			return false;
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicTreeDataPoint_Header
