#pragma once
#ifndef _PatchInteractionModel_Header
#define _PatchInteractionModel_Header

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
	tnbLib::PatchInteractionModel

Description
	Templated patch interaction model class

SourceFiles
	PatchInteractionModel.C
	PatchInteractionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <polyPatch.hxx>
#include <wallPolyPatch.hxx>
#include <tetIndices.hxx>
#include <CloudSubModelBase.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamPatchInteractionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamPatchInteractionModel_EXPORT_DEFINE
#define FoamPatchInteractionModel_EXPORT __declspec(dllexport)
#else
#define FoamPatchInteractionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class PatchInteractionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PatchInteractionModel
		:
		public CloudSubModelBase<CloudType>
	{
	public:

		// Public enumerations

			// Interaction types
		enum interactionType
		{
			itNone,
			itRebound,
			itStick,
			itEscape,
			itOther
		};

		static wordList interactionTypeNames_;


	private:

		// Private Data

			//- Name of velocity field - default = "U"
		const word UName_;


	public:

		//- Runtime type information
		//TypeName("patchInteractionModel");
		static const char* typeName_() { return "patchInteractionModel"; }
		static FoamPatchInteractionModel_EXPORT const ::tnbLib::word typeName;
		static FoamPatchInteractionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			PatchInteractionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<PatchInteractionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamPatchInteractionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamPatchInteractionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamPatchInteractionModel_EXPORT void destroydictionaryConstructorTables();

		template <class PatchInteractionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<PatchInteractionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PatchInteractionModel>(new PatchInteractionModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = PatchInteractionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"PatchInteractionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class PatchInteractionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<PatchInteractionModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<PatchInteractionModel>(new PatchInteractionModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = PatchInteractionModelType::typeName) : lookup_(lookup)
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
		PatchInteractionModel(CloudType& owner);

		//- Construct from components
		PatchInteractionModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);

		//- Construct copy
		PatchInteractionModel(const PatchInteractionModel<CloudType>& pim);

		//- Construct and return a clone
		virtual autoPtr<PatchInteractionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~PatchInteractionModel();


		//- Selector
		static autoPtr<PatchInteractionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return name of velocity field
		const word& UName() const;


		// Member Functions

			//- Convert interaction result to word
		static word interactionTypeToWord(const interactionType& itEnum);

		//- Convert word to interaction result
		static interactionType wordToInteractionType(const word& itWord);

		//- Apply velocity correction
		//  Returns true if particle remains in same cell
		virtual bool correct
		(
			typename CloudType::parcelType& p,
			const polyPatch& pp,
			bool& keepParticle
		) = 0;


		// I-O

			//- Write patch interaction info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makePatchInteractionModel(CloudType)                                   \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::PatchInteractionModel<kinematicCloudType>,                       \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            PatchInteractionModel<kinematicCloudType>,                         \
            dictionary                                                         \
        );                                                                     \
    }


#define makePatchInteractionModelType(SS, CloudType)                           \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<kinematicCloudType>, 0);      \
                                                                               \
    tnbLib::PatchInteractionModel<kinematicCloudType>::                          \
        adddictionaryConstructorToTable<tnbLib::SS<kinematicCloudType>>          \
            add##SS##CloudType##kinematicCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PatchInteractionModelI.hxx>
#include <PatchInteractionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <PatchInteractionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PatchInteractionModel_Header
