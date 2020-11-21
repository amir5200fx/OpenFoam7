#pragma once
#ifndef _SurfaceReactionModel_Header
#define _SurfaceReactionModel_Header

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
	tnbLib::SurfaceReactionModel

Description
	Templated surface reaction model class

SourceFiles
	SurfaceReactionModel.C
	SurfaceReactionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>
#include <scalarField.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSurfaceReactionModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamSurfaceReactionModel_EXPORT_DEFINE
#define FoamSurfaceReactionModel_EXPORT __declspec(dllexport)
#else
#define FoamSurfaceReactionModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class SurfaceReactionModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SurfaceReactionModel
		:
		public CloudSubModelBase<CloudType>
	{
	protected:

		// Protected data

			//- Mass of lagrangian phase converted
		scalar dMass_;


	public:

		//-Runtime type information
		//TypeName("surfaceReactionModel");
		static const char* typeName_() { return "surfaceReactionModel"; }
		static FoamSurfaceReactionModel_EXPORT const ::tnbLib::word typeName;
		static FoamSurfaceReactionModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			SurfaceReactionModel,
			dictionary,
			(
				const dictionary& dict,
				CloudType& cloud
				),
				(dict, cloud)
		);*/
		
		typedef autoPtr<SurfaceReactionModel> (*dictionaryConstructorPtr)(const dictionary& dict, CloudType& cloud);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamSurfaceReactionModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamSurfaceReactionModel_EXPORT void constructdictionaryConstructorTables();
		static FoamSurfaceReactionModel_EXPORT void destroydictionaryConstructorTables();

		template <class SurfaceReactionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<SurfaceReactionModel> New(const dictionary& dict, CloudType& cloud)
			{
				return autoPtr<SurfaceReactionModel>(new SurfaceReactionModelType(dict, cloud));
			}

			adddictionaryConstructorToTable(const word& lookup = SurfaceReactionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"SurfaceReactionModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class SurfaceReactionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<SurfaceReactionModel> New(const dictionary& dict, CloudType& cloud)
			{
				return autoPtr<SurfaceReactionModel>(new SurfaceReactionModelType(dict, cloud));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = SurfaceReactionModelType::typeName) : lookup_(
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
		SurfaceReactionModel(CloudType& owner);

		//- Construct from dictionary
		SurfaceReactionModel
		(
			const dictionary& dict,
			CloudType& cloud,
			const word& type
		);

		//- Construct copy
		SurfaceReactionModel(const SurfaceReactionModel<CloudType>& srm);

		//- Construct and return a clone
		virtual autoPtr<SurfaceReactionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~SurfaceReactionModel();


		//- Selector
		static autoPtr<SurfaceReactionModel<CloudType>> New
		(
			const dictionary& dict,
			CloudType& cloud
		);


		// Member Functions

			//- Update surface reactions
			//  Returns the heat of reaction
		virtual scalar calculate
		(
			const scalar dt,
			const label celli,
			const scalar d,
			const scalar T,
			const scalar Tc,
			const scalar pc,
			const scalar rhoc,
			const scalar mass,
			const scalarField& YGas,
			const scalarField& YLiquid,
			const scalarField& YSolid,
			const scalarField& YMixture,
			const scalar N,
			scalarField& dMassGas,
			scalarField& dMassLiquid,
			scalarField& dMassSolid,
			scalarField& dMassSRCarrier
		) const = 0;

		//- Add to devolatilisation mass
		void addToSurfaceReactionMass(const scalar dMass);


		// I-O

			//- Write injection info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeSurfaceReactionModel(CloudType)                                    \
                                                                               \
    typedef tnbLib::CloudType::reactingMultiphaseCloudType                       \
        reactingMultiphaseCloudType;                                           \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::SurfaceReactionModel<reactingMultiphaseCloudType>,               \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            SurfaceReactionModel<reactingMultiphaseCloudType>,                 \
            dictionary                                                         \
        );                                                                     \
    }


#define makeSurfaceReactionModelType(SS, CloudType)                            \
                                                                               \
    typedef tnbLib::CloudType::reactingMultiphaseCloudType                       \
        reactingMultiphaseCloudType;                                           \
    defineNamedTemplateTypeNameAndDebug                                        \
        (tnbLib::SS<reactingMultiphaseCloudType>, 0);                            \
                                                                               \
    tnbLib::SurfaceReactionModel<reactingMultiphaseCloudType>::                  \
        adddictionaryConstructorToTable                                        \
        <tnbLib::SS<reactingMultiphaseCloudType>>                                \
        add##SS##CloudType##reactingMultiphaseCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SurfaceReactionModelI.hxx>
#include <SurfaceReactionModelNew_Imp.hxx>

//#ifdef NoRepository
//#include <SurfaceReactionModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SurfaceReactionModel_Header
