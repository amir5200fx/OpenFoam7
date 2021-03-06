#pragma once
#ifndef _transferModelList_Header
#define _transferModelList_Header

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
	tnbLib::regionModels::surfaceFilmModels::transferModelList

Description
	List container for film transfer models

SourceFiles
	transferModelList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <transferModel.hxx>
#include <filmSubModelBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class transferModelList Declaration
			\*---------------------------------------------------------------------------*/

			class transferModelList
				:
				public PtrList<transferModel>,
				public filmSubModelBase
			{
				// Private Data

					//- List of mass transferred per patch
				scalarField massTransferred_;


			public:

				// Constructors

					//- Construct null
				FoamLagrangian_EXPORT transferModelList(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT transferModelList
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT transferModelList(const transferModelList&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~transferModelList();


				// Member Functions

					//- Correct kinematic transfers
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					volScalarField& massToTransfer
				);

				//- Correct kinematic and thermodynamic transfers
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					volScalarField& massToTransfer,
					volScalarField& energyToTransfer
				);

				//- Provide some info
				FoamLagrangian_EXPORT virtual void info(Ostream& os);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const transferModelList&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transferModelList_Header
