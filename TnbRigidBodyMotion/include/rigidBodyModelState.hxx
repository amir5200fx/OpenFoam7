#pragma once
#ifndef _rigidBodyModelState_Header
#define _rigidBodyModelState_Header

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
	tnbLib::RBD::rigidBodyModelState

Description
	Holds the motion state of rigid-body model.

SourceFiles
	rigidBodyModelStateI.H
	rigidBodyModelState.C
	rigidBodyModelStateIO.C

\*---------------------------------------------------------------------------*/

#include <rigidBodyModel.hxx>
#include <scalarField.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Istream;
	class Ostream;

	namespace RBD
	{

		// Forward declaration of friend functions and operators
		class rigidBodyModelState;
		FoamRigidBodyMotion_EXPORT Istream& operator>>(Istream&, rigidBodyModelState&);
		FoamRigidBodyMotion_EXPORT Ostream& operator<<(Ostream&, const rigidBodyModelState&);


		/*---------------------------------------------------------------------------*\
						  Class rigidBodyModelState Declaration
		\*---------------------------------------------------------------------------*/

		class rigidBodyModelState
		{
			// Private Data

				//- Joint position and orientation
			scalarField q_;

			//- Joint velocity
			scalarField qDot_;

			//- Joint acceleration
			scalarField qDdot_;

			//- The time
			scalar t_;

			//- The time-step used to integrate to this state
			scalar deltaT_;


		public:

			// Constructors

				//- Construct for the given rigidBodyModel
			FoamRigidBodyMotion_EXPORT rigidBodyModelState(const rigidBodyModel& model);

			//- Construct from dictionary for the given rigidBodyModel
			FoamRigidBodyMotion_EXPORT rigidBodyModelState
			(
				const rigidBodyModel& model,
				const dictionary& dict
			);


			// Member Functions

				// Access

					//- Return access to the joint position and orientation
			inline const scalarField& q() const;

			//- Return access to the joint velocity
			inline const scalarField& qDot() const;

			//- Return access to the joint acceleration
			inline const scalarField& qDdot() const;

			//- Return access to the time
			inline scalar t() const;

			//- Return access to the time-step
			inline scalar deltaT() const;


			// Edit

				//- Return access to the joint position and orientation
			inline scalarField& q();

			//- Return access to the joint velocity
			inline scalarField& qDot();

			//- Return access to the joint acceleration
			inline scalarField& qDdot();

			//- Return access to the time
			inline scalar& t();

			//- Return access to the time-step
			inline scalar& deltaT();


			//- Write to dictionary
			FoamRigidBodyMotion_EXPORT void write(dictionary& dict) const;

			//- Write to stream
			FoamRigidBodyMotion_EXPORT void write(Ostream&) const;


			// IOstream Operators

			FoamRigidBodyMotion_EXPORT friend Istream& operator>>(Istream&, rigidBodyModelState&);
			FoamRigidBodyMotion_EXPORT friend Ostream& operator<<(Ostream&, const rigidBodyModelState&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <rigidBodyModelStateI.hxx>

#endif // !_rigidBodyModelState_Header
