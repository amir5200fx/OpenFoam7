#pragma once
#ifndef _singleRegionConvergenceControl_Header
#define _singleRegionConvergenceControl_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::singleRegionConvergenceControl

Description
	Single-region-specific derivation of the convergence control class

SourceFiles
	singleRegionConvergenceControl.C

\*---------------------------------------------------------------------------*/

#include <convergenceControl.hxx>
#include <singleRegionSolutionControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class singleRegionConvergenceControl Declaration
	\*---------------------------------------------------------------------------*/

	class singleRegionConvergenceControl
		:
		public convergenceControl
	{
	protected:

		// Protected data

			//- Reference to the mesh
		const fvMesh& mesh_;

		//- List of residual data per field
		List<residualData> residualControl_;


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("singleRegionConvergenceControl");
		static const char* typeName_() { return "singleRegionConvergenceControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from a solution control
		FoamFiniteVolume_EXPORT singleRegionConvergenceControl
		(
			const singleRegionSolutionControl& control
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~singleRegionConvergenceControl();


		// Member Functions

			// IO

				//- Read residual controls
		FoamFiniteVolume_EXPORT bool readResidualControls();

		//- Print the residual controls
		FoamFiniteVolume_EXPORT void printResidualControls() const;


		// Evolution

			//- Return true if residual controls are present
		FoamFiniteVolume_EXPORT virtual bool hasResidualControls() const;

		//- Return true if all convergence checks are satisfied
		FoamFiniteVolume_EXPORT virtual bool criteriaSatisfied() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_singleRegionConvergenceControl_Header
