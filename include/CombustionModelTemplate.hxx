#pragma once
#ifndef _CombustionModelTemplate_Header
#define _CombustionModelTemplate_Header

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
	tnbLib::CombustionModel

Description
	Combustion models for templated thermodynamics

SourceFiles
	CombustionModelI.H
	CombustionModel.C
	CombustionModelNew.C

\*---------------------------------------------------------------------------*/

#include <combustionModel.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamCombustionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamCombustionModel_EXPORT_DEFINE
#define FoamCombustionModel_EXPORT __declspec(dllexport)
#else
#define FoamCombustionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 class CombustionModel Declaration
	\*---------------------------------------------------------------------------*/

	// Forward Declarations
	class compressibleTurbulenceModel;  //added by amir

	template<class ReactionThermo>
	class CombustionModel
		:
		public combustionModel
	{
	public:

		//- Thermo type
		typedef ReactionThermo reactionThermo;


		//- Runtime type information
		//TypeName("CombustionModel");
		static const char* typeName_() { return "CombustionModel"; }
		static FoamCombustionModel_EXPORT const ::tnbLib::word typeName;
		static FoamCombustionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			CombustionModel,
			dictionary,
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
				),
				(modelType, thermo, turb, combustionProperties)
		);*/

		typedef autoPtr<CombustionModel> (*dictionaryConstructorPtr)(const word& modelType, ReactionThermo& thermo,
		                                                             const compressibleTurbulenceModel& turb,
		                                                             const word& combustionProperties);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamCombustionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamCombustionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamCombustionModel_EXPORT void destroydictionaryConstructorTables();

		template <class CombustionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<CombustionModel> New(const word& modelType, ReactionThermo& thermo,
			                                    const compressibleTurbulenceModel& turb, const word& combustionProperties)
			{
				return autoPtr<CombustionModel>(new CombustionModelType(modelType, thermo, turb, combustionProperties));
			}

			adddictionaryConstructorToTable(const word& lookup = CombustionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "CombustionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class CombustionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<CombustionModel> New(const word& modelType, ReactionThermo& thermo,
			                                    const compressibleTurbulenceModel& turb, const word& combustionProperties)
			{
				return autoPtr<CombustionModel>(new CombustionModelType(modelType, thermo, turb, combustionProperties));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = CombustionModelType::typeName) : lookup_(lookup)
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
		CombustionModel
		(
			const word& modelType,
			ReactionThermo& thermo,
			const compressibleTurbulenceModel& turb,
			const word& combustionProperties
		);


		//- Selector
		static autoPtr<CombustionModel> New
		(
			ReactionThermo& thermo,
			const compressibleTurbulenceModel& turb,
			const word& combustionProperties = combustionPropertiesName
		);


		//- Destructor
		virtual ~CombustionModel();


		// Member Functions

			//- Return access to the thermo package
		virtual ReactionThermo& thermo() = 0;

		//- Return const access to the thermo package
		virtual const ReactionThermo& thermo() const = 0;


		// IO

			//- Update properties from given dictionary
		virtual bool read();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CombustionModelTemplateI.hxx>

//#ifdef NoRepository
//#include "CombustionModelTemplate.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CombustionModelTemplate_Header
