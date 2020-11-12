#pragma once
#ifndef _constantFilmThermo_Header
#define _constantFilmThermo_Header

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
	tnbLib::regionModels::surfaceFilmModels::constantFilmThermo

Description
	Constant thermo model

SourceFiles
	constantFilmThermo.C

\*---------------------------------------------------------------------------*/

#include <filmThermoModel.hxx>
#include <dimensionSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								 Class constantFilmThermo Declaration
			\*---------------------------------------------------------------------------*/

			class constantFilmThermo
				:
				public filmThermoModel
			{
			public:

				struct thermoData
				{
					word name_;
					scalar value_;
					bool set_;

					thermoData()
						:
						name_("unknown"),
						value_(0.0),
						set_(false)
					{}

					thermoData(const word& n)
						:
						name_(n),
						value_(0.0),
						set_(false)
					{}
				};


			private:

				// Private Data

					//- Specie name
				word name_;

				//- Density [kg/m^3]
				mutable thermoData rho0_;

				//- Dynamic viscosity [Pa.s]
				mutable thermoData mu0_;

				//- Surface tension [kg/s^2]
				mutable thermoData sigma0_;

				//- Specific heat capacity [J/kg/K]
				mutable thermoData Cp0_;

				//- Thermal conductivity [W/m/K]
				mutable thermoData kappa0_;

				//- Diffusivity [m2/s]
				mutable thermoData D0_;

				//- Latent heat [J/kg]
				mutable thermoData hl0_;

				//- Vapour pressure [Pa]
				mutable thermoData pv0_;

				//- Molecular weight [kg/kmol]
				mutable thermoData W0_;

				//- Boiling temperature [K]
				mutable thermoData Tb0_;


				// Private Member Functions

					//- Initialise thermoData object
				FoamLagrangian_EXPORT void init(thermoData& td);


			public:

				//- Runtime type information
				//TypeName("constant");
				static const char* typeName_() { return "constant"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT constantFilmThermo
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT constantFilmThermo(const constantFilmThermo&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~constantFilmThermo();


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
				FoamLagrangian_EXPORT void operator=(const constantFilmThermo&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantFilmThermo_Header
