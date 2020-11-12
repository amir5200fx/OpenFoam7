#pragma once
#ifndef _forceList_Header
#define _forceList_Header

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
	tnbLib::regionModels::surfaceFilmModels::forceList

Description
	List container for film sources

SourceFiles
	forceList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <force.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								   Class forceList Declaration
			\*---------------------------------------------------------------------------*/

			class forceList
				:
				public PtrList<force>
			{
			public:

				// Constructors

					//- Construct null
				FoamLagrangian_EXPORT forceList(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT forceList
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~forceList();


				// Member Functions

					//- Return (net) force system
				FoamLagrangian_EXPORT tmp<fvVectorMatrix> correct(volVectorField& U);
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_forceList_Header
