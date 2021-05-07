#pragma once
#ifndef _rigidBodyModel_Header
#define _rigidBodyModel_Header

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

Class
	tnbLib::RBD::rigidBodyModel

Description
	Basic rigid-body model representing a system of rigid-bodies connected by
	1-6 DoF joints.

	This class holds various body and joint state fields needed by the
	kinematics and forward-dynamics algorithms presented in

	reference:
	\verbatim
		Featherstone, R. (2008).
		Rigid body dynamics algorithms.
		Springer.
		Chapter 4.
	\endverbatim

SourceFiles
	rigidBodyModel.C
	kinematics.C
	forwardDynamics.C

\*---------------------------------------------------------------------------*/

#include <rigidBody.hxx>
#include <subBody.hxx>
#include <joint.hxx>
#include <compositeJoint.hxx>
#include <PtrList.hxx>
#include <HashTable.hxx>

namespace tnbLib
{
	namespace RBD
	{

		// Forward declaration of friend functions and operators
		class rigidBodyModel;

		FoamRigidBodyMotion_EXPORT Ostream& operator<<(Ostream&, const rigidBodyModel&);

		class rigidBodyModelState;
		class restraint;


		/*---------------------------------------------------------------------------*\
								 Class rigidBodyModel Declaration
		\*---------------------------------------------------------------------------*/

		class rigidBodyModel
		{
			// Private Member Functions

				//- Initialize the model with the root-body
				//  which is a fixed massless bodyat the origin.
			FoamRigidBodyMotion_EXPORT void initializeRootBody();

			//- Resize the state fields following the joining of a body
			FoamRigidBodyMotion_EXPORT void resizeState();

			//- Convert the body with given ID into a composite-body
			FoamRigidBodyMotion_EXPORT void makeComposite(const label bodyID);

			//- Add restraints to the motion
			FoamRigidBodyMotion_EXPORT void addRestraints(const dictionary& dict);

		protected:

			// Protected data representing the model structure

				//- List of the bodies.
				//  The 0'th body represents the fixed origin and is constructed
				//  automatically.  The subsequent (moving) bodies are appended by the
				//  join member function.
			PtrList<rigidBody> bodies_;

			//- Bodies may be merged into existing bodies, the inertia of which is
			//  updated to represent the combined body which is more efficient than
			//  attaching them with fixed joints.  These 'merged' bodies are held on
			//  this list.
			PtrList<subBody> mergedBodies_;

			//- Lookup-table of the IDs of the bodies
			HashTable<label, word> bodyIDs_;

			//- List of indices of the parent of each body
			DynamicList<label> lambda_;

			//- Each body it attached with a joint which are held on this list.
			PtrList<joint> joints_;

			//- Transform from the parent body frame to the joint frame.
			DynamicList<spatialTransform> XT_;

			//- The number of degrees of freedom of the model
			//  used to set the size of the of joint state fields q, qDot and qDdot.
			label nDoF_;

			//- True if any of the joints using quaternions
			bool unitQuaternions_;

			//- Motion restraints
			PtrList<restraint> restraints_;


			// Other protected member data

				//- Acceleration due to gravity
			vector g_;


			// Mutable transforms maintained by kinematics and forward-dynamics

				//- Transform from the parent body to the current body
			mutable DynamicList<spatialTransform> Xlambda_;

			//- Transform for external forces to the bodies reference frame
			mutable DynamicList<spatialTransform> X0_;


			// Mutable kinematic body state fields

				//- The spatial velocity of the bodies
			mutable DynamicList<spatialVector> v_;

			//- The spatial acceleration of the bodies
			mutable DynamicList<spatialVector> a_;

			//- The velocity dependent spatial acceleration of the joints
			mutable DynamicList<spatialVector> c_;


			// Mutable state fields needed by the forward-dynamics algorithm

				//- Velocity-product acceleration

				//- Articulated body inertia
			mutable DynamicList<spatialTensor> IA_;

			//- Articulated body bias force
			mutable DynamicList<spatialVector> pA_;


			// Mutable joint state fields

				//- Motion subspace for joints with 3 degrees of freedom
			mutable DynamicList<compactSpatialTensor> S_;

			//- Motion subspace for joints with 1 degrees of freedom
			mutable DynamicList<spatialVector> S1_;

			//- Sub-expression IA.S in the forward-dynamics algorithm
			mutable DynamicList<compactSpatialTensor> U_;

			//- Sub-expression IA.S1 in the forward-dynamics algorithm
			mutable DynamicList<spatialVector> U1_;

			//- Sub-expression (S^T.U)^-1 in the forward-dynamics algorithm
			mutable DynamicList<tensor> Dinv_;

			//- Sub-expression tau - S^T.pA in the forward-dynamics algorithm
			mutable DynamicList<vector> u_;


			// Protected member functions

				//- Join the given body to the parent with ID parentID via the given
				//  joint with transform from the parent frame to the joint frame XT.
			virtual label join_
			(
				const label parentID,
				const spatialTransform& XT,
				autoPtr<joint> jointPtr,
				autoPtr<rigidBody> bodyPtr
			);


		public:

