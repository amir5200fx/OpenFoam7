#pragma once
#ifndef _thermophysicalFunction_Header
#define _thermophysicalFunction_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::thermophysicalFunction

Description
	Abstract base class for thermo-physical functions

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>
#include <IOstreams.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class thermophysicalFunction Declaration
	\*---------------------------------------------------------------------------*/

	class thermophysicalFunction
	{

	public:

		//- Runtime type information
		//TypeName("thermophysicalFunction");
		static const char* typeName_() { return "thermophysicalFunction"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			thermophysicalFunction,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/

		typedef autoPtr<thermophysicalFunction> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class thermophysicalFunctionType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<thermophysicalFunction> New(const dictionary& dict)
			{
				return autoPtr<thermophysicalFunction>(new thermophysicalFunctionType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = thermophysicalFunctionType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"thermophysicalFunction" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class thermophysicalFunctionType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<thermophysicalFunction> New(const dictionary& dict)
			{
				return autoPtr<thermophysicalFunction>(new thermophysicalFunctionType(dict));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = thermophysicalFunctionType::typeName) : lookup_(lookup)
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

			//- Construct null
		thermophysicalFunction()
		{}

		//- Return pointer to new thermophysicalFunction created from dict
		static FoamThermophysicalModels_EXPORT autoPtr<thermophysicalFunction> New(const dictionary& dict);


		//- Destructor
		virtual ~thermophysicalFunction()
		{}


		// Member Functions

			//- Evaluate the function and return the result
		FoamThermophysicalModels_EXPORT virtual scalar f(scalar p, scalar T) const = 0;

		//- Write the function coefficients
		FoamThermophysicalModels_EXPORT virtual void writeData(Ostream& os) const = 0;


		// Ostream Operator

		friend Ostream& operator<<(Ostream& os, const thermophysicalFunction& f)
		{
			f.writeData(os);
			return os;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thermophysicalFunction_Header
