#pragma once
#ifndef _edgeIntersections_Header
#define _edgeIntersections_Header

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
	tnbLib::edgeIntersections

Description
	Holder of intersections of edges of a surface with another surface.
	Optionally shuffles around points on surface to resolve any 'conflicts'
	(edge hitting triangle edge, edge hitting point etc.).

SourceFiles
	edgeIntersections.C

\*---------------------------------------------------------------------------*/

#include <pointIndexHit.hxx>
#include <scalarField.hxx>
#include <pointField.hxx>
#include <typeInfo.hxx>
#include <boolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurface;
	class triSurfaceSearch;
	class Random;
	class edge;

	/*---------------------------------------------------------------------------*\
							   Class edgeIntersections Declaration
	\*---------------------------------------------------------------------------*/

	class edgeIntersections
		:
		public List<List<pointIndexHit>>
	{
		// Private Data

			//- For every entry in *this gives the edge classification result.
			//  -1 : intersection not close to edge
			//   0 : intersection close to e[0]
			//   1 : intersection close to e[1]
			//   2 : edge aligned with intersection face
		labelListList classification_;


		// Private Member Functions

			//- Check for too small edges
		static FoamFvMesh_EXPORT void checkEdges(const triSurface& surf);

		//- Intersect selected surface edges (edgeLabels) with surface2.
		//  Updates *this with pointHits and classification_ with status
		//  of hitPoint compared to edge end points.
		FoamFvMesh_EXPORT void intersectEdges
		(
			const triSurface& surf1,
			const pointField& points1,          // surf1 meshPoints
			const triSurfaceSearch& querySurf2,
			const scalarField& surf1PointTol,   // surf1 tolerance per point
			const labelList& edgeLabels
		);

		//- Perturb endpoints of edge if they are close to the intersection.
		//  Move point (in points1) by factor*surf1PointTol in direction of
		//  edge. Mark pointEdges of moved point in affectedEdges.
		//  Return true if anything changed.
		FoamFvMesh_EXPORT bool inlinePerturb
		(
			const triSurface& surf1,
			const scalarField& surf1PointTol,
			const label edgeI,
			Random& rndGen,
			pointField& points1,
			boolList& affectedEdges
		) const;

		//- Perturb single endpoint of edge if edge is algigned with face.
		//  See inlinePerturb. Return true if anything changed.
		FoamFvMesh_EXPORT bool rotatePerturb
		(
			const triSurface& surf1,
			const scalarField& surf1PointTol,
			const label edgeI,
			Random& rndGen,
			pointField& points1,
			boolList& affectedEdges
		) const;


		//- Perturb edge by shifting in direction trianglecentre - intersection
		//  when hits close to face. Update points, mark affected edges and
		//  return true if anything changed.
		FoamFvMesh_EXPORT bool offsetPerturb
		(
			const triSurface& surf1,
			const triSurface& surf2,
			const label edgeI,

			Random& rndGen,
			pointField& points1,
			boolList& affectedEdges
		) const;


	public:

		/*ClassName("edgeIntersections");*/
		static const char* typeName_() { return "edgeIntersections"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Static Data Members

			//- Cosine between edge and face normal when considered parallel
			//  (note: should be private and make access- and set- function)
		static FoamFvMesh_EXPORT scalar alignedCos_;


		// Static Functions

			//- Calculate min edge length for every surface point
		static FoamFvMesh_EXPORT scalarField minEdgeLength(const triSurface& surf);


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT edgeIntersections();

		//- Construct from surface and tolerance
		FoamFvMesh_EXPORT edgeIntersections
		(
			const triSurface& surf1,
			const triSurfaceSearch& query2,
			const scalarField& surf1PointTol
		);

		//- Construct from components
		FoamFvMesh_EXPORT edgeIntersections
		(
			const List<List<pointIndexHit>>&,
			const labelListList&
		);


		// Member Functions


			// Access

				//- For every intersection the classification status.
		const labelListList& classification() const
		{
			return classification_;
		}


		// Edit

			//- Resolve ties. Shuffles points so all edge - face intersections
			//  will be on the face interior.
			//  Points will be the new surface points.
			//  Returns number of iterations needed. (= nIters if still
			//  has degenerate cuts)
		FoamFvMesh_EXPORT label removeDegenerates
		(
			const label nIters,
			const triSurface& surf1,
			const triSurfaceSearch& query2,
			const scalarField& surf1PointTol,
			pointField& points1
		);

		//- Merge (or override) edge intersection for a subset
		//  (given as edge map and face map - for face indices stored in
		//  pointIndexHit.index())
		FoamFvMesh_EXPORT void merge
		(
			const edgeIntersections&,
			const labelList& edgeMap,
			const labelList& faceMap,
			const bool merge = true
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_edgeIntersections_Header
