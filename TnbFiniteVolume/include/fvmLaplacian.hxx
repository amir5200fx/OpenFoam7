#pragma once
#ifndef _fvmLaplacian_Header
#define _fvmLaplacian_Header

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
	Calculate the matrix for the laplacian of the field.

SourceFiles
	fvmLaplacian.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <fvMatrix.hxx>
#include <zero.hxx>
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
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type>
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type>
		tmp<fvMatrix<Type>> laplacian
		(
			const zero&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type>
		tmp<fvMatrix<Type>> laplacian
		(
			const zero&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type>
		tmp<fvMatrix<Type>> laplacian
		(
			const one&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type>
		tmp<fvMatrix<Type>> laplacian
		(
			const one&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);


		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<fvMatrix<Type>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvmLaplacianI.hxx>

//#ifdef NoRepository
//#include <fvmLaplacian.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvmLaplacian_Header
