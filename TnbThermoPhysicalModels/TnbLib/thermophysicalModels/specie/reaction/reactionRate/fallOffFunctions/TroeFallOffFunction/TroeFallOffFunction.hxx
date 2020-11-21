#pragma once
#ifndef _TroeFallOffFunction_Header
#define _TroeFallOffFunction_Header

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
	tnbLib::TroeFallOffFunction

Description
	The Troe fall-off function

SourceFiles
	TroeFallOffFunctionI.H

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class dictionary;  // added by amir

	class TroeFallOffFunction;
	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream&, const TroeFallOffFunction&);


	/*---------------------------------------------------------------------------*\
						 Class TroeFallOffFunction Declaration
	\*---------------------------------------------------------------------------*/

	class TroeFallOffFunction
	{
		// Private Data

		scalar alpha_;
		scalar Tsss_, Ts_, Tss_;


	public:

		// Constructors

			//- Construct from components
		FoamThermophysicalModels_EXPORT inline TroeFallOffFunction
		(
			const scalar alpha,
			const scalar Tsss,
			const scalar Ts,
			const scalar Tss
		);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT inline TroeFallOffFunction(const dictionary& dict);


		// Member Functions

			//- Return the type name
		static word type()
		{
			return "Troe";
		}

		FoamThermophysicalModels_EXPORT inline scalar operator()
			(
				const scalar T,
				const scalar Pr
				) const;

		FoamThermophysicalModels_EXPORT inline scalar ddT
		(
			const scalar Pr,
			const scalar F,
			const scalar dPrdT,
			const scalar T
		) const;

		FoamThermophysicalModels_EXPORT inline scalar ddc
		(
			const scalar Pr,
			const scalar F,
			const scalar dPrdc,
			const scalar T
		) const;

		//- Write to stream
		FoamThermophysicalModels_EXPORT inline void write(Ostream& os) const;


		// Ostream Operator

		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream&, const TroeFallOffFunction&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <TroeFallOffFunctionI.hxx>

#endif // !_TroeFallOffFunction_Header
