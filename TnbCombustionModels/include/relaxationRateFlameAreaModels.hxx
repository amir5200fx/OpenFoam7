#pragma once
#ifndef _relaxationRateFlameAreaModels_Header
#define _relaxationRateFlameAreaModels_Header

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
	tnbLib::reactionRateFlameAreaModels::relaxation

Description
	Consumption rate per unit of flame area obtained from a relaxation equation

SourceFiles
	relaxation.C

\*---------------------------------------------------------------------------*/

#include <reactionRateFlameArea.hxx>
#include <consumptionSpeed.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace reactionRateFlameAreaModels
	{

		/*---------------------------------------------------------------------------*\
								   Class relaxation Declaration
		\*---------------------------------------------------------------------------*/

		class relaxation
			:
			public reactionRateFlameArea
		{
			// Private Data

				//- Correlation
			consumptionSpeed correlation_;

			//- Proportionality constant for time scale in the relaxation Eq.
			scalar C_;

			//- Proportionality constant for sub-grid strain
			scalar alpha_;


		public:

			//- Runtime type information
			//TypeName("relaxation");
			static const char* typeName_() { return "relaxation"; }
			static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
			static FoamCombustionModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary and psiReactionThermo
			FoamCombustionModels_EXPORT relaxation
			(
				const word modelType,
				const dictionary& dictCoeffs,
				const fvMesh& mesh,
				const combustionModel& combModel
			);

			//- Disallow default bitwise copy construction
			relaxation(const relaxation&);


			// Destructor

			FoamCombustionModels_EXPORT virtual ~relaxation();


			// Member Functions

				//- Correct omega
			FoamCombustionModels_EXPORT virtual void correct(const volScalarField& sigma);


			// IO

				//- Update properties from given dictionary
			FoamCombustionModels_EXPORT virtual bool read(const dictionary& dictProperties);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const relaxation&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End reactionRateFlameAreaModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_relaxationRateFlameAreaModels_Header
