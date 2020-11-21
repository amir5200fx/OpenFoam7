#pragma once
#ifndef _polyMeshTetDecomposition_Header
#define _polyMeshTetDecomposition_Header

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
	tnbLib::polyMeshTetDecomposition

Description
	Tools for performing the minimum decomposition of faces of the
	mesh into triangles so that the cells may be tet decomposed.
	Includes functions for finding variable face starting (base)
	points on each face to avoid the decomposition of cells into tets
	that have negative or zero volume.

SourceFiles
	polyMeshTetDecomposition.C

\*---------------------------------------------------------------------------*/

#include <polyMesh.hxx>
#include <coupledPolyPatch.hxx>
#include <syncTools.hxx>
#include <tetPointRef.hxx>
#include <tetIndices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class polyMeshTetDecomposition Declaration
	\*---------------------------------------------------------------------------*/

	class polyMeshTetDecomposition
	{

	public:

		// Static Data Members

			//- Minimum tetrahedron quality
		static FoamBase_EXPORT const scalar minTetQuality;


		// Member Functions

			//- Given a face and cc and starting index for triangulation determine
			//  the worst tet quality.
		static FoamBase_EXPORT scalar minQuality
		(
			const polyMesh& mesh,
			const point& cC,
			const label fI,
			const bool isOwner,
			const label faceBasePtI
		);

		//- Find the first suitable base point to use for a minimum
		//  triangle decomposition of the face, suiting owner and
		//  neighbour cells.  Finds the first base point on the face
		//  whose worst quality tet from either cell is better than
		//  tolerance.  Neighbour cell centre supplied.  For coupled
		//  patches.
		static FoamBase_EXPORT label findSharedBasePoint
		(
			const polyMesh& mesh,
			label fI,
			const point& nCc,
			scalar tol,
			bool report = false
		);

		//- As for findSharedBasePoint, but using neighbour cell
		//  centre from the mesh.  For internal faces.
		static FoamBase_EXPORT label findSharedBasePoint
		(
			const polyMesh& mesh,
			label fI,
			scalar tol,
			bool report = false
		);

		//- Find the base point to use for a minimum triangle
		//  decomposition of the face, using only the owner
		//  information.  For non-coupled boundary faces.
		static FoamBase_EXPORT label findBasePoint
		(
			const polyMesh& mesh,
			label fI,
			scalar tol,
			bool report = false
		);

		//- Find a suitable base point for each face for decomposition
		//  into tets
		static FoamBase_EXPORT labelList findFaceBasePts
		(
			const polyMesh& mesh,
			scalar tol = minTetQuality,
			bool report = false
		);

		//- Check face-decomposition tet volume
		static FoamBase_EXPORT bool checkFaceTets
		(
			const polyMesh& mesh,
			scalar tol = minTetQuality,
			const bool report = false,
			labelHashSet* setPtr = nullptr
		);

		//- Return the tet decomposition of the given face, with
		//  respect to the given cell
		static FoamBase_EXPORT List<tetIndices> faceTetIndices
		(
			const polyMesh& mesh,
			label fI,
			label cI
		);

		//- Return the tet decomposition of the given cell, see
		//  findFacePt for the meaning of the indices
		static FoamBase_EXPORT List<tetIndices> cellTetIndices
		(
			const polyMesh& mesh,
			label cI
		);

		//- Find the tet decomposition of the cell containing the given point
		static FoamBase_EXPORT tetIndices findTet
		(
			const polyMesh& mesh,
			label cI,
			const point& pt
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyMeshTetDecomposition_Header
