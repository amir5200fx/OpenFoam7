#pragma once
#ifndef _regionModelFunctionObject_Header
#define _regionModelFunctionObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
	tnbLib::regionModels::regionModelFunctionObject

Description
	Region model function object base class

SourceFiles
	regionModelFunctionObject.C
	regionModelFunctionObjectNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace regionModels
	{

		class regionModel;

		/*---------------------------------------------------------------------------*\
						  Class regionModelFunctionObject Declaration
		\*---------------------------------------------------------------------------*/

		class regionModelFunctionObject
		{
		protected:

			// Protected data

				//- Dictionary
			dictionary dict_;

			//- Reference to the region model
			regionModel& regionModel_;

			//- Model type name
			word modelType_;


		public:

			//- Runtime type information
			//TypeName("regionModelFunctionObject");
			static const char* typeName_() { return "regionModelFunctionObject"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			//- Declare runtime constructor selection table
			/*declareRunTimeSelectionTable
			(
				autoPtr,
				regionModelFunctionObject,
				dictionary,
				(
					const dictionary& dict,
					regionModel& region
					),
					(dict, region)
			);*/
			
			typedef autoPtr<regionModelFunctionObject> (*dictionaryConstructorPtr)(
				const dictionary& dict, regionModel& region);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
			static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

			template <class regionModelFunctionObjectType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<regionModelFunctionObject> New(const dictionary& dict, regionModel& region)
				{
					return autoPtr<regionModelFunctionObject>(new regionModelFunctionObjectType(dict, region));
				}

				adddictionaryConstructorToTable(const word& lookup = regionModelFunctionObjectType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
							"regionModelFunctionObject" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class regionModelFunctionObjectType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<regionModelFunctionObject> New(const dictionary& dict, regionModel& region)
				{
					return autoPtr<regionModelFunctionObject>(new regionModelFunctionObjectType(dict, region));
				}

				addRemovabledictionaryConstructorToTable(
					const word& lookup = regionModelFunctionObjectType::typeName) : lookup_(lookup)
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

				//- Construct null from region
			FoamLagrangian_EXPORT regionModelFunctionObject(regionModel& region);

			//- Construct from dictionary
			FoamLagrangian_EXPORT regionModelFunctionObject
			(
				const dictionary& dict,
				regionModel& region,
				const word& modelType
			);

			//- Construct copy
			FoamLagrangian_EXPORT regionModelFunctionObject(const regionModelFunctionObject& ppm);

			//- Construct and return a clone
			virtual autoPtr<regionModelFunctionObject> clone() const
			{
				return autoPtr<regionModelFunctionObject>
					(
						new regionModelFunctionObject(*this)
						);
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~regionModelFunctionObject();


			//- Selector
			static FoamLagrangian_EXPORT autoPtr<regionModelFunctionObject> New
			(
				const dictionary& dict,
				regionModel& region,
				const word& modelType
			);


			// Member Functions

				// Evaluation

					//- Pre-evolve region hook
			FoamLagrangian_EXPORT virtual void preEvolveRegion();

			//- Post-evolve region hook
			FoamLagrangian_EXPORT virtual void postEvolveRegion();

			// I-O

				//- write
			FoamLagrangian_EXPORT virtual void write() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionModelFunctionObject_Header
