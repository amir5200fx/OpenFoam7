#pragma once
#ifndef _maxDeltaxyz_Header
#define _maxDeltaxyz_Header

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
	tnbLib::LESModels::maxDeltaxyz

Description
	Delta calculated by taking the maximum distance between the cell centre
	and any face centre.  For a regular hex cell, the computed delta will
	equate to half of the cell width; accordingly, the deltaCoeff model
	coefficient should be set to 2 for this case.

SourceFiles
	maxDeltaxyz.C

\*---------------------------------------------------------------------------*/

#include <LESdelta.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								 Class maxDeltaxyz Declaration
		\*---------------------------------------------------------------------------*/

		class maxDeltaxyz
			:
			public LESdelta
		{
			// Private Data

				//- Model coefficient
			scalar deltaCoeff_;


			// Private Member Functions

				// Calculate the delta values
			FoamTurbulence_EXPORT void calcDelta();


		public:

			//- Runtime type information
			//TypeName("maxDeltaxyz");
			static const char* typeName_() { return "maxDeltaxyz"; }
			static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
			static FoamTurbulence_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from name, turbulenceModel and dictionary
			FoamTurbulence_EXPORT maxDeltaxyz
			(
				const word& name,
				const turbulenceModel& turbulence,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamTurbulence_EXPORT maxDeltaxyz(const maxDeltaxyz&) = delete;


			//- Destructor
			virtual ~maxDeltaxyz()
			{}


			// Member Functions

				//- Read the LESdelta dictionary
			FoamTurbulence_EXPORT virtual void read(const dictionary&);

			// Correct values
			FoamTurbulence_EXPORT virtual void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamTurbulence_EXPORT void operator=(const maxDeltaxyz&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_maxDeltaxyz_Header
