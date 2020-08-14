#pragma once
#ifndef _chemistryReader_Header
#define _chemistryReader_Header

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
	tnbLib::chemistryReader

Description
	Abstract class for reading chemistry

SourceFiles
	chemistryReader.C

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>
#include <specieElement.hxx>
#include <Reaction.hxx>
#include <ReactionList.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	typedef HashTable<List<specieElement>> speciesCompositionTable;


	/*---------------------------------------------------------------------------*\
						  Class chemistryReader Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class chemistryReader
	{
	public:

		//- Runtime type information
		TypeName("chemistryReader");

		//- The type of thermo package the reader was instantiated for
		typedef ThermoType thermoType;


		// Constructors

			//- Construct null
		chemistryReader()
		{}

		//- Disallow default bitwise copy construction
		chemistryReader(const chemistryReader&) = delete;


		// Declare run-time constructor selection table

		declareRunTimeSelectionTable
		(
			autoPtr,
			chemistryReader,
			dictionary,
			(
				const dictionary& thermoDict,
				speciesTable& species
				),
				(thermoDict, species)
		);


		// Selectors

			//- Select constructed from dictionary
		static autoPtr<chemistryReader> New
		(
			const dictionary& thermoDict,
			speciesTable& species
		);


		//- Destructor
		virtual ~chemistryReader()
		{}


		// Member Functions

			//- Return access to the list of species
		virtual const speciesTable& species() const = 0;

		//- Table of species composition
		virtual const speciesCompositionTable& specieComposition() const = 0;

		//- Return access to the thermo packages
		virtual const HashPtrTable<ThermoType>& speciesThermo() const = 0;

		//- Return access to the list of reactions
		virtual const ReactionList<ThermoType>& reactions() const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const chemistryReader&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <chemistryReader.cxx>
#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#define makeChemistryReader(Thermo)                                            \
    defineTemplateTypeNameAndDebug(chemistryReader<Thermo>, 0);                \
    defineTemplateRunTimeSelectionTable(chemistryReader<Thermo>, dictionary)


#define makeChemistryReaderType(Reader, Thermo)                                \
    defineNamedTemplateTypeNameAndDebug(Reader<Thermo>, 0);                    \
    chemistryReader<Thermo>::adddictionaryConstructorToTable<Reader<Thermo>> \
        add##Reader##Thermo##ConstructorToTable_


// for non-templated chemistry readers
#define addChemistryReaderType(Reader, Thermo)                                 \
    defineTypeNameAndDebug(Reader, 0);                                         \
    chemistryReader<Thermo>::adddictionaryConstructorToTable<Reader>           \
        add##Reader##Thermo##ConstructorToTable_


// for templated chemistry readers
#define addTemplateChemistryReaderType(Reader, Thermo)                         \
    defineNamedTemplateTypeNameAndDebug(Reader, 0);                            \
    chemistryReader<Thermo>::adddictionaryConstructorToTable<Reader>           \
        add##Reader##Thermo##ConstructorToTable_


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_chemistryReader_Header
