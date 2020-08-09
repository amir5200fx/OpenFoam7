#pragma once
#ifndef _slicedSurfaceFields_Header
#define _slicedSurfaceFields_Header

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
	tnbLib::slicedSurfaceFields

\*---------------------------------------------------------------------------*/

#include <SlicedGeometricField.hxx>
#include <slicedFvsPatchField.hxx>
#include <surfaceMesh.hxx>
#include <slicedSurfaceFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	inline void
		SlicedGeometricField<scalar, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<vector, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField
		<
		sphericalTensor,
		fvsPatchField,
		slicedFvsPatchField,
		surfaceMesh
		>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField
		<
		symmTensor,
		fvsPatchField,
		slicedFvsPatchField,
		surfaceMesh
		>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<tensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_slicedSurfaceFields_Header
