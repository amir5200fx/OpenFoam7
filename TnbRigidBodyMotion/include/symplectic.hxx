#pragma once
#ifndef _symplectic_Header
#define _symplectic_Header

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
	tnbLib::RBD::rigidBodySolvers::symplectic

Description
	Symplectic 2nd-order explicit time-integrator for rigid-body motion.

	Reference:
	\verbatim
		Dullweber, A., Leimkuhler, B., & McLachlan, R. (1997).
		Symplectic splitting methods for rigid body molecular dynamics.
		The Journal of chemical physics, 107(15), 5840-5851.
	\endverbatim

	Can only be used for explicit integration of the motion of the body,
	i.e. may only be called once per time-step, no outer-correctors may be
	applied.  For implicit integration with outer-correctors choose either
	CrankNicolson or Newmark schemes.

	Example specification in dynamicMeshDict:
	\verbatim
	solver
	{
		type    symplectic;
	}
	\endverbatim

See also
	tnbLib::RBD::rigidBodySolvers::CrankNicolson
	tnbLib::RBD::rigidBodySolvers::Newmark

SourceFiles
	symplectic.C

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
									   Class symplectic Declaration
			\*---------------------------------------------------------------------------*/

			class symplectic
				:
				public rigidBodySolver
			{

			public:

				//- Runtime type information
				/*TypeName("symplectic");*/
				static const char* typeName_() { return "symplectic"; }
				static FoamRigidBodyMotion_EXPORT const ::tnbLib::word typeName;
				static FoamRigidBodyMotion_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct for the given body from dictionary
				FoamRigidBodyMotion_EXPORT symplectic
				(
					rigidBodyMotion& body,
					const dictionary& dict
				);


				//- Destructor
				FoamRigidBodyMotion_EXPORT virtual ~symplectic();


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

#endif // !_symplectic_Header
