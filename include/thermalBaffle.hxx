#pragma once
#ifndef _thermalBaffle_Header
#define _thermalBaffle_Header

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
	tnbLib::regionModels::thermalBaffleModels::thermalBaffle

Description
	2D thermal baffle

SourceFiles
	thermalBaffle.C
	thermalBaffleI.H

\*---------------------------------------------------------------------------*/

#include <thermalBaffleModel.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace thermalBaffleModels
		{


			/*---------------------------------------------------------------------------*\
									Class thermalBaffle Declaration
			\*---------------------------------------------------------------------------*/

			class thermalBaffle
				:
				public thermalBaffleModel
			{
				// Private Member Functions

					//- Initialize thermalBaffle
				FoamLagrangian_EXPORT void init();


			protected:

				// Protected data

					// Solution parameters

						//- Number of non orthogonal correctors
				label nNonOrthCorr_;


				// Thermo properties

					//- Solid thermo
				autoPtr<solidThermo> thermo_;

				//- Enthalpy/internal energy
				volScalarField& h_;


				// Source term fields

					//- Surface energy source  / [J/m2/s]
				volScalarField Qs_;

				//- Volumetric energy source  / [J/m3/s]
				volScalarField Q_;


				// Sub models

					//- Pointer to radiation model
				autoPtr<radiationModel> radiation_;


				// Protected member functions

					//- Read control parameters IO dictionary
				FoamLagrangian_EXPORT virtual bool read();

				//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read(const dictionary& dict);


				// Equations

					//- Solve energy equation
				FoamLagrangian_EXPORT void solveEnergy();


			public:

				//- Runtime type information
				//TypeName("thermalBaffle");
				static const char* typeName_() { return "thermalBaffle"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamLagrangian_EXPORT thermalBaffle(const word& modelType, const fvMesh& mesh);

				//- Construct from components and dict
				FoamLagrangian_EXPORT thermalBaffle
				(
					const word& modelType,
					const fvMesh& mesh,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT thermalBaffle(const thermalBaffle&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~thermalBaffle();


				// Member Functions

					// Thermo properties

						//- Return const reference to the solidThermo
				FoamLagrangian_EXPORT virtual const solidThermo& thermo() const;


				// Fields

					//- Return the film specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual const tmp<volScalarField> Cp() const;

				//- Return solid absortivity [1/m]
				FoamLagrangian_EXPORT virtual const volScalarField& kappaRad() const;

				//- Return temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& T() const;

				//- Return density [Kg/m^3]
				FoamLagrangian_EXPORT virtual const volScalarField& rho() const;

				//- Return thermal conductivity [W/m/K]
				FoamLagrangian_EXPORT virtual const volScalarField& kappa() const;


				// Helper functions

					//- Return sensible enthalpy/internal energy
					//  as a function of temperature
					//  for a patch
				inline tmp<scalarField> he
				(
					const scalarField& p,
					const scalarField& T,
					const label patchi
				) const;

				//- Return sensible enthalpy/internal energy
				inline tmp<volScalarField> he() const;


				// Evolution

					//- Pre-evolve  thermal baffle
				FoamLagrangian_EXPORT virtual void preEvolveRegion();

				//- Evolve the thermal baffle
				FoamLagrangian_EXPORT virtual void evolveRegion();


				// I-O

					 //- Provide some feedback
				FoamLagrangian_EXPORT virtual void info();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const thermalBaffle&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermalBaffleModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <thermalBaffleI.hxx>

#endif // !_thermalBaffle_Header
