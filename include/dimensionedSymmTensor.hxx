#pragma once
#ifndef _dimensionedSymmTensor_Header
#define _dimensionedSymmTensor_Header

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
	tnbLib::dimensionedSymmTensor

Description
	Dimensioned tensor obtained from generic dimensioned type.

SourceFiles
	dimensionedSymmTensor.C

\*---------------------------------------------------------------------------*/

#include <dimensionedVector.hxx>
#include <symmTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef dimensioned<symmTensor> dimensionedSymmTensor;


	// global functions

	dimensionedSymmTensor sqr(const dimensionedVector&);
	dimensionedSymmTensor innerSqr(const dimensionedSymmTensor&);

	dimensionedScalar tr(const dimensionedSymmTensor&);
	dimensionedSymmTensor symm(const dimensionedSymmTensor&);
	dimensionedSymmTensor twoSymm(const dimensionedSymmTensor&);
	dimensionedSymmTensor dev(const dimensionedSymmTensor&);
	dimensionedSymmTensor dev2(const dimensionedSymmTensor&);
	dimensionedScalar det(const dimensionedSymmTensor&);
	dimensionedSymmTensor cof(const dimensionedSymmTensor&);
	dimensionedSymmTensor inv(const dimensionedSymmTensor&);


	// global operators

	//- Hodge Dual operator (tensor -> vector)
	dimensionedVector operator*(const dimensionedSymmTensor&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dimensionedSymmTensor_Header
