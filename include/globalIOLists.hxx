#pragma once
#ifndef _globalIOLists_Header
#define _globalIOLists_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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
	tnbLib::globalIOLists

Description
	Typedefs for globalIOLists of primitive types. These are fully compatible
	with 'normal' IOLists except have global filePath() scope.

\*---------------------------------------------------------------------------*/

#include <primitiveFields.hxx>
#include <GlobalIOList.hxx>

// added by amir
#include <vector.hxx>
#include <sphericalTensor.hxx>
#include <symmTensor.hxx>
#include <tensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef GlobalIOList<label> labelGlobalIOList;
	typedef GlobalIOList<scalar> scalarGlobalIOList;
	typedef GlobalIOList<vector> vectorGlobalIOList;
	typedef GlobalIOList<sphericalTensor> sphericalTensorGlobalIOList;
	typedef GlobalIOList<symmTensor> symmTensorGlobalIOList;
	typedef GlobalIOList<tensor> tensorGlobalIOList;

	//- Template function for obtaining global status
	template<>
	inline bool typeGlobal<labelGlobalIOList>()
	{
		return true;
	}
	template<>
	inline bool typeGlobal<scalarGlobalIOList>()
	{
		return true;
	}
	template<>
	inline bool typeGlobal<vectorGlobalIOList>()
	{
		return true;
	}
	template<>
	inline bool typeGlobal<sphericalTensorGlobalIOList>()
	{
		return true;
	}
	template<>
	inline bool typeGlobal<symmTensorGlobalIOList>()
	{
		return true;
	}
	template<>
	inline bool typeGlobal<tensorGlobalIOList>()
	{
		return true;
	}

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_globalIOLists_Header
