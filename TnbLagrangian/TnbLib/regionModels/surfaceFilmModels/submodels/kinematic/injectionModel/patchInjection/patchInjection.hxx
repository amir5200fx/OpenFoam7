#pragma once
#ifndef _patchInjection_Header
#define _patchInjection_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::patchInjection

Description
	Remove and inject the mass in the film as it passes over the selected
	patches.

SourceFiles
	patchInjection.C

\*---------------------------------------------------------------------------*/

#include <injectionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								  Class patchInjection Declaration
			\*---------------------------------------------------------------------------*/

			class patchInjection
				:
				public injectionModel
			{
			protected:

				//- Stable film thickness - mass only removed if thickness exceeds
				//  this threshold value
				scalar deltaStable_;

				//- List of patch IDs at which the film is removed
				labelList patchIDs_;

				//- Injected mass for each patch at which the film is removed
				scalarField patchInjectedMasses_;


			public:

				//- Runtime type information
				//TypeName("patchInjection");
				static const char* typeName_() { return "patchInjection"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from surface film model
				FoamLagrangian_EXPORT patchInjection(surfaceFilmRegionModel& film, const dictionary& dict);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT patchInjection(const patchInjection&) = delete;


				//- Destructor
				FoamLagrangian_EXPORT virtual ~patchInjection();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToInject,
					scalarField& diameterToInject
				);

				//- Accumulate the total mass injected for the patches into the
				//  scalarField provided
				FoamLagrangian_EXPORT virtual void patchInjectedMassTotals
				(
					scalarField& patchMasses
				) const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const patchInjection&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchInjection_Header
