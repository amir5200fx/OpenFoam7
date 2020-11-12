#pragma once
#ifndef _BinaryCollisionModel_Header
#define _BinaryCollisionModel_Header

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
	tnbLib::BinaryCollisionModel

Description
	Templated DSMC particle collision class

SourceFiles
	BinaryCollisionModel.C
	BinaryCollisionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamBinaryCollisionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamBinaryCollisionModel_EXPORT_DEFINE
#define FoamBinaryCollisionModel_EXPORT __declspec(dllexport)
#else
#define FoamBinaryCollisionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class BinaryCollisionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class BinaryCollisionModel
	{
		// Private Data

			//- The cloud dictionary
		const dictionary& dict_;

		// reference to the owner cloud class
		CloudType& owner_;

		//- The coefficients dictionary
		const dictionary coeffDict_;


	public:

		//- Runtime type information
		//TypeName("BinaryCollisionModel");
		static const char* typeName_() { return "BinaryCollisionModel"; }
		static FoamBinaryCollisionModel_EXPORT const ::tnbLib::word typeName;
		static FoamBinaryCollisionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			BinaryCollisionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<BinaryCollisionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamBinaryCollisionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamBinaryCollisionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamBinaryCollisionModel_EXPORT void destroydictionaryConstructorTables();

		template <class BinaryCollisionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<BinaryCollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<BinaryCollisionModel>(new BinaryCollisionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = BinaryCollisionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"BinaryCollisionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class BinaryCollisionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<BinaryCollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<BinaryCollisionModel>(new BinaryCollisionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = BinaryCollisionModelType::typeName) : lookup_(
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

		//- Construct null from owner
		BinaryCollisionModel(CloudType& owner);

		//- Construct from components
		BinaryCollisionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);


		//- Destructor
		virtual ~BinaryCollisionModel();


		//- Selector
		static autoPtr<BinaryCollisionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return the owner cloud object
		const CloudType& owner() const;

		//- Return non-const access to the owner cloud object
		CloudType& owner();

		//- Return the dictionary
		const dictionary& dict() const;

		//- Return the coefficients dictionary
		const dictionary& coeffDict() const;


		// Member Functions

			//- Flag to indicate whether model activates collision model
		virtual bool active() const = 0;

		//- Return the collision cross section * relative velocity product
		virtual scalar sigmaTcR
		(
			const typename CloudType::parcelType& pP,
			const typename CloudType::parcelType& pQ
		) const = 0;

		//- Apply collision
		virtual void collide
		(
			typename CloudType::parcelType& pP,
			typename CloudType::parcelType& pQ
		) = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeBinaryCollisionModel(CloudType)                                    \
                                                                               \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        BinaryCollisionModel<CloudType>,                                       \
        0                                                                      \
    );                                                                         \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        BinaryCollisionModel<CloudType>,                                       \
        dictionary                                                             \
    );


#define makeBinaryCollisionModelType(SS, CloudType)                            \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(SS<CloudType>, 0);                     \
                                                                               \
    BinaryCollisionModel<CloudType>::                                          \
        adddictionaryConstructorToTable<SS<CloudType>>                         \
            add##SS##CloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <BinaryCollisionModelI.hxx>
#include <BinaryCollisionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <BinaryCollisionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_BinaryCollisionModel_Header
