#pragma once
#ifndef _tetherPotential_Header
#define _tetherPotential_Header

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
	tnbLib::tetherPotential

Description

SourceFiles
	tetherPotential.C
	tetherPotentialNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class tetherPotential Declaration
	\*---------------------------------------------------------------------------*/

	class tetherPotential
	{

	protected:

		// Protected data

		word name_;
		dictionary tetherPotentialProperties_;


	public:

		//- Runtime type information
		//TypeName("tetherPotential");
		static const char* typeName_() { return "tetherPotential"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			tetherPotential,
			dictionary,
			(
				const word& name,
				const dictionary& tetherPotentialProperties
				),
				(name, tetherPotentialProperties)
		);*/

		typedef autoPtr<tetherPotential> (*dictionaryConstructorPtr)(const word& name,
		                                                             const dictionary& tetherPotentialProperties);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class tetherPotentialType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<tetherPotential> New(const word& name, const dictionary& tetherPotentialProperties)
			{
				return autoPtr<tetherPotential>(new tetherPotentialType(name, tetherPotentialProperties));
			}

			adddictionaryConstructorToTable(const word& lookup = tetherPotentialType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "tetherPotential" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class tetherPotentialType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<tetherPotential> New(const word& name, const dictionary& tetherPotentialProperties)
			{
				return autoPtr<tetherPotential>(new tetherPotentialType(name, tetherPotentialProperties));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = tetherPotentialType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Constructors

			//- Construct from components
		FoamLagrangian_EXPORT tetherPotential
		(
			const word& name,
			const dictionary& tetherPotentialProperties
		);

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT tetherPotential(const tetherPotential&);


		// Selectors

			//- Return a reference to the selected viscosity model
		static FoamLagrangian_EXPORT autoPtr<tetherPotential> New
		(
			const word& name,
			const dictionary& tetherPotentialProperties
		);


		//- Destructor
		virtual ~tetherPotential()
		{}


		// Member Functions

		FoamLagrangian_EXPORT virtual scalar energy(const vector r) const = 0;

		FoamLagrangian_EXPORT virtual vector force(const vector r) const = 0;

		const dictionary& tetherPotentialProperties() const
		{
			return tetherPotentialProperties_;
		}

		//- Read tetherPotential dictionary
		FoamLagrangian_EXPORT virtual bool read(const dictionary& tetherPotentialProperties) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const tetherPotential&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_tetherPotential_Header
