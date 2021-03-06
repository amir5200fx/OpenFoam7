#pragma once
#ifndef _physicoChemicalConstants_Header
#define _physicoChemicalConstants_Header

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

Namespace
	tnbLib::constant::physicoChemical

Description
	Physico-chemical constants

\*---------------------------------------------------------------------------*/

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{
		namespace physicoChemical
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

				//- Group name for physico-chemical constants
			FoamBase_EXPORT extern const char* const group;

			//- Universal gas constant: default SI units: [J/mol/K]
			FoamBase_EXPORT extern const dimensionedScalar R;

			//- Faraday constant: default SI units: [C/mol]
			FoamBase_EXPORT extern const dimensionedScalar F;

			//- Stefan-Boltzmann constant: default SI units: [W/m^2/K^4]
			FoamBase_EXPORT extern const dimensionedScalar sigma;

			//- Wien displacement law constant: default SI units: [m K]
			FoamBase_EXPORT extern const dimensionedScalar b;

			//- First radiation constant: default SI units: [W/m^2]
			FoamBase_EXPORT extern const dimensionedScalar c1;

			//- Second radiation constant: default SI units: [m K]
			FoamBase_EXPORT extern const dimensionedScalar c2;

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace physicoChemical
	} // End namespace constant
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_physicoChemicalConstants_Header
