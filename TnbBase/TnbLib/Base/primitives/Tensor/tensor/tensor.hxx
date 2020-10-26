#pragma once
#ifndef _tensor_Header
#define _tensor_Header

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
	tnbLib::tensor

Description
	Tensor of scalars.

SourceFiles
	tensor.C

\*---------------------------------------------------------------------------*/

#include <TensorTemplate.hxx>
#include <vector.hxx>
#include <sphericalTensor.hxx>
#include <symmTensor.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef Tensor<scalar> tensor;

	FoamBase_EXPORT vector eigenValues(const tensor& T);
	FoamBase_EXPORT vector eigenVector
	(
		const tensor& T,
		const scalar lambda,
		const vector& direction1,
		const vector& direction2
	);
	FoamBase_EXPORT tensor eigenVectors(const tensor& T, const vector& lambdas);
	FoamBase_EXPORT tensor eigenVectors(const tensor& T);

	FoamBase_EXPORT vector eigenValues(const symmTensor& T);
	FoamBase_EXPORT vector eigenVector
	(
		const symmTensor& T,
		const scalar lambda,
		const vector& direction1,
		const vector& direction2
	);
	FoamBase_EXPORT tensor eigenVectors(const symmTensor& T, const vector& lambdas);
	FoamBase_EXPORT tensor eigenVectors(const symmTensor& T);

	//- Data associated with tensor type are contiguous
	template<>
	inline bool contiguous<tensor>() { return true; }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tensor_Header
