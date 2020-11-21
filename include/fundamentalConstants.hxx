#pragma once
#ifndef _fundamentalConstants_Header
#define _fundamentalConstants_Header

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

Description
	Fundamental dimensioned constants

\*---------------------------------------------------------------------------*/

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		namespace universal
		{
			//- Speed of light in a vacuum
			FoamBase_EXPORT extern const dimensionedScalar c;

			//- Newtonian constant of gravitation
			FoamBase_EXPORT extern const dimensionedScalar G;

			//- Planck constant
			FoamBase_EXPORT extern const dimensionedScalar h;
		}

		namespace electromagnetic
		{
			//- Elementary charge
			FoamBase_EXPORT extern const dimensionedScalar e;
		}

		namespace atomic
		{
			//- Electron mass
			FoamBase_EXPORT extern const dimensionedScalar me;

			//- Proton mass
			FoamBase_EXPORT extern const dimensionedScalar mp;
		}

		namespace physicoChemical
		{
			//- Atomic mass unit
			FoamBase_EXPORT extern const dimensionedScalar mu;

			//- Avagadro number
			FoamBase_EXPORT extern const dimensionedScalar NA;

			//- Boltzmann constant
			FoamBase_EXPORT extern const dimensionedScalar k;
		}

		namespace standard
		{
			//- Standard pressure
			FoamBase_EXPORT extern const dimensionedScalar Pstd;

			//- Standard temperature
			FoamBase_EXPORT extern const dimensionedScalar Tstd;
		}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fundamentalConstants_Header
