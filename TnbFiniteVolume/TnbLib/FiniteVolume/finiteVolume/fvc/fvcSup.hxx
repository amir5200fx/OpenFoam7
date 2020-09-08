#pragma once
#ifndef _fvcSup_Header
#define _fvcSup_Header

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
	Calculate the field for explicit evaluation of implicit and explicit
	sources.

SourceFiles
	fvcSup.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <dimensionedScalarFwd.hxx>  // added by amir

#include <tmp.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		// Explicit source

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> Su
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> Su
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		// Implicit source

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> Sp
		(
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> Sp
		(
			const tmp<volScalarField>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> Sp
		(
			const dimensionedScalar&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		// Implicit/Explicit source depending on sign of coefficient

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> SuSp
		(
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> SuSp
		(
			const tmp<volScalarField>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvcSupI.hxx>

//#ifdef NoRepository
//#include <fvcSup.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvcSup_Header
