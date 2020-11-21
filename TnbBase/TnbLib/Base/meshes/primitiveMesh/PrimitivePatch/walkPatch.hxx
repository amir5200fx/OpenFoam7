#pragma once
#ifndef _walkPatch_Header
#define _walkPatch_Header

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
	tnbLib::walkPatch

Description
	Collection of static functions to do various simple patch related things.

SourceFiles
	walkPatch.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <primitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class walkPatch Declaration
	\*---------------------------------------------------------------------------*/

	class walkPatch
	{
		// Private Data

			//- Reference to patch to walk on
		const primitivePatch& pp_;

		//- Reference to zones
		const labelList& faceZone_;

		//- How to walk through faces
		const bool reverse_;

		//- Reference to list to mark off visited faces
		boolList& visited_;


		// Faces visited
		DynamicList<label> visitOrder_;

		// Index in face of vertex it was visited through
		DynamicList<label> indexInFace_;


		// Private Member Functions

			//- Get other face using v0, v1. Returns -1 if none.
		FoamBase_EXPORT label getNeighbour
		(
			const label facei,
			const label fp,
			const label v0,
			const label v1
		) const;

		//- Gets labels of changed faces and enterVertices on faces.
		// Returns labels of faces changed and enterVertices on them.
		FoamBase_EXPORT void faceToFace
		(
			const labelList& changedFaces,
			const labelList& enterVerts,

			labelList& nbrFaces,
			labelList& nbrEnterVerts
		);


	public:

		//ClassName("walkPatch");
		static const char* typeName_() { return "walkPatch"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct from components
		FoamBase_EXPORT walkPatch
		(
			const primitivePatch& pp,
			const labelList& faceZone,  // Per face which zone it belongs to
			const bool reverse,         // Reverse walk
			const label facei,          // Current face
			const label enterVertI,     // Vertex across which this face
										// is visited.
			boolList& visited
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT walkPatch(const walkPatch&) = delete;


		// Member Functions

		const DynamicList<label>& visitOrder() const
		{
			return visitOrder_;
		}

		const DynamicList<label>& indexInFace() const
		{
			return indexInFace_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const walkPatch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_walkPatch_Header
