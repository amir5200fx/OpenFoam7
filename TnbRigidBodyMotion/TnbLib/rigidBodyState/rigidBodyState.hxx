#pragma once
#ifndef _rigidBodyState_Header
#define _rigidBodyState_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::rigidBodyState

Description
	Writes the rigid body motion state.

	Example of function object specification:
	\verbatim
	rigidBodyState
	{
		type           rigidBodyState;
		libs           ("librigidBodyState.so");
		angleFormat    degrees;
	}
	\endverbatim

Usage
	\table
		Property     | Description                  | Required | Default value
		type         | type name: rigidBodyState    | yes |
		angleFormat  | degrees or radians           | no       | radian
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	rigidBodyState.C

\*---------------------------------------------------------------------------*/

#include <RigidBodyMotion_Module.hxx>

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <rigidBodyMotion.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						   Class rigidBodyState Declaration
		\*---------------------------------------------------------------------------*/

		class rigidBodyState
			:
			public fvMeshFunctionObject,
			public logFiles
		{
			// Private Data

			word angleFormat_;

			//- List of the names of the rigid bodies
			wordList names_;


		protected:

			// Protected Member Functions

				//- overloaded writeFileHeader from writeFile
			FoamRigidBodyMotion_EXPORT virtual void writeFileHeader(const label i = 0);


		public:

			//- Runtime type information
			/*TypeName("rigidBodyState");*/
			static const char* typeName_() { return "rigidBodyState"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamRigidBodyMotion_EXPORT rigidBodyState
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			rigidBodyState(const rigidBodyState&) = delete;


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~rigidBodyState();


			// Member Functions

			FoamRigidBodyMotion_EXPORT const RBD::rigidBodyMotion& motion() const;

			//- Read the rigidBodyState data
			FoamRigidBodyMotion_EXPORT virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			FoamRigidBodyMotion_EXPORT virtual bool execute();

			//- Write the rigidBodyState
			FoamRigidBodyMotion_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const rigidBodyState&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rigidBodyState_Header
