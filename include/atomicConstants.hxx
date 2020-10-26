#pragma once
#ifndef _atomicConstants_Header
#define _atomicConstants_Header

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
	tnbLib::constant::atomic

Description
	Atomic constants

\*---------------------------------------------------------------------------*/

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{
		namespace atomic
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

				//- Group name for atomic constants
			FoamBase_EXPORT extern const char* const group;

			//- Fine-structure constant: default SI units: []
			FoamBase_EXPORT extern const dimensionedScalar alpha;

			//- Rydberg constant: default SI units: [1/m]
			FoamBase_EXPORT extern const dimensionedScalar Rinf;

			//- Bohr radius: default SI units: [m]
			FoamBase_EXPORT extern const dimensionedScalar a0;

			//- Classical electron radius: default SI units: [m]
			FoamBase_EXPORT extern const dimensionedScalar re;

			//- Hartree energy: default SI units: [J]
			FoamBase_EXPORT extern const dimensionedScalar Eh;


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace atomic
	} // End namespace constant
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_atomicConstants_Header
