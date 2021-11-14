#pragma once
#ifndef _sixDoFRigidBodyState_Header
#define _sixDoFRigidBodyState_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::sixDoFRigidBodyState

Description
	Writes the 6-DoF motion state.

	Example of function object specification:
	\verbatim
	sixDoFRigidBodyState
	{
		type           sixDoFRigidBodyState;
		libs           ("libsixDoFRigidBodyState.so");
		angleFormat    degrees;
	}
	\endverbatim

Usage
	\table
		Property     | Description                  | Required | Default value
		type         | type name: sixDoFRigidBodyState    | yes |
		angleFormat  | degrees or radians           | no       | radian
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	sixDoFRigidBodyState.C

\*---------------------------------------------------------------------------*/

#include <RigidBodyMotion_Module.hxx>

#include <fvMeshFunctionObject.hxx>
#include <vector.hxx>
#include <logFiles.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	class sixDoFRigidBodyMotion;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						   Class sixDoFRigidBodyState Declaration
		\*---------------------------------------------------------------------------*/

		class sixDoFRigidBodyState
			:
			public fvMeshFunctionObject,
			public logFiles
		{
			// Private Data

			word angleFormat_;


			// Private Member Functions

			const sixDoFRigidBodyMotion& motion() const;


		protected:

			// Protected Member Functions

				//- overloaded writeFileHeader from writeFile
			virtual void writeFileHeader(const label i = 0);


		public:

			//- Runtime type information
			TypeName("sixDoFRigidBodyState");


			// Constructors

				//- Construct from Time and dictionary
			sixDoFRigidBodyState
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			sixDoFRigidBodyState(const sixDoFRigidBodyState&) = delete;


			//- Destructor
			virtual ~sixDoFRigidBodyState();


			// Member Functions

				//- Return the current body velocity
			vector velocity() const;

			//- Return the current body angular velocity
			vector angularVelocity() const;

			//- Read the sixDoFRigidBodyState data
			virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			virtual bool execute();

			//- Write the sixDoFRigidBodyState
			virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const sixDoFRigidBodyState&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sixDoFRigidBodyState_Header
