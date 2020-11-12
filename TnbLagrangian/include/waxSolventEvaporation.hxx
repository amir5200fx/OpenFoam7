#pragma once
#ifndef _waxSolventEvaporation_Header
#define _waxSolventEvaporation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::waxSolventEvaporation

Description
	Wax solvent mixture evaporation model.

SourceFiles
	waxSolventEvaporation.C

\*---------------------------------------------------------------------------*/

#include <phaseChangeModel.hxx>
#include <uniformDimensionedFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class waxSolventEvaporation Declaration
			\*---------------------------------------------------------------------------*/

			class waxSolventEvaporation
				:
				public phaseChangeModel
			{
			protected:

				// Protected data

					//- Molecular weight of wax [kg/kmol]
				uniformDimensionedScalarField Wwax_;

				//- Molecular weight of liquid [kg/kmol]
				uniformDimensionedScalarField Wsolvent_;

				//- Initial solvent mass-fraction
				uniformDimensionedScalarField Ysolvent0_;

				//- Solvent mass-fraction
				volScalarField Ysolvent_;

				//- Minimum film height for model to be active
				const scalar deltaMin_;

				//- Length scale [m]
				const scalar L_;

				//- Boiling temperature factor
				//  Used to set max limit on temperature to Tb*TbFactor
				const scalar TbFactor_;

				//- Switch to treat YInf as zero
				Switch YInfZero_;

				//- Activity coefficient as a function of solvent mole fraction
				autoPtr<Function1<scalar>> activityCoeff_;


				// Protected member functions

					//- Return Sherwood number as a function of Reynolds and Schmidt numbers
				FoamLagrangian_EXPORT scalar Sh(const scalar Re, const scalar Sc) const;

				template<class YInfType>
				void correctModel
				(
					const scalar dt,
					scalarField& availableMass,
					scalarField& dMass,
					scalarField& dEnergy,
					YInfType YInf
				);


			public:

				//- Runtime type information
				//TypeName("waxSolventEvaporation");
				static const char* typeName_() { return "waxSolventEvaporation"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT waxSolventEvaporation
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT waxSolventEvaporation(const waxSolventEvaporation&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~waxSolventEvaporation();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correctModel
				(
					const scalar dt,
					scalarField& availableMass,
					scalarField& dMass,
					scalarField& dEnergy
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const waxSolventEvaporation&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

#include <waxSolventEvaporationI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waxSolventEvaporation_Header
