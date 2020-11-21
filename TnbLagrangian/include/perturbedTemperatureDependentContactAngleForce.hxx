#pragma once
#ifndef _perturbedTemperatureDependentContactAngleForce_Header
#define _perturbedTemperatureDependentContactAngleForce_Header

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
	tnbLib::regionModels::surfaceFilmModels::
		perturbedTemperatureDependentContactAngleForce

Description
	Temperature dependent contact angle force with a stochastic perturbation

	The contact angle in degrees is specified as a tnbLib::Function1 type, to
	enable the use of, e.g.  constant, polynomial, table values and the
	stochastic perturbation obtained from a
	tnbLib::distributionModels::distributionModel

See also
	tnbLib::regionModels::surfaceFilmModels::contactAngleForce
	tnbLib::regionModels::surfaceFilmModels::temperatureDependentContactAngleForce
	tnbLib::regionModels::surfaceFilmModels::distributionContactAngleForce
	tnbLib::Function1Types
	tnbLib::distributionModel

SourceFiles
	perturbedTemperatureDependentContactAngleForce.C

\*---------------------------------------------------------------------------*/

#include <contactAngleForce.hxx>
#include <Function1.hxx>
#include <distributionModel.hxx>
#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
				   Class perturbedTemperatureDependentContactAngleForce Declaration
			\*---------------------------------------------------------------------------*/

			class perturbedTemperatureDependentContactAngleForce
				:
				public contactAngleForce
			{
				// Private Data

					//- Contact angle function
				autoPtr<Function1<scalar>> thetaPtr_;

				//- Random number generator
				Random rndGen_;

				//- Parcel size PDF model
				const autoPtr<distributionModel> distribution_;


			protected:

				//- Return the contact angle field
				FoamLagrangian_EXPORT virtual tmp<volScalarField> theta() const;


			public:

				//- Runtime type information
				//TypeName("perturbedTemperatureDependentContactAngle");
				static const char* typeName_() { return "perturbedTemperatureDependentContactAngle"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT perturbedTemperatureDependentContactAngleForce
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT perturbedTemperatureDependentContactAngleForce
				(
					const perturbedTemperatureDependentContactAngleForce&
				) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~perturbedTemperatureDependentContactAngleForce();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=
					(
						const perturbedTemperatureDependentContactAngleForce&
						) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_perturbedTemperatureDependentContactAngleForce_Header
