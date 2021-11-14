#pragma once
#ifndef _sixDoFRigidBodyControl_Header
#define _sixDoFRigidBodyControl_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::sixDoFRigidBodyControl

Description
	Convergence control based on the 6-DoF motion state.

	The body linear and angular velocities are averaged over a specified time
	window and compared to specified velocity convergence criteria and the run
	stopped after writing the current time results, if the criteria are met.

	Example of function object specification:
	\verbatim
	sixDoFRigidBodyControl
	{
		type           sixDoFRigidBodyControl;
		libs           ("libsixDoFRigidBodyState.so");

		angleFormat    degrees;

		window                      1;
		convergedVelocity           (1e-2 1e-2 1e-2);
		convergedAngularVelocity    (5 5 5);
	}
	\endverbatim

	Note the units of the \c convergedAngularVelocity are specified by the \c
	angleFormat entry.

Usage
	\table
	Property     | Description                       | Required | Default value
	type         | Type name: sixDoFRigidBodyControl | yes      |
	angleFormat  | Degrees or radians                | no       | radian
	window       | Averaging window                  | yes      |
	convergedVelocity | Linear velocity convergence criterion         | yes |
	convergedAngularVelocity | Angular velocity convergence criterion | yes |
	\endtable

See also
	tnbLib::functionObjects::sixDoFRigidBodyState

SourceFiles
	sixDoFRigidBodyControl.C

\*---------------------------------------------------------------------------*/

#include <sixDoFRigidBodyState.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						   Class sixDoFRigidBodyControl Declaration
		\*---------------------------------------------------------------------------*/

		class sixDoFRigidBodyControl
			:
			public sixDoFRigidBodyState
		{
			// Private Data

				//- Reference to the Time
			const Time& time_;

			scalar w_;

			vector convergedVelocity_;

			vector convergedAngularVelocity_;

			vector meanVelocity_;

			vector meanAngularVelocity_;



		public:

			//- Runtime type information
			TypeName("sixDoFRigidBodyControl");


			// Constructors

				//- Construct from Time and dictionary
			sixDoFRigidBodyControl
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			sixDoFRigidBodyControl(const sixDoFRigidBodyControl&) = delete;


			//- Destructor
			virtual ~sixDoFRigidBodyControl();


			// Member Functions

				//- Read the sixDoFRigidBodyControl data
			virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			virtual bool execute();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const sixDoFRigidBodyControl&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sixDoFRigidBodyControl_Header