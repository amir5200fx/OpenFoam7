#pragma once
#ifndef _chemistryReductionMethod_Header
#define _chemistryReductionMethod_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::chemistryReductionMethod

Description
	An abstract class for methods of chemical mechanism reduction

SourceFiles
	chemistryReductionMethod.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <Switch.hxx>
#include <scalarField.hxx>

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamchemistryReductionMethod_EXPORT __declspec(dllexport)
#else
#ifdef FoamchemistryReductionMethod_EXPORT_DEFINE
#define FoamchemistryReductionMethod_EXPORT __declspec(dllexport)
#else
#define FoamchemistryReductionMethod_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class CompType, class ThermoType>
	class TDACChemistryModel;

	/*---------------------------------------------------------------------------*\
							   Class chemistrySolver Declaration
	\*---------------------------------------------------------------------------*/

	template<class CompType, class ThermoType>
	class chemistryReductionMethod
	{

	protected:

		const IOdictionary& dict_;

		//- Dictionary that store the algorithm data
		const dictionary coeffsDict_;

		//- Is mechanism reduction active?
		Switch active_;

		//- Switch to select performance logging
		Switch log_;

		TDACChemistryModel<CompType, ThermoType>& chemistry_;

		//- List of active species (active = true)
		List<bool> activeSpecies_;

		//- Number of active species
		label NsSimp_;

		//- Number of species
		const label nSpecie_;

		//- Tolerance for the mechanism reduction algorithm
		scalar tolerance_;


	public:

		//- Runtime type information
		//TypeName("chemistryReductionMethod");
		static const char* typeName_() { return "chemistryReductionMethod"; }
		static FoamchemistryReductionMethod_EXPORT const ::tnbLib::word typeName;
		static FoamchemistryReductionMethod_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			chemistryReductionMethod,
			dictionary,
			(
				const IOdictionary& dict,
				TDACChemistryModel<CompType, ThermoType>& chemistry
				),
				(dict, chemistry)
		);*/

		typedef autoPtr<chemistryReductionMethod> (*dictionaryConstructorPtr)(
			const IOdictionary& dict, TDACChemistryModel<CompType, ThermoType>& chemistry);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamchemistryReductionMethod_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamchemistryReductionMethod_EXPORT void constructdictionaryConstructorTables();
		static FoamchemistryReductionMethod_EXPORT void destroydictionaryConstructorTables();

		template <class chemistryReductionMethodType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<chemistryReductionMethod> New(const IOdictionary& dict,
			                                             TDACChemistryModel<CompType, ThermoType>& chemistry)
			{
				return autoPtr<chemistryReductionMethod>(new chemistryReductionMethodType(dict, chemistry));
			}

			adddictionaryConstructorToTable(const word& lookup = chemistryReductionMethodType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"chemistryReductionMethod" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class chemistryReductionMethodType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<chemistryReductionMethod> New(const IOdictionary& dict,
			                                             TDACChemistryModel<CompType, ThermoType>& chemistry)
			{
				return autoPtr<chemistryReductionMethod>(new chemistryReductionMethodType(dict, chemistry));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = chemistryReductionMethodType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components
		chemistryReductionMethod
		(
			const IOdictionary& dict,
			TDACChemistryModel<CompType, ThermoType>& chemistry
		);


		// Selector

		static autoPtr<chemistryReductionMethod<CompType, ThermoType>> New
		(
			const IOdictionary& dict,
			TDACChemistryModel<CompType, ThermoType>& chemistry
		);


		//- Destructor
		virtual ~chemistryReductionMethod();


		// Member Functions

			//- Is mechanism reduction active?
		inline bool active() const;

		//- Is performance data logging enabled?
		inline bool log() const;

		//- Return the active species
		inline const List<bool>& activeSpecies() const;

		//- Return the number of active species
		inline label NsSimp();

		//- Return the initial number of species
		inline label nSpecie();

		//- Return the tolerance
		inline scalar tolerance() const;

		//- Reduce the mechanism
		virtual void reduceMechanism
		(
			const scalarField &c,
			const scalar T,
			const scalar p
		) = 0;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <chemistryReductionMethodI.hxx>
#include <chemistryReductionMethod_Imp.hxx>
#include <chemistryReductionMethodNew_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <chemistryReductionMethod.cxx>
//#include <chemistryReductionMethodNew.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_chemistryReductionMethod_Header
