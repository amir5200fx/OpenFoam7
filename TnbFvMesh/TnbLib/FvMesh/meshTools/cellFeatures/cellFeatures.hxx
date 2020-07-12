#pragma once
#ifndef _cellFeatures_Header
#define _cellFeatures_Header

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
	tnbLib::cellFeatures

Description
	Cell analysis class.

	Constructs feature edges and feature points, which are edges/points with
	and angle > given specification.
	Can be asked for 'superFaces' which can be used to see if a cell is a
	'splitHex'.

SourceFiles
	cellFeatures.C

\*---------------------------------------------------------------------------*/

#include <faceList.hxx>
#include <labelList.hxx>
#include <boolList.hxx>
#include <HashSet.hxx>
#include <Map.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class primitiveMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellFeatures Declaration
	\*---------------------------------------------------------------------------*/

	class cellFeatures
	{
		// Private Data

		const primitiveMesh& mesh_;

		//- Cos of angle between two connected faces or two connected edges on
		//  same face before edge/point is 'feature'.
		scalar minCos_;

		label celli_;

		//- Feature edges
		labelHashSet featureEdge_;

		//- (demand driven) Faces after removing internal points&edges
		mutable faceList* facesPtr_;

		//- New to old face mapping
		mutable List<DynamicList<label>> faceMap_;


		// Private Member Functions

		bool faceAlignedEdge(const label, const label) const;

		label nextEdge
		(
			const Map<label>& toSuperFace,
			const label superFacei,
			const label thisEdgeI,
			const label thisVertI
		) const;

		bool isCellFeatureEdge(const scalar, const label) const;

		void walkSuperFace
		(
			const label facei,
			const label superFacei,
			Map<label>& toSuperFace
		) const;

		void calcSuperFaces() const;


	public:

		// Constructors

			//- Construct from cell in mesh
		cellFeatures
		(
			const primitiveMesh&,
			const scalar minCos,    // angle to use for feature recognition.
			const label celli
		);

		//- Disallow default bitwise copy construction
		cellFeatures(const cellFeatures&) = delete;


		//- Destructor
		~cellFeatures();


		// Member Functions

			// Access

		const labelHashSet& featureEdge() const
		{
			return featureEdge_;
		}

		const faceList& faces() const
		{
			if (!facesPtr_)
			{
				calcSuperFaces();
			}
			return *facesPtr_;
		}

		//- New to old faceMap. Guaranteed to be shrunk.
		const List<DynamicList<label>>& faceMap() const
		{
			if (!facesPtr_)
			{
				calcSuperFaces();
			}
			return faceMap_;
		}


		// Check

			//- Is edge a feature edge (uniquely determined since on cell
			//  only two faces sharing edge)
		bool isFeatureEdge(const label edgeI) const
		{
			return featureEdge().found(edgeI);
		}

		//- Are two edges connected at feature point?
		//  Is local to face since point might be seen as feature point
		//  from one face but not from another.
		bool isFeaturePoint(const label edge0, const label edge1) const;

		//- Is vertexI on facei used by two edges that form feature
		//  point
		bool isFeatureVertex(const label facei, const label vertI) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const cellFeatures&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellFeatures_Header
