#pragma once
#ifndef _liquidProperties_Header
#define _liquidProperties_Header

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
	tnbLib::liquidProperties

Description
	The thermophysical properties of a liquid

SourceFiles
	liquidProperties.C

\*---------------------------------------------------------------------------*/

#include <thermophysicalProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class liquidProperties Declaration
	\*---------------------------------------------------------------------------*/

	class liquidProperties
		:
		public thermophysicalProperties
	{
		// Private Data

			//- Critical temperature [K]
		scalar Tc_;

		//- Critical pressure [Pa]
		scalar Pc_;

		//- Critical volume [m^3/kmol]
		scalar Vc_;

		//- Critical compressibility factor []
		scalar Zc_;

		//- Triple point temperature [K]
		scalar Tt_;

		//- Triple point pressure [Pa]
		scalar Pt_;

		//- Normal boiling temperature [K]
		scalar Tb_;

		//- Dipole moment []
		scalar dipm_;

		//- Pitzer's accentric factor []
		scalar omega_;

		//- Solubility parameter [(J/m^3)^0.5]
		scalar delta_;


	public:

		//TypeName("liquid");
		static const char* typeName_() { return "liquid"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			liquidProperties,
			,
			(),
			()
		);*/

		typedef autoPtr<liquidProperties> (*ConstructorPtr)();
		typedef HashTable<ConstructorPtr, word, string::hash> ConstructorTable;
		static FoamThermophysicalModels_EXPORT ConstructorTable* ConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyConstructorTables();

		template <class liquidPropertiesType>
		class addConstructorToTable
		{
		public:
			static autoPtr<liquidProperties> New() { return autoPtr<liquidProperties>(new liquidPropertiesType()); }

			addConstructorToTable(const word& lookup = liquidPropertiesType::typeName)
			{
				constructConstructorTables();
				if (!ConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "liquidProperties" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addConstructorToTable() { destroyConstructorTables(); }
		};

		template <class liquidPropertiesType>
		class addRemovableConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<liquidProperties> New() { return autoPtr<liquidProperties>(new liquidPropertiesType()); }

			addRemovableConstructorToTable(const word& lookup = liquidPropertiesType::typeName) : lookup_(lookup)
			{
				constructConstructorTables();
				ConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableConstructorToTable() { if (ConstructorTablePtr_) { ConstructorTablePtr_->erase(lookup_); } }
		};

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			liquidProperties,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/

		typedef autoPtr<liquidProperties> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class liquidPropertiesType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<liquidProperties> New(const dictionary& dict)
			{
				return autoPtr<liquidProperties>(new liquidPropertiesType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = liquidPropertiesType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "liquidProperties" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class liquidPropertiesType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<liquidProperties> New(const dictionary& dict)
			{
				return autoPtr<liquidProperties>(new liquidPropertiesType(dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = liquidPropertiesType::typeName) : lookup_(
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

			//- Construct from components
		FoamThermophysicalModels_EXPORT liquidProperties
		(
			scalar W,
			scalar Tc,
			scalar Pc,
			scalar Vc,
			scalar Zc,
			scalar Tt,
			scalar Pt,
			scalar Tb,
			scalar dipm,
			scalar omega,
			scalar delta
		);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT liquidProperties(const dictionary& dict);

		//- Construct and return clone
		FoamThermophysicalModels_EXPORT virtual autoPtr<liquidProperties> clone() const = 0;


		// Selectors

			//- Return a pointer to a new liquidProperties created from name
		static FoamThermophysicalModels_EXPORT autoPtr<liquidProperties> New(const word& name);

		//- Return a pointer to a new liquidProperties created from dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<liquidProperties> New(const dictionary& dict);


		//- Destructor
		virtual ~liquidProperties()
		{}


		// Static data

			//- Is the equation of state is incompressible i.e. rho != f(p)
		static const bool incompressible = true;

		//- Is the equation of state is isochoric i.e. rho = const
		static const bool isochoric = false;


		// Member Functions

			// Physical constants which define the specie

				//- No of moles of this species in mixture
				//  Note Mixing of liquidProperties is not currently supported
				//  so Y = 1
		inline scalar Y() const;

		//- Critical temperature [K]
		inline scalar Tc() const;

		//- Critical pressure [Pa]
		inline scalar Pc() const;

		//- Critical volume [m^3/kmol]
		inline scalar Vc() const;

		//- Critical compressibilty factor
		inline scalar Zc() const;

		//- Triple point temperature [K]
		inline scalar Tt() const;

		//- Triple point pressure [Pa]
		inline scalar Pt() const;

		//- Normal boiling temperature [K]
		inline scalar Tb() const;

		//- Dipole moment []
		inline scalar dipm() const;

		//- Pitzer's ascentric factor []
		inline scalar omega() const;

		//- Solubility parameter [(J/m^3)^(1/2)]
		inline scalar delta() const;

		//- Limit the temperature to be in the range Tlow_ to Thigh_
		inline scalar limit(const scalar T) const;


		// Fundamental equation of state properties

			//- Liquid compressibility rho/p [s^2/m^2]
			//  Note: currently it is assumed the liquid is incompressible
		inline scalar psi(scalar p, scalar T) const;

		//- Return (Cp - Cv) [J/(kg K]
		//  Note: currently it is assumed the liquid is incompressible
		//  so CpMCv = 0
		inline scalar CpMCv(scalar p, scalar T) const;


		// Fundamental thermodynamic properties

			//- Sensible enthalpy [J/kg]
		inline scalar Hs(const scalar p, const scalar T) const;

		//- Chemical enthalpy [J/kg]
		inline scalar Hc() const;

		//- Absolute Enthalpy [J/kg]
		inline scalar Ha(const scalar p, const scalar T) const;

		// Entropy [J/kg/K]
		FoamThermophysicalModels_EXPORT scalar S(const scalar p, const scalar T) const;


		// Physical properties

			//- Vapour pressure [Pa]
		virtual scalar pv(scalar p, scalar T) const = 0;

		//- Heat of vapourisation [J/kg]
		virtual scalar hl(scalar p, scalar T) const = 0;

		//- Liquid enthalpy [J/kg] - reference to 298.15 K
		virtual scalar h(scalar p, scalar T) const = 0;

		//- Vapour heat capacity [J/kg/K]
		virtual scalar Cpg(scalar p, scalar T) const = 0;

		//- Liquid viscosity [Pa s]
		virtual scalar mu(scalar p, scalar T) const = 0;

		//- Vapour viscosity [Pa s]
		virtual scalar mug(scalar p, scalar T) const = 0;

		//- Liquid thermal conductivity  [W/m/K]
		virtual scalar kappa(scalar p, scalar T) const = 0;

		//- Liquid thermal diffusivity of enthalpy [kg/m/s]
		inline scalar alphah(const scalar p, const scalar T) const;

		//- Vapour thermal conductivity  [W/m/K]
		virtual scalar kappag(scalar p, scalar T) const = 0;

		//- Surface tension [N/m]
		virtual scalar sigma(scalar p, scalar T) const = 0;

		//- Vapour diffussivity [m2/s]
		virtual scalar D(scalar p, scalar T) const = 0;

		//- Vapour diffussivity [m2/s] with specified binary pair
		virtual scalar D(scalar p, scalar T, scalar Wb) const = 0;

		//- Invert the vapour pressure relationship to retrieve the
		//  boiling temperuture as a function of pressure
		virtual FoamThermophysicalModels_EXPORT scalar pvInvert(scalar p) const;


		// I-O

			//- Read and set the properties present it the given dictionary
		FoamThermophysicalModels_EXPORT void readIfPresent(const dictionary& dict);

		//- Read and set the function coefficients
		//  if present it the given dictionary
		template<class Func>
		inline void readIfPresent
		(
			Func& f,
			const word& name,
			const dictionary& dict
		);

		//- Read and set the function coefficients
		//  if present it the given dictionary
		template<class Liquid>
		inline void readIfPresent(Liquid& l, const dictionary& dict);

		//- Write the function coefficients
		FoamThermophysicalModels_EXPORT virtual void writeData(Ostream& os) const = 0;

		//- Write dictionary to Ostream
		FoamThermophysicalModels_EXPORT void write(Ostream& os) const;

		//- Write the data for each of the property functions
		template<class Liquid>
		inline void writeData(const Liquid& l, Ostream& os) const;

		//- Ostream Operator
		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const liquidProperties& l);
	};


	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const liquidProperties& l);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <liquidPropertiesI.hxx>

#endif // !_liquidProperties_Header
