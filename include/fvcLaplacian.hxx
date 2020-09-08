#pragma once
#ifndef _fvcLaplacian_Header
#define _fvcLaplacian_Header

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
	Calculate the laplacian of the given field.

SourceFiles
	fvcLaplacian.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <dimensionedTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const dimensioned<GType>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const dimensioned<GType>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh>>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh>> laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh>>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh>>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvcLaplacianI.hxx>

//#ifdef NoRepository
//#include <fvcLaplacian.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvcLaplacian_Header
