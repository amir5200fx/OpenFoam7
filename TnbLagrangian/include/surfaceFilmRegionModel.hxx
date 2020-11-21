#pragma once
#ifndef _surfaceFilmRegionModel_Header
#define _surfaceFilmRegionModel_Header

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
	tnbLib::regionModels::surfaceFilmModels::surfaceFilmRegionModel

Description
	Base class for surface film models

SourceFiles
	surfaceFilmRegionModel.C

\*---------------------------------------------------------------------------*/

#include <surfaceFilmModel.hxx>
#include <singleLayerRegion.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								  Class surfaceFilmRegionModel Declaration
			\*---------------------------------------------------------------------------*/

			class surfaceFilmRegionModel
				:
				public surfaceFilmModel,
				public singleLayerRegion
			{
			protected:

				// Protected data

					//- Acceleration due to gravity [m/s^2]
				const dimensionedVector& g_;


				// Protected member functions

					//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read();


			public:

				//- Runtime type information
				//TypeName("surfaceFilmRegionModel");
				static const char* typeName_() { return "surfaceFilmRegionModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from type name, mesh and gravity vector
				FoamLagrangian_EXPORT surfaceFilmRegionModel
				(
					const word& modelType,
					const fvMesh& mesh,
					const dimensionedVector& g,
					const word& regionType
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT surfaceFilmRegionModel(const surfaceFilmRegionModel&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~surfaceFilmRegionModel();


				// Member Functions

					// Access

						//- Return the acceleration due to gravity
				inline const dimensionedVector& g() const;

				//- External hook to add sources to the film
				FoamLagrangian_EXPORT virtual void addSources
				(
					const label patchi,
					const label facei,
					const scalar massSource,
					const vector& momentumSource,
					const scalar pressureSource,
					const scalar energySource
				) = 0;


				// Fields

					//- Return the film thickness [m]
				FoamLagrangian_EXPORT virtual const volScalarField& delta() const = 0;

				//- Return the film coverage, 1 = covered, 0 = uncovered / []
				FoamLagrangian_EXPORT virtual const volScalarField& alpha() const = 0;

				//- Return the film velocity [m/s]
				FoamLagrangian_EXPORT virtual const volVectorField& U() const = 0;

				//- Return the film surface velocity [m/s]
				FoamLagrangian_EXPORT virtual const volVectorField& Us() const = 0;

				//- Return the film wall velocity [m/s]
				FoamLagrangian_EXPORT virtual const volVectorField& Uw() const = 0;

				//- Return the film density [kg/m^3]
				FoamLagrangian_EXPORT virtual const volScalarField& rho() const = 0;

				//- Return the film mean temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& T() const = 0;

				//- Return the film surface temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& Ts() const = 0;

				//- Return the film wall temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& Tw() const = 0;

				//- Return the film surface temperature [J/kg]
				FoamLagrangian_EXPORT virtual const volScalarField& hs() const = 0;

				//- Return the film specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual const volScalarField& Cp() const = 0;

				//- Return the film thermal conductivity [W/m/K]
				FoamLagrangian_EXPORT virtual const volScalarField& kappa() const = 0;

				//- Return the film surface tension [N/m]
				FoamLagrangian_EXPORT virtual const volScalarField& sigma() const = 0;


				// Transfer fields - to the primary region

					//- Return mass transfer source - Eulerian phase only
				FoamLagrangian_EXPORT virtual tmp<volScalarField> primaryMassTrans() const = 0;

				//- Return the film mass available for transfer
				FoamLagrangian_EXPORT virtual const volScalarField& cloudMassTrans() const = 0;

				//- Return the parcel diameters originating from film
				FoamLagrangian_EXPORT virtual const volScalarField& cloudDiameterTrans() const = 0;


				// Evolution

					//- Main driver routing to evolve the region - calls other evolves
				FoamLagrangian_EXPORT virtual void evolve();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const surfaceFilmRegionModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceFilmRegionModelI.hxx>

#endif // !_surfaceFilmRegionModel_Header
