#pragma once
#ifndef _solidProperties_Header
#define _solidProperties_Header

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
	tnbLib::solidProperties

Description
	The thermophysical properties of a solid

SourceFiles
	solidProperties.C

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class solidProperties Declaration
	\*---------------------------------------------------------------------------*/

	class solidProperties
	{
		// Private Data

			//- Density [kg/m^3]
		scalar rho_;

		//- Specific heat capacity [J/kg/K]
		scalar Cp_;

		//- Thermal conductivity [W/m/K]
		scalar kappa_;

		//- Heat of formation [J/kg]
		scalar Hf_;

		//- Emissivity
		scalar emissivity_;


	public:

		//- Runtime type information
		//TypeName("solid");
		static const char* typeName_() { return "solid"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidProperties,
			,
			(),
			()
		);*/

		typedef autoPtr<solidProperties> (*ConstructorPtr)();
		typedef HashTable<ConstructorPtr, word, string::hash> ConstructorTable;
		static FoamThermophysicalModels_EXPORT ConstructorTable* ConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyConstructorTables();

		template <class solidPropertiesType>
		class addConstructorToTable
		{
		public:
			static autoPtr<solidProperties> New() { return autoPtr<solidProperties>(new solidPropertiesType()); }

			addConstructorToTable(const word& lookup = solidPropertiesType::typeName)
			{
				constructConstructorTables();
				if (!ConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidProperties" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addConstructorToTable() { destroyConstructorTables(); }
		};

		template <class solidPropertiesType>
		class addRemovableConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidProperties> New() { return autoPtr<solidProperties>(new solidPropertiesType()); }

			addRemovableConstructorToTable(const word& lookup = solidPropertiesType::typeName) : lookup_(lookup)
			{
				constructConstructorTables();
				ConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableConstructorToTable() { if (ConstructorTablePtr_) { ConstructorTablePtr_->erase(lookup_); } }
		};

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidProperties,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/

		typedef autoPtr<solidProperties> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class solidPropertiesType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<solidProperties> New(const dictionary& dict)
			{
				return autoPtr<solidProperties>(new solidPropertiesType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = solidPropertiesType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidProperties" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class solidPropertiesType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidProperties> New(const dictionary& dict)
			{
				return autoPtr<solidProperties>(new solidPropertiesType(dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = solidPropertiesType::typeName) : lookup_(
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
		FoamThermophysicalModels_EXPORT solidProperties
		(
			scalar rho,
			scalar Cp,
			scalar kappa,
			scalar Hf,
			scalar emissivity
		);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT solidProperties(const dictionary& dict);

		//- Construct and return clone
		virtual autoPtr<solidProperties> clone() const
		{
			return autoPtr<solidProperties>(new solidProperties(*this));
		}


		// Selectors

			//- Return a pointer to a new solidProperties created from name
		static FoamThermophysicalModels_EXPORT autoPtr<solidProperties> New(const word& name);

		//- Return a pointer to a new solidProperties created from dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<solidProperties> New(const dictionary& dict);


		//- Destructor
		virtual ~solidProperties()
		{}


		// Member Functions

			// Physical constants which define the solidProperties

				//- Density [kg/m^3]
		inline scalar rho() const;

		//- Specific heat capacity [J/kg/K]
		inline scalar Cp() const;

		//- Thermal conductivity [W/m/K]
		inline scalar kappa() const;

		//- Heat of formation [J/kg]
		inline scalar Hf() const;

		//- Sensible enthalpy - reference to Tstd [J/kg]
		inline scalar Hs(const scalar T) const;

		//- Emissivity []
		inline scalar emissivity() const;


		// I-O

			//- Read and set the properties present it the given dictionary
		FoamThermophysicalModels_EXPORT void readIfPresent(const dictionary& dict);

		//- Write the solidProperties properties
		FoamThermophysicalModels_EXPORT virtual void writeData(Ostream& os) const;

		//- Ostream Operator
		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const solidProperties& s);
	};


	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream&, const solidProperties&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <solidPropertiesI.hxx>

#endif // !_solidProperties_Header
