#pragma once
#ifndef _CompositionModel_Header
#define _CompositionModel_Header

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
	tnbLib::CompositionModel

Description
	Templated reacting parcel composition model class
	Consists of carrier species (via thermo package), and additional liquids
	and solids

SourceFiles
	CompositionModel.C
	CompositionModelNew.C

\*---------------------------------------------------------------------------*/

#include <CloudSubModelBase.hxx>
#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <PtrList.hxx>
#include <SLGThermo.hxx>

#include <phasePropertiesList.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCompositionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamCompositionModel_EXPORT_DEFINE
#define FoamCompositionModel_EXPORT __declspec(dllexport)
#else
#define FoamCompositionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class CompositionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class CompositionModel
		:
		public CloudSubModelBase<CloudType>
	{
		// Private Data

			//- Reference to the thermo database
		const SLGThermo& thermo_;

		//- List of phase properties
		phasePropertiesList phaseProps_;


	public:

		//- Runtime type information
		//TypeName("compositionModel");
		static const char* typeName_() { return "compositionModel"; }
		static FoamCompositionModel_EXPORT const ::tnbLib::word typeName;
		static FoamCompositionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			CompositionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<CompositionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamCompositionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamCompositionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamCompositionModel_EXPORT void destroydictionaryConstructorTables();

		template <class CompositionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<CompositionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<CompositionModel>(new CompositionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = CompositionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "CompositionModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class CompositionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<CompositionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<CompositionModel>(new CompositionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = CompositionModelType::typeName) : lookup_(
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
		CompositionModel(CloudType& owner);

		//- Construct from dictionary
		CompositionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		CompositionModel(const CompositionModel<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CompositionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~CompositionModel();


		//- Selector
		static autoPtr<CompositionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Member Functions

			// Access

				//- Return the thermo database
		const SLGThermo& thermo() const;


		// Composition lists

			//- Return the carrier components (wrapper function)
		const basicSpecieMixture& carrier() const;

		//- Return the global (additional) liquids
		const liquidMixtureProperties& liquids() const;

		//- Return the global (additional) solids
		const solidMixtureProperties& solids() const;

		//- Return the list of phase properties
		const phasePropertiesList& phaseProps() const;

		//- Return the number of phases
		label nPhase() const;


		// Phase properties

			//- Return the list of phase type names
			//  If only 1 phase, return the component names of that phase
		const wordList& phaseTypes() const;

		//- Return the list of state labels (s), (l), (g) etc.
		const wordList& stateLabels() const;

		//- Return the list of component names for phaseI
		const wordList& componentNames(const label phaseI) const;

		//- Return global id of component cmptName in carrier thermo
		label carrierId
		(
			const word& cmptName,
			const bool allowNotFound = false
		) const;

		//- Return local id of component cmptName in phase phaseI
		label localId
		(
			const label phaseI,
			const word& cmptName,
			const bool allowNotFound = false
		) const;

		//- Return carrier id of component given local id
		label localToCarrierId
		(
			const label phaseI,
			const label id,
			const bool allowNotFound = false
		) const;

		//- Return the list of phase phaseI mass fractions
		const scalarField& Y0(const label phaseI) const;

		//- Return the list of phase phaseI volume fractions fractions
		//  based on supplied mass fractions Y
		scalarField X(const label phaseI, const scalarField& Y) const;


		// Mixture properties

			//- Return the list of mixture mass fractions
			//  If only 1 phase, return component fractions of that phase
		virtual const scalarField& YMixture0() const = 0;

		// Indices of gas, liquid and solid phases in phase properties
		// list - returns -1 if not applicable

			//- Gas id
		virtual label idGas() const = 0;

		//- Liquid id
		virtual label idLiquid() const = 0;

		//- Solid id
		virtual label idSolid() const = 0;


		// Evaluation

			//- Return total enthalpy for the phase phaseI
		virtual scalar H
		(
			const label phaseI,
			const scalarField& Y,
			const scalar p,
			const scalar T
		) const;

		//- Return sensible enthalpy for the phase phaseI
		virtual scalar Hs
		(
			const label phaseI,
			const scalarField& Y,
			const scalar p,
			const scalar T
		) const;

		//- Return chemical enthalpy for the phase phaseI
		virtual scalar Hc
		(
			const label phaseI,
			const scalarField& Y,
			const scalar p,
			const scalar T
		) const;

		//- Return specific heat caoacity for the phase phaseI
		virtual scalar Cp
		(
			const label phaseI,
			const scalarField& Y,
			const scalar p,
			const scalar T
		) const;

		//- Return latent heat for the phase phaseI
		virtual scalar L
		(
			const label phaseI,
			const scalarField& Y,
			const scalar p,
			const scalar T
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeCompositionModel(CloudType)                                        \
                                                                               \
    typedef tnbLib::CloudType::reactingCloudType reactingCloudType;              \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::CompositionModel<reactingCloudType>,                             \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            CompositionModel<reactingCloudType>,                               \
            dictionary                                                         \
        );                                                                     \
    }


#define makeCompositionModelType(SS, CloudType)                                \
                                                                               \
    typedef tnbLib::CloudType::reactingCloudType reactingCloudType;              \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<reactingCloudType>, 0);       \
                                                                               \
    tnbLib::CompositionModel<reactingCloudType>::                                \
        adddictionaryConstructorToTable<tnbLib::SS<reactingCloudType>>           \
            add##SS##CloudType##reactingCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CompositionModelI.hxx>
#include <CompositionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <CompositionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CompositionModel_Header
