#pragma once
#ifndef _fvMotionSolver_Header
#define _fvMotionSolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
	tnbLib::fvMotionSolver

Description
	Base class for fvMesh based motionSolvers.

SourceFiles
	fvMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class velocityMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class fvMotionSolver
	{

	protected:

		// Protected data

			//- The fvMesh to be moved
		const fvMesh& fvMesh_;


		// Protected Member Functions

			//- Create the corresponding patch types for cellMotion from those
			//  of the given pointMotion
		template<class Type>
		wordList cellMotionBoundaryTypes
		(
			const typename GeometricField<Type, pointPatchField, pointMesh>::
			Boundary& pmUbf
		) const;

	public:

		//- Runtime type information
		//ClassName("displacementMotionSolver");
		static const char* typeName_() { return "displacementMotionSolver"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;

		// Constructors

			//- Construct from polyMesh
		FoamFvMotionSolver_EXPORT fvMotionSolver(const polyMesh&);


		// Member Functions

			//- Return reference to the fvMesh to be moved
		const fvMesh& mesh() const
		{
			return fvMesh_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvMotionSolverI.hxx>

//#ifdef NoRepository
//#include <fvMotionSolverTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMotionSolver_Header
