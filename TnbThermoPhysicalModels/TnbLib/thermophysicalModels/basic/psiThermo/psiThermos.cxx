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

\*---------------------------------------------------------------------------*/

#include <makeThermo.hxx>
#include <psiThermo.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <PengRobinsonGas.hxx>
#include <hConstThermo.hxx>
#include <eConstThermo.hxx>
#include <janafThermo.hxx>
#include <sensibleEnthalpy.hxx>
#include <sensibleInternalEnergy.hxx>
#include <thermo.hxx>

#include <constTransport.hxx>
#include <sutherlandTransport.hxx>

#include <hPolynomialThermo.hxx>
#include <polynomialTransport.hxx>

#include <hePsiThermo.hxx>
#include <pureMixture.hxx>

#include <thermoPhysicsTypes.hxx>

#include <addToRunTimeSelectionTable.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * * * Enthalpy-based * * * * * * * * * * * * * */

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		constTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		hConstThermo,
		PengRobinsonGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		polynomialTransport,
		sensibleEnthalpy,
		hPolynomialThermo,
		PengRobinsonGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		polynomialTransport,
		sensibleEnthalpy,
		janafThermo,
		PengRobinsonGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleEnthalpy,
		janafThermo,
		PengRobinsonGas,
		specie
	);


	/* * * * * * * * * * * * * * Internal-energy-based * * * * * * * * * * * * * */

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		eConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		eConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		constTransport,
		sensibleInternalEnergy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		hConstThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		perfectGas,
		specie
	);

	makeThermos
	(
		psiThermo,
		hePsiThermo,
		pureMixture,
		sutherlandTransport,
		sensibleInternalEnergy,
		janafThermo,
		PengRobinsonGas,
		specie
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //