#pragma once
#ifndef _CloudFunctionObject_Header
#define _CloudFunctionObject_Header

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
	tnbLib::CloudFunctionObject

Description
	Templated cloud function object base class

SourceFiles
	CloudFunctionObject.C
	CloudFunctionObjectNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <CloudSubModelBase.hxx>

#include <point.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCloudFunctionObject_EXPORT __declspec(dllexport)
#else
#ifdef FoamCloudFunctionObject_EXPORT_DEFINE
#define FoamCloudFunctionObject_EXPORT __declspec(dllexport)
#else
#define FoamCloudFunctionObject_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyPatch;
	class tetIndices;

	/*---------------------------------------------------------------------------*\
						Class CloudFunctionObject Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class CloudFunctionObject
		:
		public CloudSubModelBase<CloudType>
	{
		// Private Data

			//- Output path
		fileName outputDir_;


		// Private Member Functions

			//- Inherite write from CloudSubModelBase
		using CloudSubModelBase<CloudType>::write;

		//- Write post-processing info
		virtual void write();


	public:

		//- Runtime type information
		//TypeName("cloudFunctionObject");
		static const char* typeName_() { return "cloudFunctionObject"; }
		static FoamCloudFunctionObject_EXPORT const ::tnbLib::word typeName;
		static FoamCloudFunctionObject_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			CloudFunctionObject,
			dictionary,
			(
				const dictionary& dict,
				CloudType& owner,
				const word& modelName
				),
				(dict, owner, modelName)
		);*/
		
		typedef autoPtr<CloudFunctionObject> (*dictionaryConstructorPtr)(
			const dictionary& dict, CloudType& owner, const word& modelName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamCloudFunctionObject_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamCloudFunctionObject_EXPORT void constructdictionaryConstructorTables();
		static FoamCloudFunctionObject_EXPORT void destroydictionaryConstructorTables();

		template <class CloudFunctionObjectType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<CloudFunctionObject> New(const dictionary& dict, CloudType& owner, const word& modelName)
			{
				return autoPtr<CloudFunctionObject>(new CloudFunctionObjectType(dict, owner, modelName));
			}

			adddictionaryConstructorToTable(const word& lookup = CloudFunctionObjectType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "CloudFunctionObject"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class CloudFunctionObjectType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<CloudFunctionObject> New(const dictionary& dict, CloudType& owner, const word& modelName)
			{
				return autoPtr<CloudFunctionObject>(new CloudFunctionObjectType(dict, owner, modelName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = CloudFunctionObjectType::typeName) : lookup_(
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
		CloudFunctionObject(CloudType& owner);

		//- Construct from dictionary
		CloudFunctionObject
		(
			const dictionary& dict,
			CloudType& owner,
			const word& objectType,
			const word& modelName
		);

		//- Construct copy
		CloudFunctionObject(const CloudFunctionObject<CloudType>& ppm);

		//- Construct and return a clone
		virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
		{
			return autoPtr<CloudFunctionObject<CloudType>>
				(
					new CloudFunctionObject<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~CloudFunctionObject();


		//- Selector
		static autoPtr<CloudFunctionObject<CloudType>> New
		(
			const dictionary& dict,
			CloudType& owner,
			const word& objectType,
			const word& modelName
		);


		// Member Functions

			// Evaluation

				//- Pre-evolve hook
		virtual void preEvolve();

		//- Post-evolve hook
		virtual void postEvolve();

		//- Post-move hook
		virtual void postMove
		(
			typename CloudType::parcelType& p,
			const scalar dt,
			const point& position0,
			bool& keepParticle
		);

		//- Post-patch hook
		virtual void postPatch
		(
			const typename CloudType::parcelType& p,
			const polyPatch& pp,
			bool& keepParticle
		);

		//- Post-face hook
		virtual void postFace
		(
			const typename CloudType::parcelType& p,
			bool& keepParticle
		);


		// Input/output

			//- Return the output path
		const fileName& outputDir() const;

		//- Return the output time path
		fileName writeTimeDir() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeCloudFunctionObject(CloudType)                                     \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        tnbLib::CloudFunctionObject<kinematicCloudType>,                         \
        0                                                                      \
    );                                                                         \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            CloudFunctionObject<kinematicCloudType>,                           \
            dictionary                                                         \
        );                                                                     \
    }


#define makeCloudFunctionObjectType(SS, CloudType)                             \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<kinematicCloudType>, 0);      \
                                                                               \
    tnbLib::CloudFunctionObject<kinematicCloudType>::                            \
        adddictionaryConstructorToTable<tnbLib::SS<kinematicCloudType>>          \
            add##SS##CloudType##kinematicCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CloudFunctionObject_Imp.hxx>
#include <CloudFunctionObjectNew_Imp.hxx>

//#ifdef NoRepository
//#include <CloudFunctionObject.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CloudFunctionObject_Header
