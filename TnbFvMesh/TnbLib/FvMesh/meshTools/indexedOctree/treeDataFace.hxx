#pragma once
#ifndef _treeDataFace_Header
#define _treeDataFace_Header

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
	tnbLib::treeDataFace

Description
	Encapsulation of data needed to search for faces.

SourceFiles
	treeDataFace.C

\*---------------------------------------------------------------------------*/

#include <face.hxx>
#include <indexedOctree.hxx>
#include <treeBoundBoxList.hxx>
#include <PackedBoolList.hxx>
#include <primitiveMesh.hxx>
#include <volumeType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	//class primitiveMesh;
	//template<class Type> class indexedOctree;
	class polyPatch;

	/*---------------------------------------------------------------------------*\
							Class treeDataFace Declaration
	\*---------------------------------------------------------------------------*/

	class treeDataFace
	{
		// Static data

			//- Tolerance on linear dimensions
		static FoamFvMesh_EXPORT scalar tolSqr;



		// Private Data

		const primitiveMesh& mesh_;

		//- Subset of faces to work on
		const labelList faceLabels_;

		//- Inverse of faceLabels. For every mesh whether face is in faceLabels.
		PackedBoolList isTreeFace_;

		//- Whether to precalculate and store face bounding box
		const bool cacheBb_;

		//- Face bounding boxes (valid only if cacheBb_)
		treeBoundBoxList bbs_;


		// Private Member Functions

			//- Calculate face bounding box
		FoamFvMesh_EXPORT treeBoundBox calcBb(const label celli) const;

		//- Initialise all member data
		FoamFvMesh_EXPORT void update();

	public:


		class findNearestOp
		{
			const indexedOctree<treeDataFace>& tree_;

		public:

			FoamFvMesh_EXPORT findNearestOp(const indexedOctree<treeDataFace>& tree);

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
			const indexedOctree<treeDataFace>& tree_;

		public:

			FoamFvMesh_EXPORT findIntersectOp(const indexedOctree<treeDataFace>& tree);

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
		/*ClassName("treeDataFace");*/
		static const char* typeName_() { return "treeDataFace"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct from mesh and subset of faces.
		FoamFvMesh_EXPORT treeDataFace
		(
			const bool cacheBb,
			const primitiveMesh&,
			const labelUList&
		);

		//- Construct from mesh and subset of faces, transferring contents
		FoamFvMesh_EXPORT treeDataFace
		(
			const bool cacheBb,
			const primitiveMesh&,
			labelList&&
		);

		//- Construct from mesh. Uses all faces in mesh.
		FoamFvMesh_EXPORT treeDataFace(const bool cacheBb, const primitiveMesh&);

		//- Construct from mesh. Uses all faces in patch.
		FoamFvMesh_EXPORT treeDataFace(const bool cacheBb, const polyPatch&);


		// Member Functions

			// Access

		inline const labelList& faceLabels() const
		{
			return faceLabels_;
		}

		inline const primitiveMesh& mesh() const
		{
			return mesh_;
		}

		inline label size() const
		{
			return faceLabels_.size();
		}

		//- Get representative point cloud for all shapes inside
		//  (one point per shape)
		FoamFvMesh_EXPORT pointField shapePoints() const;


		// Search

			//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
			//  Only makes sense for closed surfaces.
		FoamFvMesh_EXPORT volumeType getVolumeType
		(
			const indexedOctree<treeDataFace>&,
			const point&
		) const;

		//- Does (bb of) shape at index overlap bb
		FoamFvMesh_EXPORT bool overlaps
		(
			const label index,
			const treeBoundBox& sampleBb
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_treeDataFace_Header
