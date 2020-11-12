#pragma once
#ifndef _waxSolventViscosity_Header
#define _waxSolventViscosity_Header

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
	tnbLib::regionModels::surfaceFilmModels::waxSolventViscosity

Description
	Wax solvent mixture viscosity model.

SourceFiles
	waxSolventViscosity.C

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
								Class waxSolventViscosity Declaration
			\*---------------------------------------------------------------------------*/

			class waxSolventViscosity
				:
				public filmViscosityModel
			{
				// Private Member Functions

					//- Correct the mixture viscosity
				FoamLagrangian_EXPORT void correctMu();


			protected:

				// Protected data

					//- Wax viscosity
				volScalarField muWax_;

				//- Wax viscosity model
				autoPtr<filmViscosityModel> muWaxModel_;

				//- Solvent viscosity
				volScalarField muSolvent_;

				//- Solvent viscosity model
				autoPtr<filmViscosityModel> muSolventModel_;


			public:

				//- Runtime type information
				//TypeName("waxSolvent");
				static const char* typeName_() { return "waxSolvent"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT waxSolventViscosity
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT waxSolventViscosity(const waxSolventViscosity&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~waxSolventViscosity();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					const volScalarField& p,
					const volScalarField& T
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const waxSolventViscosity&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waxSolventViscosity_Header
