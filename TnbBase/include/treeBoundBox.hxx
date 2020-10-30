#pragma once
#ifndef _treeBoundBox_Header
#define _treeBoundBox_Header

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
	tnbLib::treeBoundBox

Description
	Standard boundBox + extra functionality for use in octree.

	Numbering of corner points is according to octant numbering.

	On the back plane (z=0):

	\verbatim
		Y
		^
		|
		+--------+
		|2      3|
		|        |
		|        |
		|        |
		|0      1|
		+--------+->X
	\endverbatim

	For the front plane add 4 to the point labels.


SourceFiles
	treeBoundBoxI.H
	treeBoundBox.C
	treeBoundBoxTemplates.C

\*---------------------------------------------------------------------------*/

#include <boundBox.hxx>
#include <direction.hxx>
#include <pointField.hxx>
#include <faceList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Random;


	// Forward declaration of friend functions and operators

	class treeBoundBox;

	FoamBase_EXPORT bool operator==(const treeBoundBox&, const treeBoundBox&);
	FoamBase_EXPORT bool operator!=(const treeBoundBox&, const treeBoundBox&);

	FoamBase_EXPORT Istream& operator>>(Istream& is, treeBoundBox&);
	FoamBase_EXPORT Ostream& operator<<(Ostream& os, const treeBoundBox&);


	/*---------------------------------------------------------------------------*\
							Class treeBoundBox Declaration
	\*---------------------------------------------------------------------------*/

	class treeBoundBox
		:
		public boundBox
	{
		//- To initialise edges.
		static FoamBase_EXPORT edgeList calcEdges(const label[12][2]);

		//- To initialise faceNormals.
		static FoamBase_EXPORT FixedList<vector, 6> calcFaceNormals();

	public:

		// Static Data Members

			//- The great value used for greatBox and invertedBox
		static FoamBase_EXPORT const scalar great;

		//- As per boundBox::greatBox, but with great instead of vGreat
		static FoamBase_EXPORT const treeBoundBox greatBox;

		//- As per boundBox::invertedBox, but with great instead of vGreat
		static FoamBase_EXPORT const treeBoundBox invertedBox;

		//- Bits used for octant/point coding.
		//  Every octant/corner point is the combination of three faces.
		struct octantBit
		{
			enum
			{
				rightHalf = 0x1 << 0,
				topHalf = 0x1 << 1,
				frontHalf = 0x1 << 2
			};
		};

		//- Face codes
		struct faceId
		{
			enum
			{
				left = 0,
				right = 1,
				bottom = 2,
				top = 3,
				back = 4,
				front = 5
			};
		};

		//- Bits used for face coding
		struct faceBit
		{
			enum
			{
				noFace = 0,
				left = 0x1 << faceId::left,    //1
				right = 0x1 << faceId::right,   //2
				bottom = 0x1 << faceId::bottom,  //4
				top = 0x1 << faceId::top,     //8
				back = 0x1 << faceId::back,    //16
				front = 0x1 << faceId::front,   //32
			};
		};

		//- Edges codes.
		//  e01 = edge between 0 and 1.
		struct edgeId
		{
			enum
			{
				e01 = 0,
				e13 = 1,
				e23 = 2,
				e02 = 3,

				e45 = 4,
				e57 = 5,
				e67 = 6,
				e46 = 7,

				e04 = 8,
				e15 = 9,
				e37 = 10,
				e26 = 11
			};
		};

		//- Face to point addressing
		static FoamBase_EXPORT const faceList faces;

		//- Edge to point addressing
		static FoamBase_EXPORT const edgeList edges;

		//- Per face the unit normal
		static FoamBase_EXPORT const FixedList<vector, 6> faceNormals;


		// Constructors

			//- Construct null setting points to zero
		inline treeBoundBox();

		//- Construct from a boundBox
		explicit inline treeBoundBox(const boundBox& bb);

		//- Construct from components
		inline treeBoundBox(const point& min, const point& max);

		//- Construct as the bounding box of the given pointField.
		//  Local processor domain only (no reduce as in boundBox)
		FoamBase_EXPORT explicit treeBoundBox(const UList<point>&);

		//- Construct as subset of points
		//  Local processor domain only (no reduce as in boundBox)
		FoamBase_EXPORT treeBoundBox(const UList<point>&, const labelUList& indices);

		//- Construct as subset of points
		//  The indices could be from edge/triFace etc.
		//  Local processor domain only (no reduce as in boundBox)
		template<unsigned Size>
		treeBoundBox
		(
			const UList<point>&,
			const FixedList<label, Size>& indices
		);


		//- Construct from Istream
		inline treeBoundBox(Istream&);


		// Member Functions

			// Access

				//- Typical dimension length,height,width
		inline scalar typDim() const;

		//- Vertex coordinates. In octant coding.
		FoamBase_EXPORT tmp<pointField> points() const;


		// Check

			//- Corner point given octant
		inline point corner(const direction) const;

		//- Sub box given by octant number. Midpoint calculated.
		FoamBase_EXPORT treeBoundBox subBbox(const direction) const;

		//- Sub box given by octant number. Midpoint provided.
		FoamBase_EXPORT treeBoundBox subBbox(const point& mid, const direction) const;

		//- Returns octant number given point and the calculated midpoint.
		inline direction subOctant
		(
			const point& pt
		) const;

		//- Returns octant number given point and midpoint.
		static inline direction subOctant
		(
			const point& mid,
			const point& pt
		);

		//- Returns octant number given point and the calculated midpoint.
		//  onEdge set if the point is on edge of subOctant
		inline direction subOctant
		(
			const point& pt,
			bool& onEdge
		) const;

		//- Returns octant number given point and midpoint.
		//  onEdge set if the point is on edge of subOctant
		static inline direction subOctant
		(
			const point& mid,
			const point& pt,
			bool& onEdge
		);

		//- Returns octant number given intersection and midpoint.
		//  onEdge set if the point is on edge of subOctant
		//  If onEdge, the direction vector determines which octant to use
		//  (acc. to which octant the point would be if it were moved
		//  along dir)
		static inline direction subOctant
		(
			const point& mid,
			const vector& dir,
			const point& pt,
			bool& onEdge
		);

		//- Calculates optimal order to look for nearest to point.
		//  First will be the octant containing the point,
		//  second the octant with boundary nearest to the point etc.
		inline void searchOrder
		(
			const point& pt,
			FixedList<direction, 8>& octantOrder
		) const;

		//- Overlaps other bounding box?
		using boundBox::overlaps;

		//- Intersects segment; set point to intersection position and face,
		//  return true if intersection found.
		//  (pt argument used during calculation even if not intersecting).
		//  Calculates intersections from outside supplied vector
		//  (overallStart, overallVec). This is so when
		//  e.g. tracking through lots of consecutive boxes
		// (typical octree) we're not accumulating truncation errors. Set
		// to start, (end-start) if not used.
		FoamBase_EXPORT bool intersects
		(
			const point& overallStart,
			const vector& overallVec,
			const point& start,
			const point& end,
			point& pt,
			direction& ptBits
		) const;

		//- Like above but does not return faces point is on
		FoamBase_EXPORT bool intersects
		(
			const point& start,
			const point& end,
			point& pt
		) const;

		//- Contains point or other bounding box?
		using boundBox::contains;

		//- Contains point (inside or on edge) and moving in direction
		//  dir would cause it to go inside.
		FoamBase_EXPORT bool contains(const vector& dir, const point&) const;

		//- Code position of point on bounding box faces
		FoamBase_EXPORT direction faceBits(const point&) const;

		//- Position of point relative to bounding box
		FoamBase_EXPORT direction posBits(const point&) const;

		//- Calculate nearest and furthest (to point) vertex coords of
		//  bounding box
		FoamBase_EXPORT void calcExtremities
		(
			const point& pt,
			point& nearest,
			point& furthest
		) const;

		//- Returns distance point to furthest away corner.
		FoamBase_EXPORT scalar maxDist(const point&) const;

		//- Compare distance to point with other bounding box
		//  return:
		//  -1 : all vertices of my bounding box are nearer than any of
		//       other
		//  +1 : all vertices of my bounding box are further away than
		//       any of other
		//   0 : none of the above.
		FoamBase_EXPORT label distanceCmp(const point&, const treeBoundBox& other) const;

		//- Return asymetrically extended bounding box, with guaranteed
		//  minimum width of s*mag(span) in any direction
		inline treeBoundBox extend(const scalar s) const;

		// Write

		FoamBase_EXPORT void writeOBJ(const fileName& fName) const;


		// Friend Operators

		friend FoamBase_EXPORT bool operator==(const treeBoundBox&, const treeBoundBox&);
		friend FoamBase_EXPORT bool operator!=(const treeBoundBox&, const treeBoundBox&);


		// IOstream operator

		friend FoamBase_EXPORT Istream& operator>>(Istream& is, treeBoundBox&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream& os, const treeBoundBox&);
	};


	//- Data associated with treeBoundBox type are contiguous
	template<>
	inline bool contiguous<treeBoundBox>() { return contiguous<boundBox>(); }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


#include <treeBoundBoxI.hxx>
#include <treeBoundBoxTemplatesI.hxx>

//#ifdef NoRepository
//#include <treeBoundBoxTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_treeBoundBox_Header
