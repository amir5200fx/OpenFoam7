#pragma once
#ifndef _symmTransformField_Header
#define _symmTransformField_Header

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
	tnbLib::symmTransformField

Description
	Spatial transformation functions for primitive fields.

SourceFiles
	symmTransformField.C

\*---------------------------------------------------------------------------*/

#include <symmTransform.hxx>
#include <symmTensorField.hxx>
#include <sphericalTensor.hxx>

#include <transformField.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type>
	void transform(Field<Type>&, const symmTensorField&, const Field<Type>&);

	template<class Type>
	tmp<Field<Type>> transform(const symmTensorField&, const Field<Type>&);

	template<class Type>
	tmp<Field<Type>> transform(const symmTensorField&, const tmp<Field<Type>>&);

	template<class Type>
	tmp<Field<Type>> transform(const tmp<symmTensorField>&, const Field<Type>&);

	template<class Type>
	tmp<Field<Type>> transform
	(
		const tmp<symmTensorField>&,
		const tmp<Field<Type>>&
	);


	template<class Type>
	void transform(Field<Type>&, const tensor&, const Field<Type>&);

	template<class Type>
	tmp<Field<Type>> transform(const tensor&, const Field<Type>&);

	template<class Type>
	tmp<Field<Type>> transform(const tensor&, const tmp<Field<Type>>&);


	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const symmTensorField&
			);

	template<>
	tmp<Field<sphericalTensor>> transformFieldMask<sphericalTensor>
		(
			const tmp<symmTensorField>&
			);


	template<>
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const symmTensorField&
			);

	template<>
	tmp<Field<symmTensor>> transformFieldMask<symmTensor>
		(
			const tmp<symmTensorField>&
			);


	template<>
	tmp<Field<tensor>> transformFieldMask<tensor>
		(
			const symmTensorField&
			);

	template<>
	tmp<Field<tensor>> transformFieldMask<tensor>
		(
			const tmp<symmTensorField>&
			);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <symmTransformFieldI.hxx>

//#ifdef NoRepository
//#include <symmTransformField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmTransformField_Header
