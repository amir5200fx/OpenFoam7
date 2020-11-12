#pragma once
#ifndef _shifted_Header
#define _shifted_Header

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
	tnbLib::energyScalingFunctions::shifted

Description


SourceFiles
	shifted.C

\*---------------------------------------------------------------------------*/

#include <energyScalingFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace energyScalingFunctions
	{

		/*---------------------------------------------------------------------------*\
								   Class shifted Declaration
		\*---------------------------------------------------------------------------*/

		class shifted
			:
			public energyScalingFunction
		{
			// Private Data

			scalar e_at_rCut_;


		public:

			//- Runtime type information
			//TypeName("shifted");
			static const char* typeName_() { return "shifted"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT shifted
			(
				const word& name,
				const dictionary& energyScalingFunctionProperties,
				const pairPotential& pairPot
			);


			//- Destructor
			~shifted()
			{}


			// Member Functions

			FoamLagrangian_EXPORT void scaleEnergy(scalar& e, const scalar r) const;

			//- Read dictionary
			FoamLagrangian_EXPORT bool read(const dictionary& energyScalingFunctionProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace energyScalingFunctions
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_shifted_Header
