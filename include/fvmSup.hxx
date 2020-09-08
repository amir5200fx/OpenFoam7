#pragma once
#ifndef _fvmSup_Header
#define _fvmSup_Header

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
	tnbLib::fvm

Description
	Calculate the matrix for implicit and explicit sources.

SourceFiles
	fvmSup.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <fvMatrix.hxx>
#include <zeroField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvm functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvm
	{
		// Explicit source

		template<class Type>
		tmp<fvMatrix<Type>> Su
		(
			const DimensionedField<Type, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> Su
		(
			const tmp<DimensionedField<Type, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> Su
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		zeroField Su
		(
			const zero&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		// Implicit source

		template<class Type>
		tmp<fvMatrix<Type>> Sp
		(
			const volScalarField::Internal&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> Sp
		(
			const tmp<volScalarField::Internal>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> Sp
		(
			const tmp<volScalarField>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type>
		tmp<fvMatrix<Type>> Sp
		(
			const dimensionedScalar&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type>
		zeroField Sp
		(
			const zero&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		// Implicit/Explicit source depending on sign of coefficient

		template<class Type>
		tmp<fvMatrix<Type>> SuSp
		(
			const volScalarField::Internal&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> SuSp
		(
			const tmp<volScalarField::Internal>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> SuSp
		(
			const tmp<volScalarField>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		zeroField SuSp
		(
			const zero&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvmSupI.hxx>

//#ifdef NoRepository
//#include <fvmSup.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvmSup_Header
