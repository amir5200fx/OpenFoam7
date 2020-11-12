#pragma once
#ifndef _pairPotential_Header
#define _pairPotential_Header

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
	tnbLib::pairPotential

Description

SourceFiles
	pairPotential.C
	pairPotentialNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <List.hxx>
#include <Pair.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class energyScalingFunction;

	/*---------------------------------------------------------------------------*\
							Class pairPotential Declaration
	\*---------------------------------------------------------------------------*/

	class pairPotential
	{

	protected:

		// Protected member data

		word name_;
		dictionary pairPotentialProperties_;

		scalar rCut_;
		scalar rCutSqr_;

		scalar rMin_;
		scalar dr_;

		List<scalar> forceLookup_;
		List<scalar> energyLookup_;

		mutable energyScalingFunction* esfPtr_;

		bool writeTables_;


		// Protected member functions

		FoamLagrangian_EXPORT void scaleEnergy(scalar& e, const scalar r) const;


	public:

		//- Runtime type information
		//TypeName("pairPotential");
		static const char* typeName_() { return "pairPotential"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			pairPotential,
			dictionary,
			(
				const word& name,
				const dictionary& pairPotentialProperties
				),
				(name, pairPotentialProperties)
		);*/

		typedef autoPtr<pairPotential> (*dictionaryConstructorPtr)(const word& name,
		                                                           const dictionary& pairPotentialProperties);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class pairPotentialType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<pairPotential> New(const word& name, const dictionary& pairPotentialProperties)
			{
				return autoPtr<pairPotential>(new pairPotentialType(name, pairPotentialProperties));
			}

			adddictionaryConstructorToTable(const word& lookup = pairPotentialType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "pairPotential" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class pairPotentialType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<pairPotential> New(const word& name, const dictionary& pairPotentialProperties)
			{
				return autoPtr<pairPotential>(new pairPotentialType(name, pairPotentialProperties));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = pairPotentialType::typeName) : lookup_(lookup)
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
		static FoamLagrangian_EXPORT autoPtr<pairPotential> New
		(
			const word& name,
			const dictionary& pairPotentialProperties
		);


		// Constructors

			//- Construct from components
		FoamLagrangian_EXPORT pairPotential
		(
			const word& name,
			const dictionary& pairPotentialProperties
		);

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT pairPotential(const pairPotential&);


		//- Destructor
		virtual ~pairPotential()
		{}


		// Member Functions

		FoamLagrangian_EXPORT void setLookupTables();

		inline scalar rMin() const;

		inline scalar dr() const;

		inline scalar rCut() const;

		inline scalar rCutSqr() const;

		FoamLagrangian_EXPORT scalar energy(const scalar r) const;

		FoamLagrangian_EXPORT scalar force(const scalar r) const;

		FoamLagrangian_EXPORT List<Pair<scalar>> energyTable() const;

		FoamLagrangian_EXPORT List<Pair<scalar>> forceTable() const;

		inline bool writeTables() const;

		FoamLagrangian_EXPORT virtual scalar unscaledEnergy(const scalar r) const = 0;

		FoamLagrangian_EXPORT scalar scaledEnergy(const scalar r) const;

		FoamLagrangian_EXPORT scalar energyDerivative
		(
			const scalar r,
			const bool scaledEnergyDerivative = true
		) const;

		const dictionary& pairPotentialProperties() const
		{
			return pairPotentialProperties_;
		}

		FoamLagrangian_EXPORT bool writeEnergyAndForceTables(Ostream& os) const;

		//- Read pairPotential dictionary
		FoamLagrangian_EXPORT virtual bool read(const dictionary& pairPotentialProperties) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const pairPotential&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pairPotentialI.hxx>

#endif // !_pairPotential_Header
