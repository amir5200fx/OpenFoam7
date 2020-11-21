#pragma once
#ifndef _HeatTransferModelTemplate_Header
#define _HeatTransferModelTemplate_Header

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
	tnbLib::HeatTransferModel

Description
	Templated heat transfer model class

SourceFiles
	HeatTransferModel.C
	HeatTransferModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <Switch.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamHeatTransferModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamHeatTransferModel_EXPORT_DEFINE
#define FoamHeatTransferModel_EXPORT __declspec(dllexport)
#else
#define FoamHeatTransferModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class HeatTransferModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class HeatTransferModel
		:
		public CloudSubModelBase<CloudType>
	{
		// Private Data

			//- Apply Bird's correction to the htc
		const Switch BirdCorrection_;


	public:

		//- Runtime type information
		//TypeName("heatTransferModel");
		static const char* typeName_() { return "heatTransferModel"; }
		static FoamHeatTransferModel_EXPORT const ::tnbLib::word typeName;
		static FoamHeatTransferModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			HeatTransferModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<HeatTransferModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamHeatTransferModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamHeatTransferModel_EXPORT void constructdictionaryConstructorTables();
		static FoamHeatTransferModel_EXPORT void destroydictionaryConstructorTables();

		template <class HeatTransferModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<HeatTransferModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<HeatTransferModel>(new HeatTransferModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = HeatTransferModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "HeatTransferModel"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class HeatTransferModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<HeatTransferModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<HeatTransferModel>(new HeatTransferModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = HeatTransferModelType::typeName) : lookup_(
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
		HeatTransferModel(CloudType& owner);

		//- Construct from dictionary
		HeatTransferModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		HeatTransferModel(const HeatTransferModel<CloudType>& htm);

		//- Construct and return a clone
		virtual autoPtr<HeatTransferModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~HeatTransferModel();


		//- Selector
		static autoPtr<HeatTransferModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			// Access

				//- Return the Bird htc correction flag
		const Switch& BirdCorrection() const;


		// Evaluation

			//- Nusselt number
		virtual scalar Nu
		(
			const scalar Re,
			const scalar Pr
		) const = 0;

		//- Return heat transfer coefficient
		virtual scalar htc
		(
			const scalar dp,
			const scalar Re,
			const scalar Pr,
			const scalar kappa,
			const scalar NCpW
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeHeatTransferModel(CloudType)                                       \
                                                                               \
    typedef tnbLib::CloudType::thermoCloudType thermoCloudType;                  \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::HeatTransferModel<thermoCloudType>,                              \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            HeatTransferModel<thermoCloudType>,                                \
            dictionary                                                         \
        );                                                                     \
    }


#define makeHeatTransferModelType(SS, CloudType)                               \
                                                                               \
    typedef tnbLib::CloudType::thermoCloudType thermoCloudType;                  \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<thermoCloudType>, 0);         \
                                                                               \
    tnbLib::HeatTransferModel<thermoCloudType>::                                 \
        adddictionaryConstructorToTable<tnbLib::SS<thermoCloudType>>             \
            add##SS##CloudType##thermoCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <HeatTransferModelTemplateI.hxx>
#include <HeatTransferModelTemplateNew_Imp.hxx>

//#ifdef NoRepository
//#include <HeatTransferModelTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_HeatTransferModelTemplate_Header
