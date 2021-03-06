#pragma once
#ifndef _PhaseChangeModelTemplate_Header
#define _PhaseChangeModelTemplate_Header

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
	tnbLib::PhaseChangeModel

Description
	Templated phase change model class

SourceFiles
	PhaseChangeModel.C
	PhaseChangeModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <primitiveFieldsFwd.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamPhaseChangeModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamPhaseChangeModel_EXPORT_DEFINE
#define FoamPhaseChangeModel_EXPORT __declspec(dllexport)
#else
#define FoamPhaseChangeModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class PhaseChangeModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PhaseChangeModel
		:
		public CloudSubModelBase<CloudType>
	{
	public:

		// Public enumerations

			//- Enthalpy transfer type
		enum enthalpyTransferType
		{
			etLatentHeat,
			etEnthalpyDifference
		};

		//- Name representations of enthalpy transfer types
		static const tnbLib::wordList enthalpyTransferTypeNames;


	protected:

		// Protected data

			//- Enthalpy transfer type enumeration
		enthalpyTransferType enthalpyTransfer_;


		// Counters

			//- Mass of lagrangian phase converted
		scalar dMass_;


		// Protected Member Functions

			//- Convert word to enthalpy transfer type
		enthalpyTransferType wordToEnthalpyTransfer(const word& etName) const;

		//- Sherwood number
		scalar Sh() const;


	public:

		//- Runtime type information
		//TypeName("phaseChangeModel");
		static const char* typeName_() { return "phaseChangeModel"; }
		static FoamPhaseChangeModel_EXPORT const ::tnbLib::word typeName;
		static FoamPhaseChangeModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			PhaseChangeModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<PhaseChangeModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamPhaseChangeModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamPhaseChangeModel_EXPORT void constructdictionaryConstructorTables();
		static FoamPhaseChangeModel_EXPORT void destroydictionaryConstructorTables();

		template <class PhaseChangeModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<PhaseChangeModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PhaseChangeModel>(new PhaseChangeModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = PhaseChangeModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "PhaseChangeModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class PhaseChangeModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<PhaseChangeModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PhaseChangeModel>(new PhaseChangeModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = PhaseChangeModelType::typeName) : lookup_(
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
		PhaseChangeModel(CloudType& owner);

		//- Construct from dictionary
		PhaseChangeModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		PhaseChangeModel(const PhaseChangeModel<CloudType>& pcm);

		//- Construct and return a clone
		virtual autoPtr<PhaseChangeModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~PhaseChangeModel();


		//- Selector
		static autoPtr<PhaseChangeModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return the enthalpy transfer type enumeration
		const enthalpyTransferType& enthalpyTransfer() const;


		// Member Functions

			//- Update model
		virtual void calculate
		(
			const scalar dt,
			const label celli,
			const scalar Re,
			const scalar Pr,
			const scalar d,
			const scalar nu,
			const scalar T,
			const scalar Ts,
			const scalar pc,
			const scalar Tc,
			const scalarField& X,
			scalarField& dMassPC
		) const = 0;

		//- Return the enthalpy per unit mass
		virtual scalar dh
		(
			const label idc,
			const label idl,
			const scalar p,
			const scalar T
		) const;

		//- Return vapourisation temperature
		virtual scalar Tvap(const scalarField& X) const;

		//- Return maximum/limiting temperature
		virtual scalar TMax(const scalar p, const scalarField& X) const;

		//- Add to phase change mass
		void addToPhaseChangeMass(const scalar dMass);


		// I-O

			//- Write injection info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makePhaseChangeModel(CloudType)                                        \
                                                                               \
    typedef tnbLib::CloudType::reactingCloudType reactingCloudType;              \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::PhaseChangeModel<reactingCloudType>,                             \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            PhaseChangeModel<reactingCloudType>,                               \
            dictionary                                                         \
        );                                                                     \
    }


#define makePhaseChangeModelType(SS, CloudType)                                \
                                                                               \
    typedef tnbLib::CloudType::reactingCloudType reactingCloudType;              \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<reactingCloudType>, 0);       \
                                                                               \
    tnbLib::PhaseChangeModel<reactingCloudType>::                                \
        adddictionaryConstructorToTable<tnbLib::SS<reactingCloudType>>           \
            add##SS##CloudType##reactingCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PhaseChangeModelTemplateI.hxx>
#include <PhaseChangeModelTemplateNew_Imp.hxx>

//#ifdef NoRepository
//#include <PhaseChangeModelTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PhaseChangeModelTemplate_Header
