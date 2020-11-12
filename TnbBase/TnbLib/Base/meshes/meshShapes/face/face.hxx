#pragma once
#ifndef _face_Header
#define _face_Header

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
	tnbLib::face

Description
	A face is a list of labels corresponding to mesh vertices.

See also
	tnbLib::triFace

SourceFiles
	faceI.H
	face.C
	faceIntersection.C
	faceContactSphere.C
	faceAreaInContact.C
	faceTemplates.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <labelList.hxx>
#include <edgeList.hxx>
#include <vectorField.hxx>
#include <faceListFwd.hxx>
#include <intersection.hxx>
#include <pointHit.hxx>
#include <ListListOps.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class face;
	class triFace;

	template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
	class DynamicList;

	inline bool operator==(const face& a, const face& b);
	inline bool operator!=(const face& a, const face& b);
	inline Istream& operator>>(Istream&, face&);

	/*---------------------------------------------------------------------------*\
							   Class face Declaration
	\*---------------------------------------------------------------------------*/

	class face
		:
		public labelList
	{
		// Private Member Functions

			//- Edge to the right of face vertex i
		inline label right(const label i) const;

		//- Edge to the left of face vertex i
		inline label left(const label i) const;

		//- Construct list of edge vectors for face
		FoamBase_EXPORT tmp<vectorField> calcEdges
		(
			const pointField& points
		) const;

		//- Cos between neighbouring edges
		FoamBase_EXPORT scalar edgeCos
		(
			const vectorField& edges,
			const label index
		) const;

		//- Find index of largest internal angle on face
		FoamBase_EXPORT label mostConcaveAngle
		(
			const pointField& points,
			const vectorField& edges,
			scalar& edgeCos
		) const;

		//- Enumeration listing the modes for split()
		enum splitMode
		{
			COUNTTRIANGLE,  // count if split into triangles
			COUNTQUAD,      // count if split into triangles&quads
			SPLITTRIANGLE,  // split into triangles
			SPLITQUAD       // split into triangles&quads
		};

		//- Split face into triangles or triangles&quads.
		//  Stores results quadFaces[quadI], triFaces[triI]
		//  Returns number of new faces created
		FoamBase_EXPORT label split
		(
			const splitMode mode,
			const pointField& points,
			label& triI,
			label& quadI,
			faceList& triFaces,
			faceList& quadFaces
		) const;


	public:

		//- Return types for classify
		enum proxType
		{
			NONE,
			POINT,  // Close to point
			EDGE    // Close to edge
		};

		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;


		// Constructors

			//- Construct null
		inline face();

		//- Construct given size
		explicit inline face(label);

		//- Construct from list of labels
		explicit inline face(const labelUList&);

		//- Construct from list of labels
		explicit inline face(const labelList&);

		//- Construct by transferring the parameter contents
		explicit inline face(labelList&&);

		//- Copy construct from triFace
		FoamBase_EXPORT face(const triFace&);

		//- Construct from Istream
		inline face(Istream&);


		// Member Functions

			//- Collapse face by removing duplicate point labels
			//  return the collapsed size
		FoamBase_EXPORT label collapse();

		//- Flip the face in-place.
		//  The starting points of the original and flipped face are identical.
		FoamBase_EXPORT void flip();

		//- Return the points corresponding to this face
		inline pointField points(const pointField&) const;

		//- Centre point of face
		FoamBase_EXPORT point centre(const pointField&) const;

		//- Calculate average value at centroid of face
		template<class Type>
		Type average(const pointField&, const Field<Type>&) const;

		//- Return vector area
		FoamBase_EXPORT vector area(const pointField&) const;

		//- Return scalar magnitude
		inline scalar mag(const pointField&) const;

		//- Return unit normal
		FoamBase_EXPORT vector normal(const pointField&) const;

		//- Return face with reverse direction
		//  The starting points of the original and reverse face are identical.
		FoamBase_EXPORT face reverseFace() const;

		//- Navigation through face vertices

			//- Which vertex on face (face index given a global index)
			//  returns -1 if not found
		FoamBase_EXPORT label which(const label globalIndex) const;

		//- Next vertex on face
		inline label nextLabel(const label i) const;

		//- Previous vertex on face
		inline label prevLabel(const label i) const;


		//- Return the volume swept out by the face when its points move
		FoamBase_EXPORT scalar sweptVol
		(
			const pointField& oldPoints,
			const pointField& newPoints
		) const;

		//- Return the inertia tensor, with optional reference
		//  point and density specification
		FoamBase_EXPORT tensor inertia
		(
			const pointField&,
			const point& refPt = vector::zero,
			scalar density = 1.0
		) const;

		//- Return potential intersection with face with a ray starting
		//  at p, direction n (does not need to be normalized)
		//  Does face-centre decomposition and returns triangle intersection
		//  point closest to p. Face-centre is calculated from point average.
		//  For a hit, the distance is signed.  Positive number
		//  represents the point in front of triangle
		//  In case of miss the point is the nearest point on the face
		//  and the distance is the distance between the intersection point
		//  and the original point.
		//  The half-ray or full-ray intersection and the contact
		//  sphere adjustment of the projection vector is set by the
		//  intersection parameters
		FoamBase_EXPORT pointHit ray
		(
			const point& p,
			const vector& n,
			const pointField&,
			const intersection::algorithm alg =
			intersection::algorithm::fullRay,
			const intersection::direction dir =
			intersection::direction::vector
		) const;

		//- Fast intersection with a ray.
		//  Does face-centre decomposition and returns triangle intersection
		//  point closest to p. See triangle::intersection for details.
		FoamBase_EXPORT pointHit intersection
		(
			const point& p,
			const vector& q,
			const point& ctr,
			const pointField&,
			const intersection::algorithm alg,
			const scalar tol = 0.0
		) const;

		//- Return nearest point to face
		FoamBase_EXPORT pointHit nearestPoint
		(
			const point& p,
			const pointField&
		) const;

		//- Return nearest point to face and classify it:
		//  + near point (nearType=POINT, nearLabel=0, 1, 2)
		//  + near edge (nearType=EDGE, nearLabel=0, 1, 2)
		//    Note: edges are counted from starting vertex so
		//    e.g. edge n is from f[n] to f[0], where the face has n + 1
		//    points
		FoamBase_EXPORT pointHit nearestPointClassify
		(
			const point& p,
			const pointField&,
			label& nearType,
			label& nearLabel
		) const;

		//- Return contact sphere diameter
		FoamBase_EXPORT scalar contactSphereDiameter
		(
			const point& p,
			const vector& n,
			const pointField&
		) const;

		//- Return area in contact, given the displacement in vertices
		FoamBase_EXPORT scalar areaInContact
		(
			const pointField&,
			const scalarField& v
		) const;

		//- Return number of edges
		inline label nEdges() const;

		//- Return edges in face point ordering,
		//  i.e. edges()[0] is edge between [0] and [1]
		FoamBase_EXPORT edgeList edges() const;

		//- Return n-th face edge
		inline edge faceEdge(const label n) const;

		//- Return the edge direction on the face
		//  Returns:
		//  -  0: edge not found on the face
		//  - +1: forward (counter-clockwise) on the face
		//  - -1: reverse (clockwise) on the face
		FoamBase_EXPORT int edgeDirection(const edge&) const;

		// Face splitting utilities

			//- Number of triangles after splitting
		inline label nTriangles() const;

		//- Number of triangles after splitting
		FoamBase_EXPORT label nTriangles(const pointField& points) const;

		//- Split into triangles using existing points.
		//  Result in triFaces[triI..triI+nTri].
		//  Splits intelligently to maximize triangle quality.
		//  Returns number of faces created.
		FoamBase_EXPORT label triangles
		(
			const pointField& points,
			label& triI,
			faceList& triFaces
		) const;

		//- Split into triangles using existing points.
		//  Append to DynamicList.
		//  Returns number of faces created.
		template<unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
		label triangles
		(
			const pointField& points,
			DynamicList<face, SizeInc, SizeMult, SizeDiv>& triFaces
		) const;

		//- Number of triangles and quads after splitting
		//  Returns the sum of both
		FoamBase_EXPORT label nTrianglesQuads
		(
			const pointField& points,
			label& nTris,
			label& nQuads
		) const;

		//- Split into triangles and quads.
		//  Results in triFaces (starting at triI) and quadFaces
		//  (starting at quadI).
		//  Returns number of new faces created.
		FoamBase_EXPORT label trianglesQuads
		(
			const pointField& points,
			label& triI,
			label& quadI,
			faceList& triFaces,
			faceList& quadFaces
		) const;

		//- Compare faces
		//   0: different
		//  +1: identical
		//  -1: same face, but different orientation
		static FoamBase_EXPORT int compare(const face&, const face&);

		//- Return true if the faces have the same vertices
		static FoamBase_EXPORT bool sameVertices(const face&, const face&);


		// Member Operators

			//- Move assignment labelList
		inline void operator=(labelList&&);


		// Friend Operators

		friend bool operator==(const face& a, const face& b);
		friend bool operator!=(const face& a, const face& b);


		// Istream Operator

		friend Istream& operator>>(Istream&, face&);
	};


	//- Hash specialization to offset faces in ListListOps::combineOffset
	template<>
	class offsetOp<face>
	{

	public:

		inline face operator()
			(
				const face& x,
				const label offset
				) const
		{
			face result(x.size());

			forAll(x, xI)
			{
				result[xI] = x[xI] + offset;
			}
			return result;
		}
	};


	// Global functions

	//- Find the longest edge on a face. Face point labels index into pts.
	FoamBase_EXPORT label longestEdge(const face& f, const pointField& pts);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <faceI.hxx>
#include <faceTemplatesI.hxx>

//#ifdef NoRepository
//#include <faceTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_face_Header
