#pragma once
#ifndef _CrankNicolson_Header
#define _CrankNicolson_Header

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
	tnbLib::RBD::rigidBodySolvers::CrankNicolson

Description
	Crank-Nicolson 2nd-order time-integrator for 6DoF solid-body motion.

	The off-centering coefficients for acceleration (velocity integration) and
	velocity (position/orientation integration) may be specified but default
	values of 0.5 for each are used if they are not specified.  With the default
	off-centering this scheme is equivalent to the Newmark scheme with default
	coefficients.

	Example specification in dynamicMeshDict:
	\verbatim
	solver
	{
		type    CrankNicolson;
		aoc     0.5;    // Acceleration off-centering coefficient
		voc     0.5;    // Velocity off-centering coefficient
	}
	\endverbatim

See also
	tnbLib::RBD::rigidBodySolvers::Newmark

SourceFiles
	CrankNicolson.C

\*---------------------------------------------------------------------------*/

#include <rigidBodySolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace rigidBodySolvers
		{

			/*---------------------------------------------------------------------------*\
									   Class CrankNicolson Declaration
			\*---------------------------------------------------------------------------*/

			class CrankNicolson
				:
				public rigidBodySolver
			{
				// Private Data

					//- Acceleration off-centering coefficient (default: 0.5)
				const scalar aoc_;

				//- Velocity off-centering coefficient (default: 0.5)
				const scalar voc_;


			public:

				//- Runtime type information
				/*TypeName("CrankNicolson");*/
				static const char* typeName_() { return "CrankNicolson"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct for the given body from dictionary
				FoamRigidBodyMotion_EXPORT CrankNicolson
				(
					rigidBodyMotion& body,
					const dictionary& dict
				);


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~CrankNicolson();


				// Member Functions

					//- Integrate the rigid-body motion for one time-step
				FoamRigidBodyMotion_EXPORT virtual void solve
				(
					const scalarField& tau,
					const Field<spatialVector>& fx
				);
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace rigidBodySolvers
	} // End namespace RBD
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CrankNicolson_Header
