#pragma once
#ifndef _fvMeshAdder_Header
#define _fvMeshAdder_Header

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
	tnbLib::fvMeshAdder

Description
	Adds two fvMeshes without using any polyMesh morphing.
	Uses polyMeshAdder.

SourceFiles
	fvMeshAdder.C
	fvMeshAdderTemplates.C

\*---------------------------------------------------------------------------*/

#include <polyMeshAdder.hxx>
#include <volFieldsFwd.hxx>
#include <fvPatchFieldsFwd.hxx>
#include <fvsPatchFieldsFwd.hxx>
#include <fvPatchFieldMapper.hxx>
#include <DimensionedField.hxx>
#include <pointFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class IOobject;
	class faceCoupleInfo;
	class IOobjectList;
	class fvMesh;
	class volMesh;
	class surfaceMesh;
	class mapAddedPolyMesh;

	/*---------------------------------------------------------------------------*\
							   Class fvMeshAdder Declaration
	\*---------------------------------------------------------------------------*/

	class fvMeshAdder
		:
		public polyMeshAdder
	{
		// Private Member Functions

			//- Calculate map from new patch faces to old patch faces. -1 where
			//  could not map.
		static FoamDynamicMesh_EXPORT labelList calcPatchMap
		(
			const label oldStart,
			const label oldSize,
			const labelList& oldToNew,
			const polyPatch& newPatch,
			const label unmappedIndex
		);

		//- Update single volField.
		template<class Type>
		static void MapVolField
		(
			const mapAddedPolyMesh& meshMap,

			GeometricField<Type, fvPatchField, volMesh>& fld,
			const GeometricField<Type, fvPatchField, volMesh>& fldToAdd
		);

		//- Update single surfaceField.
		template<class Type>
		static void MapSurfaceField
		(
			const mapAddedPolyMesh& meshMap,

			GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
			const GeometricField<Type, fvsPatchField, surfaceMesh>& fldToAdd
		);

		//- Update single pointField.
		template<class Type>
		static void MapPointField
		(
			const pointMesh& mesh,
			const mapAddedPolyMesh& meshMap,
			const labelListList& oldMeshPoints,

			GeometricField<Type, pointPatchField, pointMesh>& fld,
			const GeometricField<Type, pointPatchField, pointMesh>& fldToAdd
		);

		//- Update single dimensionedField.
		template<class Type>
		static void MapDimField
		(
			const mapAddedPolyMesh& meshMap,

			DimensionedField<Type, volMesh>& fld,
			const DimensionedField<Type, volMesh>& fldToAdd
		);

	public:

		// Declare name of the class and its debug switch
		//ClassName("fvMeshAdder");
		static const char* typeName_() { return "fvMeshAdder"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;


		// Member Functions

			//- Inplace add mesh to fvMesh. Maps all stored fields. Returns map.
		static FoamDynamicMesh_EXPORT autoPtr<mapAddedPolyMesh> add
		(
			fvMesh& mesh0,
			const fvMesh& mesh1,
			const faceCoupleInfo& coupleInfo,
			const bool validBoundary = true
		);

		//- Map all volFields of Type
		template<class Type>
		static void MapVolFields
		(
			const mapAddedPolyMesh&,
			const fvMesh& mesh,
			const fvMesh& meshToAdd
		);

		//- Map all surfaceFields of Type
		template<class Type>
		static void MapSurfaceFields
		(
			const mapAddedPolyMesh&,
			const fvMesh& mesh,
			const fvMesh& meshToAdd
		);

		//- Map all surfaceFields of Type
		template<class Type>
		static void MapPointFields
		(
			const mapAddedPolyMesh&,
			const pointMesh& mesh,
			const labelListList& oldMeshPoints,
			const objectRegistry& meshToAdd
		);

		//- Map all DimensionedFields of Type
		template<class Type>
		static void MapDimFields
		(
			const mapAddedPolyMesh&,
			const fvMesh& mesh,
			const fvMesh& meshToAdd
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvMeshAdderI.hxx>

//#ifdef NoRepository
//#include <fvMeshAdderTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMeshAdder_Header
