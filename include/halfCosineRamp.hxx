#pragma once
#ifndef _halfCosineRamp_Header
#define _halfCosineRamp_Header

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
	tnbLib::Function1Types::halfCosineRamp

Description
	Half-cosine ramp function starting from 0 and increasing to 1 from \c start
	over the \c duration and remaining at 1 thereafter.

See also
	tnbLib::Function1Types::ramp

SourceFiles
	halfCosineRamp.C

\*---------------------------------------------------------------------------*/

#include <ramp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class halfCosineRamp Declaration
		\*---------------------------------------------------------------------------*/

		class halfCosineRamp
			:
			public ramp
		{

		public:

			// Runtime type information
			//TypeName("halfCosineRamp");
			static const char* typeName_() { return "halfCosineRamp"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from entry name and dictionary
			FoamBase_EXPORT halfCosineRamp
			(
				const word& entryName,
				const dictionary& dict
			);


			//- Destructor
			FoamBase_EXPORT virtual ~halfCosineRamp();


			// Member Functions

				//- Return value for time t
			virtual inline scalar value(const scalar t) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const halfCosineRamp&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <halfCosineRampI.hxx>

#endif // !_halfCosineRamp_Header
