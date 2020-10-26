#pragma once
#ifndef _dimensionedTensor_Header
#define _dimensionedTensor_Header

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
	tnbLib::dimensionedTensor

Description
	Dimensioned tensor obtained from generic dimensioned type.

SourceFiles
	dimensionedTensor.C

\*---------------------------------------------------------------------------*/

#include <dimensionedVector.hxx>
#include <dimensionedSymmTensor.hxx>
#include <tensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef dimensioned<tensor> dimensionedTensor;


	// global functions

	FoamBase_EXPORT dimensionedScalar tr(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor dev(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor dev2(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedScalar det(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor cof(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor inv(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedSymmTensor symm(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedSymmTensor twoSymm(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor skew(const dimensionedTensor&);

	FoamBase_EXPORT dimensionedVector eigenValues(const dimensionedTensor&);
	FoamBase_EXPORT dimensionedTensor eigenVectors(const dimensionedTensor&);

	FoamBase_EXPORT dimensionedVector eigenValues(const dimensionedSymmTensor&);
	FoamBase_EXPORT dimensionedTensor eigenVectors(const dimensionedSymmTensor&);


	// global operators

	//- Hodge Dual operator (tensor -> vector)
	FoamBase_EXPORT dimensionedVector operator*(const dimensionedTensor&);

	//- Hodge Dual operator (vector -> tensor)
	FoamBase_EXPORT dimensionedTensor operator*(const dimensionedVector&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dimensionedTensor_Header
