#pragma once
#ifndef _ParticleStressModel_Header
#define _ParticleStressModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::ParticleStressModel

Description
	Base class for inter-particle stress models.

SourceFiles
	exponential.C

\*---------------------------------------------------------------------------*/

#include <Field.hxx>
#include <FieldField.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class ParticleStressModel Declaration
	\*---------------------------------------------------------------------------*/

	class ParticleStressModel
	{
		// Private member functions

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const ParticleStressModel&) = delete;


	protected:

		// Protected data

			//- Close pack volume fraction
		scalar alphaPacked_;


	public:

		//- Runtime type information
		//TypeName("particleStressModel");
		static const char* typeName_() { return "particleStressModel"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			ParticleStressModel,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/
		
		typedef autoPtr<ParticleStressModel> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class ParticleStressModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<ParticleStressModel> New(const dictionary& dict)
			{
				return autoPtr<ParticleStressModel>(new ParticleStressModelType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = ParticleStressModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "ParticleStressModel"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class ParticleStressModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<ParticleStressModel> New(const dictionary& dict)
			{
				return autoPtr<ParticleStressModel>(new ParticleStressModelType(dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = ParticleStressModelType::typeName) : lookup_(
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


		//- Constructors

			//- Construct from components
		FoamLagrangian_EXPORT ParticleStressModel(const dictionary& dict);

		//- Construct a copy
		FoamLagrangian_EXPORT ParticleStressModel(const ParticleStressModel& sm);

		//- Construct and return a clone
		FoamLagrangian_EXPORT virtual autoPtr<ParticleStressModel> clone() const = 0;


		//- Selector
		static FoamLagrangian_EXPORT autoPtr<ParticleStressModel> New
		(
			const dictionary& dict
		);


		//- Destructor
		FoamLagrangian_EXPORT virtual ~ParticleStressModel();


		//- Member Functions

			//- Access max volume fraction
		FoamLagrangian_EXPORT scalar alphaPacked() const;

		//- Collision stress
		FoamLagrangian_EXPORT virtual tmp<Field<scalar>> tau
		(
			const Field<scalar>& alpha,
			const Field<scalar>& rho,
			const Field<scalar>& uRms
		) const = 0;

		//- Collision stress derivaive w.r.t. the volume fraction
		FoamLagrangian_EXPORT virtual tmp<Field<scalar>> dTaudTheta
		(
			const Field<scalar>& alpha,
			const Field<scalar>& rho,
			const Field<scalar>& uRms
		) const = 0;

		//- Collision stress using FieldFields
		FoamLagrangian_EXPORT tmp<FieldField<Field, scalar>> tau
		(
			const FieldField<Field, scalar>& alpha,
			const FieldField<Field, scalar>& rho,
			const FieldField<Field, scalar>& uRms
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ParticleStressModel_Header
