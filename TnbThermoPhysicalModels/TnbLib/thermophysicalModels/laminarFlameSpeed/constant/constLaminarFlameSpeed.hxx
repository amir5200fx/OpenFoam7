#pragma once
#ifndef _constLaminarFlameSpeed_Header
#define _constLaminarFlameSpeed_Header

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
	tnbLib::laminarFlameSpeedModels::constant

Description
	Constant laminar flame speed model.

SourceFiles
	selectLaminarFlameSpeed.C

\*---------------------------------------------------------------------------*/

#include <laminarFlameSpeed.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{

		/*---------------------------------------------------------------------------*\
								   Class constant Declaration
		\*---------------------------------------------------------------------------*/

		class constant
			:
			public laminarFlameSpeed
		{
			// Const laminar flame speed

			dimensionedScalar Su_;


			// Private Member Functions

				//- Construct as copy (not implemented)
			FoamThermophysicalModels_EXPORT constant(const constant&);
			FoamThermophysicalModels_EXPORT void operator=(const constant&);


		public:

			//- Runtime type information
			//TypeName("constant");
			static const char* typeName_() { return "constant"; }
			static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
			static FoamThermophysicalModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary and psiuReactionThermo
			FoamThermophysicalModels_EXPORT constant
			(
				const dictionary&,
				const psiuReactionThermo&
			);


			//- Destructor
			FoamThermophysicalModels_EXPORT virtual ~constant();


			// Member Functions

				//- Return the laminar flame speed [m/s]
			FoamThermophysicalModels_EXPORT tmp<volScalarField> operator()() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End laminarFlameSpeedModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constLaminarFlameSpeed_Header
