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

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamchemistryReader_EXPORT __declspec(dllexport)
#else
#ifdef FoamchemistryReader_EXPORT_DEFINE
#define FoamchemistryReader_EXPORT __declspec(dllexport)
#else
#define FoamchemistryReader_EXPORT __declspec(dllimport)
#endif
#endif

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
		//TypeName("chemistryReader");
		static const char* typeName_() { return "chemistryReader"; }
		static FoamchemistryReader_EXPORT const ::tnbLib::word typeName;
		static FoamchemistryReader_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- The type of thermo package the reader was instantiated for
		typedef ThermoType thermoType;


		// Constructors

			//- Construct null
		chemistryReader()
		{}

		//- Disallow default bitwise copy construction
		chemistryReader(const chemistryReader&) = delete;


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			chemistryReader,
			dictionary,
			(
				const dictionary& thermoDict,
				speciesTable& species
				),
				(thermoDict, species)
		);*/

		typedef autoPtr<chemistryReader> (*dictionaryConstructorPtr)(const dictionary& thermoDict,
		                                                             speciesTable& species);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamchemistryReader_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamchemistryReader_EXPORT void constructdictionaryConstructorTables();
		static FoamchemistryReader_EXPORT void destroydictionaryConstructorTables();

		template <class chemistryReaderType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<chemistryReader> New(const dictionary& thermoDict, speciesTable& species)
			{
				return autoPtr<chemistryReader>(new chemistryReaderType(thermoDict, species));
			}

			adddictionaryConstructorToTable(const word& lookup = chemistryReaderType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "chemistryReader" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class chemistryReaderType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<chemistryReader> New(const dictionary& thermoDict, speciesTable& species)
			{
				return autoPtr<chemistryReader>(new chemistryReaderType(thermoDict, species));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = chemistryReaderType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


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

#include <chemistryReaderI.hxx>

//#ifdef NoRepository
//#include <chemistryReader.cxx>
//#endif


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
