#pragma once
#ifndef _dampedCoulomb_Header
#define _dampedCoulomb_Header

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
	tnbLib::pairPotentials::dampedCoulomb

Description


SourceFiles
	dampedCoulomb.C

\*---------------------------------------------------------------------------*/

#include <pairPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		/*---------------------------------------------------------------------------*\
								 Class dampedCoulomb Declaration
		\*---------------------------------------------------------------------------*/

		class dampedCoulomb
			:
			public pairPotential
		{
			// Private Data

			dictionary dampedCoulombCoeffs_;

			scalar alpha_;


		public:

			//- Runtime type information
			TypeName("dampedCoulomb");


			// Static Data Members

			static scalar oneOverFourPiEps0;


			// Constructors

				//- Construct from components
			dampedCoulomb
			(
				const word& name,
				const dictionary& pairPotentialProperties
			);


			//- Destructor
			~dampedCoulomb()
			{}


			// Member Functions

			scalar unscaledEnergy(const scalar r) const;

			//- Read dictionary
			bool read(const dictionary& pairPotentialProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dampedCoulomb_Header
