#pragma once
#ifndef _points0MotionSolver_Header
#define _points0MotionSolver_Header

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
	tnbLib::points0MotionSolver

Description
	Virtual base class for displacement motion solvers.

SourceFiles
	points0MotionSolver.C

\*---------------------------------------------------------------------------*/

#include <motionSolver.hxx>
#include <pointFields.hxx>
#include <pointIOField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
					   Class points0MotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class points0MotionSolver
		:
		public motionSolver
	{
	protected:

		// Protected data

			//- Starting points
		pointIOField points0_;


	public:

		//- Runtime type information
		TypeName("points0MotionSolver");


		// Constructors

			//- Construct from mesh and dictionary
		points0MotionSolver
		(
			const polyMesh&,
			const dictionary&,
			const word& type
		);

		//- Disallow default bitwise copy construction
		points0MotionSolver(const points0MotionSolver&) = delete;


		//- Destructor
		virtual ~points0MotionSolver();


		// Member Functions

			//- Return reference to the reference field
		pointField& points0()
		{
			return points0_;
		}

		//- Return reference to the reference field
		const pointField& points0() const
		{
			return points0_;
		}

		//- Update local data for geometry changes
		virtual void movePoints(const pointField&);

		//-  Update local data for topology changes
		virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const points0MotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_points0MotionSolver_Header
