#pragma once
#ifndef _StochasticCollisionModel_Header
#define _StochasticCollisionModel_Header

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
	tnbLib::StochasticCollisionModel

Description
	Templated stochastic collision model class

SourceFiles
	StochasticCollisionModel.C
	StochasticCollisionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamStochasticCollisionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamStochasticCollisionModel_EXPORT_DEFINE
#define FoamStochasticCollisionModel_EXPORT __declspec(dllexport)
#else
#define FoamStochasticCollisionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class StochasticCollisionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class StochasticCollisionModel
		:
		public CloudSubModelBase<CloudType>
	{
	protected:

		//- Main collision routine
		virtual void collide
		(
			typename CloudType::parcelType::trackingData& td,
			const scalar dt
		) = 0;


	public:

		//- Runtime type information
		//TypeName("collisionModel");
		static const char* typeName_() { return "collisionModel"; }
		static FoamStochasticCollisionModel_EXPORT const ::tnbLib::word typeName;
		static FoamStochasticCollisionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			StochasticCollisionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<StochasticCollisionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamStochasticCollisionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamStochasticCollisionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamStochasticCollisionModel_EXPORT void destroydictionaryConstructorTables();

		template <class StochasticCollisionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<StochasticCollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<StochasticCollisionModel>(new StochasticCollisionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = StochasticCollisionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"StochasticCollisionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class StochasticCollisionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<StochasticCollisionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<StochasticCollisionModel>(new StochasticCollisionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = StochasticCollisionModelType::typeName) : lookup_(lookup)
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
		StochasticCollisionModel(CloudType& owner);

		//- Construct from dictionary
		StochasticCollisionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		StochasticCollisionModel(const StochasticCollisionModel<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<StochasticCollisionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~StochasticCollisionModel();


		//- Selector
		static autoPtr<StochasticCollisionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Update the model
		void update
		(
			typename CloudType::parcelType::trackingData& td,
			const scalar dt
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeStochasticCollisionModel(CloudType)                                \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::StochasticCollisionModel<kinematicCloudType>,                    \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            StochasticCollisionModel<kinematicCloudType>,                      \
            dictionary                                                         \
        );                                                                     \
    }


#define makeStochasticCollisionModelType(SS, CloudType)                        \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<kinematicCloudType>, 0);      \
                                                                               \
    tnbLib::StochasticCollisionModel<kinematicCloudType>::                       \
        adddictionaryConstructorToTable<tnbLib::SS<kinematicCloudType>>          \
            add##SS##CloudType##kinematicCloudType##ConstructorToTable_;



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <StochasticCollisionModelI.hxx>
#include <StochasticCollisionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <StochasticCollisionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_StochasticCollisionModel_Header
