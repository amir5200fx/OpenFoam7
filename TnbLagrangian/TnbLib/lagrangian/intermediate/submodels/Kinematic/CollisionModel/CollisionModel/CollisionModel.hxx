#pragma once
#ifndef _CollisionModel_Header
#define _CollisionModel_Header

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
	tnbLib::CollisionModel

Description
	Templated collision model class.

SourceFiles
	CollisionModel.C
	CollisionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCollisionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamCollisionModel_EXPORT_DEFINE
#define FoamCollisionModel_EXPORT __declspec(dllexport)
#else
#define FoamCollisionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class CollisionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class CollisionModel
		:
		public CloudSubModelBase<CloudType>
	{
		// Protected data

			//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;


	public:

		//- Runtime type information
		//TypeName("collisionModel");
		static const char* typeName_() { return "collisionModel"; }
		static FoamCollisionModel_EXPORT const ::tnbLib::word typeName;
		static FoamCollisionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			CollisionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/

		typedef autoPtr<CollisionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamCollisionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamCollisionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamCollisionModel_EXPORT void destroydictionaryConstructorTables();

		template <class CollisionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<CollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<CollisionModel>(new CollisionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = CollisionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "CollisionModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class CollisionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<CollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<CollisionModel>(new CollisionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = CollisionModelType::typeName) : lookup_(
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
		CollisionModel(CloudType& owner);

		//- Construct from components
		CollisionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		CollisionModel(const CollisionModel<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CollisionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~CollisionModel();


		//- Selector
		static autoPtr<CollisionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Return the number of times to subcycle the current
			//  timestep to meet the criteria of the collision model
		virtual label nSubCycles() const = 0;

		// Collision function
		virtual void collide() = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeCollisionModel(CloudType)                                          \
                                                                               \
    typedef tnbLib::CloudType::collidingCloudType collidingCloudType;            \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::CollisionModel<collidingCloudType>,                              \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            CollisionModel<collidingCloudType>,                                \
            dictionary                                                         \
        );                                                                     \
    }


#define makeCollisionModelType(SS, CloudType)                                  \
                                                                               \
    typedef tnbLib::CloudType::collidingCloudType collidingCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<collidingCloudType>, 0);      \
                                                                               \
    tnbLib::CollisionModel<collidingCloudType>::                                 \
        adddictionaryConstructorToTable<tnbLib::SS<collidingCloudType>>          \
            add##SS##CloudType##collidingCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CollisionModelI.hxx>
#include <CollisionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <CollisionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CollisionModel_Header
