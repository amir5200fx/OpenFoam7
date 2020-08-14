#pragma once
#ifndef _foamChemistryReader_Header
#define _foamChemistryReader_Header

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
	tnbLib::foamChemistryReader

Description
	Chemistry reader for OpenFOAM format

SourceFiles
	foamChemistryReader.C

\*---------------------------------------------------------------------------*/

#include <chemistryReader.hxx>
#include <fileName.hxx>
#include <typeInfo.hxx>
#include <HashPtrTable.hxx>
#include <labelList.hxx>
#include <speciesTable.hxx>
#include <atomicWeights.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class foamChemistry Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class foamChemistryReader
		:
		public chemistryReader<ThermoType>
	{
		//- Chemistry/reactions dictionary
		dictionary chemDict_;

		//- Thermo properties dictionary
		dictionary thermoDict_;

		//- List of elements
		DynamicList<word> elementNames_;

		//- Element indices
		HashTable<label> elementIndices_;

		//- Table of species
		speciesTable& speciesTable_;

		//- Table of species composition
		speciesCompositionTable speciesComposition_;

		//- Table of the thermodynamic data given in the foamChemistry file
		HashPtrTable<ThermoType> speciesThermo_;

		//- List of the reactions
		ReactionList<ThermoType> reactions_;


		// Private Member Functions

			//- Set the species list
		speciesTable& setSpecies(const dictionary& dict, speciesTable& species);

		//- Read the species composition
		void readSpeciesComposition();


	public:

		//- Runtime type information
		TypeName("foamChemistryReader");


		// Constructors

			//- Construct from foamChemistry and thermodynamics file names
		foamChemistryReader
		(
			const fileName& reactionsFileName,
			speciesTable& species,
			const fileName& thermoFileName
		);

		//- Construct by getting the foamChemistry and thermodynamics file names
		//  from dictionary
		foamChemistryReader
		(
			const dictionary& thermoDict,
			speciesTable& species
		);

		//- Disallow default bitwise copy construction
		foamChemistryReader(const foamChemistryReader&) = delete;


		//- Destructor
		virtual ~foamChemistryReader()
		{}


		// Member Functions

			//- List of elements
		const wordList& elementNames() const
		{
			return elementNames_;
		}

		//- Element indices
		const HashTable<label>& elementIndices() const
		{
			return elementIndices_;
		}

		//- Table of species
		const speciesTable& species() const
		{
			return speciesTable_;
		}

		//- Table of species composition
		const speciesCompositionTable& specieComposition() const
		{
			return speciesComposition_;
		}

		//- Table of the thermodynamic data given in the foamChemistry file
		const HashPtrTable<ThermoType>& speciesThermo() const
		{
			return speciesThermo_;
		}

		//- List of the reactions
		const ReactionList<ThermoType>& reactions() const
		{
			return reactions_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const foamChemistryReader&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <foamChemistryReader.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_foamChemistryReader_Header
