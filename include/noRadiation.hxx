#pragma once
#ifndef _noRadiation_Header
#define _noRadiation_Header

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
	tnbLib::regionModels::surfaceFilmModels::noRadiation

Description
	Dummy radiation model for 'none' option

SourceFiles
	noRadiation.C

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
									 Class noRadiation Declaration
			\*---------------------------------------------------------------------------*/

			class noRadiation
				:
				public filmRadiationModel
			{
			public:

				//- Runtime type information
				//TypeName("none");
				static const char* typeName_() { return "none"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model and dictionary
				FoamLagrangian_EXPORT noRadiation
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT noRadiation(const noRadiation&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~noRadiation();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct();

				//- Return the radiation sensible enthalpy source
				FoamLagrangian_EXPORT virtual tmp<volScalarField> Shs();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const noRadiation&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noRadiation_Header
