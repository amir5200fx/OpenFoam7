#pragma once
#ifndef _surfaceInterpolate_Header
#define _surfaceInterpolate_Header

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
	Surface Interpolation

SourceFiles
	surfaceInterpolate.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <surfaceInterpolationScheme.hxx>
#include <one.hxx>
#include <word.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	template<template<class> class Field, class Type>
	class FieldField;  // added by amir

	template<class Type>
	class surfaceInterpolationScheme;  // added by amir

	class fvMesh;  // added by amir

	namespace fvc
	{
		//- Return weighting factors for scheme given from Istream
		template<class Type>
		/*static*/ tmp<surfaceInterpolationScheme<Type>> scheme
		(
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);

		//- Return weighting factors for scheme given by name in dictionary
		template<class Type>
		/*static*/ tmp<surfaceInterpolationScheme<Type>> scheme
		(
			const surfaceScalarField& faceFlux,
			const word& name
		);


		//- Return weighting factors for scheme given from Istream
		template<class Type>
		/*static*/ tmp<surfaceInterpolationScheme<Type>> scheme
		(
			const fvMesh& mesh,
			Istream& schemeData
		);

		//- Return weighting factors for scheme given by name in dictionary
		template<class Type>
		/*static*/ tmp<surfaceInterpolationScheme<Type>> scheme
		(
			const fvMesh& mesh,
			const word& name
		);


		//- Interpolate field onto faces using scheme given by Istream
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const surfaceScalarField& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
			const surfaceScalarField& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const tmp<surfaceScalarField>& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
			const tmp<surfaceScalarField>& faceFlux,
			const word& name
		);


		//- Interpolate field onto faces using scheme given by Istream
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			Istream& schemeData
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf,
			const word& name
		);


		//- Interpolate field onto faces using 'interpolate(\<name\>)'
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf
		);

		//- Interpolate tmp field onto faces using 'interpolate(\<name\>)'
		template<class Type>
		/*static*/ tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
		);


		//- Interpolate boundary field onto faces (simply a type conversion)
		template<class Type>
		/*static*/ tmp<FieldField<fvsPatchField, Type>> interpolate
		(
			const FieldField<fvPatchField, Type>& fvpff
		);

		//- Interpolate boundary field onto faces (simply a type conversion)
		template<class Type>
		/*static*/ tmp<FieldField<fvsPatchField, Type>> interpolate
		(
			const tmp<FieldField<fvPatchField, Type>>& tfvpff
		);

		//- Interpolate 'one' returning 'one'
		inline one interpolate(const one&)
		{
			return one();
		}


		//- Interpolate field onto faces
		//  and 'dot' with given surfaceVectorField Sf
		template<class Type>
		/*static*/
			tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type,
			fvsPatchField,
			surfaceMesh
			>
			> dotInterpolate
			(
				const surfaceVectorField& Sf,
				const GeometricField<Type, fvPatchField, volMesh>& tvf
			);

		//- Interpolate tmp field onto faces
		//  and 'dot' with given surfaceVectorField Sf
		template<class Type>
		/*static*/
			tmp
			<
			GeometricField
			<
			typename innerProduct<vector, Type>::type,
			fvsPatchField,
			surfaceMesh
			>
			> dotInterpolate
			(
				const surfaceVectorField& Sf,
				const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
			);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <surfaceInterpolate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolate_Header
