#pragma once
#ifndef _distributedTriSurfaceMesh_Header
#define _distributedTriSurfaceMesh_Header

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
	tnbLib::distributedTriSurfaceMesh

Description
	IOoject and searching on distributed triSurface. All processor hold
	(possibly overlapping) part of the overall surface. All queries are
	distributed to the processor that can answer it and the result sent back.

	Can work in three modes:
	- follow : makes sure each processor has all the triangles inside the
	externally provided bounding box (usually the mesh bounding box).
	Guarantees minimum amount of communication since mesh-local queries
	should be answerable without any comms.
	- independent : surface is decomposed according to the triangle centres
	so the decomposition might be radically different from the mesh
	decomposition. Guarantees best memory balance but at the expense of
	more communication.
	- frozen : no change

SourceFiles
	distributedTriSurfaceMesh.C

\*---------------------------------------------------------------------------*/

#include <triSurfaceMesh.hxx>
#include <IOdictionary.hxx>
#include <Pair.hxx>
#include <globalIndex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapDistribute;
	class decompositionMethod;

	// Typedefs
	typedef Pair<point> segment;
	template<>
	inline bool contiguous<segment>() { return contiguous<point>(); }


	/*---------------------------------------------------------------------------*\
					   Class distributedTriSurfaceMesh Declaration
	\*---------------------------------------------------------------------------*/

	class distributedTriSurfaceMesh
		:
		public triSurfaceMesh
	{
	public:

		// Static data

		enum distributionType
		{
			FOLLOW = 0,
			INDEPENDENT = 1,
			FROZEN = 2
		};

		static FoamParallel_EXPORT const NamedEnum<distributionType, 3> distributionTypeNames_;


	private:

		// Private Data

			//- Merging distance
		scalar mergeDist_;

		//- Decomposition used when independently decomposing surface.
		autoPtr<decompositionMethod> decomposer_;

		//- Bounding box settings
		IOdictionary dict_;

		//- Bounding boxes of all processors
		List<List<treeBoundBox>> procBb_;

		//- Global triangle numbering
		mutable autoPtr<globalIndex> globalTris_;

		//- The distribution type.
		distributionType distType_;


		// Private Member Functions

			// Read

				//- Read my additional data
		FoamParallel_EXPORT bool read();


		// Line intersection

		static FoamParallel_EXPORT bool isLocal
		(
			const List<treeBoundBox>& myBbs,
			const point& start,
			const point& end
		);

		//- Split segment into subsegments overlapping the processor
		//  bounding box.
		// void tnbLib::distributedTriSurfaceMesh::splitSegment
		//(
		//    const label segmentI,
		//    const point& start,
		//    const point& end,
		//    const treeBoundBox& bb,
		//
		//    DynamicList<segment>& allSegments,
		//    DynamicList<label>& allSegmentMap,
		//    DynamicList<label> sendMap
		//) const

		//- Distribute segments into overlapping processor
		//  bounding boxes. Sort per processor.
		FoamParallel_EXPORT void distributeSegment
		(
			const label,
			const point& start,
			const point& end,

			DynamicList<segment>&,
			DynamicList<label>&,
			List<DynamicList<label>>&
		) const;

		//- Divide edges into local and remote segments. Construct map to
		//  distribute and collect data.
		FoamParallel_EXPORT autoPtr<mapDistribute> distributeSegments
		(
			const pointField& start,
			const pointField& end,

			List<segment>& allSegments,
			List<label>& allSegmentMap
		) const;

		//- Split edges, distribute, test and collect.
		FoamParallel_EXPORT void findLine
		(
			const bool nearestIntersection,
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>& info
		) const;


		// Triangle index

			//- Obtains global indices from pointIndexHit and swaps them back
			//  to their original processor. Used to calculate local region
			//  and normal.
		FoamParallel_EXPORT autoPtr<mapDistribute> calcLocalQueries
		(
			const List<pointIndexHit>&,
			labelList& triangleIndex
		) const;


		// Nearest

		FoamParallel_EXPORT label calcOverlappingProcs
		(
			const point& centre,
			const scalar radiusSqr,
			boolList& overlaps
		) const;

		FoamParallel_EXPORT autoPtr<mapDistribute> calcLocalQueries
		(
			const pointField& centres,
			const scalarField& radiusSqr,

			pointField& allCentres,
			scalarField& allRadiusSqr,
			labelList& allSegmentMap
		) const;


		// Surface redistribution

			//- Finds new bounds based on an independent decomposition.
		FoamParallel_EXPORT List<List<treeBoundBox>> independentlyDistributedBbs
		(
			const triSurface&
		);

		//- Does any part of triangle overlap bb.
		static FoamParallel_EXPORT bool overlaps
		(
			const List<treeBoundBox>& bb,
			const point& p0,
			const point& p1,
			const point& p2
		);

		//- Find points used in subset
		static FoamParallel_EXPORT void subsetMeshMap
		(
			const triSurface& s,
			const boolList& include,
			const label nIncluded,
			labelList& newToOldPoints,
			labelList& oldToNewPoints,
			labelList& newToOldFaces
		);

		//- Construct subsetted surface
		static FoamParallel_EXPORT triSurface subsetMesh
		(
			const triSurface& s,
			const labelList& newToOldPoints,
			const labelList& oldToNewPoints,
			const labelList& newToOldFaces
		);

		//- Subset given marked faces
		static FoamParallel_EXPORT triSurface subsetMesh
		(
			const triSurface& s,
			const boolList& include,
			labelList& newToOldPoints,
			labelList& newToOldFaces
		);

		//- Subset given marked faces
		static FoamParallel_EXPORT triSurface subsetMesh
		(
			const triSurface& s,
			const labelList& newToOldFaces,
			labelList& newToOldPoints
		);

		//- Find triangle otherF in allFaces.
		static FoamParallel_EXPORT label findTriangle
		(
			const List<labelledTri>& allFaces,
			const labelListList& allPointFaces,
			const labelledTri& otherF
		);

		//- Merge triSurface (subTris, subPoints) into allTris, allPoints.
		static FoamParallel_EXPORT void merge
		(
			const scalar mergeDist,
			const List<labelledTri>& subTris,
			const pointField& subPoints,

			List<labelledTri>& allTris,
			pointField& allPoints,

			labelList& faceConstructMap,
			labelList& pointConstructMap
		);

		//- Distribute stored fields
		template<class Type>
		void distributeFields(const mapDistribute& map);


	public:

		//- Runtime type information
		//TypeName("distributedTriSurfaceMesh");
		static const char* typeName_() { return "distributedTriSurfaceMesh"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from triSurface
		FoamParallel_EXPORT distributedTriSurfaceMesh
		(
			const IOobject&,
			const triSurface&,
			const dictionary& dict
		);

		//- Construct read. Does findInstance to find io.local().
		FoamParallel_EXPORT distributedTriSurfaceMesh(const IOobject& io);

		//- Construct from dictionary (used by searchableSurface).
		//  Does read. Does findInstance to find io.local().
		FoamParallel_EXPORT distributedTriSurfaceMesh
		(
			const IOobject& io,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT distributedTriSurfaceMesh(const distributedTriSurfaceMesh&) = delete;


		//- Destructor
		FoamParallel_EXPORT virtual ~distributedTriSurfaceMesh();

		//- Clear storage
		FoamParallel_EXPORT void clearOut();


		// Member Functions

			//- Triangle indexing (demand driven)
		FoamParallel_EXPORT const globalIndex& globalTris() const;


		// searchableSurface implementation

			//- Whether supports volume type below. I.e. whether is closed.
			//  Not supported.
		virtual bool hasVolumeType() const
		{
			return false;
		}

		//- Range of global indices that can be returned.
		virtual label globalSize() const
		{
			return globalTris().size();
		}

		FoamParallel_EXPORT virtual void findNearest
		(
			const pointField& sample,
			const scalarField& nearestDistSqr,
			List<pointIndexHit>&
		) const;

		FoamParallel_EXPORT virtual void findLine
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const;

		FoamParallel_EXPORT virtual void findLineAny
		(
			const pointField& start,
			const pointField& end,
			List<pointIndexHit>&
		) const;

		//- Get all intersections in order from start to end.
		FoamParallel_EXPORT virtual void findLineAll
		(
			const pointField& start,
			const pointField& end,
			List<List<pointIndexHit>>&
		) const;

		//- From a set of points and indices get the region
		FoamParallel_EXPORT virtual void getRegion
		(
			const List<pointIndexHit>&,
			labelList& region
		) const;

		//- From a set of points and indices get the normal
		FoamParallel_EXPORT virtual void getNormal
		(
			const List<pointIndexHit>&,
			vectorField& normal
		) const;

		//- Determine type (inside/outside/mixed) for point. unknown if
		//  cannot be determined (e.g. non-manifold surface)
		FoamParallel_EXPORT virtual void getVolumeType
		(
			const pointField&,
			List<volumeType>&
		) const;

		//- Set bounds of surface. Bounds currently set as list of
		//  bounding boxes. Will do redistribution of surface to locally
		//  have all triangles overlapping bounds.
		//  Larger bounds: more triangles (memory), more fully local tests
		//  (quick).
		//  keepNonLocal = true : keep triangles that do not overlap
		//  any processor bounds.
		//  Should really be split into a routine to determine decomposition
		//  and one that does actual distribution but determining
		//  decomposition with duplicate triangle merging requires
		//  same amount as work as actual distribution.
		FoamParallel_EXPORT virtual void distribute
		(
			const List<treeBoundBox>&,
			const bool keepNonLocal,
			autoPtr<mapDistribute>& faceMap,
			autoPtr<mapDistribute>& pointMap
		);


		// Other

			//- WIP. From a set of hits (points and
			//  indices) get the specified field. Misses do not get set.
		FoamParallel_EXPORT virtual void getField(const List<pointIndexHit>&, labelList&) const;

		//- Subset the part of surface that is overlapping bounds.
		static FoamParallel_EXPORT triSurface overlappingSurface
		(
			const triSurface&,
			const List<treeBoundBox>&,
			labelList& subPointMap,
			labelList& subFaceMap
		);

		//- Print some stats. Parallel aware version of
		//  triSurface::writeStats.
		FoamParallel_EXPORT void writeStats(Ostream& os) const;


		// regIOobject implementation

			//- Write using given format, version and compression
			//  Do not use the triSurfaceMesh::writeObject since it
			//  would filter out empty regions. These need to be preserved
			//  in case we want to make decisions based on the number of
			//  regions.
		FoamParallel_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write = true
		) const;

		//- Is object global
		virtual bool global() const
		{
			return false;
		}

		//- Return complete path + object name if the file exists
		//  either in the case/processor or case otherwise null
		virtual fileName filePath() const
		{
			return searchableSurface::localFilePath(type());
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const distributedTriSurfaceMesh&) = delete;
	};


	//- Template function for obtaining global status
	template<>
	inline bool typeGlobal<distributedTriSurfaceMesh>()
	{
		return false;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <distributedTriSurfaceMeshI.hxx>

//#ifdef NoRepository
//#include <distributedTriSurfaceMeshTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_distributedTriSurfaceMesh_Header
