#pragma once
#ifndef _basicSpecieMixture_Header
#define _basicSpecieMixture_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::basicSpecieMixture

Description
	Specialization of basicMultiComponentMixture for a mixture consisting
	of a number for molecular species.

SourceFiles
	basicSpecieMixture.C

\*---------------------------------------------------------------------------*/

#include <basicMultiComponentMixture.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class basicSpecieMixture Declaration
	\*---------------------------------------------------------------------------*/

	class basicSpecieMixture
		:
		public basicMultiComponentMixture
	{

	public:

		//- Run time type information
		//TypeName("basicSpecieMixture");
		static const char* typeName_() { return "basicSpecieMixture"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- The base class of the mixture
		typedef basicSpecieMixture basicMixtureType;


		// Constructors

			//- Construct from dictionary, species names, mesh and phase name
		FoamThermophysicalModels_EXPORT basicSpecieMixture
		(
			const dictionary&,
			const wordList& specieNames,
			const fvMesh&,
			const word&
		);


		//- Destructor
		virtual ~basicSpecieMixture()
		{}


		// Member Functions

			// Per specie properties

				//- Molecular weight of the given specie [kg/kmol]
		FoamThermophysicalModels_EXPORT virtual scalar Wi(const label speciei) const = 0;


		// Per specie thermo properties

			//- Heat capacity at constant pressure [J/kg/K]
		FoamThermophysicalModels_EXPORT virtual scalar Cp
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Heat capacity at constant volume [J/kg/K]
		FoamThermophysicalModels_EXPORT virtual scalar Cv
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Absolute enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Ha
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Sensible enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Hs
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Chemical enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Hc(const label speciei) const = 0;

		//- Entropy [J/kg/K]
		FoamThermophysicalModels_EXPORT virtual scalar S
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Sensible internal energy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Es
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Gibbs free energy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar G
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Helmholtz free energy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar A
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;


		// Per specie transport properties

			//- Dynamic viscosity [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual scalar mu
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Thermal conductivity [W/m/K]
		FoamThermophysicalModels_EXPORT virtual scalar kappa
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Thermal diffusivity of enthalpy [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual scalar alphah
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;

		//- Density [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual scalar rho
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_basicSpecieMixture_Header
