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

#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <makeChemistrySolverTypes.hxx>

#include <thermoPhysicsTypes.hxx>
#include <psiReactionThermo.hxx>
#include <rhoReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// Chemistry solvers based on sensibleEnthalpy
	typedef noChemistrySolver<StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	noChemistrySolverpsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word noChemistrySolverpsiReactionThermoconstGasHThermoPhysics::typeName(
		("noChemistrySolver""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) +
			"<" + word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int noChemistrySolverpsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("noChemistrySolver""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) +
			"<" + word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<noChemistrySolverpsiReactionThermoconstGasHThermoPhysics>
	tnbLib::RegisterDebugSwitch<noChemistrySolverpsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("noChemistrySolver""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) +
			"<" + word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<
		noChemistrySolverpsiReactionThermoconstGasHThermoPhysics>
	addnoChemistrySolverpsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;
	typedef noChemistrySolver<TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics::typeName(
		("noChemistrySolver""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("noChemistrySolver""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics>
	tnbLib::RegisterDebugSwitch<TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("noChemistrySolver""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<
		TDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysics>
	addTDACnoChemistrySolverpsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;
	;
	typedef EulerImplicit<StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	EulerImplicitpsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word EulerImplicitpsiReactionThermoconstGasHThermoPhysics::typeName(
		("EulerImplicit""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int EulerImplicitpsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("EulerImplicit""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<EulerImplicitpsiReactionThermoconstGasHThermoPhysics> tnbLib::RegisterDebugSwitch<
		EulerImplicitpsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("EulerImplicit""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<"
			+ word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<
		EulerImplicitpsiReactionThermoconstGasHThermoPhysics>
	addEulerImplicitpsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;
	typedef EulerImplicit<TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics::typeName(
		("EulerImplicit""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("EulerImplicit""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics>
	tnbLib::RegisterDebugSwitch<TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("EulerImplicit""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<
		TDACEulerImplicitpsiReactionThermoconstGasHThermoPhysics>
	addTDACEulerImplicitpsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;
	;
	typedef ode<StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	odepsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word odepsiReactionThermoconstGasHThermoPhysics::typeName(
		("ode""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int odepsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("ode""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<odepsiReactionThermoconstGasHThermoPhysics> tnbLib::RegisterDebugSwitch<
		odepsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("ode""<" + word(StandardChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<odepsiReactionThermoconstGasHThermoPhysics>
	addodepsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;
	typedef ode<TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>>
	TDACodepsiReactionThermoconstGasHThermoPhysics;
	template <>
	const ::tnbLib::word TDACodepsiReactionThermoconstGasHThermoPhysics::typeName(
		("ode""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	template <>
	int TDACodepsiReactionThermoconstGasHThermoPhysics::debug(::tnbLib::debug::debugSwitch(
		("ode""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str(), 0));
	template <>
	const tnbLib::RegisterDebugSwitch<TDACodepsiReactionThermoconstGasHThermoPhysics> tnbLib::RegisterDebugSwitch<
		TDACodepsiReactionThermoconstGasHThermoPhysics>::registerDebugSwitch(
		("ode""<" + word(TDACChemistryModel<psiReactionThermo, constGasHThermoPhysics>::typeName_()) + "<" +
			word(psiReactionThermo::typeName_()) + "," + constGasHThermoPhysics::typeName() + ">>").c_str());
	BasicChemistryModel<psiReactionThermo>::addthermoConstructorToTable<TDACodepsiReactionThermoconstGasHThermoPhysics>
	addTDACodepsiReactionThermoconstGasHThermoPhysicsthermoConstructorToBasicChemistryModelpsiReactionThermoTable_;;;
	makeChemistrySolverTypes(psiReactionThermo, gasHThermoPhysics);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		constIncompressibleGasHThermoPhysics
	);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		incompressibleGasHThermoPhysics
	);
	makeChemistrySolverTypes(psiReactionThermo, icoPoly8HThermoPhysics);
	makeChemistrySolverTypes(psiReactionThermo, constFluidHThermoPhysics);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		constAdiabaticFluidHThermoPhysics
	);
	makeChemistrySolverTypes(psiReactionThermo, constHThermoPhysics);

	makeChemistrySolverTypes(rhoReactionThermo, constGasHThermoPhysics);
	makeChemistrySolverTypes(rhoReactionThermo, gasHThermoPhysics);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		constIncompressibleGasHThermoPhysics
	);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		incompressibleGasHThermoPhysics
	);
	makeChemistrySolverTypes(rhoReactionThermo, icoPoly8HThermoPhysics);
	makeChemistrySolverTypes(rhoReactionThermo, constFluidHThermoPhysics);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		constAdiabaticFluidHThermoPhysics
	);
	makeChemistrySolverTypes(rhoReactionThermo, constHThermoPhysics);

	// Chemistry solvers based on sensibleInternalEnergy
	makeChemistrySolverTypes(psiReactionThermo, constGasEThermoPhysics);
	makeChemistrySolverTypes(psiReactionThermo, gasEThermoPhysics);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		constIncompressibleGasEThermoPhysics
	);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		incompressibleGasEThermoPhysics
	);
	makeChemistrySolverTypes(psiReactionThermo, icoPoly8EThermoPhysics);
	makeChemistrySolverTypes(psiReactionThermo, constFluidEThermoPhysics);
	makeChemistrySolverTypes
	(
		psiReactionThermo,
		constAdiabaticFluidEThermoPhysics
	);
	makeChemistrySolverTypes(psiReactionThermo, constEThermoPhysics);

	makeChemistrySolverTypes(rhoReactionThermo, constGasEThermoPhysics);
	makeChemistrySolverTypes(rhoReactionThermo, gasEThermoPhysics);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		constIncompressibleGasEThermoPhysics
	);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		incompressibleGasEThermoPhysics
	);
	makeChemistrySolverTypes(rhoReactionThermo, icoPoly8EThermoPhysics);
	makeChemistrySolverTypes(rhoReactionThermo, constFluidEThermoPhysics);
	makeChemistrySolverTypes
	(
		rhoReactionThermo,
		constAdiabaticFluidEThermoPhysics
	);
	makeChemistrySolverTypes(rhoReactionThermo, constEThermoPhysics);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //