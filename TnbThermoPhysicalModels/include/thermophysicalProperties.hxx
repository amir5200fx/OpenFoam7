#pragma once
#ifndef _thermophysicalProperties_Header
#define _thermophysicalProperties_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::thermophysicalProperties

Description
	Base-class for thermophysical properties of solids, liquids and gases
	providing an interface compatible with the templated thermodynamics
	packages.

SourceFiles
	thermophysicalPropertiesI.H
	thermophysicalProperties.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class thermophysicalProperties Declaration
	\*---------------------------------------------------------------------------*/

	class thermophysicalProperties
	{
		// Private Data

			//- Molecular weight [kg/kmol]
		scalar W_;


	public:

		//TypeName("thermophysicalProperties");
		static const char* typeName_() { return "thermophysicalProperties"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			thermophysicalProperties,
			,
			(),
			()
		);*/

		typedef autoPtr<thermophysicalProperties> (*ConstructorPtr)();
		typedef HashTable<ConstructorPtr, word, string::hash> ConstructorTable;
		static FoamThermophysicalModels_EXPORT ConstructorTable* ConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyConstructorTables();

		template <class thermophysicalPropertiesType>
		class addConstructorToTable
		{
		public:
			static autoPtr<thermophysicalProperties> New()
			{
				return autoPtr<thermophysicalProperties>(new thermophysicalPropertiesType());
			}

			addConstructorToTable(const word& lookup = thermophysicalPropertiesType::typeName)
			{
				constructConstructorTables();
				if (!ConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"thermophysicalProperties" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addConstructorToTable() { destroyConstructorTables(); }
		};

		template <class thermophysicalPropertiesType>
		class addRemovableConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<thermophysicalProperties> New()
			{
				return autoPtr<thermophysicalProperties>(new thermophysicalPropertiesType());
			}

			addRemovableConstructorToTable(const word& lookup = thermophysicalPropertiesType::typeName) : lookup_(
				lookup)
			{
				constructConstructorTables();
				ConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableConstructorToTable() { if (ConstructorTablePtr_) { ConstructorTablePtr_->erase(lookup_); } }
		};

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			thermophysicalProperties,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/

		typedef autoPtr<thermophysicalProperties> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class thermophysicalPropertiesType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<thermophysicalProperties> New(const dictionary& dict)
			{
				return autoPtr<thermophysicalProperties>(new thermophysicalPropertiesType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = thermophysicalPropertiesType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"thermophysicalProperties" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class thermophysicalPropertiesType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<thermophysicalProperties> New(const dictionary& dict)
			{
				return autoPtr<thermophysicalProperties>(new thermophysicalPropertiesType(dict));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = thermophysicalPropertiesType::typeName) : lookup_(lookup)
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

			//- Construct from molecular weight
		FoamThermophysicalModels_EXPORT thermophysicalProperties(scalar W);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT thermophysicalProperties(const dictionary& dict);


		// Selectors

			//- Return a pointer to a new thermophysicalProperties created from name
		static FoamThermophysicalModels_EXPORT autoPtr<thermophysicalProperties> New(const word& name);

		//- Return a pointer to a new thermophysicalProperties
		//  created from dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<thermophysicalProperties> New(const dictionary& dict);


		//- Destructor
		virtual ~thermophysicalProperties()
		{}


		// Member Functions

			// Physical constants which define the specie

				//- Molecular weight [kg/kmol]
		inline scalar W() const;

		//- Limit the temperature to be in the range Tlow_ to Thigh_
		inline scalar limit(const scalar T) const;


		// Fundamental equation of state properties

			//- Liquid density [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual scalar rho(scalar p, scalar T) const = 0;

		//- Liquid compressibility rho/p [s^2/m^2]
		//  Note: currently it is assumed the liquid is incompressible
		FoamThermophysicalModels_EXPORT virtual scalar psi(scalar p, scalar T) const = 0;

		//- Return (Cp - Cv) [J/(kg K]
		//  Note: currently it is assumed the liquid is incompressible
		//  so CpMCv 0
		FoamThermophysicalModels_EXPORT virtual scalar CpMCv(scalar p, scalar T) const = 0;


		// Fundamental thermodynamic properties

			//- Heat capacity at constant pressure [J/kg/K]
		FoamThermophysicalModels_EXPORT virtual scalar Cp(const scalar p, const scalar T) const = 0;

		//- Sensible enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Hs(const scalar p, const scalar T) const = 0;

		//- Chemical enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Hc() const = 0;

		//- Absolute Enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual scalar Ha(const scalar p, const scalar T) const = 0;

		// Entropy [J/kg/K]
		FoamThermophysicalModels_EXPORT virtual scalar S(const scalar p, const scalar T) const = 0;


		// Physical properties

			//- Liquid viscosity [Pa s]
		FoamThermophysicalModels_EXPORT virtual scalar mu(scalar p, scalar T) const = 0;

		//- Liquid thermal conductivity  [W/m/K]
		FoamThermophysicalModels_EXPORT virtual scalar kappa(scalar p, scalar T) const = 0;

		//- Liquid thermal diffusivity of enthalpy [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual scalar alphah(const scalar p, const scalar T) const = 0;


		// I-O

			//- Read and set the properties present it the given dictionary
		FoamThermophysicalModels_EXPORT void readIfPresent(const dictionary& dict);

		//- Write the function coefficients
		FoamThermophysicalModels_EXPORT virtual void writeData(Ostream& os) const = 0;

		//- Write dictionary to Ostream
		FoamThermophysicalModels_EXPORT void write(Ostream& os) const;

		//- Ostream Operator
		friend FoamThermophysicalModels_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const thermophysicalProperties& l
				);
	};


	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const thermophysicalProperties& l);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <thermophysicalPropertiesI.hxx>

#endif // !_thermophysicalProperties_Header
