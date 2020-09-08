#pragma once
#ifndef _volFieldsFwd_Header
#define _volFieldsFwd_Header

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
	tnbLib::volFields

Description

SourceFiles
	volFields.C

\*---------------------------------------------------------------------------*/

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class volMesh;

	template<class Type>
	class fvPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

	typedef GeometricField<scalar, fvPatchField, volMesh> volScalarField;
	typedef GeometricField<vector, fvPatchField, volMesh> volVectorField;
	typedef GeometricField<sphericalTensor, fvPatchField, volMesh>
		volSphericalTensorField;
	typedef GeometricField<symmTensor, fvPatchField, volMesh> volSymmTensorField;
	typedef GeometricField<tensor, fvPatchField, volMesh> volTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volFieldsFwd_Header
