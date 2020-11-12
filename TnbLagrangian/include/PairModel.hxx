#pragma once
#ifndef _PairModel_Header
#define _PairModel_Header

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
	tnbLib::PairModel

Description
	Templated pair interaction class

SourceFiles
	PairModel.C
	PairModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamPairModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamPairModel_EXPORT_DEFINE
#define FoamPairModel_EXPORT __declspec(dllexport)
#else
#define FoamPairModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class PairModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PairModel
	{
		// Private Data

			//- The CollisionModel dictionary
		const dictionary& dict_;

		//- Reference to the owner cloud class
		CloudType& owner_;

		//- The coefficients dictionary
		const dictionary coeffDict_;


	public:

		//- Runtime type information
		//TypeName("pairModel");
		static const char* typeName_() { return "pairModel"; }
		static FoamPairModel_EXPORT const ::tnbLib::word typeName;
		static FoamPairModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			PairModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/

		typedef autoPtr<PairModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamPairModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamPairModel_EXPORT void constructdictionaryConstructorTables();
		static FoamPairModel_EXPORT void destroydictionaryConstructorTables();

		template <class PairModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<PairModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PairModel>(new PairModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = PairModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "PairModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class PairModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<PairModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PairModel>(new PairModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = PairModelType::typeName) : lookup_(lookup)
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

			//- Construct from components
		PairModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);


		//- Destructor
		virtual ~PairModel();


		//- Selector
		static autoPtr<PairModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return the owner cloud object
		const CloudType& owner() const;

		//- Return the dictionary
		const dictionary& dict() const;

		//- Return the coefficients dictionary
		const dictionary& coeffDict() const;


		// Member Functions

			//- Whether the PairModel has a timestep limit that will
			//  require subCycling
		virtual bool controlsTimestep() const = 0;

		//- For PairModels that control the timestep, calculate the
		//  number of subCycles needed to satisfy the minimum
		//  allowable timestep
		virtual label nSubCycles() const = 0;

		//- Calculate the pair interaction between parcels
		virtual void evaluatePair
		(
			typename CloudType::parcelType& pA,
			typename CloudType::parcelType& pB
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makePairModel(CloudType)                                               \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(tnbLib::PairModel<tnbLib::CloudType>, 0); \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            PairModel<tnbLib::CloudType>,                                        \
            dictionary                                                         \
        );                                                                     \
    }


#define makePairModelType(SS, CloudType)                                       \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<tnbLib::CloudType>, 0);         \
                                                                               \
    tnbLib::PairModel<tnbLib::CloudType>::                                         \
        adddictionaryConstructorToTable<tnbLib::SS<tnbLib::CloudType>>             \
        add##SS##CloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PairModelI.hxx>
#include <PairModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <PairModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PairModel_Header
