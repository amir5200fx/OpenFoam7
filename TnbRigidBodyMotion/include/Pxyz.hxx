#pragma once
#ifndef _Pxyz_Header
#define _Pxyz_Header

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
	tnbLib::RBD::joints::Pxyz

Description
	Prismatic joint for translation in the x/y/z directions.

	Reference:
	\verbatim
		Featherstone, R. (2008).
		Rigid body dynamics algorithms.
		Springer.
		Chapter 4.
	\endverbatim

SourceFiles
	Pxyz.C

\*---------------------------------------------------------------------------*/

#include <joint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{

			/*---------------------------------------------------------------------------*\
									 Class Pxyz Declaration
			\*---------------------------------------------------------------------------*/

			class Pxyz
				:
				public joint
			{

			public:

				//- Runtime type information
				/*TypeName("Pxyz");*/
				static const char* typeName_() { return "Pxyz"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct for given model
				FoamRigidBodyMotion_EXPORT Pxyz(const rigidBodyModel& model);

				//- Construct for given model from dictionary
				FoamRigidBodyMotion_EXPORT Pxyz(const rigidBodyModel& model, const dictionary& dict);

				//- Clone this joint
				FoamRigidBodyMotion_EXPORT virtual autoPtr<joint> clone() const;


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~Pxyz();


				// Member Functions

					//- Update the model state for this joint
				FoamRigidBodyMotion_EXPORT virtual void jcalc
				(
					joint::XSvc& J,
					const rigidBodyModelState& state
				) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace joints
	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Pxyz_Header
