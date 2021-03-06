#pragma once
#ifndef _rpm_Header
#define _rpm_Header

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
	tnbLib::SRF::rpm

Description
	Basic SRF model whereby angular velocity is specified in terms of
	a (global) axis and revolutions-per-minute [rpm]

SourceFiles
	rpm.C

\*---------------------------------------------------------------------------*/

#include <SRFModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace SRF
	{

		/*---------------------------------------------------------------------------*\
									Class rpm Declaration
		\*---------------------------------------------------------------------------*/

		class rpm
			:
			public SRFModel
		{

			// Private Data

			//- Revolutions per minute
			scalar rpm_;


		public:

			//- Runtime type information
			//TypeName("rpm");
			static const char* typeName_() { return "rpm"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

			//- Construct from components
			FoamFiniteVolume_EXPORT rpm(const volVectorField& U);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT rpm(const rpm&) = delete;


			//- Destructor
			FoamFiniteVolume_EXPORT ~rpm();


			// Member Functions

			// I-O

			//- Read
			FoamFiniteVolume_EXPORT bool read();


			// Member Operators

			//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const rpm&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace SRF
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rpm_Header
