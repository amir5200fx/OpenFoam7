#pragma once
#ifndef _harmonicSpring_Header
#define _harmonicSpring_Header

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
	tnbLib::tetherPotentials::harmonicSpring

Description


SourceFiles
	harmonicSpring.C

\*---------------------------------------------------------------------------*/

#include <tetherPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace tetherPotentials
	{

		/*---------------------------------------------------------------------------*\
							   Class harmonicSpring Declaration
		\*---------------------------------------------------------------------------*/

		class harmonicSpring
			:
			public tetherPotential
		{
			// Private Data

			dictionary harmonicSpringCoeffs_;

			scalar springConstant_;


		public:

			//- Runtime type information
			//TypeName("harmonicSpring");
			static const char* typeName_() { return "harmonicSpring"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT harmonicSpring
			(
				const word& name,
				const dictionary& tetherPotentialProperties
			);


			//- Destructor
			~harmonicSpring()
			{}


			// Member Functions

			FoamLagrangian_EXPORT scalar energy(const vector r) const;

			FoamLagrangian_EXPORT vector force(const vector r) const;

			//- Read dictionary
			FoamLagrangian_EXPORT bool read(const dictionary& tetherPotentialProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tetherPotentials
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_harmonicSpring_Header
