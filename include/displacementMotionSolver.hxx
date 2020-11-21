#pragma once
#ifndef _displacementMotionSolver_Header
#define _displacementMotionSolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::displacementMotionSolver

Description
	Virtual base class for displacement motion solver

	The boundary displacement is set as a boundary condition
	on the pointDisplacement pointVectorField.

SourceFiles
	displacementMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <points0MotionSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class displacementMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class displacementMotionSolver
		:
		public points0MotionSolver
	{
	protected:

		// Protected data

			//- Point motion field
		mutable pointVectorField pointDisplacement_;


	public:

		//- Runtime type information
		//TypeName("displacementMotionSolver");
		static const char* typeName_() { return "displacementMotionSolver"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT displacementMotionSolver
		(
			const polyMesh&,
			const dictionary&,
			const word& type
		);

		//- Disallow default bitwise copy construction
		displacementMotionSolver(const displacementMotionSolver&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~displacementMotionSolver();


		// Member Functions

			//- Return reference to the point motion displacement field
		pointVectorField& pointDisplacement()
		{
			return pointDisplacement_;
		}

		//- Return const reference to the point motion displacement field
		const pointVectorField& pointDisplacement() const
		{
			return pointDisplacement_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const displacementMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_displacementMotionSolver_Header
