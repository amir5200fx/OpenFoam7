#pragma once
#ifndef _contactAngleForce_Header
#define _contactAngleForce_Header

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
	tnbLib::regionModels::surfaceFilmModels::contactAngleForce

Description
	Base-class for film contact angle force models.

	The effect of the contact angle force can be ignored over a specified
	distance from patches.

SourceFiles
	contactAngleForce.C

\*---------------------------------------------------------------------------*/

#include <force.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								  Class contactAngleForce Declaration
			\*---------------------------------------------------------------------------*/

			class contactAngleForce
				:
				public force
			{
				// Private Data

					//- Coefficient applied to the contact angle force
				scalar Ccf_;

				//- Mask over which force is applied
				volScalarField mask_;


				// Private Member Functions

					//- Initialise
				FoamLagrangian_EXPORT void initialise();


			protected:

				//- Return the contact angle field
				FoamLagrangian_EXPORT virtual tmp<volScalarField> theta() const = 0;


			public:

				//- Runtime type information
				//TypeName("contactAngle");
				static const char* typeName_() { return "contactAngle"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT contactAngleForce
				(
					const word& typeName,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT contactAngleForce(const contactAngleForce&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~contactAngleForce();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual tmp<fvVectorMatrix> correct(volVectorField& U);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const contactAngleForce&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_contactAngleForce_Header
