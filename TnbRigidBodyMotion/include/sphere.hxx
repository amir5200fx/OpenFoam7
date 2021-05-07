#pragma once
#ifndef _sphere_Header
#define _sphere_Header

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
	tnbLib::RBD::sphere

Description
	Specialization of rigidBody to construct a sphere given the mass and radius.

SourceFiles
	sphereI.H
	sphere.C

\*---------------------------------------------------------------------------*/

#include <rigidBody.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		/*---------------------------------------------------------------------------*\
								 Class sphere Declaration
		\*---------------------------------------------------------------------------*/

		class sphere
			:
			public rigidBody
		{
			// Private member data

				//- Radius
			scalar r_;


			// Private Member Functions

				// Calculate and return the inertia tensor
			inline symmTensor I(const scalar m, const scalar r) const;


		public:

			//- Runtime type information
			//TypeName("sphere");
			static const char* typeName_() { return "sphere"; }
			static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
			static FoamRigidBodyMotion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from name, mass, centre of mass and radius
			inline sphere
			(
				const word& name,
				const scalar m,
				const vector& c,
				const scalar r
			);

			//- Construct from dictionary
			inline sphere
			(
				const word& name,
				const dictionary& dict
			);

			//- Return clone of this sphere
			FoamRigidBodyMotion_EXPORT virtual autoPtr<rigidBody> clone() const;


			//- Destructor
			FoamRigidBodyMotion_EXPORT virtual ~sphere();


			// Member Functions

				//- Return the radius of the sphere
			inline scalar r() const;

			//- Write
			FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <sphereI.hxx>

#endif // !_sphere_Header
