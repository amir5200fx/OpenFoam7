#pragma once
#ifndef _noPhaseChange_Header
#define _noPhaseChange_Header

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
	tnbLib::regionModels::surfaceFilmModels::noPhaseChange

Description
	Dummy phase change model for 'none'

SourceFiles
	noPhaseChange.C

\*---------------------------------------------------------------------------*/

#include <phaseChangeModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
									Class noPhaseChange Declaration
			\*---------------------------------------------------------------------------*/

			class noPhaseChange
				:
				public phaseChangeModel
			{
			public:

				//- Runtime type information
				//TypeName("none");
				static const char* typeName_() { return "none"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT noPhaseChange(surfaceFilmRegionModel& film, const dictionary& dict);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT noPhaseChange(const noPhaseChange&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~noPhaseChange();


				// Member Functions

					// Evolution

						//- Return the model 'active' status - default active = true
				FoamLagrangian_EXPORT virtual bool active() const;

				//- Correct
				FoamLagrangian_EXPORT virtual void correctModel
				(
					const scalar dt,
					scalarField& availableMass,
					scalarField& dMass,
					scalarField& dEnergy
				);


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const noPhaseChange&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noPhaseChange_Header
