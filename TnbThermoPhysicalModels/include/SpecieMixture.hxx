#pragma once
#ifndef _SpecieMixture_Header
#define _SpecieMixture_Header

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
	tnbLib::SpecieMixture

Description
	tnbLib::SpecieMixture

SourceFiles
	SpecieMixture.C

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class dictionary;
	class fvMesh;


	/*---------------------------------------------------------------------------*\
						 Class SpecieMixture Declaration
	\*---------------------------------------------------------------------------*/

	template<class MixtureType>
	class SpecieMixture
		:
		public MixtureType
	{

	public:

		// Constructors

			//- Construct from dictionary, mesh and phase name
		SpecieMixture(const dictionary&, const fvMesh&, const word& phaseName);


		//- Destructor
		virtual ~SpecieMixture()
		{}


		// Member Functions

			// Per specie properties

				//- Molecular weight of the given specie [kg/kmol]
		virtual scalar Wi(const label speciei) const;


		// Per specie thermo properties

			//- Heat capacity at constant pressure [J/kg/K]
		virtual scalar Cp
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Heat capacity at constant volume [J/kg/K]
		virtual scalar Cv
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Absolute enthalpy [J/kg]
		virtual scalar Ha
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Sensible enthalpy [J/kg]
		virtual scalar Hs
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Chemical enthalpy [J/kg]
		virtual scalar Hc(const label speciei) const;

		//- Entropy [J/kg/K]
		virtual scalar S
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Sensible internal energy [J/kg]
		virtual scalar Es
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Gibbs free energy [J/kg]
		virtual scalar G
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Helmholtz free energy [J/kg]
		virtual scalar A
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;


		// Per specie transport properties

			//- Dynamic viscosity [kg/m/s]
		virtual scalar mu
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Thermal conductivity [W/m/K]
		virtual scalar kappa
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Thermal diffusivity of enthalpy [kg/m/s]
		virtual scalar alphah
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;

		//- Density [kg/m^3]
		virtual scalar rho
		(
			const label speciei,
			const scalar p,
			const scalar T
		) const;


		// Field properties abstract functions
		// provided here to avoid issues with inheritance of virtual functions
		// in heThermo

			//- Heat capacity at constant pressure for patch [J/kg/K]
		virtual tmp<scalarField> Cp
		(
			const scalarField& p,
			const scalarField& T,
			const label patchi
		) const = 0;

		//- Heat capacity at constant pressure for patch [J/kg/K]
		virtual tmp<volScalarField> Cp() const = 0;

		//- Heat capacity at constant volume for patch [J/kg/K]
		virtual tmp<scalarField> Cv
		(
			const scalarField& p,
			const scalarField& T,
			const label patchi
		) const = 0;

		//- Heat capacity at constant volume [J/kg/K]
		virtual tmp<volScalarField> Cv() const = 0;

		//- Molecular weight of the given specie [kg/kmol]
		virtual tmp<volScalarField> W() const = 0;

		//- Thermal diffusivity for temperature
		//  of mixture for patch [W/m/K]
		virtual tmp<scalarField> kappa
		(
			const label patchi
		) const = 0;

		//- Thermal diffusivity for temperature of mixture [W/m/K]
		virtual tmp<volScalarField> kappa() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifdef NoRepository
#include <SpecieMixture.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SpecieMixture_Header
