#pragma once
#ifndef _DimensionedSphericalTensorField_Header
#define _DimensionedSphericalTensorField_Header

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
	tnbLib::DimensionedSphericalTensorField

Description
	Specialisation of DimensionedField<T, GeoMesh> for sphericalTensor.

SourceFiles
	DimensionedSphericalTensorField.C

\*---------------------------------------------------------------------------*/

#include <DimensionedField.hxx>
#include <sphericalTensor.hxx>

//#define TEMPLATE template<class GeoMesh>
//#include <DimensionedFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const DimensionedField<sphericalTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> tr(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const DimensionedField<sphericalTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> sph(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const DimensionedField<sphericalTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<scalar, GeoMesh>> det(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1);
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> inv(const DimensionedField<sphericalTensor, GeoMesh>& df);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> inv(const tmp<DimensionedField<sphericalTensor, GeoMesh>>& tdf1);

		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                           const DimensionedField<sphericalTensor, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                           const tmp<DimensionedField<sphericalTensor, GeoMesh>>&
	                                                           tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                           const DimensionedField<sphericalTensor, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                           const tmp<DimensionedField<sphericalTensor, GeoMesh>>&
	                                                           tdf2);
		
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                           const DimensionedField<sphericalTensor, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const scalar& t1,
	                                                           const DimensionedField<sphericalTensor, GeoMesh>& df2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const dimensioned<scalar>& dt1,
	                                                           const tmp<DimensionedField<sphericalTensor, GeoMesh>>&
	                                                           tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const scalar& t1,
	                                                           const tmp<DimensionedField<sphericalTensor, GeoMesh>>&
	                                                           tdf2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                           const dimensioned<sphericalTensor>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const DimensionedField<scalar, GeoMesh>& df1,
	                                                           const sphericalTensor& t2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                           const dimensioned<sphericalTensor>& dt2);
	template <class GeoMesh>
	tmp<DimensionedField<sphericalTensor, GeoMesh>> operator /(const tmp<DimensionedField<scalar, GeoMesh>>& tdf1,
	                                                           const sphericalTensor& t2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <DimensionedSphericalTensorFieldI.hxx>

//#ifdef NoRepository
//#include <DimensionedSphericalTensorField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DimensionedSphericalTensorField_Header
