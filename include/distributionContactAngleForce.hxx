#pragma once
#ifndef _distributionContactAngleForce_Header
#define _distributionContactAngleForce_Header

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
	tnbLib::regionModels::surfaceFilmModels::distributionContactAngleForce

Description
	PDF distribution based film contact angle force

See also
	tnbLib::regionModels::surfaceFilmModels::contactAngleForce
	tnbLib::distributionModel

SourceFiles
	distributionContactAngleForce.C

\*---------------------------------------------------------------------------*/

#include <contactAngleForce.hxx>
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
							Class distributionContactAngleForce Declaration
			\*---------------------------------------------------------------------------*/

			class distributionContactAngleForce
				:
				public contactAngleForce
			{
				// Private Data

					//- Random number generator
				Random rndGen_;

				//- Parcel size PDF model
				const autoPtr<distributionModel> distribution_;


			protected:

				//- Return the contact angle field
				FoamLagrangian_EXPORT virtual tmp<volScalarField> theta() const;


			public:

				//- Runtime type information
				//TypeName("distributionContactAngle");
				static const char* typeName_() { return "distributionContactAngle"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT distributionContactAngleForce
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT distributionContactAngleForce
				(
					const distributionContactAngleForce&
				) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~distributionContactAngleForce();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const distributionContactAngleForce&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_distributionContactAngleForce_Header
