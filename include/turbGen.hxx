#pragma once
#ifndef _turbGen_Header
#define _turbGen_Header

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

Class
	tnbLib::turbGen

Description
	Generate a turbulent velocity field conforming to a given
	energy spectrum and being divergence free.

SourceFiles
	turbGen.C
	turbGenIO.C

\*---------------------------------------------------------------------------*/

#include <RandomProcesses_Module.hxx>
#include <Random.hxx>
#include <primitiveFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Kmesh;

	/*---------------------------------------------------------------------------*\
							   Class turbGen Declaration
	\*---------------------------------------------------------------------------*/

	class turbGen
	{
		// Private Data

		const Kmesh& K;
		const scalar Ea;
		const scalar k0;
		Random RanGen;


	public:

		// Constructors

			//- Construct from components
		FoamRandomProcesses_EXPORT turbGen(const Kmesh& k, const scalar EA, const scalar K0);


		// Member Functions

			//- Generate and return a velocity field
		FoamRandomProcesses_EXPORT vectorField U();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbGen_Header
