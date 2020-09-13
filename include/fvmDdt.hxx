#pragma once
#ifndef _fvmDdt_Header
#define _fvmDdt_Header

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
	Calculate the matrix for the first temporal derivative.

SourceFiles
	fvmDdt.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <fvMatrix.hxx>
#include <one.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvm functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvm
	{
		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const one&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const dimensionedScalar&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const volScalarField&,
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const one&,
			const one&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const one&,
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type>> ddt
		(
			const volScalarField&,
			const one&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvmDdtI.hxx>

//#ifdef NoRepository
//#include <fvmDdt.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvmDdt_Header
