#pragma once
#ifndef _labelField_Header
#define _labelField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::labelField

Description
	Specialisation of Field\<T\> for label.

SourceFiles
	labelField.C

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <Field.hxx>

//#define TEMPLATE
//#include <FieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	typedef Field<label> labelField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	 
	FoamBase_EXPORT void mag(Field<label>& res, const UList<label>& f);
	FoamBase_EXPORT tmp<Field<label>> mag(const UList<label>& f);
	FoamBase_EXPORT tmp<Field<label>> mag(const tmp<Field<label>>& tf);	
	 
	FoamBase_EXPORT void add(Field<label>& f, const label& s1, const UList<label>& f2);
	FoamBase_EXPORT tmp<Field<label>> operator +(const label& s1, const UList<label>& f2);
	FoamBase_EXPORT tmp<Field<label>> operator +(const label& s1, const tmp<Field<label>>& tf2);
	FoamBase_EXPORT void add(Field<label>& f, const UList<label>& f1, const label& s2);
	FoamBase_EXPORT tmp<Field<label>> operator +(const UList<label>& f1, const label& s2);
	FoamBase_EXPORT tmp<Field<label>> operator +(const tmp<Field<label>>& tf1, const label& s2);
		
	FoamBase_EXPORT void subtract(Field<label>& f, const label& s1, const UList<label>& f2);
	FoamBase_EXPORT tmp<Field<label>> operator -(const label& s1, const UList<label>& f2);
	FoamBase_EXPORT tmp<Field<label>> operator -(const label& s1, const tmp<Field<label>>& tf2);
	FoamBase_EXPORT void subtract(Field<label>& f, const UList<label>& f1, const label& s2);
	FoamBase_EXPORT tmp<Field<label>> operator -(const UList<label>& f1, const label& s2);
	FoamBase_EXPORT tmp<Field<label>> operator -(const tmp<Field<label>>& tf1, const label& s2);


		
	template<>
	FoamBase_EXPORT tmp<labelField> labelField::component(const direction) const;

	template<>
	FoamBase_EXPORT void component
	(
		labelField& lf,
		const labelUList& f,
		const direction
	);

	template<>
	FoamBase_EXPORT void labelField::replace(const direction, const labelUList& lf);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_labelField_Header
