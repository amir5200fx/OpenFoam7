#pragma once
#ifndef _restrainedHarmonicSpring_Header
#define _restrainedHarmonicSpring_Header

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
	tnbLib::tetherPotentials::restrainedHarmonicSpring

Description


SourceFiles
	restrainedHarmonicSpring.C

\*---------------------------------------------------------------------------*/

#include <tetherPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace tetherPotentials
	{

		/*---------------------------------------------------------------------------*\
						  Class restrainedHarmonicSpring Declaration
		\*---------------------------------------------------------------------------*/

		class restrainedHarmonicSpring
			:
			public tetherPotential
		{
			// Private Data

			dictionary restrainedHarmonicSpringCoeffs_;

			scalar springConstant_;

			scalar rR_;


		public:

			//- Runtime type information
			TypeName("restrainedHarmonicSpring");


			// Constructors

				//- Construct from components
			restrainedHarmonicSpring
			(
				const word& name,
				const dictionary& tetherPotentialProperties
			);


			//- Destructor
			~restrainedHarmonicSpring()
			{}


			// Member Functions

			scalar energy(const vector r) const;

			vector force(const vector r) const;

			//- Read dictionary
			bool read(const dictionary& tetherPotentialProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tetherPotentials
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_restrainedHarmonicSpring_Header
