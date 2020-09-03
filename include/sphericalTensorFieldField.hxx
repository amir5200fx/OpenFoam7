#pragma once
#ifndef _sphericalTensorFieldField_Header
#define _sphericalTensorFieldField_Header

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
	tnbLib::sphericalTensorFieldField

Description
	Specialisation of FieldField<Field, T> for sphericalTensor.

SourceFiles
	sphericalTensorFieldField.C

\*---------------------------------------------------------------------------*/

#include <FieldField.hxx>
#include <sphericalTensor.hxx>

//#define TEMPLATE template<template<class> class Field>
//#include <FieldFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template <template<class> class Field>
	void tr(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> tr(const tmp<FieldField<Field, sphericalTensor>>& tf);
		
	template <template<class> class Field>
	void sph(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> sph(const tmp<FieldField<Field, sphericalTensor>>& tf);
		
	template <template<class> class Field>
	void det(FieldField<Field, scalar>& res, const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, scalar>> det(const tmp<FieldField<Field, sphericalTensor>>& tf);
		
	template <template<class> class Field>
	void inv(FieldField<Field, sphericalTensor>& res, const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> inv(const FieldField<Field, sphericalTensor>& f);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> inv(const tmp<FieldField<Field, sphericalTensor>>& tf);


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1,
	            const FieldField<Field, sphericalTensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1,
	                                                   const FieldField<Field, sphericalTensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1,
	                                                   const tmp<FieldField<Field, sphericalTensor>>& tf2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
	                                                   const FieldField<Field, sphericalTensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
	                                                   const tmp<FieldField<Field, sphericalTensor>>& tf2);
		
	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const scalar& s1, const FieldField<Field, sphericalTensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s1, const FieldField<Field, sphericalTensor>& f2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const scalar& s1,
	                                                   const tmp<FieldField<Field, sphericalTensor>>& tf2);
	template <template<class> class Field>
	void divide(FieldField<Field, sphericalTensor>& f, const FieldField<Field, scalar>& f1, const sphericalTensor& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const FieldField<Field, scalar>& f1, const sphericalTensor& s2);
	template <template<class> class Field>
	tmp<FieldField<Field, sphericalTensor>> operator /(const tmp<FieldField<Field, scalar>>& tf1,
	                                                   const sphericalTensor& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

#include <sphericalTensorFieldFieldI.hxx>

//#ifdef NoRepository
//#include <sphericalTensorFieldField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sphericalTensorFieldField_Header
