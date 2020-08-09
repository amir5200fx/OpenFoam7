#pragma once
#ifndef _fvcSurfaceIntegrate_Header
#define _fvcSurfaceIntegrate_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

InNamespace
	tnbLib::fvc

Description
	Surface integrate surfaceField creating a volField.
	Surface sum a surfaceField creating a volField.

SourceFiles
	fvcSurfaceIntegrate.C

\*---------------------------------------------------------------------------*/

#include <primitiveFieldsFwd.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>

#include <tmp.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		template<class Type>
		void surfaceIntegrate
		(
			Field<Type>&,
			const GeometricField<Type, fvsPatchField, surfaceMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			surfaceIntegrate
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>&
			);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>>
			surfaceIntegrate
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>&
			);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> surfaceSum
		(
			const GeometricField<Type, fvsPatchField, surfaceMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> surfaceSum
		(
			const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <fvcSurfaceIntegrate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvcSurfaceIntegrate_Header
