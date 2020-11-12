#pragma once
#ifndef _drippingInjection_Header
#define _drippingInjection_Header

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
	tnbLib::regionModels::surfaceFilmModels::drippingInjection

Description
	Film Dripping mass transfer model.

	If the film mass exceeds that needed to generate a valid parcel, the
	equivalent mass is removed from the film.

	New parcel diameters are sampled from a PDF.

SourceFiles
	drippingInjection.C

\*---------------------------------------------------------------------------*/

#include <injectionModel.hxx>
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
								Class drippingInjection Declaration
			\*---------------------------------------------------------------------------*/

			class drippingInjection
				:
				public injectionModel
			{
			protected:

				// Protected data

					//- Stable film thickness - drips only formed if thickness
					//  exceeds this threshold value
				scalar deltaStable_;

				//- Number of particles per parcel
				scalar particlesPerParcel_;

				//- Random number generator
				Random rndGen_;

				//- Parcel size PDF model
				const autoPtr<distributionModel>
					parcelDistribution_;

				//- Diameters of particles to inject into the dripping
				scalarList diameter_;


			public:

				//- Runtime type information
				//TypeName("drippingInjection");
				static const char* typeName_() { return "drippingInjection"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT drippingInjection
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT drippingInjection(const drippingInjection&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~drippingInjection();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToInject,
					scalarField& diameterToInject
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const drippingInjection&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_drippingInjection_Header
