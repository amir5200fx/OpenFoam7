#pragma once
#ifndef _surfaceFieldsFwd_Header
#define _surfaceFieldsFwd_header

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
	tnbLib::surfaceFields

Description

SourceFiles
	surfaceFields.C

\*---------------------------------------------------------------------------*/

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class surfaceMesh;

	template<class Type>
	class fvsPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

	typedef GeometricField<scalar, fvsPatchField, surfaceMesh> surfaceScalarField;
	typedef GeometricField<vector, fvsPatchField, surfaceMesh> surfaceVectorField;
	typedef GeometricField<sphericalTensor, fvsPatchField, surfaceMesh>
		surfaceSphericalTensorField;
	typedef GeometricField<symmTensor, fvsPatchField, surfaceMesh>
		surfaceSymmTensorField;
	typedef GeometricField<tensor, fvsPatchField, surfaceMesh> surfaceTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceFieldsFwd_Header
