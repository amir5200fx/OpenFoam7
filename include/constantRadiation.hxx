#pragma once
#ifndef _constantRadiation_Header
#define _constantRadiation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::constantRadiation

Description
	Film constant radiation model.  The constant radiative flux is specified
	by the user, and operated over a time interval defined by a start time and
	duration.  In addition, a mask can be applied to shield the film from the
	radiation.

SourceFiles
	constantRadiation.C

\*---------------------------------------------------------------------------*/

#include <filmRadiationModel.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								  Class constantRadiation Declaration
			\*---------------------------------------------------------------------------*/

			class constantRadiation
				:
				public filmRadiationModel
			{
				// Private Data

					//- Constant radiative flux [kg/s^3]
				volScalarField qrConst_;

				//- Radiation mask
				volScalarField mask_;

				//- Absorptivity
				scalar absorptivity_;

				//- Time start [s]
				const scalar timeStart_;

				//- Duration [s]
				const scalar duration_;


			public:

				//- Runtime type information
				//TypeName("constantRadiation");
				static const char* typeName_() { return "constantRadiation"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT constantRadiation
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT constantRadiation(const constantRadiation&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~constantRadiation();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct();

				//- Return the radiation sensible enthalpy source
				//  Also updates qrNet
				FoamLagrangian_EXPORT virtual tmp<volScalarField> Shs();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const constantRadiation&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantRadiation_Header