			//- Runtime type information
			/*TypeName("rigidBodyModel");*/
			static const char* typeName_() { return "rigidBodyModel"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Null-constructor which adds the single root-body at the origin
			FoamRigidBodyMotion_EXPORT rigidBodyModel();

			FoamRigidBodyMotion_EXPORT //- Construct from dictionary
			rigidBodyModel(const dictionary& dict);


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~rigidBodyModel();


			// Member Functions

				//- Return the number of bodies in the model (bodies().size())
			inline label nBodies() const;

			//- Return the list of the bodies in the model
			inline PtrList<rigidBody> bodies() const;

			//- List of indices of the parent of each body
			inline const DynamicList<label>& lambda() const;

			//- Return the list of joints in the model
			inline const PtrList<joint>& joints() const;

			//- Return the number of degrees of freedom of the model
			//  used to set the size of the of joint state fields q, qDot and qDdot.
			inline label nDoF() const;

			//- Return true if any of the joints using quaternions
			inline bool unitQuaternions() const;

			//- Return the acceleration due to gravity
			inline const vector& g() const;

			//- Allow the acceleration due to gravity to be set
			//  after model construction
			inline vector& g();

			//- Return the name of body with the given ID
			inline const word& name(const label bodyID) const;

			//- Return the names of the moving bodies
			FoamRigidBodyMotion_EXPORT wordList movingBodyNames() const;

			//- Return the inertia of body i
			inline const rigidBodyInertia& I(const label i) const;

			//- Return the spatial velocity of the bodies
			inline const spatialVector& v(const label i) const;

			//- Join the given body to the parent with ID parentID via the given
			//  joint with transform from the parent frame to the joint frame XT.
			FoamRigidBodyMotion_EXPORT virtual label join
			(
				const label parentID,
				const spatialTransform& XT,
				autoPtr<joint> jointPtr,
				autoPtr<rigidBody> bodyPtr
			);

			//- Join the given body to the parent with ID parentID via the given
			//  composite joint (specified as a list of co-located joints) with
			//  transform from the parent frame to the joint frame XT.
			//  Composite joins are useful to represent complex joints with degrees
			//  of freedom other than 1 or 3 which are directly supported.
			FoamRigidBodyMotion_EXPORT label join
			(
				const label parentID,
				const spatialTransform& XT,
				autoPtr<joints::composite> cJoint,
				autoPtr<rigidBody> bodyPtr
			);

			//- Merge the given body with transform X into the parent with ID
			//  parentID.  The parent body assumes the properties of the combined
			//  body (inertia etc.) and the merged body is held on a
			//  separate list for reference.
			FoamRigidBodyMotion_EXPORT label merge
			(
				const label parentID,
				const spatialTransform& X,
				autoPtr<rigidBody> bodyPtr
			);

			//- Return true if the body with given ID has been merged with a parent
			inline bool merged(label bodyID) const;

			//- Return the ID of the master body for a sub-body otherwise
			//  return the given body ID
			inline label master(label bodyID) const;

			//- Return the index of the merged body in the mergedBody list
			//  from the given body ID
			inline label mergedBodyIndex(const label mergedBodyID) const;

			//- Return the merged body ID for the given merged body index
			//  in the mergedBody list
			inline label mergedBodyID(const label mergedBodyIndex) const;

			//- Return the merged body for the given body ID
			inline const subBody& mergedBody(label mergedBodyID) const;

			//- Return the ID of the body with the given name
			inline label bodyID(const word& name) const;

			//- Return the current transform to the global frame for the given body
			FoamRigidBodyMotion_EXPORT spatialTransform X0(const label bodyId) const;

			// Find the corresponding point in the master body frame
			FoamRigidBodyMotion_EXPORT vector masterPoint(const label bodyID, const vector& p) const;

			//- Return the velocity of the given point on the given body
			FoamRigidBodyMotion_EXPORT spatialVector v(const label bodyID, const vector& p) const;

			//- Apply the restraints and accumulate the internal joint forces
			//  into the tau field and external forces into the fx field
			FoamRigidBodyMotion_EXPORT void applyRestraints(scalarField& tau, Field<spatialVector>& fx) const;

			//- Calculate the joint acceleration qDdot from the joint state q,
			//  velocity qDot, internal force tau (in the joint frame) and
			//  external force fx (in the global frame) using the articulated body
			//  algorithm (Section 7.3 and Table 7.1)
			FoamRigidBodyMotion_EXPORT void forwardDynamics
			(
				rigidBodyModelState& state,
				const scalarField& tau,
				const Field<spatialVector>& fx
			) const;

			//- Correct the velocity and acceleration of the bodies in the model
			//  from the given joint state fields following an integration step
			//  of the forwardDynamics
			FoamRigidBodyMotion_EXPORT void forwardDynamicsCorrection(const rigidBodyModelState& state) const;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;

			//- Read coefficients dictionary and update system parameters,
			//  restraints but not the current state
			FoamRigidBodyMotion_EXPORT bool read(const dictionary& dict);


			// Ostream Operator

			FoamRigidBodyMotion_EXPORT friend Ostream& operator<<(Ostream&, const rigidBodyModel&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <rigidBodyModelI.hxx>

#endif // !_rigidBodyModel_Header
