#pragma once
#ifndef _linearSpring_Header
#define _linearSpring_Header

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
	tnbLib::RBD::restraints::linearSpring

Description
	Linear spring restraint.

SourceFiles
	linearSpring.C

\*---------------------------------------------------------------------------*/

#include <rigidBodyRestraint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace restraints
		{

			/*---------------------------------------------------------------------------*\
									  Class linearSpring Declaration
			\*---------------------------------------------------------------------------*/

			class linearSpring
				:
				public restraint
			{
				// Private Data

					//- Anchor point, where the spring is attached to an immovable
					//  object
				point anchor_;

				//- Reference point of attachment to the solid body
				point refAttachmentPt_;

				//- Spring stiffness coefficient [N/m]
				scalar stiffness_;

				//- Damping coefficient [Ns/m]
				scalar damping_;

				//- Rest length - length of spring when no forces are applied to it
				scalar restLength_;


			public:

				//- Runtime type information
				/*TypeName("linearSpring");*/
				static const char* typeName_() { return "linearSpring"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamRigidBodyMotion_EXPORT linearSpring
				(
					const word& name,
					const dictionary& dict,
					const rigidBodyModel& model
				);

				//- Construct and return a clone
				virtual autoPtr<restraint> clone() const
				{
					return autoPtr<restraint>
						(
							new linearSpring(*this)
							);
				}


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~linearSpring();


				// Member Functions

					//- Accumulate the retraint internal joint forces into the tau field and
					//  external forces into the fx field
				FoamRigidBodyMotion_EXPORT virtual void restrain
				(
					scalarField& tau,
					Field<spatialVector>& fx
				) const;

				//- Update properties from given dictionary
				FoamRigidBodyMotion_EXPORT virtual bool read(const dictionary& dict);

				//- Write
				FoamRigidBodyMotion_EXPORT virtual void write(Ostream&) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace restraints
	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearSpring_Header
