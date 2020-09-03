#pragma once
#ifndef _tensorFieldField_Header
#define _tensorFieldField_Header

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
	tnbLib::tensorFieldField

Description
	Specialisation of FieldField\<T\> for tensor.

SourceFiles
	tensorFieldField.C

\*---------------------------------------------------------------------------*/

#include <sphericalTensorFieldField.hxx>
#include <symmTensorFieldField.hxx>
#include <tensor.hxx>

//#define TEMPLATE template<template<class> class Field>
//#include <FieldFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class Field>
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void symm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> symm(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void twoSymm(FieldField<Field, symmTensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> twoSymm(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void skew(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> skew(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> skew(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void dev(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> dev(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> dev(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void dev2(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> dev2(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> dev2(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void det(FieldField<Field, scalar>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void cof(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> cof(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> cof(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void inv(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> inv(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> inv(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void eigenVectors(FieldField<Field, tensor>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> eigenVectors(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> eigenVectors(const tmp<FieldField<Field, tensor>>& tf);

		
	template <template<class> class Field>
	void eigenValues(FieldField<Field, vector>& res, const FieldField<Field, symmTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const FieldField<Field, symmTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> eigenValues(const tmp<FieldField<Field, symmTensor>>& tf);
		
	template <template<class> class Field>
	void eigenVectors(FieldField<Field, symmTensor>& res, const FieldField<Field, symmTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> eigenVectors(const FieldField<Field, symmTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, symmTensor>> eigenVectors(const tmp<FieldField<Field, symmTensor>>& tf);

		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <template<class> class Field>
	void hdual(FieldField<Field, vector>& res, const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const FieldField<Field, tensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator *(const tmp<FieldField<Field, tensor>>& tf);
		
	template <template<class> class Field>
	void hdual(FieldField<Field, tensor>& res, const FieldField<Field, vector>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> operator *(const FieldField<Field, vector>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, tensor>> operator *(const tmp<FieldField<Field, vector>>& tf);

		
	template <template<class> class Field>
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const FieldField<Field, tensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1,
	                                          const tmp<FieldField<Field, tensor>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1,
	                                          const FieldField<Field, tensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1,
	                                          const tmp<FieldField<Field, tensor>>& tf2);
		
	template <template<class> class Field>
	void divide(FieldField<Field, vector>& f, const vector& s1, const FieldField<Field, tensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const vector& s1, const FieldField<Field, tensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const vector& s1, const tmp<FieldField<Field, tensor>>& tf2);
	template <template<class> class Field>
	void divide(FieldField<Field, vector>& f, const FieldField<Field, vector>& f1, const tensor& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const FieldField<Field, vector>& f1, const tensor& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, vector>> operator /(const tmp<FieldField<Field, vector>>& tf1, const tensor& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <tensorFieldFieldI.hxx>

//#ifdef NoRepository
//#include <tensorFieldField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tensorFieldField_Header
