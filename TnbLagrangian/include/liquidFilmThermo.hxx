#pragma once
#ifndef _liquidFilmThermo_Header
#define _liquidFilmThermo_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::liquidFilmThermo

Description
	Liquid thermo model

SourceFiles
	liquidFilmThermo.C

\*---------------------------------------------------------------------------*/

#include <filmThermoModel.hxx>
#include <liquidProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// Forward class declarations
			class thermoSingleLayer;

			/*---------------------------------------------------------------------------*\
								  Class liquidFilmThermo Declaration
			\*---------------------------------------------------------------------------*/

			class liquidFilmThermo
				:
				public filmThermoModel
			{
			protected:

				// Protected data

					//- Liquid name
				word name_;

				//- Pointer to the liquid properties
				const liquidProperties* liquidPtr_;

				//- Flag to indicate that model owns the liquid object
				bool ownLiquid_;

				//- Flag to indicate that reference values of p and T should be used
				bool useReferenceValues_;

				//- Reference pressure [pa]
				scalar pRef_;

				//- Reference temperature [K]
				scalar TRef_;


				// Protected member functions

					//- Return a reference to a thermo film
				FoamLagrangian_EXPORT const thermoSingleLayer& thermoFilm() const;

				//- Initialise the liquid pointer
				FoamLagrangian_EXPORT void initLiquid(const dictionary& dict);


			public:

				//- Runtime type information
				//TypeName("liquid");
				static const char* typeName_() { return "liquid"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT liquidFilmThermo
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT liquidFilmThermo(const liquidFilmThermo&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~liquidFilmThermo();


				// Member Functions

					//- Return the specie name
				FoamLagrangian_EXPORT virtual const word& name() const;


				// Elemental access

					//- Return density [kg/m^3]
				FoamLagrangian_EXPORT virtual scalar rho(const scalar p, const scalar T) const;

				//- Return dynamic viscosity [Pa.s]
				FoamLagrangian_EXPORT virtual scalar mu(const scalar p, const scalar T) const;

				//- Return surface tension [kg/s^2]
				FoamLagrangian_EXPORT virtual scalar sigma(const scalar p, const scalar T) const;

				//- Return specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual scalar Cp(const scalar p, const scalar T) const;

				//- Return thermal conductivity [W/m/K]
				FoamLagrangian_EXPORT virtual scalar kappa(const scalar p, const scalar T) const;

				//- Return diffusivity [m2/s]
				FoamLagrangian_EXPORT virtual scalar D(const scalar p, const scalar T) const;

				//- Return latent heat [J/kg]
				FoamLagrangian_EXPORT virtual scalar hl(const scalar p, const scalar T) const;

				//- Return vapour pressure [Pa]
				FoamLagrangian_EXPORT virtual scalar pv(const scalar p, const scalar T) const;

				//- Return molecular weight [kg/kmol]
				FoamLagrangian_EXPORT virtual scalar W() const;

				//- Return boiling temperature [K]
				FoamLagrangian_EXPORT virtual scalar Tb(const scalar p) const;


				// Field access

					//- Return density [kg/m^3]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> rho() const;

				//- Return dynamic viscosity [Pa.s]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> mu() const;

				//- Return surface tension [kg/s^2]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> sigma() const;

				//- Return specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> Cp() const;

				//- Return thermal conductivity [W/m/K]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> kappa() const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const liquidFilmThermo&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_liquidFilmThermo_Header
