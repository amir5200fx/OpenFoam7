#pragma once
#ifndef _ArrheniusViscosity_Header
#define _ArrheniusViscosity_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::ArrheniusViscosity

Description
	The Arrhenius temperature-dependent viscosity model multiplies the viscosity
	of a base model by an Arrhenius-type temperature function:

		mu = mu0*exp(k1*(1/(T + k2) - 1/(Tref + k2)))

	Where:
		mu0 is the base-model viscosity
		k1 and k2 are Arrhenius coefficients
		T is the local temperature
		Tref is the reference temperature

SourceFiles
	ArrheniusViscosity.C

\*---------------------------------------------------------------------------*/

#include <filmViscosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class ArrheniusViscosity Declaration
			\*---------------------------------------------------------------------------*/

			class ArrheniusViscosity
				:
				public filmViscosityModel
			{
			protected:

				// Protected data

					//- Base viscosity model
				autoPtr<filmViscosityModel> viscosity_;

				//- Coefficient k1
				dimensionedScalar k1_;

				//- Coefficient k2
				dimensionedScalar k2_;

				//- Reference temperature
				dimensionedScalar Tref_;


			public:

				//- Runtime type information
				//TypeName("Arrhenius");
				static const char* typeName_() { return "Arrhenius"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT ArrheniusViscosity
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT ArrheniusViscosity(const ArrheniusViscosity&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~ArrheniusViscosity();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					const volScalarField& p,
					const volScalarField& T
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const ArrheniusViscosity&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ArrheniusViscosity_Header
