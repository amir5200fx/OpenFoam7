#pragma once
#ifndef _sphericalTensorField_Header
#define _sphericalTensorField_Header

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
	tnbLib::sphericalTensorField

Description
	Specialisation of Field\<T\> for sphericalTensor.

SourceFiles
	sphericalTensorField.C

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <sphericalTensor.hxx>

//#define TEMPLATE
//#include <FieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	typedef Field<sphericalTensor> sphericalTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void tr(Field<scalar>& res, const UList<sphericalTensor>& f);
	tmp<Field<scalar>> tr(const UList<sphericalTensor>& f);
	tmp<Field<scalar>> tr(const tmp<Field<sphericalTensor>>& tf);
		
	void sph(Field<sphericalTensor>& res, const UList<sphericalTensor>& f);
	tmp<Field<sphericalTensor>> sph(const UList<sphericalTensor>& f);
	tmp<Field<sphericalTensor>> sph(const tmp<Field<sphericalTensor>>& tf);
		
	void det(Field<scalar>& res, const UList<sphericalTensor>& f);
	tmp<Field<scalar>> det(const UList<sphericalTensor>& f);
	tmp<Field<scalar>> det(const tmp<Field<sphericalTensor>>& tf);
		
	void inv(Field<sphericalTensor>& res, const UList<sphericalTensor>& f);
	tmp<Field<sphericalTensor>> inv(const UList<sphericalTensor>& f);
	tmp<Field<sphericalTensor>> inv(const tmp<Field<sphericalTensor>>& tf);

		
	void divide(Field<sphericalTensor>& f, const UList<scalar>& f1, const UList<sphericalTensor>& f2);
	tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const UList<sphericalTensor>& f2);
	tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const tmp<Field<sphericalTensor>>& tf2);
	tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const UList<sphericalTensor>& f2);
	tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const tmp<Field<sphericalTensor>>& tf2);
		
	void divide(Field<sphericalTensor>& f, const scalar& s1, const UList<sphericalTensor>& f2);
	tmp<Field<sphericalTensor>> operator /(const scalar& s1, const UList<sphericalTensor>& f2);
	tmp<Field<sphericalTensor>> operator /(const scalar& s1, const tmp<Field<sphericalTensor>>& tf2);
	void divide(Field<sphericalTensor>& f, const UList<scalar>& f1, const sphericalTensor& s2);
	tmp<Field<sphericalTensor>> operator /(const UList<scalar>& f1, const sphericalTensor& s2);
	tmp<Field<sphericalTensor>> operator /(const tmp<Field<scalar>>& tf1, const sphericalTensor& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sphericalTensorField_Header
