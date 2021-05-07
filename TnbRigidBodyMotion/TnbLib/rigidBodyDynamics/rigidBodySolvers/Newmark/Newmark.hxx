#pragma once
#ifndef _Newmark_Header
#define _Newmark_Header

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
	tnbLib::RBD::rigidBodySolvers::Newmark

Description
	Newmark 2nd-order time-integrator for 6DoF solid-body motion.

	Reference:
	\verbatim
		Newmark, N. M. (1959).
		A method of computation for structural dynamics.
		Journal of the Engineering Mechanics Division, 85(3), 67-94.
	\endverbatim

	Example specification in dynamicMeshDict:
	\verbatim
	solver
	{
		type    Newmark;
		gamma   0.5;    // Velocity integration coefficient
		beta    0.25;   // Position integration coefficient
	}
	\endverbatim

SourceFiles
	Newmark.C

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
									   Class Newmark Declaration
			\*---------------------------------------------------------------------------*/

			class Newmark
				:
				public rigidBodySolver
			{
				// Private Data

					//- Coefficient for velocity integration (default: 0.5)
				const scalar gamma_;

				//- Coefficient for position and orientation integration (default: 0.25)
				const scalar beta_;


			public:

				//- Runtime type information
				/*TypeName("Newmark");*/
				static const char* typeName_() { return "Newmark"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct for the given body from dictionary
				FoamRigidBodyMotion_EXPORT Newmark
				(
					rigidBodyMotion& body,
					const dictionary& dict
				);


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~Newmark();


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

#endif // !_Newmark_Header
