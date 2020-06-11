#pragma once
#ifndef _mathematicalConstants_Header
#define _mathematicalConstants_Header

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

Namespace
	tnbLib::constant::mathematical

Description
	mathematical constants.

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>

#include <corecrt_math_defines.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{
		namespace mathematical
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			static const char* const group = "mathematical";

			const scalar e(M_E);
			const scalar pi(M_PI);
			const scalar twoPi(2 * pi);
			const scalar piByTwo(0.5*pi);

			//- Euler's constant
			const scalar Eu(0.57721566490153286060651209);

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace mathematical
	} // End namespace constant

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mathematicalConstants_Header
