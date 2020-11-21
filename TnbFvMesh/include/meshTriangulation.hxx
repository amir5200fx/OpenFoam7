#pragma once
#ifndef _meshTriangulation_Header
#define _meshTriangulation_Header

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
	tnbLib::meshTriangulation

Description
	Triangulation of mesh faces. Generates (multiply connected) trisurface.

	All patch faces keep their patchID as triangle region.
	Internal faces get the supplied region number.

SourceFiles
	meshTriangulation.C

\*---------------------------------------------------------------------------*/

#include <triSurface.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class primitiveMesh;

	/*---------------------------------------------------------------------------*\
							   Class meshTriangulation Declaration
	\*---------------------------------------------------------------------------*/

	class meshTriangulation
		:
		public triSurface
	{
		// Private Data

			//- Number of triangles in this that are internal to the surface.
		label nInternalFaces_;

		//- From triangle to mesh face
		labelList faceMap_;

		// Private Member Functions

			//- Is face internal to the subset.
		static FoamFvMesh_EXPORT bool isInternalFace
		(
			const primitiveMesh&,
			const boolList& includedCell,
			const label facei
		);

		//- Find boundary faces of subset.
		static FoamFvMesh_EXPORT void getFaces
		(
			const primitiveMesh&,
			const boolList& includedCell,
			boolList& faceIsCut,
			label& nFaces,
			label& nInternalFaces
		);

		//- Add triangulation of face to triangles. Optionally reverse.
		void FoamFvMesh_EXPORT insertTriangles
		(
			const triFaceList&,
			const label facei,
			const label regionI,
			const bool reverse,

			List<labelledTri>& triangles,
			label& triI
		);


	public:

		/*ClassName("meshTriangulation");*/
		static const char* typeName_() { return "meshTriangulation"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT meshTriangulation();

		//- Construct from selected mesh cell and region number to be used
		//  for triangles resulting from internal faces. (all boundary triangles
		//  get polyMesh patch id).
		//  faceCentreDecomposition = true  : decomposition around face centre
		//                            false : decomposition using
		//                                    existing vertices
		FoamFvMesh_EXPORT meshTriangulation
		(
			const polyMesh&,
			const label internalFacesPatch,
			const boolList& includedCell,
			const bool faceCentreDecomposition = false
		);


		// Member Functions

			//- Number of triangles in *this which are internal to the surface
		label nInternalFaces() const
		{
			return nInternalFaces_;
		}

		//- From triangle to mesh face
		const labelList& faceMap() const
		{
			return faceMap_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshTriangulation_Header
