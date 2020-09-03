#pragma once
#ifndef _GeometricSymmTensorField_Header
#define _GeometricSymmTensorField_Header

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
	tnbLib::GeometricSymmTensorField

Description
	SymmTensor specific part of the implementation of GeometricField.

SourceFiles
	GeometricSymmTensorField.C

\*---------------------------------------------------------------------------*/


#include <GeometricField.hxx>
#include <DimensionedSymmTensorField.hxx>

//#define TEMPLATE template<template<class> class PatchField, class GeoMesh>
//#include <GeometricFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const GeometricField<vector, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> sqr(const tmp<GeometricField<vector, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> innerSqr(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> tr(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<sphericalTensor, PatchField, GeoMesh>> sph(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> symm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>>
	twoSymm(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> twoSymm(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> dev2(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<scalar, PatchField, GeoMesh>> det(const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> cof(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(const GeometricField<symmTensor, PatchField, GeoMesh>& df);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<symmTensor, PatchField, GeoMesh>> inv(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator
	*(const GeometricField<symmTensor, PatchField, GeoMesh>& df1);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<vector, PatchField, GeoMesh>> operator *(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1);

		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& df1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>&
	                                                            df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& df1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1,
		const GeometricField<symmTensor, PatchField, GeoMesh>& df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1,
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf2);
		
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>&
	                                                            df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
	                                                            const GeometricField<symmTensor, PatchField, GeoMesh>&
	                                                            df2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const dimensioned<symmTensor>& dt1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const symmTensor& t1,
	                                                            const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>&
	                                                            tdf2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& df1,
	                                                            const dimensioned<symmTensor>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(const GeometricField<symmTensor, PatchField, GeoMesh>& df1,
	                                                            const symmTensor& t2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1, const dimensioned<symmTensor>& dt2);
	template <template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<tensor, PatchField, GeoMesh>> operator &(
		const tmp<GeometricField<symmTensor, PatchField, GeoMesh>>& tdf1, const symmTensor& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <GeometricSymmTensorFieldI.hxx>

//#ifdef NoRepository
//#include <GeometricSymmTensorField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GeometricSymmTensorField_Header
