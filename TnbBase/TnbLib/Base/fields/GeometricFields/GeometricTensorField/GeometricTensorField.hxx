#pragma once
#ifndef _GeometricTensorField_Header
#define _GeometricTensorField_Header

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

InClass
	tnbLib::GeometricTensorField

Description
	Tensor specific part of the implementation of GeometricField.

SourceFiles
	GeometricTensorField.C

\*---------------------------------------------------------------------------*/

#include <GeometricSphericalTensorField.hxx>
#include <GeometricSymmTensorField.hxx>
#include <DimensionedTensorField.hxx>

//#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
//#include <GeometricFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> T(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> T(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>>
	symm(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> skew(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> skew(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev2(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> dev2(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> cof(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> cof(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> inv(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> inv(const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> eigenVectors(const GeometricField<tensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> eigenVectors(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>>
	eigenValues(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> eigenValues(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> eigenVectors(
		const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> eigenVectors(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(const GeometricField<tensor, PatchField, GeoMesh>& df1);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator *(const GeometricField<vector, PatchField, GeoMesh>& df1);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& df1,
	                                                            const GeometricField<tensor, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& df1,
	                                                            const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1, const GeometricField<tensor, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1,
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& tdf2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const dimensioned<vector>& dt1,
	                                                            const GeometricField<tensor, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const vector& t1,
	                                                            const GeometricField<tensor, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const dimensioned<vector>& dt1,
	                                                            const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const vector& t1,
	                                                            const tmp<GeometricField<tensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& df1,
	                                                            const dimensioned<tensor>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(const GeometricField<vector, PatchField, GeoMesh>& df1,
	                                                            const tensor& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1, const dimensioned<tensor>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator /(
		const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1, const tensor& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <GeometricTensorFieldI.hxx>

//#ifdef NoRepository
//#include <GeometricTensorField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GeometricTensorField_Header
