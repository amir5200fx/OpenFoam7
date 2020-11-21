#pragma once
#ifndef _velocityMotionSolver_Header
#define _velocityMotionSolver_Header

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
	tnbLib::velocityMotionSolver

Description
	Virtual base class for velocity motion solver

	The boundary displacement is set as a boundary condition
	on the pointMotionU pointVectorField.

SourceFiles
	velocityMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <motionSolver.hxx>
#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
					   Class velocityMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class velocityMotionSolver
		:
		public motionSolver
	{
	protected:

		// Protected data

			//- Point motion field
		mutable pointVectorField pointMotionU_;


	public:

		//- Runtime type information
		//TypeName("velocityMotionSolver");
		static const char* typeName_() { return "velocityMotionSolver"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and dictionary
		FoamDynamicMesh_EXPORT velocityMotionSolver
		(
			const polyMesh&,
			const dictionary&,
			const word& type
		);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT velocityMotionSolver
		(
			const velocityMotionSolver&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~velocityMotionSolver();


		// Member Functions

			//- Return reference to the point motion velocity field
		pointVectorField& pointMotionU()
		{
			return pointMotionU_;
		}

		//- Return const reference to the point motion velocity field
		const pointVectorField& pointMotionU() const
		{
			return pointMotionU_;
		}

		//- Update local data for geometry changes
		FoamDynamicMesh_EXPORT virtual void movePoints(const pointField&);

		//-  Update local data for topology changes
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const velocityMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_velocityMotionSolver_Header
