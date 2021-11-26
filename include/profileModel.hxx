#pragma once
#ifndef _profileModel_Header
#define _profileModel_Header

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
	tnbLib::profileModel

Description
	Base class for profile models

SourceFiles
	profileModel.C

\*---------------------------------------------------------------------------*/

#include <FvOptions_Module.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class profileModel Declaration
	\*---------------------------------------------------------------------------*/

	class profileModel
	{

	protected:

		// Protected data

			//- Coefficients dictionary
		const dictionary dict_;

		//- Name of profile model
		const word name_;

		//- File name (optional)
		fileName fName_;


		// Protected Member Functions

			//- Return true if file name is set
		FoamFvOptions_EXPORT bool readFromFile() const;


	public:

		//- Runtime type information
		//TypeName("profileModel");
		static const char* typeName_() { return "profileModel"; }
		static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
		static FoamFvOptions_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			profileModel,
			dictionary,
			(
				const dictionary& dict,
				const word& modelName
				),
				(dict, modelName)
		);*/

		typedef autoPtr<profileModel> (*dictionaryConstructorPtr)(const dictionary& dict, const word& modelName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamFvOptions_EXPORT void constructdictionaryConstructorTables();
		static FoamFvOptions_EXPORT void destroydictionaryConstructorTables();

		template <class profileModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<profileModel> New(const dictionary& dict, const word& modelName)
			{
				return autoPtr<profileModel>(new profileModelType(dict, modelName));
			}

			adddictionaryConstructorToTable(const word& lookup = profileModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "profileModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class profileModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<profileModel> New(const dictionary& dict, const word& modelName)
			{
				return autoPtr<profileModel>(new profileModelType(dict, modelName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = profileModelType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Selectors

			//- Return a reference to the selected fvOption model
		static FoamFvOptions_EXPORT autoPtr<profileModel> New(const dictionary& dict);


		//- Constructor
		FoamFvOptions_EXPORT profileModel(const dictionary& dict, const word& modelName);


		//- Destructor
		FoamFvOptions_EXPORT virtual ~profileModel();


		// Member Functions

			// Access

				//- Return const access to the source name
		FoamFvOptions_EXPORT const word& name() const;


		// Evaluation

			//- Return the Cd and Cl for a given angle-of-attack
		FoamFvOptions_EXPORT virtual void Cdl
		(
			const scalar alpha,
			scalar& Cd,
			scalar& Cl
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_profileModel_Header
