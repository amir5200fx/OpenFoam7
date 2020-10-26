#pragma once
#ifndef _flipOp_Header
#define _flipOp_Header

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

Class
	tnbLib::flipOp

Description
	Class containing functor to negate primitives. Dummy for all other types.

	Used in mesh transformations where face can flip.

SourceFiles
	flipOp.C

\*---------------------------------------------------------------------------*/

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class flipOp Declaration
	\*---------------------------------------------------------------------------*/

	class flipOp
	{
	public:

		template<class Type>
		Type operator()(const Type& val) const
		{
			return val;
		}
	};


	class noOp
	{
	public:

		template<class Type>
		Type operator()(const Type& val) const
		{
			return val;
		}
	};


	class flipLabelOp
	{
	public:

		label operator()(const label& val) const
		{
			return -val;
		}
	};


	// Template specialisation for primitives that support negation
	template<> FoamBase_EXPORT scalar flipOp::operator()(const scalar&) const;
	template<> FoamBase_EXPORT vector flipOp::operator()(const vector&) const;
	template<> FoamBase_EXPORT sphericalTensor flipOp::operator()(const sphericalTensor&) const;
	template<> FoamBase_EXPORT symmTensor flipOp::operator()(const symmTensor&) const;
	template<> FoamBase_EXPORT tensor flipOp::operator()(const tensor&) const;
	template<> FoamBase_EXPORT triad flipOp::operator()(const triad&) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_flipOp_Header
