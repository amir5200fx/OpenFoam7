#pragma once
#ifndef _tensorField_Header
#define _tensorField_Header

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
	tnbLib::tensorField

Description
	Specialisation of Field\<T\> for tensor.

SourceFiles
	tensorField.C

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <vectorField.hxx>
#include <sphericalTensorField.hxx>
#include <symmTensorField.hxx>
#include <tensor.hxx>

//#define TEMPLATE
//#include <FieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	typedef Field<tensor> tensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	
	void tr(Field<scalar>& res, const UList<tensor>& f);
	tmp<Field<scalar>> tr(const UList<tensor>& f);
	tmp<Field<scalar>> tr(const tmp<Field<tensor>>& tf);
		
	void sph(Field<sphericalTensor>& res, const UList<tensor>& f);
	tmp<Field<sphericalTensor>> sph(const UList<tensor>& f);
	tmp<Field<sphericalTensor>> sph(const tmp<Field<tensor>>& tf);
		
	void symm(Field<symmTensor>& res, const UList<tensor>& f);
	tmp<Field<symmTensor>> symm(const UList<tensor>& f);
	tmp<Field<symmTensor>> symm(const tmp<Field<tensor>>& tf);
		
	void twoSymm(Field<symmTensor>& res, const UList<tensor>& f);
	tmp<Field<symmTensor>> twoSymm(const UList<tensor>& f);
	tmp<Field<symmTensor>> twoSymm(const tmp<Field<tensor>>& tf);
		
	void skew(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> skew(const UList<tensor>& f);
	tmp<Field<tensor>> skew(const tmp<Field<tensor>>& tf);
		
	void dev(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> dev(const UList<tensor>& f);
	tmp<Field<tensor>> dev(const tmp<Field<tensor>>& tf);
		
	void dev2(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> dev2(const UList<tensor>& f);
	tmp<Field<tensor>> dev2(const tmp<Field<tensor>>& tf);
		
	void det(Field<scalar>& res, const UList<tensor>& f);
	tmp<Field<scalar>> det(const UList<tensor>& f);
	tmp<Field<scalar>> det(const tmp<Field<tensor>>& tf);
		
	void cof(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> cof(const UList<tensor>& f);
	tmp<Field<tensor>> cof(const tmp<Field<tensor>>& tf);
		
	void inv(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> inv(const UList<tensor>& f);
	tmp<Field<tensor>> inv(const tmp<Field<tensor>>& tf);
		
	void eigenValues(Field<vector>& res, const UList<tensor>& f);
	tmp<Field<vector>> eigenValues(const UList<tensor>& f);
	tmp<Field<vector>> eigenValues(const tmp<Field<tensor>>& tf);
		
	void eigenVectors(Field<tensor>& res, const UList<tensor>& f);
	tmp<Field<tensor>> eigenVectors(const UList<tensor>& f);
	tmp<Field<tensor>> eigenVectors(const tmp<Field<tensor>>& tf);

		 
	void eigenValues(Field<vector>& res, const UList<symmTensor>& f);
	tmp<Field<vector>> eigenValues(const UList<symmTensor>& f);
	tmp<Field<vector>> eigenValues(const tmp<Field<symmTensor>>& tf);
		
	void eigenVectors(Field<tensor>& res, const UList<symmTensor>& f);
	tmp<Field<tensor>> eigenVectors(const UList<symmTensor>& f);
	tmp<Field<tensor>> eigenVectors(const tmp<Field<symmTensor>>& tf);


		// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

		
	void hdual(Field<vector>& res, const UList<tensor>& f);
	tmp<Field<vector>> operator *(const UList<tensor>& f);
	tmp<Field<vector>> operator *(const tmp<Field<tensor>>& tf);
		
	void hdual(Field<tensor>& res, const UList<vector>& f);
	tmp<Field<tensor>> operator *(const UList<vector>& f);
	tmp<Field<tensor>> operator *(const tmp<Field<vector>>& tf);

		
	void divide(Field<vector>& f, const UList<vector>& f1, const UList<tensor>& f2);
	tmp<Field<vector>> operator /(const UList<vector>& f1, const UList<tensor>& f2);
	tmp<Field<vector>> operator /(const UList<vector>& f1, const tmp<Field<tensor>>& tf2);
	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const UList<tensor>& f2);
	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const tmp<Field<tensor>>& tf2);
		
	void divide(Field<vector>& f, const vector& s1, const UList<tensor>& f2);
	tmp<Field<vector>> operator /(const vector& s1, const UList<tensor>& f2);
	tmp<Field<vector>> operator /(const vector& s1, const tmp<Field<tensor>>& tf2);
	void divide(Field<vector>& f, const UList<vector>& f1, const tensor& s2);
	tmp<Field<vector>> operator /(const UList<vector>& f1, const tensor& s2);
	tmp<Field<vector>> operator /(const tmp<Field<vector>>& tf1, const tensor& s2);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#include <undefFieldFunctionsM.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tensorField_Header
