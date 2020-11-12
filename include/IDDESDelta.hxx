#pragma once
#ifndef _IDDESDelta_Header
#define _IDDESDelta_Header

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
	tnbLib::LESModels::IDDESDelta

Description
	IDDESDelta used by the IDDES (improved low Re Spalart-Allmaras DES model)
	The min and max delta are calculated using the double distance of the min or
	max from the face centre to the cell centre.

SourceFiles
	IDDESDelta.C

\*---------------------------------------------------------------------------*/

#include <maxDeltaxyz.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								 Class IDDESDelta Declaration
		\*---------------------------------------------------------------------------*/

		class IDDESDelta
			:
			public LESdelta
		{
			// Private Data

			maxDeltaxyz hmax_;

			scalar Cw_;


			// Private Member Functions

				//- Calculate the delta values
			FoamTurbulence_EXPORT void calcDelta();


		public:

			//- Runtime type information
			//TypeName("IDDESDelta");
			static const char* typeName_() { return "IDDESDelta"; }
			static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
			static FoamTurbulence_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from name, mesh and IOdictionary
			FoamTurbulence_EXPORT IDDESDelta
			(
				const word& name,
				const turbulenceModel& turbulence,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamTurbulence_EXPORT IDDESDelta(const IDDESDelta&) = delete;


			// Destructor

			~IDDESDelta()
			{}


			// Member Functions

				//- Read the LESdelta dictionary
			FoamTurbulence_EXPORT void read(const dictionary&);

			//- Return the hmax delta field
			const volScalarField& hmax() const
			{
				return hmax_;
			}

			// Correct values
			FoamTurbulence_EXPORT void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamTurbulence_EXPORT void operator=(const IDDESDelta&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IDDESDelta_Header
