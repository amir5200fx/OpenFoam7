#pragma once
#ifndef _rigidBodySolver_Header
#define _rigidBodySolver_Header

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

Class
	tnbLib::RBD::rigidBodySolver

Description

SourceFiles
	rigidBodySolver.C
	newSixDoFSolver.C

\*---------------------------------------------------------------------------*/

#include <rigidBodyMotion.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{
	namespace RBD
	{

		/*---------------------------------------------------------------------------*\
								 Class rigidBodySolver Declaration
		\*---------------------------------------------------------------------------*/

		class rigidBodySolver
		{
		protected:

			// Protected data

				//- The rigid-body model
			rigidBodyMotion& model_;


			//- Return the motion state
			inline rigidBodyModelState& state();

			//- Return the current joint position and orientation
			inline scalarField& q();

			//- Return the current joint quaternion

			//- Return the current joint velocity
			inline scalarField& qDot();

			//- Return the current joint acceleration
			inline scalarField& qDdot();

			//- Return the current time-step
			inline scalar deltaT() const;


			//- Return the previous motion state
			inline const rigidBodyModelState& state0() const;

			//- Return the current joint position and orientation
			inline const scalarField& q0() const;

			//- Return the current joint quaternion

			//- Return the current joint velocity
			inline const scalarField& qDot0() const;

			//- Return the current joint acceleration
			inline const scalarField& qDdot0() const;

			//- Return the previous time-step
			inline scalar deltaT0() const;

			//- Correct the quaternion joints based on the current change in q
			FoamRigidBodyMotion_EXPORT void correctQuaternionJoints();


		public:

			//- Runtime type information
			/*TypeName("rigidBodySolver");*/
			static const char* typeName_() { return "rigidBodySolver"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare runtime construction

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				rigidBodySolver,
				dictionary,
				(
					rigidBodyMotion& body,
					const dictionary& dict
					),
					(body, dict)
			);*/

			typedef autoPtr<rigidBodySolver> (*dictionaryConstructorPtr)(rigidBodyMotion& body, const dictionary& dict);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRigidBodyMotion_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRigidBodyMotion_EXPORT void constructdictionaryConstructorTables();
			static FoamRigidBodyMotion_EXPORT void destroydictionaryConstructorTables();

			template <class rigidBodySolverType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<rigidBodySolver> New(rigidBodyMotion& body, const dictionary& dict)
				{
					return autoPtr<rigidBodySolver>(new rigidBodySolverType(body, dict));
				}

				adddictionaryConstructorToTable(const word& lookup = rigidBodySolverType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "rigidBodySolver" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class rigidBodySolverType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<rigidBodySolver> New(rigidBodyMotion& body, const dictionary& dict)
				{
					return autoPtr<rigidBodySolver>(new rigidBodySolverType(body, dict));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = rigidBodySolverType::typeName) : lookup_(lookup)
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

				// Construct for given body
			FoamRigidBodyMotion_EXPORT rigidBodySolver(rigidBodyMotion& body);


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~rigidBodySolver();


			// Selectors

			static FoamRigidBodyMotion_EXPORT autoPtr<rigidBodySolver> New
			(
				rigidBodyMotion& body,
				const dictionary& dict
			);


			// Member Functions

				//- Integrate the rigid-body motion for one time-step
			virtual void solve
			(
				const scalarField& tau,
				const Field<spatialVector>& fx
			) = 0;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <rigidBodySolverI.hxx>

#endif // !_rigidBodySolver_Header
