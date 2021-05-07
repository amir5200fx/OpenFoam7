#pragma once
#ifndef _compositeBody_Header
#define _compositeBody_Header

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
	tnbLib::RBD::compositeBody

Description
	This specialized rigidBody holds the original body after it has been merged
	into a parent.

SourceFiles
	compositeBodyI.H
	compositeBody.C

\*---------------------------------------------------------------------------*/

#include <rigidBody.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		/*---------------------------------------------------------------------------*\
								 Class compositeBody Declaration
		\*---------------------------------------------------------------------------*/

		class compositeBody
			:
			public rigidBody
		{
			// Private Data

				//- Original body from which this composite-body was constructed
			autoPtr<rigidBody> body_;

		public:

			// Constructors

				//- Construct a merged version of the given rigidBody
				//  providing the ID of the parent body to which this will be merged
				//  and the transform relative to the parent
			inline compositeBody(const autoPtr<rigidBody>& bodyPtr);

			//- Return clone of this compositeBody
			FoamRigidBodyMotion_EXPORT virtual autoPtr<rigidBody> clone() const;


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~compositeBody();


			// Member Functions

				//- Return the type name of the original body
			FoamRigidBodyMotion_EXPORT virtual const word& type() const;

			//- Return the original body from which this composite-body
			//  was constructed
			inline const rigidBody& body() const;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <compositeBodyI.hxx>

#endif // !_compositeBody_Header
