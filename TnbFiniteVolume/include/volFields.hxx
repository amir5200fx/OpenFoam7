#pragma once
#ifndef _volFields_Header
#define _volFields_Header

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

#include <GeometricFields.hxx>
#include <volMesh.hxx>
#include <fvMesh.hxx>
#include <fvPatchField.hxx>
#include <volFieldsFwd.hxx>
#include <calculatedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	FoamFiniteVolume_EXPORT tmp<GeometricField<scalar, fvPatchField, volMesh>>
		GeometricField<scalar, fvPatchField, volMesh>::component
		(
			const direction
		) const;

	template<>
	FoamFiniteVolume_EXPORT void GeometricField<scalar, fvPatchField, volMesh>::replace
	(
		const direction,
		const GeometricField<scalar, fvPatchField, volMesh>& sf
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <volFieldsI.hxx>

#endif // !_volFields_Header
