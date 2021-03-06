#pragma once
#ifndef _cellDistFuncs_Header
#define _cellDistFuncs_Header

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
	tnbLib::cellDistFuncs

Description
	Collection of functions used in wall distance calculation.

SourceFiles
	cellDistFuncs.C
	cellDistFuncsTemplates.C

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <HashSet.hxx>
#include <Map.hxx>
#include <wordReList.hxx>
#include <point.hxx>
#include <primitivePatch.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class polyPatch;
	class polyBoundaryMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellDistFuncs Declaration
	\*---------------------------------------------------------------------------*/

	class cellDistFuncs
	{
		// Private Member Data

			//- Reference to mesh
		const polyMesh& mesh_;


		// Private Member Functions

			//- Search for element in first n elements of labelList. Return index
			//  or -1.
		static FoamFvMesh_EXPORT label findIndex(const label n, const labelList&, const label);


	public:

		//ClassName("cellDistFuncs");
		static const char* typeName_() { return "cellDistFuncs"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;

		// Constructors

			//- Construct from mesh
		FoamFvMesh_EXPORT cellDistFuncs(const polyMesh& mesh);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT cellDistFuncs(const cellDistFuncs&) = delete;


		// Member Functions

			//- Access mesh
		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Return the set of patch IDs corresponding to the given names
		FoamFvMesh_EXPORT labelHashSet getPatchIDs(const wordReList& patchNames) const;

		//- Get patchIDs of/derived off certain type (e.g. 'processorPolyPatch')
		//  Uses isA, not isType
		template<class Type>
		labelHashSet getPatchIDs() const;

		//- Calculate smallest true distance (and face index)
		//  from pt to faces wallFaces.
		//  For efficiency reasons we still pass in patch instead of extracting
		//  it from mesh_
		FoamFvMesh_EXPORT scalar smallestDist
		(
			const point& p,
			const polyPatch& patch,
			const label nWallFaces,
			const labelList& wallFaces,
			label& meshFacei
		) const;

		//- Get faces sharing point with face on patch
		FoamFvMesh_EXPORT label getPointNeighbours
		(
			const primitivePatch&,
			const label patchFacei,
			labelList&
		) const;

		//- Size of largest patch (out of supplied subset of patches)
		FoamFvMesh_EXPORT label maxPatchSize(const labelHashSet& patchIDs) const;

		//- Sum of patch sizes (out of supplied subset of patches).
		//  Used in sizing arrays.
		FoamFvMesh_EXPORT label sumPatchSize(const labelHashSet& patchIDs) const;

		//- Correct all cells connected to boundary (via face). Sets values in
		//  wallDistCorrected. Sets nearest wallface in nearestFace.
		FoamFvMesh_EXPORT void correctBoundaryFaceCells
		(
			const labelHashSet& patchIDs,
			scalarField& wallDistCorrected,
			Map<label>& nearestFace
		) const;


		//- Correct all cells connected to wall (via point). Sets values in
		//  wallDistCorrected. Uses/sets nearest wallFace in nearestFace.
		FoamFvMesh_EXPORT void correctBoundaryPointCells
		(
			const labelHashSet& patchIDs,
			scalarField& wallDistCorrected,
			Map<label>& nearestFace
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const cellDistFuncs&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cellDistFuncsTemplatesI.hxx>

//#ifdef NoRepository
//#include <cellDistFuncsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellDistFuncs_Header
