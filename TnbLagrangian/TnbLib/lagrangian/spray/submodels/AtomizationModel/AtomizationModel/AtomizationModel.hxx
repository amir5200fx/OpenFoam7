#pragma once
#ifndef _AtomizationModel_Header
#define _AtomizationModel_Header

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
	tnbLib::AtomizationModel

Description
	Templated atomization model class

SourceFiles
	AtomizationModel.C
	AtomizationModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <vector.hxx>  // added by amir
#include <Random.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamAtomizationModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamAtomizationModel_EXPORT_DEFINE
#define FoamAtomizationModel_EXPORT __declspec(dllexport)
#else
#define FoamAtomizationModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class AtomizationModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class AtomizationModel
		:
		public CloudSubModelBase<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("atomizationModel");
		static const char* typeName_() { return "atomizationModel"; }
		static FoamAtomizationModel_EXPORT const ::tnbLib::word typeName;
		static FoamAtomizationModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			AtomizationModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<AtomizationModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamAtomizationModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamAtomizationModel_EXPORT void constructdictionaryConstructorTables();
		static FoamAtomizationModel_EXPORT void destroydictionaryConstructorTables();

		template <class AtomizationModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<AtomizationModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<AtomizationModel>(new AtomizationModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = AtomizationModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "AtomizationModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class AtomizationModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<AtomizationModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<AtomizationModel>(new AtomizationModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = AtomizationModelType::typeName) : lookup_(
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
		AtomizationModel(CloudType& owner);

		//- Construct from dictionary
		AtomizationModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		AtomizationModel(const AtomizationModel<CloudType>& am);

		//- Construct and return a clone
		virtual autoPtr<AtomizationModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~AtomizationModel();


		//- Selector
		static autoPtr<AtomizationModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			//- Average temperature calculation
		scalar Taverage(const scalar& Tliq, const scalar& Tc) const;

		//- Initial value of liquidCore
		virtual scalar initLiquidCore() const = 0;

		//- Flag to indicate if chi needs to be calculated
		virtual bool calcChi() const = 0;

		virtual void update
		(
			const scalar dt,
			scalar& d,
			scalar& liquidCore,
			scalar& tc,
			const scalar rho,
			const scalar mu,
			const scalar sigma,
			const scalar volFlowRate,
			const scalar rhoAv,
			const scalar Urel,
			const vector& pos,
			const vector& injectionPos,
			const scalar pAmbient,
			const scalar chi,
			Random& rndGen
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeAtomizationModel(CloudType)                                        \
                                                                               \
    typedef tnbLib::CloudType::sprayCloudType sprayCloudType;                    \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::AtomizationModel<sprayCloudType>,                                \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            AtomizationModel<sprayCloudType>,                                  \
            dictionary                                                         \
        );                                                                     \
    }


#define makeAtomizationModelType(SS, CloudType)                                \
                                                                               \
    typedef tnbLib::CloudType::sprayCloudType sprayCloudType;                    \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<sprayCloudType>, 0);          \
                                                                               \
    tnbLib::AtomizationModel<sprayCloudType>::                                   \
        adddictionaryConstructorToTable<tnbLib::SS<sprayCloudType>>              \
            add##SS##CloudType##sprayCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <AtomizationModelI.hxx>
#include <AtomizationModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <AtomizationModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_AtomizationModel_Header
