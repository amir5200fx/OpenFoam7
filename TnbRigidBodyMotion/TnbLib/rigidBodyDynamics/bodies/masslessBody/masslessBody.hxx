#pragma once
#ifndef _masslessBody_Header
#define _masslessBody_Header

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
	tnbLib::RBD::masslessBody

Description

SourceFiles
	masslessBodyI.H
	masslessBody.C

\*---------------------------------------------------------------------------*/

#include <rigidBody.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		/*---------------------------------------------------------------------------*\
								 Class masslessBody Declaration
		\*---------------------------------------------------------------------------*/

		class masslessBody
			:
			public rigidBody
		{

		public:

			//- Runtime type information
			//TypeName("masslessBody");
			static const char* typeName_() { return "masslessBody"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct a massless body
			inline masslessBody();

			//- Construct a named massless body
			inline masslessBody(const word& name);

			//- Construct from dictionary
			inline masslessBody
			(
				const word& name,
				const dictionary& dict
			);

			//- Return clone of this masslessBody
			FoamRigidBodyMotion_EXPORT virtual autoPtr<rigidBody> clone() const;


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~masslessBody();


			// Member Functions

				//- Return true if this body is a massless component of a composite body
			FoamRigidBodyMotion_EXPORT virtual bool massless() const;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <masslessBodyI.hxx>

#endif // !_masslessBody_Header
