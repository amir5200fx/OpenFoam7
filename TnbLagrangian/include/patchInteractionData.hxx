#pragma once
#ifndef _patchInteractionData_Header
#define _patchInteractionData_Header

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
	tnbLib::patchInteractionData

Description
	Helper class for the LocalInteraction patch interaction model

\*---------------------------------------------------------------------------*/

#include <Istream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						Class patchInteractionData Declaration
	\*---------------------------------------------------------------------------*/

	// Forward declaration of classes
	class patchInteractionData;

	// Forward declaration of friend functions
	FoamLagrangian_EXPORT Ostream& operator<<
		(
			Ostream& os,
			const patchInteractionData& pid
			);  //- added by amir

	FoamLagrangian_EXPORT Istream& operator>>
		(
			Istream& is,
			patchInteractionData& pid
			);


	class patchInteractionData
	{
		// Private Data

			//- Interaction type name
		word interactionTypeName_;

		//- Patch name
		word patchName_;

		//- Elasticity coefficient
		scalar e_;

		//- Restitution coefficient
		scalar mu_;


	public:

		// Constructor

			//- Construct null
		FoamLagrangian_EXPORT patchInteractionData();


		// Member Functions

			// Access

				//- Return const access to the interaction type name
		FoamLagrangian_EXPORT const word& interactionTypeName() const;

		//- Return const access to the patch name
		FoamLagrangian_EXPORT const word& patchName() const;

		//- Return const access to the elasticity coefficient
		FoamLagrangian_EXPORT scalar e() const;

		//- Return const access to the restitution coefficient
		FoamLagrangian_EXPORT scalar mu() const;


		FoamLagrangian_EXPORT bool operator==(const patchInteractionData&) const;  //- added by amir
		FoamLagrangian_EXPORT bool operator!=(const patchInteractionData&) const;  //- added by amir

		// I-O

		friend FoamLagrangian_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const patchInteractionData& pid
				);  //- added by amir

			//- Istream operator
		friend FoamLagrangian_EXPORT Istream& operator>>
			(
				Istream& is,
				patchInteractionData& pid
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchInteractionData_Header
