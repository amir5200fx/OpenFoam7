#pragma once
#ifndef _treeDataEdge_Header
#define _treeDataEdge_Header

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
	tnbLib::treeDataEdge

Description
	Holds data for octree to work on an edges subset.

SourceFiles
	treeDataEdge.C

\*---------------------------------------------------------------------------*/

#include <treeBoundBoxList.hxx>
#include <linePointRef.hxx>
#include <volumeType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	template<class Type> class indexedOctree;

	/*---------------------------------------------------------------------------*\
							   Class treeDataEdge Declaration
	\*---------------------------------------------------------------------------*/

	class treeDataEdge
	{
		// Static data

			//- Tolerance on linear dimensions
		static FoamFvMesh_EXPORT scalar tol;


		// Private Data

			//- Reference to edgeList
		const edgeList& edges_;

		//- Reference to points
		const pointField& points_;

		//- Labels of edges
		const labelList edgeLabels_;

		//- Whether to precalculate and store face bounding box
		const bool cacheBb_;

		//- Bbs for all above edges (valid only if cacheBb_)
		treeBoundBoxList bbs_;


		// Private Member Functions

			//- Calculate edge bounding box
		FoamFvMesh_EXPORT treeBoundBox calcBb(const label edgeI) const;

		//- Initialise all member data
		FoamFvMesh_EXPORT void update();

	public:


		class findNearestOp
		{
			const indexedOctree<treeDataEdge>& tree_;

		public:

			FoamFvMesh_EXPORT findNearestOp(const indexedOctree<treeDataEdge>& tree);

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

			FoamFvMesh_EXPORT findIntersectOp(const indexedOctree<treeDataEdge>& tree);

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
		/*ClassName("treeDataEdge");*/
		static const char* typeName_() { return "treeDataEdge"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct from selected edges. !Holds references to edges and points
		FoamFvMesh_EXPORT treeDataEdge
		(
			const bool cacheBb,
			const edgeList& edges,
			const pointField& points,
			const labelUList& edgeLabels
		);

		//- Construct from selected edges, transferring contents.
		// !Holds references to edges and points
		FoamFvMesh_EXPORT treeDataEdge
		(
			const bool cacheBb,
			const edgeList& edges,
			const pointField& points,
			labelList&& edgeLabels
		);


		// Member Functions

			// Access

		const edgeList& edges() const
		{
			return edges_;
		}

		const pointField& points() const
		{
			return points_;
		}

		const labelList& edgeLabels() const
		{
			return edgeLabels_;
		}

		label size() const
		{
			return edgeLabels_.size();
		}

		//- Get representative point cloud for all shapes inside
		//  (one point per shape)
		FoamFvMesh_EXPORT pointField shapePoints() const;


		// Search

			//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
			//  Only makes sense for closed surfaces.
		FoamFvMesh_EXPORT volumeType getVolumeType
		(
			const indexedOctree<treeDataEdge>&,
			const point&
		) const;

		//- Does (bb of) shape at index overlap bb
		FoamFvMesh_EXPORT bool overlaps
		(
			const label index,
			const treeBoundBox& sampleBb
		) const;

		//- Does (bb of) shape at index overlap bb
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

#endif // !_treeDataEdge_Header
