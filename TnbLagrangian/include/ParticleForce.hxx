#pragma once
#ifndef _ParticleForce_Header
#define _ParticleForce_Header

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
	tnbLib::ParticleForce

Description
	Abstract base class for particle forces

SourceFiles
	ParticleForceI.H
	ParticleForce.C
	ParticleForceNew.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <forceSuSp.hxx>
#include <fvMesh.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamParticleForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamParticleForce_EXPORT_DEFINE
#define FoamParticleForce_EXPORT __declspec(dllexport)
#else
#define FoamParticleForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class ParticleForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ParticleForce
	{
		// Private Data

			//- Reference to the owner cloud
		CloudType& owner_;

		//- Reference to the mesh database
		const fvMesh& mesh_;

		//- Force coefficients dictionary
		const dictionary coeffs_;


	public:

		//- Runtime type information
		//TypeName("particleForce");
		static const char* typeName_() { return "particleForce"; }
		static FoamParticleForce_EXPORT const ::tnbLib::word typeName;
		static FoamParticleForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			ParticleForce,
			dictionary,
			(
				CloudType& owner,
				const fvMesh& mesh,
				const dictionary& dict
				),
				(owner, mesh, dict)
		);*/
		
		typedef autoPtr<ParticleForce> (*dictionaryConstructorPtr)(CloudType& owner, const fvMesh& mesh,
		                                                           const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamParticleForce_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamParticleForce_EXPORT void constructdictionaryConstructorTables();
		static FoamParticleForce_EXPORT void destroydictionaryConstructorTables();

		template <class ParticleForceType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<ParticleForce> New(CloudType& owner, const fvMesh& mesh, const dictionary& dict)
			{
				return autoPtr<ParticleForce>(new ParticleForceType(owner, mesh, dict));
			}

			adddictionaryConstructorToTable(const word& lookup = ParticleForceType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "ParticleForce" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class ParticleForceType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<ParticleForce> New(CloudType& owner, const fvMesh& mesh, const dictionary& dict)
			{
				return autoPtr<ParticleForce>(new ParticleForceType(owner, mesh, dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = ParticleForceType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		//- Convenience typedef for return type
		typedef VectorSpace<Vector<vector>, vector, 2> returnType;


		// Constructors

			//- Construct from mesh
		ParticleForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType,
			const bool readCoeffs
		);

		//- Construct copy
		ParticleForce(const ParticleForce& pf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new ParticleForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ParticleForce();


		//- Selector
		static autoPtr<ParticleForce<CloudType>> New
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType
		);


		// Member Functions

			// Access

				//- Return const access to the cloud owner
		inline const CloudType& owner() const;

		//- Return references to the cloud owner
		inline CloudType& owner();

		//- Return the mesh database
		inline const fvMesh& mesh() const;

		//- Return the force coefficients dictionary
		inline const dictionary& coeffs() const;


		// Evaluation

			//- Cache fields
		virtual void cacheFields(const bool store);

		//- Calculate the coupled force
		virtual forceSuSp calcCoupled
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar dt,
			const scalar mass,
			const scalar Re,
			const scalar muc
		) const;

		//- Calculate the non-coupled force
		virtual forceSuSp calcNonCoupled
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar dt,
			const scalar mass,
			const scalar Re,
			const scalar muc
		) const;

		//- Return the added mass
		virtual scalar massAdd
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar mass
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ParticleForceI.hxx>
#include <ParticleForce_Imp.hxx>
#include <ParticleForceNew_Imp.hxx>

//#ifdef NoRepository
//#include <ParticleForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeParticleForceModel(CloudType)                                      \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug                                        \
        (tnbLib::ParticleForce<kinematicCloudType>, 0);                          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            ParticleForce<kinematicCloudType>,                                 \
            dictionary                                                         \
        );                                                                     \
    }


#define makeParticleForceModelType(SS, CloudType)                              \
                                                                               \
    typedef tnbLib::CloudType::kinematicCloudType kinematicCloudType;            \
    defineNamedTemplateTypeNameAndDebug(tnbLib::SS<kinematicCloudType>, 0);      \
                                                                               \
    tnbLib::ParticleForce<kinematicCloudType>::                                  \
        adddictionaryConstructorToTable<tnbLib::SS<kinematicCloudType>>          \
            add##SS##CloudType##kinematicCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ParticleForce_Header
