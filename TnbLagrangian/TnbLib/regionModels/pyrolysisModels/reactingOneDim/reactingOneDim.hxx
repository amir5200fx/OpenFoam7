#pragma once
#ifndef _reactingOneDim_Header
#define _reactingOneDim_Header

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
	tnbLib::regionModels::pyrolysisModels::reactingOneDim

Description
	Reacting, 1-D pyrolysis model

SourceFiles
	reactingOneDim.C

\*---------------------------------------------------------------------------*/

#include <pyrolysisModel.hxx>
#include <basicSolidChemistryModel.hxx>
#include <radiationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{


			/*---------------------------------------------------------------------------*\
								  Class reactingOneDim Declaration
			\*---------------------------------------------------------------------------*/

			class reactingOneDim
				:
				public pyrolysisModel
			{
				// Private Member Functions

					//- Read model controls
				FoamLagrangian_EXPORT void readReactingOneDimControls();


			protected:

				// Protected data

					//- Reference to solid thermo
				autoPtr<solidReactionThermo> solidThermo_;

				//- Reference to the solid chemistry model
				autoPtr<basicSolidChemistryModel> solidChemistry_;

				//- Pointer to radiation model
				autoPtr<radiationModel> radiation_;


				// Reference to solid thermo properties

					//- Density [kg/m^3]
				volScalarField rho_;

				//- List of solid components
				PtrList<volScalarField>& Ys_;

				// Non-const access to enthalpy
				volScalarField& h_;


				// Solution parameters

					//- Number of non-orthogonal correctors
				label nNonOrthCorr_;

				//- Maximum diffussivity
				scalar maxDiff_;

				//- Minimum delta for combustion
				scalar minimumDelta_;


				// Fields

					//- Total gas mass flux to the primary region [kg/m^2/s]
				surfaceScalarField phiGas_;

				//- Sensible enthalpy gas flux [J/m2/s]
				volScalarField phiHsGas_;

				//- Heat release rate [J/s/m^3]
				volScalarField chemistryQdot_;


				// Source term fields

					//- Coupled region radiative heat flux [W/m^2]
					//  Requires user to input mapping info for coupled patches
					// volScalarField qrCoupled_;

					//- In depth radiative heat flux [W/m^2]
				volScalarField qr_;


				// Checks

					//- Cumulative lost mass of the condensed phase [kg]
				dimensionedScalar lostSolidMass_;

				//- Cumulative mass generation of the gas phase [kg]
				dimensionedScalar addedGasMass_;

				//- Total mass gas flux at the pyrolysing walls [kg/s]
				scalar totalGasMassFlux_;

				//- Total heat release rate [J/s]
				dimensionedScalar totalHeatRR_;


				// Options

					//- Add gas enthalpy source term
				bool  gasHSource_;

				//- Add in depth radiation source term
				bool  qrHSource_;

				//- Use chemistry solvers (ode or sequential)
				bool useChemistrySolvers_;


				// Protected member functions

					//- Read control parameters from dictionary
				FoamLagrangian_EXPORT bool read();

				//- Read control parameters from dict
				FoamLagrangian_EXPORT bool read(const dictionary& dict);

				//- Update submodels
				FoamLagrangian_EXPORT void updateFields();

				//- Update/move mesh based on change in mass
				FoamLagrangian_EXPORT void updateMesh(const scalarField& mass0);

				//- Update radiative flux in pyrolysis region
				FoamLagrangian_EXPORT void updateqr();

				//- Update enthalpy flux for pyrolysis gases
				FoamLagrangian_EXPORT void updatePhiGas();

				//- Mass check
				FoamLagrangian_EXPORT void calculateMassTransfer();


				// Equations

					//- Solve continuity equation
				FoamLagrangian_EXPORT void solveContinuity();

				//- Solve energy
				FoamLagrangian_EXPORT void solveEnergy();

				//- Solve solid species mass conservation
				FoamLagrangian_EXPORT void solveSpeciesMass();


			public:

				//- Runtime type information
				//TypeName("reactingOneDim");
				static const char* typeName_() { return "reactingOneDim"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from type name and mesh
				FoamLagrangian_EXPORT reactingOneDim
				(
					const word& modelType,
					const fvMesh& mesh,
					const word& regionType
				);

				//- Construct from type name, mesh and dictionary
				FoamLagrangian_EXPORT reactingOneDim
				(
					const word& modelType,
					const fvMesh& mesh,
					const dictionary& dict,
					const word& regionType
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT reactingOneDim(const reactingOneDim&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~reactingOneDim();


				// Member Functions

					// Access

						//- Fields

							//- Return const density [Kg/m^3]
				FoamLagrangian_EXPORT const volScalarField& rho() const;

				//- Return const temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& T() const;

				//- Return specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual const tmp<volScalarField> Cp() const;

				//- Return the region absorptivity [1/m]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> kappaRad() const;

				//- Return the region thermal conductivity [W/m/k]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> kappa() const;

				//- Return the total gas mass flux to primary region [kg/m^2/s]
				FoamLagrangian_EXPORT virtual const surfaceScalarField& phiGas() const;


				// Solution parameters

					//- Return the number of non-orthogonal correctors
				inline label nNonOrthCorr() const;

				//- Return max diffusivity allowed in the solid
				FoamLagrangian_EXPORT virtual scalar maxDiff() const;


				// Helper functions

					//- External hook to add mass to the primary region
				FoamLagrangian_EXPORT virtual scalar addMassSources
				(
					const label patchi,            // patchi on primary region
					const label facei              // facei of patchi
				);

				//- Mean diffusion number of the solid region
				FoamLagrangian_EXPORT virtual scalar solidRegionDiffNo() const;


				// Evolution

					 //- Pre-evolve region
				FoamLagrangian_EXPORT virtual void preEvolveRegion();

				//- Evolve the pyrolysis equations
				FoamLagrangian_EXPORT virtual void evolveRegion();


				// I-O

					 //- Provide some feedback
				FoamLagrangian_EXPORT virtual void info();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const reactingOneDim&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <reactingOneDimI.hxx>

#endif // !_reactingOneDim_Header
