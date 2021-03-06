#pragma once
#ifndef _chemkinReader_Header
#define _chemkinReader_Header

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
	tnbLib::chemkinReader

Description
	tnbLib::chemkinReader

SourceFiles
	chemkinReader.C
	chemkinLexer.C

\*---------------------------------------------------------------------------*/

#include <chemistryReader.hxx>
#include <fileName.hxx>
#include <typeInfo.hxx>
#include <Switch.hxx>
#include <HashPtrTable.hxx>
#include <ReactionList.hxx>
#include <DynamicList.hxx>
#include <labelList.hxx>
#include <speciesTable.hxx>
#include <atomicWeights.hxx>
#include <reactionTypes.hxx>

#include <FlexLexer.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class chemkinReader Declaration
	\*---------------------------------------------------------------------------*/

	class chemkinReader
		:
		public chemistryReader<gasHThermoPhysics>,
		public yyFlexLexer
	{

	public:

		// Public data types

		enum phase
		{
			solid,
			liquid,
			gas
		};


	private:

		// Private Data

		static FoamThermophysicalModels_EXPORT int yyBufSize;
		label lineNo_;

		//- Table of reaction type keywords
		HashTable<int> reactionKeywordTable_;

		//- Currently supported reaction types
		enum reactionKeyword
		{
			thirdBodyReactionType,
			unimolecularFallOffReactionType,
			chemicallyActivatedBimolecularReactionType,
			TroeReactionType,
			SRIReactionType,
			LandauTellerReactionType,
			reverseLandauTellerReactionType,
			JanevReactionType,
			powerSeriesReactionRateType,
			radiationActivatedReactionType,
			speciesTempReactionType,
			energyLossReactionType,
			plasmaMomentumTransfer,
			collisionCrossSection,
			nonEquilibriumReversibleReactionType,
			duplicateReactionType,
			speciesOrderForward,
			speciesOrderReverse,
			UnitsOfReaction,
			end
		};

		enum reactionType
		{
			irreversible,
			reversible,
			nonEquilibriumReversible,
			unknownReactionType
		};

		static FoamThermophysicalModels_EXPORT const char* reactionTypeNames[4];

		enum reactionRateType
		{
			Arrhenius,
			thirdBodyArrhenius,
			unimolecularFallOff,
			chemicallyActivatedBimolecular,
			LandauTeller,
			Janev,
			powerSeries,
			unknownReactionRateType
		};

		static FoamThermophysicalModels_EXPORT const char* reactionRateTypeNames[8];

		enum fallOffFunctionType
		{
			Lindemann,
			Troe,
			SRI,
			unknownFallOffFunctionType
		};

		static FoamThermophysicalModels_EXPORT const char* fallOffFunctionNames[4];


		FoamThermophysicalModels_EXPORT void initReactionKeywordTable();


		//- List of elements
		DynamicList<word> elementNames_;

		//- Element indices
		HashTable<label> elementIndices_;

		//- Isotope molecular weights
		HashTable<scalar> isotopeAtomicWts_;

		//- List of species
		DynamicList<word> specieNames_;

		//- Specie indices
		HashTable<label> specieIndices_;

		//- Table of species
		speciesTable& speciesTable_;

		//- Specie phase
		HashTable<phase> speciePhase_;

		//- Table of the thermodynamic data given in the CHEMKIN file
		HashPtrTable<gasHThermoPhysics> speciesThermo_;

		//- Table of species composition
		speciesCompositionTable speciesComposition_;

		//- List of the reactions
		ReactionList<gasHThermoPhysics> reactions_;

		//- Transport properties dictionary
		dictionary transportDict_;

		//- Flag to indicate that file is in new format
		Switch newFormat_;

		//- Tolerance for element imbalance in a reaction
		scalar imbalanceTol_;


		// Private Member Functions

			//- Flex lexer to read the CHEMKIN III file
		FoamThermophysicalModels_EXPORT int lex();

		inline scalar stringToScalar(const string& s)
		{
			string& str = const_cast<string&>(s);
			str.replaceAll(" ", "");
			str.replaceAll("D", "e");
			str.replaceAll("d", "e");
			return atof(str.c_str());
		}

		inline scalar stringToScalar(const char* cstr)
		{
			return stringToScalar(string(cstr));
		}

		inline void correctElementName(word& elementName)
		{
			if (elementName.size() == 2)
			{
				elementName[1] = tolower(elementName[1]);
			}
			else if (elementName[0] == 'E')
			{
				elementName = 'e';
			}
		}

		FoamThermophysicalModels_EXPORT scalar molecularWeight
		(
			const List<specieElement>& specieComposition
		) const;

		FoamThermophysicalModels_EXPORT void finishElements(labelList& currentAtoms);

		FoamThermophysicalModels_EXPORT void checkCoeffs
		(
			const scalarList& reactionCoeffs,
			const char* reationRateName,
			const label nCoeffs
		) const;

		template<class ReactionRateType>
		void addReactionType
		(
			const reactionType rType,
			DynamicList<specieCoeffs>& lhs,
			DynamicList<specieCoeffs>& rhs,
			const ReactionRateType& rr
		);

		template<template<class, class> class PressureDependencyType>
		void addPressureDependentReaction
		(
			const reactionType rType,
			const fallOffFunctionType fofType,
			DynamicList<specieCoeffs>& lhs,
			DynamicList<specieCoeffs>& rhs,
			const scalarList& thirdBodyEfficiencies,
			const scalarList& k0Coeffs,
			const scalarList& kInfCoeffs,
			const HashTable<scalarList>& reactionCoeffsTable,
			const scalar Afactor0,
			const scalar AfactorInf,
			const scalar RR
		);

		FoamThermophysicalModels_EXPORT void addReaction
		(
			DynamicList<specieCoeffs>& lhs,
			DynamicList<specieCoeffs>& rhs,
			const scalarList& thirdBodyEfficiencies,
			const reactionType rType,
			const reactionRateType rrType,
			const fallOffFunctionType fofType,
			const scalarList& ArrheniusReactionCoeffs,
			HashTable<scalarList>& reactionCoeffsTable,
			const scalar RR
		);

		// Read the CHEMKIN files
		FoamThermophysicalModels_EXPORT void read
		(
			const fileName& CHEMKINFileName,
			const fileName& thermoFileName,
			const fileName& transportFileName
		);

		//- Disallow default bitwise copy construction
		FoamThermophysicalModels_EXPORT chemkinReader(const chemkinReader&) = delete;

		//- Disallow default bitwise assignment
		FoamThermophysicalModels_EXPORT void operator=(const chemkinReader&) = delete;


	public:

		//- Runtime type information
		//TypeName("chemkinReader");
		static const char* typeName_() { return "chemkinReader"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from CHEMKIN III file name
		FoamThermophysicalModels_EXPORT chemkinReader
		(
			speciesTable& species,
			const fileName& CHEMKINFileName,
			const fileName& transportFileName,
			const fileName& thermoFileName = fileName::null,
			const bool newFormat = false
		);

		//- Construct by getting the CHEMKIN III file name from dictionary
		FoamThermophysicalModels_EXPORT chemkinReader(const dictionary& thermoDict, speciesTable& species);


		//- Destructor
		virtual ~chemkinReader()
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

		//- Isotope molecular weights
		const HashTable<scalar>& isotopeAtomicWts() const
		{
			return isotopeAtomicWts_;
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

		//- Specie phase
		const HashTable<phase>& speciePhase() const
		{
			return speciePhase_;
		}

		//- Table of the thermodynamic data given in the CHEMKIN file
		const HashPtrTable<gasHThermoPhysics>& speciesThermo() const
		{
			return speciesThermo_;
		}

		//- List of the reactions
		const ReactionList<gasHThermoPhysics>& reactions() const
		{
			return reactions_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <chemkinReaderI.hxx>

#endif // !_chemkinReader_Header
