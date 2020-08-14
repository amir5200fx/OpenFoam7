#pragma once
#ifndef _moleFractionsFunctionObjects_Header
#define _moleFractionsFunctionObjects_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::psiReactionThermoMoleFractionsFunctionObject

Description
	Instantiate the moleFractions functionObject for psiReactionThermo

Typedef
	tnbLib::rhoReactionThermoMoleFractionsFunctionObject

Description
	Instantiate the moleFractions functionObject for rhoReactionThermo

SourceFiles
	moleFractionsFunctionObjects.C

\*---------------------------------------------------------------------------*/

#include <moleFractions.hxx>
#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef moleFractions<psiReactionThermo>
		psiReactionThermoMoleFractionsFunctionObject;

	typedef moleFractions<rhoReactionThermo>
		rhoReactionThermoMoleFractionsFunctionObject;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_moleFractionsFunctionObjects_Header
