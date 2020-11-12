#pragma once
#ifndef _basicSolidChemistryModel_Header
#define _basicSolidChemistryModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::basicSolidChemistryModel

Description
	Chemistry model for solid thermodynamics

SourceFiles
	basicSolidChemistryModelI.H
	basicSolidChemistryModel.C
	newChemistrySolidModel.C

\*---------------------------------------------------------------------------*/

#include <basicChemistryModel.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <solidReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	/*---------------------------------------------------------------------------*\
						 class basicSolidChemistryModel Declaration
	\*---------------------------------------------------------------------------*/

	class basicSolidChemistryModel
		:
		public basicChemistryModel
	{
	protected:

		// Protected data

			//- Solid thermo
		solidReactionThermo& solidThermo_;


	public:

		//- Runtime type information
		//TypeName("basicSolidChemistryModel");
		static const char* typeName_() { return "basicSolidChemistryModel"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Thermo type
		typedef solidReactionThermo reactionThermo;


		//- Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			basicSolidChemistryModel,
			thermo,
			(solidReactionThermo& thermo),
			(thermo)
		);*/
		
		typedef autoPtr<basicSolidChemistryModel> (*thermoConstructorPtr)(solidReactionThermo& thermo);
		typedef HashTable<thermoConstructorPtr, word, string::hash> thermoConstructorTable;
		static FoamThermophysicalModels_EXPORT thermoConstructorTable* thermoConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructthermoConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroythermoConstructorTables();

		template <class basicSolidChemistryModelType>
		class addthermoConstructorToTable
		{
		public:
			static autoPtr<basicSolidChemistryModel> New(solidReactionThermo& thermo)
			{
				return autoPtr<basicSolidChemistryModel>(new basicSolidChemistryModelType(thermo));
			}

			addthermoConstructorToTable(const word& lookup = basicSolidChemistryModelType::typeName)
			{
				constructthermoConstructorTables();
				if (!thermoConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"basicSolidChemistryModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addthermoConstructorToTable() { destroythermoConstructorTables(); }
		};

		template <class basicSolidChemistryModelType>
		class addRemovablethermoConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<basicSolidChemistryModel> New(solidReactionThermo& thermo)
			{
				return autoPtr<basicSolidChemistryModel>(new basicSolidChemistryModelType(thermo));
			}

			addRemovablethermoConstructorToTable(const word& lookup = basicSolidChemistryModelType::typeName) : lookup_(
				lookup)
			{
				constructthermoConstructorTables();
				thermoConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablethermoConstructorToTable()
			{
				if (thermoConstructorTablePtr_) { thermoConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from thermo
		FoamThermophysicalModels_EXPORT basicSolidChemistryModel(solidReactionThermo& thermo);

		//- Construct as copy (not implemented)
		FoamThermophysicalModels_EXPORT basicSolidChemistryModel(const basicSolidChemistryModel&);


		//- Selector
		static FoamThermophysicalModels_EXPORT autoPtr<basicSolidChemistryModel> New(solidReactionThermo& thermo);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~basicSolidChemistryModel();


		// Member Functions

			//- Return access to the solid thermo package
		inline solidReactionThermo& solidThermo();

		//- Return const access to the solid thermo package
		inline const solidReactionThermo& solidThermo() const;

		//- Return total gases mass source term [kg/m^3/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField::Internal> RRg() const = 0;

		//- Return total solids mass source term [kg/m^3/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField::Internal> RRs() const = 0;

		//- Return chemical source terms for solids [kg/m^3/s]
		FoamThermophysicalModels_EXPORT virtual const volScalarField::Internal& RRs
		(
			const label i
		) const = 0;

		//- Return chemical source terms for gases [kg/m^3/s]
		FoamThermophysicalModels_EXPORT virtual const volScalarField::Internal& RRg
		(
			const label i
		) const = 0;

		//- Returns the reaction rate of the speciei in reactionI
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField::Internal> calculateRR
		(
			const label reactionI,
			const label speciei
		) const;

		//- Return sensible enthalpy for gas i [J/Kg]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> gasHs
		(
			const volScalarField& p,
			const volScalarField& T,
			const label i
		) const = 0;

		//- Return specie Table for gases
		FoamThermophysicalModels_EXPORT virtual const speciesTable& gasTable() const = 0;

		//- Set reacting status of cell, celli
		FoamThermophysicalModels_EXPORT virtual void setCellReacting(const label celli, const bool active) = 0;

		//- Calculates the reaction rates
		FoamThermophysicalModels_EXPORT virtual void calculate() = 0;

		//- Return const access to the total source terms
		FoamThermophysicalModels_EXPORT virtual const volScalarField::Internal& RR
		(
			const label i
		) const;

		//- Return non-const access to the total source terms
		FoamThermophysicalModels_EXPORT virtual volScalarField::Internal& RR(const label i);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamThermophysicalModels_EXPORT void operator=(const basicSolidChemistryModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <basicSolidChemistryModelI.hxx>

#endif // !_basicSolidChemistryModel_Header
