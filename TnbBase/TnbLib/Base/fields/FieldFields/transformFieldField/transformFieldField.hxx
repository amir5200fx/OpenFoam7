#pragma once
#ifndef _transformFieldField_Header
#define _transformFieldField_Header

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

InNamespace
	tnbLib

Description
	transformFieldField
	Spatial transformation functions for FieldField.

SourceFiles
	transformFieldField.C

\*---------------------------------------------------------------------------*/

#include <transform.hxx>
#include <tensorFieldField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<template<class> class Field, class Type>
	void transform
	(
		FieldField<Field, Type>&,
		const FieldField<Field, tensor>&,
		const FieldField<Field, Type>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const FieldField<Field, tensor>&,
		const FieldField<Field, Type>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const FieldField<Field, tensor>&,
		const tmp<FieldField<Field, Type>>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tmp<FieldField<Field, tensor>>&,
		const FieldField<Field, Type>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tmp<FieldField<Field, tensor>>&,
		const tmp<FieldField<Field, Type>>&
	);


	template<template<class> class Field, class Type>
	void transform
	(
		FieldField<Field, Type>&,
		const tensor&,
		const FieldField<Field, Type>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tensor&,
		const FieldField<Field, Type>&
	);

	template<template<class> class Field, class Type>
	tmp<FieldField<Field, Type>> transform
	(
		const tensor&,
		const tmp<FieldField<Field, Type>>&
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <transformFieldFieldI.hxx>

//#ifdef NoRepository
//#include <transformFieldField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformFieldField_Header
