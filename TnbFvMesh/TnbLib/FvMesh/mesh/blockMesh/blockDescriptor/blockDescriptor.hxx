#pragma once
#ifndef _blockDescriptor_Header
#define _blockDescriptor_Header

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
	tnbLib::blockDescriptor

Description
	Takes the description of the block and the list of curved edges and
	creates a list of points on edges together with the weighting factors

	For a given block, the correspondence between the ordering of vertex labels
	and face labels is shown below.  For vertex numbering in the sequence 0 to 7
	(block, centre): faces 0 (f0) and 1 are left and right, respectively; faces
	2 and 3 are front and back; and faces 4 and 5 are bottom and top:
	\verbatim
				   7 ---- 6
			  f5   |\     |\   f3
			   |   | 4 ---- 5    \
			   |   3 |--- 2 |     \
			   |    \|     \|      f2
			  f4     0 ---- 1

		 Z         f0 ----- f1
		 |  Y
		 | /
		 O --- X
	 \endverbatim

SourceFiles
	blockDescriptor.C
	blockDescriptorEdges.C

\*---------------------------------------------------------------------------*/

#include <cellShape.hxx>
#include <pointField.hxx>
#include <scalarList.hxx>
#include <blockEdgeList.hxx>
#include <blockFaceList.hxx>
#include <gradingDescriptors.hxx>

#include <FixedList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class blockDescriptor;
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockDescriptor&);

	/*---------------------------------------------------------------------------*\
						   Class blockDescriptor Declaration
	\*---------------------------------------------------------------------------*/

	class blockDescriptor
	{
		// Private Data

			//- Reference to point field defining the block mesh
		const pointField& vertices_;

		//- Reference to a list of block edges
		const blockEdgeList& edges_;

		//- Reference to the list of curved faces
		const blockFaceList& faces_;

		//- Block shape
		cellShape blockShape_;

		//- The number of cells in the i,j,k directions
		Vector<label> density_;

		//- Expansion ratios in all directions
		List<gradingDescriptors> expand_;

		//- Name of the zone (empty word if none)
		word zoneName_;

		//- Curved-face labels for each block-face (-1 for flat faces)
		FixedList<label, 6> curvedFaces_;

		//- Number of curved faces in this block
		label nCurvedFaces_;


		// Private Member Functions

			//- Check block has outward-pointing faces
		FoamFvMesh_EXPORT void check(const Istream& is);

		//- Calculate the points and weights for the specified edge.
		//  Return the number of curved edges
		FoamFvMesh_EXPORT label edgePointsWeights
		(
			pointField(&edgePoints)[12],
			scalarList(&edgeWeights)[12],
			const label edgei,
			const label start,
			const label end,
			const label dim
		) const;

		FoamFvMesh_EXPORT void findCurvedFaces();


	public:

		// Constructors

			//- Construct from components. Optional cellSet/zone name.
		FoamFvMesh_EXPORT blockDescriptor
		(
			const cellShape&,
			const pointField& vertices,
			const blockEdgeList&,
			const blockFaceList&,
			const Vector<label>& density,
			const UList<gradingDescriptors>& expand,
			const word& zoneName = ""
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT blockDescriptor
		(
			const dictionary& dict,
			const label index,
			const pointField& vertices,
			const blockEdgeList&,
			const blockFaceList&,
			Istream&
		);


		// Member Functions

			//- Reference to point field defining the block mesh
		inline const pointField& vertices() const;

		//- Return reference to the list of curved faces
		inline const blockFaceList& faces() const;

		//- Return the block shape
		inline const cellShape& blockShape() const;

		//- Return the mesh density (number of cells) in the i,j,k directions
		inline const Vector<label>& density() const;

		//- Return the (optional) zone name
		inline const word& zoneName() const;

		//- Return the number of points
		inline label nPoints() const;

		//- Return the number of cells
		inline label nCells() const;

		//- Curved-face labels for each block-face (-1 for flat faces)
		inline const FixedList<label, 6>& curvedFaces() const;

		//- Number of curved faces in this block
		inline label nCurvedFaces() const;

		//- Return block point for local label i
		inline const point& blockPoint(const label i) const;

		//- Vertex label offset for a particular i,j,k position
		inline label pointLabel
		(
			const label i,
			const label j,
			const label k
		) const;

		//- Face vertex label offset for a particular i,j,k position
		inline label facePointLabel
		(
			const label facei,
			const label i,
			const label j
		) const;

		//- Return true if point i,j,k addresses a block vertex
		inline bool vertex(const label i, const label j, const label k) const;

		//- Return true if point i,j,k addresses a block edge
		inline bool edge(const label i, const label j, const label k) const;

		//- Calculate the points and weights for all edges.
		//  Return the number of curved edges
		label edgesPointsWeights
		(
			pointField(&edgePoints)[12],
			scalarList(&edgeWeights)[12]
		) const;

		//- Return true if point i,j,k addresses a block flat face or edge
		inline bool flatFaceOrEdge
		(
			const label i,
			const label j,
			const label k
		) const;

		//- Return the list of face-points for all of the faces of the block
		FoamFvMesh_EXPORT FixedList<pointField, 6> facePoints(const pointField& points) const;

		//- Correct the location of the given face-points
		//  to lie on the faces of the block
		FoamFvMesh_EXPORT void correctFacePoints(FixedList<pointField, 6>&) const;

		//- Write block index with dictionary lookup
		static FoamFvMesh_EXPORT void write(Ostream&, const label blocki, const dictionary&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const blockDescriptor&) = delete;


		// IOstream Operators

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const blockDescriptor&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <blockDescriptorI.hxx>

#endif // !_blockDescriptor_Header
