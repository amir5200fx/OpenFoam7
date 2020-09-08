#pragma once
#ifndef _convergenceControl_Header
#define _convergenceControl_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::convergenceControl

Description
	Convergence control class. Provides methods to check the convergence of the
	time loop against an absolute residual tolerance.

SourceFiles
	convergenceControl.C
	convergenceControlTemplates.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>
#include <solutionControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class convergenceControl Declaration
	\*---------------------------------------------------------------------------*/

	class convergenceControl
	{
	public:

		//- Classes

			//- Residual data structure
		struct residualData
		{
			wordRe name;
			scalar absTol;
		};


		// Static Functions

			//- Get the list of names of the fields
			//  for which residual data is available
		static DynamicList<word> getFieldNames(const fvMesh& mesh);

		//- Get the initial residuals for the first and the i-th solves in this
		//  time-step
		static void getInitialResiduals
		(
			const fvMesh& mesh,
			const word& fieldName,
			const label solvei,
			scalar& r0,
			scalar& r
		);


		// Static Template Functions

			//- Return the index of the named field in residual control data, or -1
			//  if not present
		template<class ResidualData>
		static label residualControlIndex
		(
			const word& fieldName,
			const List<ResidualData>& residualControl,
			const bool useRegEx = true
		);

		//- Append the of names of the fields of this Type to the given list
		template<class Type>
		static void getFieldTypeNames
		(
			const fvMesh& mesh,
			DynamicList<word>& fieldNames
		);

		//- Get the initial residuals for the first and the i-th solves in this
		//  time-step
		template<class Type>
		static void getInitialTypeResiduals
		(
			const fvMesh& mesh,
			const word& fieldName,
			const label solvei,
			scalar& r0,
			scalar& r
		);


	protected:

		// Protected data

			//- Reference to the solution control
		const solutionControl& control_;


	public:

		// Static Data Members

			//- Run-time type information
		TypeName("convergenceControl");


		// Constructors

			//- Construct from a solution control
		convergenceControl(const solutionControl& control);

		//- Disallow default bitwise copy construction
		convergenceControl(const convergenceControl&) = delete;


		//- Destructor
		virtual ~convergenceControl();


		// Member Functions

			// Evolution

				//- Return true if residual controls are present
		virtual bool hasResidualControls() const = 0;

		//- Return true if all convergence checks are satisfied
		virtual bool criteriaSatisfied() const = 0;

		//- Flag to indicate whether convergance has been reached
		bool converged();

		//- End the run if convergance has been reached
		bool endIfConverged(Time& time);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const convergenceControl&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <convergenceControlI.hxx>

//#ifdef NoRepository
//#include <convergenceControlTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_convergenceControl_Header
