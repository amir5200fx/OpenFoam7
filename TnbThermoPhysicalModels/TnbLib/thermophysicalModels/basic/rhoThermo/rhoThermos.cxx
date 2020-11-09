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

\*---------------------------------------------------------------------------*/

#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <rhoThermo.hxx>
#include <makeThermo.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <incompressiblePerfectGas.hxx>
#include <Boussinesq.hxx>
#include <rhoConst.hxx>
#include <perfectFluid.hxx>
#include <PengRobinsonGas.hxx>
#include <adiabaticPerfectFluid.hxx>

#include <hConstThermo.hxx>
#include <eConstThermo.hxx>
#include <janafThermo.hxx>
#include <sensibleEnthalpy.hxx>
#include <sensibleInternalEnergy.hxx>
#include <thermo.hxx>

#include <constTransport.hxx>
#include <sutherlandTransport.hxx>
#include <WLFTransport.hxx>

#include <icoPolynomial.hxx>
#include <hPolynomialThermo.hxx>
#include <polynomialTransport.hxx>

#include <heRhoThermo.hxx>
#include <pureMixture.hxx>

#include <addToRunTimeSelectionTable.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		rhoConst,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		adiabaticPerfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		polynomialTransport,
		sensibleEnthalpy,
		hPolynomialThermo,
		icoPolynomial,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		PengRobinsonGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		polynomialTransport,
		sensibleEnthalpy,
		hPolynomialThermo,
		PengRobinsonGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		polynomialTransport,
		sensibleEnthalpy,
		janafThermo,
		PengRobinsonGas,
		specie
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		rhoConst,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		eConstThermo,
		rhoConst,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		perfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		eConstThermo,
		perfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		adiabaticPerfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		eConstThermo,
		adiabaticPerfectFluid,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		polynomialTransport,
		sensibleInternalEnergy,
		hPolynomialThermo,
		icoPolynomial,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		hConstThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		incompressiblePerfectGas,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		eConstThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		hConstThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		Boussinesq,
		specie
	);

	makeThermos
	(
		rhoThermo,
		heRhoThermo,
		pureMixture,
		WLFTransport,
		sensibleInternalEnergy,
		eConstThermo,
		rhoConst,
		specie
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //