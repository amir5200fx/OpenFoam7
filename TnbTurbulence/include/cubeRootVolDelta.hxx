#pragma once
#ifndef _cubeRootVolDelta_Header
#define _cubeRootVolDelta_Header

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
	tnbLib::LESModels::cubeRootVolDelta

Description
	Simple cube-root of cell volume delta used in LES SGS models.

SourceFiles
	cubeRootVolDelta.C

\*---------------------------------------------------------------------------*/

#include <LESdelta.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								   Class cubeRootVolDelta Declaration
		\*---------------------------------------------------------------------------*/

		class cubeRootVolDelta
			:
			public LESdelta
		{
			// Private Data

			scalar deltaCoeff_;


			// Private Member Functions

				// Calculate the delta values
			FoamTurbulence_EXPORT void calcDelta();


		public:

			//- Runtime type information
			//TypeName("cubeRootVol");
			static const char* typeName_() { return "cubeRootVol"; }
			static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
			static FoamTurbulence_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from name, turbulenceModel and dictionary
			FoamTurbulence_EXPORT cubeRootVolDelta
			(
				const word& name,
				const turbulenceModel& turbulence,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamTurbulence_EXPORT cubeRootVolDelta(const cubeRootVolDelta&) = delete;


			//- Destructor
			virtual ~cubeRootVolDelta()
			{}


			// Member Functions

				//- Read the LESdelta dictionary
			FoamTurbulence_EXPORT virtual void read(const dictionary&);

			// Correct values
			FoamTurbulence_EXPORT virtual void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamTurbulence_EXPORT void operator=(const cubeRootVolDelta&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cubeRootVolDelta_Header
