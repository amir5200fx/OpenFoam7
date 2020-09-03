#pragma once
#ifndef _DimensionedSymmTensorField_Header
#define _DimensionedSymmTensorField_Header

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
	tnbLib::DimensionedSymmTensorField

Description
	SymmTensor specific part of the implementation of DimensionedField.

SourceFiles
	DimensionedSymmTensorField.C

\*---------------------------------------------------------------------------*/

#include <DimensionedField.hxx>
#include <symmTensor.hxx>

#include <vector.hxx>  // added by amir
#include <sphericalTensor.hxx>  // added by amir

//#define TEMPLATE template<class GeoMesh>
//#include <DimensionedFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const DimensionedField<vector, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> sqr(const tmp<DimensionedField<vector, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> innerSqr(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> innerSqr(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);

		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> symm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> twoSymm(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> dev2(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> cof(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const DimensionedField<symmTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<symmTensor, GeoMesh>> inv(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const DimensionedField<symmTensor, GeoMesh>& df1);
	template <class GeoMesh>
	tmp<DimensionedField<vector, GeoMesh>> operator *(const tmp<DimensionedField<symmTensor, GeoMesh>>& tdf1);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <DimensionedSymmTensorFieldI.hxx>

//#ifdef NoRepository
//#include <DimensionedSymmTensorField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DimensionedSymmTensorField_Header
