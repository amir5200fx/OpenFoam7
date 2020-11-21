#pragma once
#ifndef _maitlandSmith_Header
#define _maitlandSmith_Header

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
	tnbLib::pairPotentials::maitlandSmith

Description

	Reference:
	\verbatim
		Maitland, G. C., & Smith, E. B. (1973).
		A simplified representation of intermolecular potential energy.
		Chemical Physics Letters, 22(3), 443-446.
	\endverbatim

	Parameters for other monoatomics from:
	\verbatim
		Maitland, G. C., Rigby, M., Smith, E., Wakeham, W. (1981).
		Intermolecular forces: Their origin and determination.
		Oxford: Clarendon Press.
	\endverbatim

SourceFiles
	maitlandSmith.C

\*---------------------------------------------------------------------------*/

#include <pairPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace pairPotentials
	{

		/*---------------------------------------------------------------------------*\
							   Class maitlandSmith Declaration
		\*---------------------------------------------------------------------------*/

		class maitlandSmith
			:
			public pairPotential
		{
			// Private Data

			dictionary maitlandSmithCoeffs_;

			scalar m_;
			scalar gamma_;
			scalar rm_;
			scalar epsilon_;


		public:

			//- Runtime type information
			//TypeName("maitlandSmith");
			static const char* typeName_() { return "maitlandSmith"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT maitlandSmith
			(
				const word& name,
				const dictionary& pairPotentialProperties
			);


			//- Destructor
			~maitlandSmith()
			{}


			// Member Functions

			FoamLagrangian_EXPORT scalar unscaledEnergy(const scalar r) const;

			//- Read dictionary
			FoamLagrangian_EXPORT bool read(const dictionary& pairPotentialProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_maitlandSmith_Header
