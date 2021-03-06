#pragma once
#ifndef _standardRadiation_Header
#define _standardRadiation_Header

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
	tnbLib::regionModels::surfaceFilmModels::standardRadiation

Description
	Standard radiation model

SourceFiles
	standardRadiation.C

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
								 Class standardRadiation Declaration
			\*---------------------------------------------------------------------------*/

			class standardRadiation
				:
				public filmRadiationModel
			{
				// Private Data

					//- Radiative incident flux mapped from  the primary region / [kg/s^3]
				volScalarField qinPrimary_;

				//- Remaining radiative flux after removing local contribution
				volScalarField qrNet_;


				// Model coefficients

					//- Beta coefficient
				scalar beta_;

				//- Bar(kappa) coefficient
				scalar kappaBar_;


			public:

				//- Runtime type information
				//TypeName("standardRadiation");
				static const char* typeName_() { return "standardRadiation"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT standardRadiation
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT standardRadiation(const standardRadiation&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~standardRadiation();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct();

				//- Return the radiation sensible enthalpy source
				//  Also updates qrNet
				FoamLagrangian_EXPORT virtual tmp<volScalarField> Shs();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const standardRadiation&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_standardRadiation_Header
