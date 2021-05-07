#pragma once
#ifndef _rigidBodyRestraint_Header
#define _rigidBodyRestraint_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

Namespace
	tnbLib::RBD::restraints

Description
	Namespace for rigid-body dynamics restraints

Class
	tnbLib::RBD::restraint

Description
	Base class for defining restraints for rigid-body dynamics

SourceFiles
	rigidBodyRestraint.C
	rigidBodyRestraintNew.C

\*---------------------------------------------------------------------------*/

#include <RigidBodyMotion_Module.hxx>
#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <spatialVector.hxx>
#include <point.hxx>
#include <scalarField.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		// Forward declaration of classes
		class rigidBodyModel;

		/*---------------------------------------------------------------------------*\
						Class restraint Declaration
		\*---------------------------------------------------------------------------*/

		class restraint
		{

		protected:

			// Protected data

				//- Name of the restraint
			word name_;

			//- ID of the body the restraint is applied to
			label bodyID_;

			//- Index of the body the force is applied to
			label bodyIndex_;

			//- Restraint model specific coefficient dictionary
			dictionary coeffs_;

			//- Reference to the model
			const rigidBodyModel& model_;

			//- Transform the given point on the restrained body to the global frame
			inline point bodyPoint(const point& p) const;

			//- Transform the velocity of the given point on the restrained body
			//  to the global frame
			inline spatialVector bodyPointVelocity(const point& p) const;


		public:

			//- Runtime type information
			/*TypeName("restraint");*/
			static const char* typeName_() { return "restraint"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				restraint,
				dictionary,
				(
					const word& name,
					const dictionary& dict,
					const rigidBodyModel& model
					),
					(name, dict, model)
			);*/

			typedef autoPtr<restraint> (*dictionaryConstructorPtr)(const word& name, const dictionary& dict,
			                                                       const rigidBodyModel& model);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRigidBodyMotion_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRigidBodyMotion_EXPORT void constructdictionaryConstructorTables();
			static FoamRigidBodyMotion_EXPORT void destroydictionaryConstructorTables();

			template <class restraintType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<restraint> New(const word& name, const dictionary& dict, const rigidBodyModel& model)
				{
					return autoPtr<restraint>(new restraintType(name, dict, model));
				}

				adddictionaryConstructorToTable(const word& lookup = restraintType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "restraint" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class restraintType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<restraint> New(const word& name, const dictionary& dict, const rigidBodyModel& model)
				{
					return autoPtr<restraint>(new restraintType(name, dict, model));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = restraintType::typeName) : lookup_(lookup)
				{
					constructdictionaryConstructorTables();
					dictionaryConstructorTablePtr_->set(lookup, New);
				}

				~addRemovabledictionaryConstructorToTable()
				{
					if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

				//- Construct from the dict dictionary and Time
			FoamRigidBodyMotion_EXPORT restraint
			(
				const word& name,
				const dictionary& dict,
				const rigidBodyModel& model
			);

			//- Construct and return a clone
			virtual autoPtr<restraint> clone() const = 0;


			// Selectors

				//- Select constructed from the dict dictionary and Time
			static FoamRigidBodyMotion_EXPORT autoPtr<restraint> New
			(
				const word& name,
				const dictionary& dict,
				const rigidBodyModel& model
			);


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~restraint();


			// Member Functions

				//- Return the name
			const word& name() const
			{
				return name_;
			}

			label bodyID() const
			{
				return bodyID_;
			}

			//- Accumulate the retraint internal joint forces into the tau field and
			//  external forces into the fx field
			virtual void restrain
			(
				scalarField& tau,
				Field<spatialVector>& fx
			) const = 0;

			//- Update properties from given dictionary
			FoamRigidBodyMotion_EXPORT virtual bool read(const dictionary& dict);

			//- Return access to coeffs
			FoamRigidBodyMotion_EXPORT const dictionary& coeffDict() const;

			//- Write
			virtual void write(Ostream&) const = 0;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <rigidBodyRestraintI.hxx>

#endif // !_rigidBodyRestraint_Header
