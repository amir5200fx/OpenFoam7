#pragma once
#ifndef _GAMGInterfaceField_Header
#define _GAMGInterfaceField_Header

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
	tnbLib::GAMGInterfaceField

Description
	 Abstract base class for GAMG agglomerated interface fields.

SourceFiles
	GAMGInterfaceField.C
	GAMGInterfaceFieldNew.C

\*---------------------------------------------------------------------------*/

#include <lduInterface.hxx>
#include <GAMGInterface.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class GAMGInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class GAMGInterfaceField
		:
		public lduInterfaceField
	{
		// Private Data

			//- Local reference cast into the interface
		const GAMGInterface& interface_;


	public:

		//- Runtime type information
		//TypeName("GAMGInterfaceField");
		static const char* typeName_() { return "GAMGInterfaceField"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGInterfaceField,
			lduInterfaceField,
			(
				const GAMGInterface& GAMGCp,
				const lduInterfaceField& fineInterface
				),
				(GAMGCp, fineInterface)
		);*/

		typedef autoPtr<GAMGInterfaceField> (*lduInterfaceFieldConstructorPtr)(
			const GAMGInterface& GAMGCp, const lduInterfaceField& fineInterface);
		typedef HashTable<lduInterfaceFieldConstructorPtr, word, string::hash> lduInterfaceFieldConstructorTable;
		static FoamBase_EXPORT lduInterfaceFieldConstructorTable* lduInterfaceFieldConstructorTablePtr_;
		static FoamBase_EXPORT void constructlduInterfaceFieldConstructorTables();
		static FoamBase_EXPORT void destroylduInterfaceFieldConstructorTables();

		template <class GAMGInterfaceFieldType>
		class addlduInterfaceFieldConstructorToTable
		{
		public:
			static autoPtr<GAMGInterfaceField> New(const GAMGInterface& GAMGCp, const lduInterfaceField& fineInterface)
			{
				return autoPtr<GAMGInterfaceField>(new GAMGInterfaceFieldType(GAMGCp, fineInterface));
			}

			addlduInterfaceFieldConstructorToTable(const word& lookup = GAMGInterfaceFieldType::typeName)
			{
				constructlduInterfaceFieldConstructorTables();
				if (!lduInterfaceFieldConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGInterfaceField" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addlduInterfaceFieldConstructorToTable() { destroylduInterfaceFieldConstructorTables(); }
		};

		template <class GAMGInterfaceFieldType>
		class addRemovablelduInterfaceFieldConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGInterfaceField> New(const GAMGInterface& GAMGCp, const lduInterfaceField& fineInterface)
			{
				return autoPtr<GAMGInterfaceField>(new GAMGInterfaceFieldType(GAMGCp, fineInterface));
			}

			addRemovablelduInterfaceFieldConstructorToTable(const word& lookup = GAMGInterfaceFieldType::typeName) : lookup_(
				lookup)
			{
				constructlduInterfaceFieldConstructorTables();
				lduInterfaceFieldConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablelduInterfaceFieldConstructorToTable()
			{
				if (lduInterfaceFieldConstructorTablePtr_) { lduInterfaceFieldConstructorTablePtr_->erase(lookup_); }
			}
		};;

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGInterfaceField,
			lduInterface,
			(
				const GAMGInterface& GAMGCp,
				const bool doTransform,
				const int rank
				),
				(GAMGCp, doTransform, rank)
		);*/

		typedef autoPtr<GAMGInterfaceField> (*lduInterfaceConstructorPtr)(const GAMGInterface& GAMGCp, const bool doTransform,
		                                                                  const int rank);
		typedef HashTable<lduInterfaceConstructorPtr, word, string::hash> lduInterfaceConstructorTable;
		static FoamBase_EXPORT lduInterfaceConstructorTable* lduInterfaceConstructorTablePtr_;
		static FoamBase_EXPORT void constructlduInterfaceConstructorTables();
		static FoamBase_EXPORT void destroylduInterfaceConstructorTables();

		template <class GAMGInterfaceFieldType>
		class addlduInterfaceConstructorToTable
		{
		public:
			static autoPtr<GAMGInterfaceField> New(const GAMGInterface& GAMGCp, const bool doTransform, const int rank)
			{
				return autoPtr<GAMGInterfaceField>(new GAMGInterfaceFieldType(GAMGCp, doTransform, rank));
			}

			addlduInterfaceConstructorToTable(const word& lookup = GAMGInterfaceFieldType::typeName)
			{
				constructlduInterfaceConstructorTables();
				if (!lduInterfaceConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGInterfaceField" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addlduInterfaceConstructorToTable() { destroylduInterfaceConstructorTables(); }
		};

		template <class GAMGInterfaceFieldType>
		class addRemovablelduInterfaceConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGInterfaceField> New(const GAMGInterface& GAMGCp, const bool doTransform, const int rank)
			{
				return autoPtr<GAMGInterfaceField>(new GAMGInterfaceFieldType(GAMGCp, doTransform, rank));
			}

			addRemovablelduInterfaceConstructorToTable(const word& lookup = GAMGInterfaceFieldType::typeName) : lookup_(lookup)
			{
				constructlduInterfaceConstructorTables();
				lduInterfaceConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablelduInterfaceConstructorToTable()
			{
				if (lduInterfaceConstructorTablePtr_) { lduInterfaceConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Selectors

			//- Return a pointer to a new interface created on freestore given
			//  the fine interface
		static FoamBase_EXPORT autoPtr<GAMGInterfaceField> New
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField& fineInterface
		);

		//- Return a pointer to a new interface created on freestore given
		//  the fine interface
		static FoamBase_EXPORT autoPtr<GAMGInterfaceField> New
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		);


		// Constructors

			//- Construct from GAMG interface and fine level interface field
		GAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField&
		)
			:
			lduInterfaceField(GAMGCp),
			interface_(GAMGCp)
		{}

		//- Construct from GAMG interface and fine level interface field
		GAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		)
			:
			lduInterfaceField(GAMGCp),
			interface_(GAMGCp)
		{}

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT GAMGInterfaceField(const GAMGInterfaceField&) = delete;


		// Member Functions

			// Access

				//- Return interface
		const GAMGInterface& interface() const
		{
			return interface_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const GAMGInterfaceField&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GAMGInterfaceField_Header
