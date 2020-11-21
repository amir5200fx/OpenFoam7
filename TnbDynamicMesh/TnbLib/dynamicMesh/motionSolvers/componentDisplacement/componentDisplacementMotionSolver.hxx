#pragma once
#ifndef _componentDisplacementMotionSolver_Header
#define _componentDisplacementMotionSolver_Header

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
	tnbLib::componentDisplacementMotionSolver

Description
	Virtual base class for displacement motion solver

	The boundary displacement is set as a boundary condition
	on the pointDisplacementX pointScalarField.

SourceFiles
	componentDisplacementMotionSolver.C

\*---------------------------------------------------------------------------*/

#include <motionSolver.hxx>
#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
					   Class componentDisplacementMotionSolver Declaration
	\*---------------------------------------------------------------------------*/

	class componentDisplacementMotionSolver
		:
		public motionSolver
	{
	protected:

		// Protected data

			//- The component name to solve for
		word cmptName_;

		//- The component to solve for
		direction cmpt_;

		//- Reference point field for this component
		scalarField points0_;

		//- Point motion field
		mutable pointScalarField pointDisplacement_;


	private:

		// Private Member Functions

			//- Return the component corresponding to the given component name
		FoamDynamicMesh_EXPORT direction cmpt(const word& cmptName) const;


	public:

		//- Runtime type information
		//TypeName("componentDisplacementMotionSolver");
		static const char* typeName_() { return "componentDisplacementMotionSolver"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyMesh and dictionary and type
		FoamDynamicMesh_EXPORT componentDisplacementMotionSolver
		(
			const polyMesh&,
			const dictionary&,
			const word& type
		);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT componentDisplacementMotionSolver
		(
			const componentDisplacementMotionSolver&
		);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~componentDisplacementMotionSolver();


		// Member Functions

			//- Return reference to the reference field
		scalarField& points0()
		{
			return points0_;
		}

		//- Return reference to the reference field
		const scalarField& points0() const
		{
			return points0_;
		}

		//- Update local data for geometry changes
		FoamDynamicMesh_EXPORT virtual void movePoints(const pointField&);

		//-  Update local data for topology changes
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const componentDisplacementMotionSolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_componentDisplacementMotionSolver_Header
