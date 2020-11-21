#pragma once
#ifndef _singleRegionCorrectorConvergenceControl_Header
#define _singleRegionCorrectorConvergenceControl_Header

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
	tnbLib::singleRegionCorrectorConvergenceControl

Description
	Single-region-specific derivation of the corrector convergence control
	class

SourceFiles
	singleRegionCorrectorConvergenceControl.C

\*---------------------------------------------------------------------------*/

#include <correctorConvergenceControl.hxx>
#include <singleRegionSolutionControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class singleRegionCorrectorConvergenceControl Declaration
	\*---------------------------------------------------------------------------*/

	class singleRegionCorrectorConvergenceControl
		:
		public correctorConvergenceControl
	{
	protected:

		// Protected data

			//- Reference to the mesh
		const fvMesh& mesh_;

		//- List of residual data per field
		List<corrResidualData> corrResidualControl_;

		//- The index of the solution at the start of the corrector loop, for
		//  each field. If the field name is not in the table then the index is
		//  assumed to be zero; i.e, the first solution.
		HashTable<label> solveIndex_;


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("singleRegionCorrectorConvergenceControl");
		static const char* typeName_() { return "singleRegionCorrectorConvergenceControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from a solution control and the loop name
		FoamFiniteVolume_EXPORT singleRegionCorrectorConvergenceControl
		(
			const singleRegionSolutionControl& control,
			const word& loopName
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~singleRegionCorrectorConvergenceControl();


		// Member Functions

			// IO

				//- Read residual controls
		FoamFiniteVolume_EXPORT bool readCorrResidualControls();

		//- Print the residual controls
		FoamFiniteVolume_EXPORT void printCorrResidualControls(const label n) const;


		// Evolution

			//- Return true if corrector residual controls are present
		FoamFiniteVolume_EXPORT virtual bool hasCorrResidualControls() const;

		//- Return true if all correction convergence checks are satisfied
		FoamFiniteVolume_EXPORT virtual bool corrCriteriaSatisfied() const;

		//- Reset the solve index in the correction residual control data
		FoamFiniteVolume_EXPORT virtual void resetCorrSolveIndex();

		//- Update the solve index in the correction residual control data
		FoamFiniteVolume_EXPORT virtual void updateCorrSolveIndex();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_singleRegionCorrectorConvergenceControl_Header
