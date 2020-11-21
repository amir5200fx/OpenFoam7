#pragma once
#ifndef _fvMeshTools_Header
#define _fvMeshTools_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fvMeshTools

Description
	A collection of tools for operating on an fvMesh.

SourceFiles
	fvMeshTools.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class fvMeshTools Declaration
	\*---------------------------------------------------------------------------*/

	class fvMeshTools
	{
		//- Set patchFields according to dictionary
		template<class GeoField>
		static void setPatchFields
		(
			typename  GeoField::Mesh& mesh,
			const label patchi,
			const dictionary& patchFieldDict
		);

		//- Set patchFields to value
		template<class GeoField>
		static void setPatchFields
		(
			typename  GeoField::Mesh& mesh,
			const label patchi,
			const typename GeoField::value_type& value
		);


	public:

		//- Add patch. Inserts patch before all processor patches.
		//  Supply per field the new patchField per field as a
		//  subdictionary or a default type. If validBoundary call is parallel
		//  synced and all add the same patch with same settings.
		static FoamDynamicMesh_EXPORT label addPatch
		(
			fvMesh& mesh,
			const polyPatch& patch,
			const dictionary& patchFieldDict,
			const word& defaultPatchFieldType,
			const bool validBoundary
		);

		//- Change patchField on registered fields according to dictionary
		static FoamDynamicMesh_EXPORT void setPatchFields
		(
			fvMesh& mesh,
			const label patchi,
			const dictionary& patchFieldDict
		);

		//- Change patchField to zero on registered fields
		static FoamDynamicMesh_EXPORT void zeroPatchFields(fvMesh& mesh, const label patchi);

		//- Reorder and remove trailing patches. If validBoundary call is parallel
		//  synced and all add the same patch with same settings
		static FoamDynamicMesh_EXPORT void reorderPatches
		(
			fvMesh&,
			const labelList& oldToNew,
			const label nPatches,
			const bool validBoundary
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvMeshToolsI.hxx>

//#ifdef NoRepository
//#include <fvMeshToolsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMeshTools_Header
