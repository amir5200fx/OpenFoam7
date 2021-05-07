#pragma once
#ifndef _cuboid_Header
#define _cuboid_Header

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
	tnbLib::RBD::cuboid

Description
	Specialization of rigidBody to construct a cuboid given the mass and
	lengths of the sides.

SourceFiles
	cuboidI.H
	cuboid.C

\*---------------------------------------------------------------------------*/

#include <rigidBody.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		/*---------------------------------------------------------------------------*\
								 Class cuboid Declaration
		\*---------------------------------------------------------------------------*/

		class cuboid
			:
			public rigidBody
		{
			// Private member data

				//- Lengths of the sides
			vector L_;


			// Private Member Functions

				// Calculate and return the inertia tensor
			inline symmTensor I(const scalar m, const vector& L) const;


		public:

			//- Runtime type information
			//TypeName("cuboid");
			static const char* typeName_() { return "cuboid"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from name, mass, centre of mass and lengths of the sides.
			inline cuboid
			(
				const word& name,
				const scalar m,
				const vector& c,
				const vector& L
			);

			//- Construct from dictionary
			inline cuboid
			(
				const word& name,
				const dictionary& dict
			);

			//- Return clone of this cuboid
			FoamRigidBodyMotion_EXPORT virtual autoPtr<rigidBody> clone() const;


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~cuboid();


			// Member Functions

				//- Return the lengths of the sides of the cuboid
			inline const vector& L() const;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cuboidI.hxx>

#endif // !_cuboid_Header
