#pragma once
#ifndef _noPyrolysis_Header
#define _noPyrolysis_Header

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
	tnbLib::regionModels::pyrolysisModels::noPyrolysis

Description
	Dummy surface pyrolysis model for 'none'

SourceFiles
	noPyrolysis.C

\*---------------------------------------------------------------------------*/

#include <pyrolysisModel.hxx>
#include <volFieldsFwd.hxx>
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
									  Class noPyrolysis Declaration
			\*---------------------------------------------------------------------------*/

			class noPyrolysis
				:
				public pyrolysisModel
			{
			protected:

				// Protected member functions

					//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read();

				//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read(const dictionary& dict);

				//- Reset solidChemistryModel and solidThermo pointers
				FoamLagrangian_EXPORT void constructThermoChemistry();

				//- Reference to solid thermo
				autoPtr<solidReactionThermo> solidThermo_;

				//- Reference to the solid chemistry model
				autoPtr<basicSolidChemistryModel> solidChemistry_;

				//- Pointer to radiation model
				autoPtr<radiationModel> radiation_;


			public:

				//- Runtime type information
				//TypeName("none");
				static const char* typeName_() { return "none"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from type name and mesh
				FoamLagrangian_EXPORT noPyrolysis
				(
					const word& modelType,
					const fvMesh& mesh,
					const word& regionType
				);

				//- Construct from type name and mesh and dict
				FoamLagrangian_EXPORT noPyrolysis
				(
					const word& modelType,
					const fvMesh& mesh,
					const dictionary& dict,
					const word& regionType
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT noPyrolysis(const noPyrolysis&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~noPyrolysis();


				// Member Functions

					// Fields

						//- Return density [kg/m^3]
				FoamLagrangian_EXPORT virtual const volScalarField& rho() const;

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


				// Evolution

					//- Pre-evolve region
				FoamLagrangian_EXPORT virtual void preEvolveRegion();

				//- Evolve the pyrolysis equations
				FoamLagrangian_EXPORT virtual void evolveRegion();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const noPyrolysis&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_noPyrolysis_Header
