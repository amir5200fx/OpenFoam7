#pragma once
#ifndef _displacementSBRStressFvMotionSolver_Header
#define _displacementSBRStressFvMotionSolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::displacementSBRStressFvMotionSolver

Description
	Mesh motion solver for an fvMesh.  Based on solving the cell-centre
	solid-body rotation stress equations for the motion displacement.

SourceFiles
	displacementSBRStressFvMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <displacementMotionSolver.hxx>
#include <fvMotionSolver.hxx>
#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward class declarations
	class motionDiffusivity;

	/*---------------------------------------------------------------------------*\
				 Class displacementSBRStressFvMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class displacementSBRStressFvMotionSolver
		:
		public displacementMotionSolver,
		public fvMotionSolver
	{
		// Private Data

			//- Cell-centre motion field
		mutable volVectorField cellDisplacement_;

		//- Diffusivity used to control the motion
		autoPtr<motionDiffusivity> diffusivityPtr_;


	public:

		//- Runtime type information
		//TypeName("displacementSBRStress");
		static const char* typeName_() { return "displacementSBRStress"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary
		FoamFvMotionSolver_EXPORT displacementSBRStressFvMotionSolver
		(
			const polyMesh&,
			const dictionary&
		);

		//- Disallow default bitwise copy construction
		FoamFvMotionSolver_EXPORT displacementSBRStressFvMotionSolver
		(
			const displacementSBRStressFvMotionSolver&
		);


		//- Destructor
		FoamFvMotionSolver_EXPORT ~displacementSBRStressFvMotionSolver();


		// Member Functions

			//- Return reference to the cell motion displacement field
		volVectorField& cellDisplacement()
		{
			return cellDisplacement_;
		}

		//- Return const reference to the cell motion displacement field
		const volVectorField& cellDisplacement() const
		{
			return cellDisplacement_;
		}

		//- Return diffusivity
		motionDiffusivity& diffusivity()
		{
			return diffusivityPtr_();
		}

		//- Return point location obtained from the current motion field
		FoamFvMotionSolver_EXPORT virtual tmp<pointField> curPoints() const;

		//- Solve for motion
		FoamFvMotionSolver_EXPORT virtual void solve();

		//- Update topology
		FoamFvMotionSolver_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMotionSolver_EXPORT void operator=(const displacementSBRStressFvMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_displacementSBRStressFvMotionSolver_Header
