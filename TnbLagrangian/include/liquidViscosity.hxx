#pragma once
#ifndef _liquidViscosity_Header
#define _liquidViscosity_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::liquidViscosity

Description
	liquidViscosity viscosity model

SourceFiles
	liquidViscosity.C

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
								   Class liquidViscosity Declaration
			\*---------------------------------------------------------------------------*/

			class liquidViscosity
				:
				public filmViscosityModel
			{
			public:

				//- Runtime type information
				TypeName("liquid");


				// Constructors

					//- Construct from surface film model
				liquidViscosity
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);

				//- Disallow default bitwise copy construction
				liquidViscosity(const liquidViscosity&) = delete;


				//- Destructor
				virtual ~liquidViscosity();


				// Member Functions

					// Evolution

						//- Correct
				virtual void correct
				(
					const volScalarField& p,
					const volScalarField& T
				);


				// Member Operators

					//- Disallow default bitwise assignment
				void operator=(const liquidViscosity&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_liquidViscosity_Header
