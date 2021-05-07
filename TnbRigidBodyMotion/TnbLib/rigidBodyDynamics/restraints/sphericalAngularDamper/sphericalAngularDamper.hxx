#pragma once
#ifndef _sphericalAngularDamper_Header
#define _sphericalAngularDamper_Header

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
	tnbLib::RBD::restraints::sphericalAngularDamper

Description
	Spherical angular damper restraint.
	Operates in the local frame of the body.

SourceFiles
	sphericalAngularDamper.C

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
							   Class sphericalAngularDamper Declaration
			\*---------------------------------------------------------------------------*/

			class sphericalAngularDamper
				:
				public restraint
			{
				// Private Data

					//- Damping coefficient [Nms/rad]
				scalar coeff_;


			public:

				//- Runtime type information
				/*TypeName("sphericalAngularDamper");*/
				static const char* typeName_() { return "sphericalAngularDamper"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamRigidBodyMotion_EXPORT sphericalAngularDamper
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
							new sphericalAngularDamper(*this)
							);
				}


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~sphericalAngularDamper();


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

#endif // !_sphericalAngularDamper_Header
