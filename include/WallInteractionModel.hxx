#pragma once
#ifndef _WallInteractionModel_Header
#define _WallInteractionModel_Header

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
	tnbLib::WallInteractionModel

Description
	Templated wall interaction model class

SourceFiles
	WallInteractionModel.C
	WallInteractionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamWallInteractionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamWallInteractionModel_EXPORT_DEFINE
#define FoamWallInteractionModel_EXPORT __declspec(dllexport)
#else
#define FoamWallInteractionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class WallInteractionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class WallInteractionModel
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
		//TypeName("WallInteractionModel");
		static const char* typeName_() { return "WallInteractionModel"; }
		static FoamWallInteractionModel_EXPORT const ::tnbLib::word typeName;
		static FoamWallInteractionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			WallInteractionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/

		typedef autoPtr<WallInteractionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamWallInteractionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamWallInteractionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamWallInteractionModel_EXPORT void destroydictionaryConstructorTables();

		template <class WallInteractionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<WallInteractionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<WallInteractionModel>(new WallInteractionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = WallInteractionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"WallInteractionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class WallInteractionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<WallInteractionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<WallInteractionModel>(new WallInteractionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = WallInteractionModelType::typeName) : lookup_(
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
		WallInteractionModel(CloudType& owner);

		//- Construct from components
		WallInteractionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);


		//- Destructor
		virtual ~WallInteractionModel();


		//- Selector
		static autoPtr<WallInteractionModel<CloudType>> New
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

			//- Apply wall correction
		virtual void correct(typename CloudType::parcelType& p) = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeWallInteractionModel(CloudType)                                    \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(WallInteractionModel<CloudType>, 0);   \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        WallInteractionModel<CloudType>,                                       \
        dictionary                                                             \
    );


#define makeWallInteractionModelType(SS, CloudType)                            \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(SS<CloudType>, 0);                     \
                                                                               \
    WallInteractionModel<CloudType>::                                          \
        adddictionaryConstructorToTable<SS<CloudType>>                         \
            add##SS##CloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WallInteractionModelI.hxx>
#include <WallInteractionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <WallInteractionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WallInteractionModel_Header
