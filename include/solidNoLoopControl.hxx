#pragma once
#ifndef _solidNoLoopControl_Header
#define _solidNoLoopControl_Header

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
	tnbLib::solidNoLoopControl

Description
	Solid no-loop control class. Implements non-orthogonal and convergence
	controls, but leaves loop controls to the derivation or owner. Can be
	derived into a "full" solid control or can be owned by a multi-region class.

SourceFiles
	solidNoLoopControl.C

\*---------------------------------------------------------------------------*/

#include <nonOrthogonalSolutionControl.hxx>
#include <pimpleLoop.hxx>
#include <singleRegionConvergenceControl.hxx>
#include <singleRegionCorrectorConvergenceControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class solidNoLoopControl Declaration
	\*---------------------------------------------------------------------------*/

	class solidNoLoopControl
		:
		public nonOrthogonalSolutionControl,
		public singleRegionConvergenceControl,
		public singleRegionCorrectorConvergenceControl
	{
	protected:

		// Protected data

		//- The pimple loop
		const pimpleLoop& loop_;


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("solidNoLoopControl");
		static const char* typeName_() { return "solidNoLoopControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from a mesh, the name of the algorithm, and a reference
		//  to the pimple loop
		FoamFiniteVolume_EXPORT solidNoLoopControl
		(
			fvMesh& mesh,
			const word& algorithmName,
			const pimpleLoop& loop
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~solidNoLoopControl();


		// Member Functions

		// IO

		//- Read controls
		FoamFiniteVolume_EXPORT virtual bool read();

		// Access

		//- Flag to indicate whether in final state
		FoamFiniteVolume_EXPORT virtual bool isFinal() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidNoLoopControl_Header
