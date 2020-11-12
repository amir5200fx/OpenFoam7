#pragma once
#ifndef _InflowBoundaryModel_Header
#define _InflowBoundaryModel_Header

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
	tnbLib::InflowBoundaryModel


Description
	Templated inflow boundary model class

SourceFiles
	InflowBoundaryModel.C
	InflowBoundaryModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamInflowBoundaryModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamInflowBoundaryModel_EXPORT_DEFINE
#define FoamInflowBoundaryModel_EXPORT __declspec(dllexport)
#else
#define FoamInflowBoundaryModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward Declarations
	class mapPolyMesh;  // added by amir

	/*---------------------------------------------------------------------------*\
						 Class InflowBoundaryModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class InflowBoundaryModel
	{
		// Private Data

			//- The cloud dictionary
		const dictionary& dict_;

		// Reference to the owner cloud class
		CloudType& owner_;

		//- The coefficients dictionary
		const dictionary coeffDict_;


	public:

		//- Runtime type information
		//TypeName("InflowBoundaryModel");
		static const char* typeName_() { return "InflowBoundaryModel"; }
		static FoamInflowBoundaryModel_EXPORT const ::tnbLib::word typeName;
		static FoamInflowBoundaryModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			InflowBoundaryModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner
				),
				(dict, owner)
		);*/
		
		typedef autoPtr<InflowBoundaryModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& owner);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamInflowBoundaryModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamInflowBoundaryModel_EXPORT void constructdictionaryConstructorTables();
		static FoamInflowBoundaryModel_EXPORT void destroydictionaryConstructorTables();

		template <class InflowBoundaryModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<InflowBoundaryModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<InflowBoundaryModel>(new InflowBoundaryModelType(dict, owner));
			}

			adddictionaryConstructorToTable(const word& lookup = InflowBoundaryModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "InflowBoundaryModel"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class InflowBoundaryModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<InflowBoundaryModel> New(const dictionary& dict, CloudType& owner)
			{
				return autoPtr<InflowBoundaryModel>(new InflowBoundaryModelType(dict, owner));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = InflowBoundaryModelType::typeName) : lookup_(
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
		InflowBoundaryModel(CloudType& owner);

		//- Construct from dictionary
		InflowBoundaryModel
		(
			const dictionary& dict,
			CloudType& owner,
			const word& type
		);


		//- Destructor
		virtual ~InflowBoundaryModel();


		//- Selector
		static autoPtr<InflowBoundaryModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner
		);


		// Access

			//- Return const access the owner cloud object
		inline const CloudType& owner() const;

		//- Return non-const access the owner cloud object for manipulation
		inline CloudType& owner();

		//- Return the owner cloud dictionary
		inline const dictionary& dict() const;

		//- Return the coefficients dictionary
		inline const dictionary& coeffDict() const;

		// Mapping

			//- Remap the particles to the correct cells following mesh change
		virtual void autoMap(const mapPolyMesh&)
		{}

		//- Introduce particles
		virtual void inflow() = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeInflowBoundaryModel(CloudType)                                     \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(InflowBoundaryModel<CloudType>, 0);    \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        InflowBoundaryModel<CloudType>,                                        \
        dictionary                                                             \
    );


#define makeInflowBoundaryModelType(SS, CloudType)                             \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(SS<CloudType>, 0);                     \
                                                                               \
    InflowBoundaryModel<CloudType>::                                           \
        adddictionaryConstructorToTable<SS<CloudType>>                         \
            add##SS##CloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <InflowBoundaryModelI.hxx>
#include <InflowBoundaryModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <InflowBoundaryModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_InflowBoundaryModel_Header
