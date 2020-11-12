#pragma once
#ifndef _laminarFlameSpeed_Header
#define _laminarFlameSpeed_Header

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

Namespace
	tnbLib::laminarFlameSpeedModels

Description
	Namespace for laminar flame speed models


Class
	tnbLib::laminarFlameSpeed

Description
	Abstract class for laminar flame speed

SourceFiles
	laminarFlameSpeed.C
	laminarFlameSpeedNew.C

\*---------------------------------------------------------------------------*/

#include <psiuReactionThermo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class laminarFlameSpeed Declaration
	\*---------------------------------------------------------------------------*/

	class laminarFlameSpeed
	{

	protected:

		// Protected data

		const psiuReactionThermo& psiuReactionThermo_;

		//- Fuel
		word fuel_;

		//- Equivalence ratio of a homogeneous mixture
		scalar equivalenceRatio_;


	private:

		// Private Member Functions

			//- Construct as copy (not implemented)
		FoamThermophysicalModels_EXPORT laminarFlameSpeed(const laminarFlameSpeed&);
		FoamThermophysicalModels_EXPORT void operator=(const laminarFlameSpeed&);


	public:

		//- Runtime type information
		//TypeName("laminarFlameSpeed");
		static const char* typeName_() { return "laminarFlameSpeed"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			laminarFlameSpeed,
			dictionary,
			(
				const dictionary& dict,
				const psiuReactionThermo& ct
				),
				(dict, ct)
		);*/

		typedef autoPtr<laminarFlameSpeed> (*dictionaryConstructorPtr)(const dictionary& dict,
		                                                               const psiuReactionThermo& ct);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class laminarFlameSpeedType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<laminarFlameSpeed> New(const dictionary& dict, const psiuReactionThermo& ct)
			{
				return autoPtr<laminarFlameSpeed>(new laminarFlameSpeedType(dict, ct));
			}

			adddictionaryConstructorToTable(const word& lookup = laminarFlameSpeedType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "laminarFlameSpeed"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class laminarFlameSpeedType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<laminarFlameSpeed> New(const dictionary& dict, const psiuReactionThermo& ct)
			{
				return autoPtr<laminarFlameSpeed>(new laminarFlameSpeedType(dict, ct));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = laminarFlameSpeedType::typeName) : lookup_(
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


		// Constructors

			//- Construct from dictionary and psiuReactionThermo
		FoamThermophysicalModels_EXPORT laminarFlameSpeed
		(
			const dictionary&,
			const psiuReactionThermo&
		);


		// Selector

		static FoamThermophysicalModels_EXPORT autoPtr<laminarFlameSpeed> New
		(
			const psiuReactionThermo&
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~laminarFlameSpeed();


		// Member Functions

			//- Return the laminar flame speed [m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> operator()() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_laminarFlameSpeed_Header
