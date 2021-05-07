#pragma once
#ifndef _joint_Header
#define _joint_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::RBD::joints

Description
	Namespace for rigid-body joints

Class
	tnbLib::RBD::joint

Description
	Abstract base-class for all rigid-body joints.

	Reference:
	\verbatim
		Featherstone, R. (2008).
		Rigid body dynamics algorithms.
		Springer.
		Chapter 4.
	\endverbatim

SourceFiles
	jointI.H
	joint.C

\*---------------------------------------------------------------------------*/

#include <RigidBodyMotion_Module.hxx>
#include <List.hxx>
#include <spatialVector.hxx>
#include <compactSpatialTensor.hxx>
#include <CompactSpatialTensorT.hxx>
#include <spatialTransform.hxx>
#include <quaternion.hxx>
#include <scalarField.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{
	namespace RBD
	{

		// Forward declaration of classes
		class rigidBodyModel;
		class rigidBodyModelState;

		// Forward declaration of friend functions and operators
		class joint;

		inline Ostream& operator<<(Ostream&, const joint&);


		/*---------------------------------------------------------------------------*\
								 Class joint Declaration
		\*---------------------------------------------------------------------------*/

		class joint
		{

		protected:

			// Protected data

				//- Reference to the model
			const rigidBodyModel& model_;

			//- Joint motion sub-space
			List<spatialVector> S_;

			//- Index of this joint in the rigidBodyModel
			label index_;

			//- Index of this joints data in the rigidBodyModel state
			label qIndex_;


		private:

			// Private Member Functions to be used by rigidBodyModel

				//- Allow the rigidBodyModel to set the index for this joint
			label& index()
			{
				return index_;
			}

			//- Allow the rigidBodyModel to set the qIndex for this joint
			label& qIndex()
			{
				return qIndex_;
			}


		public:

			//- Allow the rigidBodyModel class to set the joint indices
			friend class rigidBodyModel;

			//- Joint state returned by jcalc
			class XSvc
			{
			public:

				//- The joint transformation
				spatialTransform X;

				//- The joint motion sub-space (3-DoF)
				compactSpatialTensor S;

				//- The joint motion sub-space (1-DoF)
				spatialVector S1;

				//- The constrained joint velocity
				spatialVector v;

				//- The constrained joint acceleration correction
				//  due to changes in the motion sub-space S
				spatialVector c;

				//- Null constructor
				XSvc()
					:
					X(),
					v(Zero),
					c(Zero)
				{}
			};


		public:

			//- Runtime type information
			//TypeName("joint");
			static const char* typeName_() { return "joint"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				joint,
				dictionary,
				(const rigidBodyModel& model, const dictionary& dict),
				(model, dict)
			);*/

			typedef autoPtr<joint> (*dictionaryConstructorPtr)(const rigidBodyModel& model, const dictionary& dict);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRigidBodyMotion_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRigidBodyMotion_EXPORT void constructdictionaryConstructorTables();
			static FoamRigidBodyMotion_EXPORT void destroydictionaryConstructorTables();

			template <class jointType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<joint> New(const rigidBodyModel& model, const dictionary& dict)
				{
					return autoPtr<joint>(new jointType(model, dict));
				}

				adddictionaryConstructorToTable(const word& lookup = jointType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "joint" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class jointType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<joint> New(const rigidBodyModel& model, const dictionary& dict)
				{
					return autoPtr<joint>(new jointType(model, dict));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = jointType::typeName) : lookup_(lookup)
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

				//- Construct joint setting the size of the motion sub-space
				//  to the given degrees of freedom of the joint
			inline joint(const rigidBodyModel& model, const label nDoF);

			//- Copy constructor
			joint(const joint&) = default;

			//- Clone this joint (needed by PtrList)
			virtual autoPtr<joint> clone() const = 0;

			class iNew
			{

				const rigidBodyModel& model_;

			public:

				iNew(const rigidBodyModel& model)
					:
					model_(model)
				{}

				inline autoPtr<joint> operator()(Istream& is) const;
			};


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~joint();


			// Selectors

				//- Simple selector to return an autoPtr<joint> of the given joint*
			static FoamRigidBodyMotion_EXPORT autoPtr<joint> New(joint* jointPtr);

			//- Select from dictionary
			static FoamRigidBodyMotion_EXPORT autoPtr<joint> New
			(
				const rigidBodyModel& model,
				const dictionary& dict
			);


			// Member Functions

				//- Return the number of degrees of freedom in this joint
			inline label nDoF() const;

			//- Return true if this joint describes rotation using a quaternion
			inline virtual bool unitQuaternion() const;

			//- Return the index of this joint in the model
			inline label index() const;

			//- Return start index for the state variables for this joint
			//  in the rigidBodyModel state fields
			inline label qIndex() const;

			//- Return the joint motion sub-space
			inline const List<spatialVector>& S() const;

			//- Update the rigidBodyModel state for the joint given
			//  the joint state q, w and velocity qDot
			virtual void jcalc
			(
				XSvc& J,
				const rigidBodyModelState& state
			) const = 0;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;


			// Member Operators

				//- Assignment
			inline void operator=(const joint& j);

			//- Return the unit quaternion for this joint
			//  if it uses a quaternion representation for rotation
			inline quaternion unitQuaternion
			(
				const scalarField& q
			) const;

			//- Set the unit quaternion for this joint
			//  if it uses a quaternion representation for rotation
			inline void unitQuaternion
			(
				const quaternion& quat,
				scalarField& q
			) const;


			// Ostream Operator

			friend Ostream& operator<<(Ostream&, const joint&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <jointI.hxx>

#endif // !_joint_Header
