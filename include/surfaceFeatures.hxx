#pragma once
#ifndef _surfaceFeatures_Header
#define _surfaceFeatures_Header

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
	tnbLib::surfaceFeatures

Description
	Holds feature edges/points of surface.

	Feature edges are stored in one list and sorted:
		0 .. externalStart_-1               : region edges
		externalStart_ .. internalStart_-1  : external edges
		internalStart_ .. size-1            : internal edges

	NOTE: angle is included angle, not feature angle and is in degrees.
	The included angle is the smallest angle between two planes. For coplanar
	faces it is 180, for straight angles it is 90. To pick up straight edges
	only use included angle of 91 degrees

SourceFiles
	surfaceFeatures.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <Map.hxx>
#include <HashSet.hxx>
#include <pointIndexHit.hxx>
#include <edgeList.hxx>
#include <typeInfo.hxx>
#include <boundBox.hxx>
#include <plane.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurface;

	/*---------------------------------------------------------------------------*\
							   Class surfaceFeatures Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceFeatures
	{
	public:

		enum edgeStatus
		{
			NONE,
			REGION,
			EXTERNAL,
			INTERNAL
		};


	private:

		//- Label and scalar; used in path walking
		class labelScalar
		{
		public:
			label n_;
			scalar len_;

			labelScalar(const label n, const scalar len)
				:
				n_(n),
				len_(len)
			{}
		};

		// Static data

			//- Tolerance for determining whether two vectors are parallel
		static FoamFvMesh_EXPORT const scalar parallelTolerance;


		// Private Data

			//- Reference to surface
		const triSurface& surf_;

		//- Labels of points that are features
		labelList featurePoints_;

		//- Labels of edges that are features
		labelList featureEdges_;

		//- Start of external edges in featureEdges_
		label externalStart_;

		//- Start of internal edges in featureEdges_
		label internalStart_;


		// Private Member Functions

			//- Return nearest point on edge (start..end). Also classify nearest:
			//  index=-1: nearest on mid of edge. index=0:nearest on edge.start()
			//  index=1: nearest on edge.end().
		static FoamFvMesh_EXPORT pointIndexHit edgeNearest
		(
			const point& start,
			const point& end,
			const point& sample
		);


		//- Construct feature points where more than 2 feature edges meet
		FoamFvMesh_EXPORT void calcFeatPoints
		(
			const List<edgeStatus>& edgeStat,
			const scalar minCos
		);

		//- Classify the angles of the feature edges
		FoamFvMesh_EXPORT void classifyFeatureAngles
		(
			const labelListList& edgeFaces,
			List<edgeStatus>& edgeStat,
			const scalar minCos,
			const bool geometricTestOnly
		) const;

		//- Choose next unset feature edge.
		FoamFvMesh_EXPORT label nextFeatEdge
		(
			const List<edgeStatus>& edgeStat,
			const labelList& featVisited,
			const label unsetVal,
			const label prevEdgeI,
			const label vertI
		) const;

		//- Walk connected feature edges. Marks edges in featVisited.
		FoamFvMesh_EXPORT labelScalar walkSegment
		(
			const bool mark,
			const List<edgeStatus>& edgeStat,
			const label startEdgeI,
			const label startPointi,
			const label currentFeatI,
			labelList& featVisited
		);

	public:

		/*ClassName("surfaceFeatures");*/
		static const char* typeName_() { return "surfaceFeatures"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;

		// Constructors

			//- Construct from surface
		FoamFvMesh_EXPORT surfaceFeatures(const triSurface&);

		//- Construct from components
		FoamFvMesh_EXPORT surfaceFeatures
		(
			const triSurface&,
			const labelList& featurePoints,
			const labelList& featureEdges,
			const label externalStart,
			const label internalStart
		);

		//- Construct from surface, angle and min cumulative length and/or
		//  number of elements. If geometric test only is true, then region
		//  information is ignored and features are only assigned based on the
		//  geometric criteria
		FoamFvMesh_EXPORT surfaceFeatures
		(
			const triSurface&,
			const scalar includedAngle,
			const scalar minLen = 0,
			const label minElems = 0,
			const bool geometricTestOnly = false
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT surfaceFeatures(const triSurface&, const dictionary& dict);

		//- Construct from file
		FoamFvMesh_EXPORT surfaceFeatures(const triSurface&, const fileName& fName);

		//- Construct from pointField and edgeList (edgeMesh)
		FoamFvMesh_EXPORT surfaceFeatures
		(
			const triSurface&,
			const pointField& points,
			const edgeList& edges,
			const scalar mergeTol = 1e-6,
			const bool geometricTestOnly = false
		);

		//- Copy constructor
		FoamFvMesh_EXPORT surfaceFeatures(const surfaceFeatures&);


		// Member Functions

			// Access

		inline const triSurface& surface() const
		{
			return surf_;
		}

		//- Return feature point list
		inline const labelList& featurePoints() const
		{
			return featurePoints_;
		}

		//- Return feature edge list
		inline const labelList& featureEdges() const
		{
			return featureEdges_;
		}

		//- Start of external edges
		inline label externalStart() const
		{
			return externalStart_;
		}

		//- Start of internal edges
		inline label internalStart() const
		{
			return internalStart_;
		}

		//- Return number of region edges
		inline label nRegionEdges() const
		{
			return externalStart_;
		}

		//- Return number of external edges
		inline label nExternalEdges() const
		{
			return internalStart_ - externalStart_;
		}

		//- Return number of internal edges
		inline label nInternalEdges() const
		{
			return featureEdges_.size() - internalStart_;
		}

		//- Helper function: select a subset of featureEdges_
		FoamFvMesh_EXPORT labelList selectFeatureEdges
		(
			const bool regionEdges,
			const bool externalEdges,
			const bool internalEdges
		) const;


		// Edit

			//- Find feature edges using provided included angle
		FoamFvMesh_EXPORT void findFeatures
		(
			const scalar includedAngle,
			const bool geometricTestOnly
		);

		//- Delete small sets of edges. Edges are stringed up and any
		//  string of length < minLen (or nElems < minElems) is deleted.
		FoamFvMesh_EXPORT labelList trimFeatures
		(
			const scalar minLen,
			const label minElems,
			const scalar includedAngle
		);

		//- From member feature edges to status per edge.
		FoamFvMesh_EXPORT List<edgeStatus> toStatus() const;

		//- Set from status per edge
		FoamFvMesh_EXPORT void setFromStatus
		(
			const List<edgeStatus>& edgeStat,
			const scalar includedAngle
		);


		// Find

			//- Find nearest sample for selected surface points
			//  (usually the set of featurePoints). Return map from
			//  index in samples to surface point. Do not include
			//  points that are further than maxDist away (separate
			//  maxDist for every sample).  Supply maxDistSqr.
		FoamFvMesh_EXPORT Map<label> nearestSamples
		(
			const labelList& selectedPoints,
			const pointField& samples,
			const scalarField& maxDistSqr
		) const;

		//- Find nearest sample for regularly sampled points along
		//  the selected (surface) edges. Return map from sample
		//  to edge.  maxDistSqr is distance squared below which
		//  gets snapped.  Edge gets sampled at points
		//  sampleDist[sampleI] apart.  (with a maximum of 10
		//  samples per edge)
		FoamFvMesh_EXPORT Map<label> nearestSamples
		(
			const labelList& selectedEdges,
			const pointField& samples,
			const scalarField& sampleDist,
			const scalarField& maxDistSqr,
			const scalar minSampleDist = 0.1
		) const;

		//- Like nearestSamples but now gets nearest point on
		//  sample-edge instead of nearest sample-point itself.
		//  Return map from sample edge to feature edge.
		FoamFvMesh_EXPORT Map<pointIndexHit> nearestEdges
		(
			const labelList& selectedEdges,
			const edgeList& sampleEdges,
			const labelList& selectedSampleEdges,
			const pointField& samplePoints,
			const scalarField& sampleDist,
			const scalarField& maxDistSqr,
			const scalar minSampleDist = 0.1
		) const;


		//- Find nearest surface edge (out of selectedEdges) for
		//  each sample point.
		//  Sets:
		//  - edgeLabel : label of surface edge.
		//  - edgePoint : exact position of nearest point on edge.
		//  - edgeEndPoint : -1, 0, 1 depending on whether edgePoint is
		//                  on inside/start/end of edge
		FoamFvMesh_EXPORT void nearestSurfEdge
		(
			const labelList& selectedEdges,
			const pointField& samples,
			scalar searchSpanSqr,   // search span
			labelList& edgeLabel,
			labelList& edgeEndPoint,
			pointField& edgePoint
		) const;

		//- Find nearest surface edge (out of selectedEdges) for each
		//  sample edge.
		//  Sets:
		//  - edgeLabel         : label of surface edge.
		//  - pointOnEdge       : exact position of nearest point on edge.
		//  - pointOnFeature    : exact position on sample edge.
		FoamFvMesh_EXPORT void nearestSurfEdge
		(
			const labelList& selectedEdges,
			const edgeList& sampleEdges,
			const labelList& selectedSampleEdges,
			const pointField& samplePoints,
			const vector& searchSpan,   // search span

			labelList& edgeLabel,       // label of surface edge or -1
			pointField& pointOnEdge,    // point on above edge
			pointField& pointOnFeature  // point on sample edge
		) const;

		//- Find nearest feature edge to each surface edge. Uses the
		//  mid-point of the surface edges.
		FoamFvMesh_EXPORT void nearestFeatEdge
		(
			const edgeList& edges,
			const pointField& points,
			scalar searchSpanSqr,
			labelList& edgeLabel
		) const;


		// Write

			//- Write as dictionary
		FoamFvMesh_EXPORT void writeDict(Ostream&) const;

		//- Write as dictionary to file
		FoamFvMesh_EXPORT void write(const fileName& fName) const;

		//- Write to separate OBJ files (region, external, internal edges,
		//  feature points) for visualization
		FoamFvMesh_EXPORT void writeObj(const fileName& prefix) const;



		// Member Operators

		FoamFvMesh_EXPORT void operator=(const surfaceFeatures&);
	};


	//- Select edges inside or outside bounding box
	FoamFvMesh_EXPORT void selectBox
	(
		const triSurface& surf,
		const boundBox& bb,
		const bool removeInside,
		List<surfaceFeatures::edgeStatus>& edgeStat
	);

	//- Select edges that are intersected by the given plane
	FoamFvMesh_EXPORT void selectCutEdges
	(
		const triSurface& surf,
		const plane& cutPlane,
		List<surfaceFeatures::edgeStatus>& edgeStat
	);

	//- Divide into multiple normal bins
	//  - return REGION if != 2 normals
	//  - return REGION if 2 normals that make feature angle
	//  - otherwise return NONE and set normals,bins
	FoamFvMesh_EXPORT surfaceFeatures::edgeStatus checkNonManifoldEdge
	(
		const triSurface& surf,
		const scalar tol,
		const scalar includedAngle,
		const label edgei
	);

	//- Select manifold edges
	FoamFvMesh_EXPORT void selectManifoldEdges
	(
		const triSurface& surf,
		const scalar tol,
		const scalar includedAngle,
		List<surfaceFeatures::edgeStatus>& edgeStat
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceFeatures_Header
