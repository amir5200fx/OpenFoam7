#pragma once
#ifndef _phasePropertiesList_Header
#define _phasePropertiesList_Header

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
	tnbLib::phasePropertiesList

Description
	Simple container for a list of phase properties

SourceFiles
	phasePropertiesList.C

\*---------------------------------------------------------------------------*/

#include <Istream.hxx>
#include <volFields.hxx>
#include <wordList.hxx>
#include <phaseProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class phasePropertiesList Declaration
	\*---------------------------------------------------------------------------*/

	class phasePropertiesList
	{
		// Private Data

			//- List of phase properties
		List<phaseProperties> props_;

		//- List of word representation of phase types
		wordList phaseTypeNames_;

		//- List of state labels
		wordList stateLabels_;


	public:

		// Constructors

		   //- Construct null
		FoamLagrangian_EXPORT phasePropertiesList();

		//- Construct from components
		FoamLagrangian_EXPORT phasePropertiesList
		(
			Istream& is,
			const wordList& gasNames,
			const wordList& liquidNames,
			const wordList& solidNames
		);


		//- Destructor
		FoamLagrangian_EXPORT ~phasePropertiesList();


		// Public Member Functions

			//- Return the list of phase properties
		FoamLagrangian_EXPORT const List<phaseProperties>& props() const;

		//- Return the list of word representation of phase types
		FoamLagrangian_EXPORT const wordList& phaseTypes() const;

		//- Return the list of state labels
		FoamLagrangian_EXPORT const wordList& stateLabels() const;

		//- Return the size (number of phases)
		FoamLagrangian_EXPORT label size() const;


		// Member Operators

		FoamLagrangian_EXPORT const phaseProperties& operator[](const label) const;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phasePropertiesList_Header
