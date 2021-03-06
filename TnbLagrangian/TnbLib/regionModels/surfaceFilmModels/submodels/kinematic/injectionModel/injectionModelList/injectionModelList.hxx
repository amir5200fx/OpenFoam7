#pragma once
#ifndef _injectionModelList_Header
#define _injectionModelList_Header

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
	tnbLib::regionModels::surfaceFilmModels::injectionModelList

Description
	List container for film injection models

SourceFiles
	injectionModelList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <injectionModel.hxx>
#include <filmSubModelBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class injectionModelList Declaration
			\*---------------------------------------------------------------------------*/

			class injectionModelList
				:
				public PtrList<injectionModel>,
				public filmSubModelBase
			{
				// Private Data

					//- List of mass injected per patch
				scalarField massInjected_;


			public:

				// Constructors

					//- Construct null
				FoamLagrangian_EXPORT injectionModelList(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT injectionModelList
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT injectionModelList(const injectionModelList&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~injectionModelList();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					volScalarField& massToInject,
					volScalarField& diameterToInject
				);


				// I-O

					//- Provide some info
				FoamLagrangian_EXPORT virtual void info(Ostream& os);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const injectionModelList&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_injectionModelList_Header
