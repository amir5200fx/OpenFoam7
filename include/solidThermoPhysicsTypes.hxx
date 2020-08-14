#pragma once
#ifndef _solidThermoPhysicsTypes_Header
#define _solidThermoPhysicsTypes_Header

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

Typedefs
	tnbLib::solidThermoPhysicsTypes

Description
	Type definitions for solid-thermo-physics models

\*---------------------------------------------------------------------------*/

#include <specie.hxx>
#include <rhoConst.hxx>
#include <hConstThermo.hxx>
#include <hPolynomialThermo.hxx>
#include <hPowerThermo.hxx>
#include <constIsoSolidTransport.hxx>
#include <constAnIsoSolidTransport.hxx>
#include <exponentialSolidTransport.hxx>
#include <polynomialSolidTransport.hxx>

#include <sensibleEnthalpy.hxx>
#include <thermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef
		constIsoSolidTransport
		<
		species::thermo
		<
		hConstThermo
		<
		rhoConst<specie>
		>,
		sensibleEnthalpy
		>
		> hConstSolidThermoPhysics;

	typedef
		exponentialSolidTransport
		<
		species::thermo
		<
		hPowerThermo
		<
		rhoConst<specie>
		>,
		sensibleEnthalpy
		>
		> hPowerSolidThermoPhysics;

	typedef
		polynomialSolidTransport
		<
		species::thermo
		<
		hPolynomialThermo
		<
		rhoConst<specie>,
		8
		>,
		sensibleEnthalpy
		>,
		8
		> hTransportThermoPoly8SolidThermoPhysics;

	typedef
		constIsoSolidTransport
		<
		species::thermo
		<
		hPowerThermo
		<
		rhoConst<specie>
		>,
		sensibleEnthalpy
		>
		> hExpKappaConstSolidThermoPhysics;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidThermoPhysicsTypes_Header
