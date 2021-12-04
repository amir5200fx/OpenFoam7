#pragma once
#ifndef _constantHeatTransfer_Header
#define _constantHeatTransfer_Header

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
	tnbLib::regionModels::surfaceFilmModels::constantHeatTransfer

Description
	Constant heat transfer model

SourceFiles
	constantHeatTransfer.C

\*---------------------------------------------------------------------------*/

#include <heatTransferModel.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
									Class constantHeatTransfer Declaration
			\*---------------------------------------------------------------------------*/

			class constantHeatTransfer
				:
				public heatTransferModel
			{
				// Private Data

					//- Constant heat transfer coefficient [W/m^2/K]
				scalar c0_;


			public:

				//- Runtime type information
				//TypeName("constant");
				static const char* typeName_() { return "constant"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT constantHeatTransfer
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT constantHeatTransfer(const constantHeatTransfer&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~constantHeatTransfer();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct();

				//- Return the heat transfer coefficient [W/m^2/K]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> h() const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const constantHeatTransfer&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantHeatTransfer_Header
