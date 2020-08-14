#pragma once
#ifndef _thermoPhysicsTypes_Header
#define _thermoPhysicsTypes_Header

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
	tnbLib::thermoPhysicsTypes

Description
	Type definitions for thermo-physics models

\*---------------------------------------------------------------------------*/

#include <specie.hxx>
#include <perfectGas.hxx>
#include <incompressiblePerfectGas.hxx>
#include <perfectFluid.hxx>
#include <adiabaticPerfectFluid.hxx>
#include <rhoConst.hxx>
#include <hConstThermo.hxx>
#include <eConstThermo.hxx>
#include <janafThermo.hxx>

#include <sensibleEnthalpy.hxx>
#include <sensibleInternalEnergy.hxx>
#include <sutherlandTransport.hxx>
#include <constTransport.hxx>

#include <icoPolynomial.hxx>
#include <hPolynomialThermo.hxx>
#include <polynomialTransport.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// thermo physics types based on sensibleEnthalpy
	typedef
		constTransport
		<
		species::thermo
		<
		hConstThermo
		<
		perfectGas<specie>
		>,
		sensibleEnthalpy
		>
		> constGasHThermoPhysics;

	typedef
		sutherlandTransport
		<
		species::thermo
		<
		janafThermo
		<
		perfectGas<specie>
		>,
		sensibleEnthalpy
		>
		> gasHThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		hConstThermo
		<
		incompressiblePerfectGas<specie>
		>,
		sensibleEnthalpy
		>
		> constIncompressibleGasHThermoPhysics;

	typedef
		sutherlandTransport
		<
		species::thermo
		<
		janafThermo
		<
		incompressiblePerfectGas<specie>
		>,
		sensibleEnthalpy
		>
		> incompressibleGasHThermoPhysics;

	typedef
		polynomialTransport
		<
		species::thermo
		<
		hPolynomialThermo
		<
		icoPolynomial<specie, 8>,
		8
		>,
		sensibleEnthalpy
		>,
		8
		> icoPoly8HThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		hConstThermo
		<
		perfectFluid<specie>
		>,
		sensibleEnthalpy
		>
		>
		constFluidHThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		hConstThermo
		<
		adiabaticPerfectFluid<specie>
		>,
		sensibleEnthalpy
		>
		>
		constAdiabaticFluidHThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		hConstThermo
		<
		rhoConst<specie>
		>,
		sensibleEnthalpy
		>
		>
		constHThermoPhysics;


	// thermo physics types based on sensibleInternalEnergy
	typedef
		constTransport
		<
		species::thermo
		<
		eConstThermo
		<
		perfectGas<specie>
		>,
		sensibleInternalEnergy
		>
		> constGasEThermoPhysics;

	typedef
		sutherlandTransport
		<
		species::thermo
		<
		janafThermo
		<
		perfectGas<specie>
		>,
		sensibleInternalEnergy
		>
		> gasEThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		eConstThermo
		<
		incompressiblePerfectGas<specie>
		>,
		sensibleInternalEnergy
		>
		> constIncompressibleGasEThermoPhysics;

	typedef
		sutherlandTransport
		<
		species::thermo
		<
		janafThermo
		<
		incompressiblePerfectGas<specie>
		>,
		sensibleInternalEnergy
		>
		> incompressibleGasEThermoPhysics;

	typedef
		polynomialTransport
		<
		species::thermo
		<
		hPolynomialThermo
		<
		icoPolynomial<specie, 8>,
		8
		>,
		sensibleInternalEnergy
		>,
		8
		> icoPoly8EThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		eConstThermo
		<
		perfectFluid<specie>
		>,
		sensibleInternalEnergy
		>
		>
		constFluidEThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		eConstThermo
		<
		adiabaticPerfectFluid<specie>
		>,
		sensibleInternalEnergy
		>
		>
		constAdiabaticFluidEThermoPhysics;

	typedef
		constTransport
		<
		species::thermo
		<
		eConstThermo
		<
		rhoConst<specie>
		>,
		sensibleInternalEnergy
		>
		>
		constEThermoPhysics;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thermoPhysicsTypes_Header
