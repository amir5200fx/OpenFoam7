#pragma once
#ifndef _complexFields_Header
#define _complexFields_Header

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

Typedef
	tnbLib::complexField

Description
	Specialisation of Field\<T\> for complex.

Typedef
	tnbLib::complexVectorField

Description
	Specialisation of Field\<T\> for complexVector.

SourceFiles
	complexFields.C

\*---------------------------------------------------------------------------*/

#include <complex.hxx>
#include <complexVector.hxx>
#include <primitiveFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef Field<complex> complexField;

	FoamBase_EXPORT complexField ComplexField(const UList<scalar>&, const UList<scalar>&);
	FoamBase_EXPORT complexField ReComplexField(const UList<scalar>&);
	FoamBase_EXPORT complexField ImComplexField(const UList<scalar>&);
	FoamBase_EXPORT scalarField Re(const UList<complex>&);
	FoamBase_EXPORT scalarField Im(const UList<complex>&);
	FoamBase_EXPORT scalarField ReImSum(const UList<complex>&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef Field<complexVector> complexVectorField;

	FoamBase_EXPORT complexVectorField ComplexField(const UList<vector>&, const UList<vector>&);
	FoamBase_EXPORT complexVectorField ReComplexField(const UList<vector>&);
	FoamBase_EXPORT complexVectorField ImComplexField(const UList<vector>&);
	FoamBase_EXPORT vectorField Re(const UList<complexVector>&);
	FoamBase_EXPORT vectorField Im(const UList<complexVector>&);
	FoamBase_EXPORT vectorField ReImSum(const UList<complexVector>&);

	FoamBase_EXPORT complexVectorField operator^
		(
			const UList<vector>&,
			const UList<complexVector>&
			);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_complexFields_Header
