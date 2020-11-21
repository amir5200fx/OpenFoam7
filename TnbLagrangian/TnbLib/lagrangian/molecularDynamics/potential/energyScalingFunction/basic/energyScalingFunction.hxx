#pragma once
#ifndef _energyScalingFunction_Header
#define _energyScalingFunction_Header

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
	tnbLib::energyScalingFunction

Description

SourceFiles
	energyScalingFunction.C
	energyScalingFunctionNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <pairPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class energyScalingFunction Declaration
	\*---------------------------------------------------------------------------*/

	class energyScalingFunction
	{

	protected:

		// Protected data

		word name_;

		dictionary energyScalingFunctionProperties_;

		const pairPotential& pairPot_;


	public:

		//- Runtime type information
		//TypeName("energyScalingFunction");
		static const char* typeName_() { return "energyScalingFunction"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			energyScalingFunction,
			dictionary,
			(
				const word& name,
				const dictionary& energyScalingFunctionProperties,
				const pairPotential& pairPot
				),
				(name, energyScalingFunctionProperties, pairPot)
		);*/

		typedef autoPtr<energyScalingFunction> (*dictionaryConstructorPtr)(
			const word& name, const dictionary& energyScalingFunctionProperties, const pairPotential& pairPot);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class energyScalingFunctionType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<energyScalingFunction> New(const word& name,
			                                          const dictionary& energyScalingFunctionProperties,
			                                          const pairPotential& pairPot)
			{
				return autoPtr<energyScalingFunction>(
					new energyScalingFunctionType(name, energyScalingFunctionProperties, pairPot));
			}

			adddictionaryConstructorToTable(const word& lookup = energyScalingFunctionType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"energyScalingFunction" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class energyScalingFunctionType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<energyScalingFunction> New(const word& name,
			                                          const dictionary& energyScalingFunctionProperties,
			                                          const pairPotential& pairPot)
			{
				return autoPtr<energyScalingFunction>(
					new energyScalingFunctionType(name, energyScalingFunctionProperties, pairPot));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = energyScalingFunctionType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Selectors

			//- Return a reference to the selected viscosity model
		static FoamLagrangian_EXPORT autoPtr<energyScalingFunction> New
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		);


		// Constructors

			//- Construct from components
		FoamLagrangian_EXPORT energyScalingFunction
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		);

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT energyScalingFunction(const energyScalingFunction&);


		//- Destructor
		virtual ~energyScalingFunction()
		{}


		// Member Functions

		FoamLagrangian_EXPORT virtual void scaleEnergy(scalar& e, const scalar r) const = 0;

		const dictionary& energyScalingFunctionProperties() const
		{
			return energyScalingFunctionProperties_;
		}

		//- Read energyScalingFunction dictionary
		virtual bool read
		(
			const dictionary& energyScalingFunctionProperties
		) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const energyScalingFunction&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_energyScalingFunction_Header
