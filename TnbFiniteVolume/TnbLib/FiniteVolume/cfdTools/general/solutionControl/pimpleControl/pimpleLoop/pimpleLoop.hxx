#pragma once
#ifndef _pimpleLoop_Header
#define _pimpleLoop_Header

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
	tnbLib::pimpleLoop

Description
	Pimple loop class. Implements the logic which controls the pimple loop
	generically for a given corrector convergence control. Can therefore be
	used be either single- or multi-region control classes.

SourceFiles
	pimpleLoopI.H
	pimpleLoop.C

\*---------------------------------------------------------------------------*/

#include <correctorConvergenceControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class pimpleLoop Declaration
	\*---------------------------------------------------------------------------*/

	class pimpleLoop
	{
	protected:

		// Protected data

		//- Reference to the solution control
		const solutionControl& control_;

		//- Maximum number of pimple correctors
		label nCorrPimple_;

		//- Current pimple corrector
		label corrPimple_;

		//- Flag to indicate convergence of the pimple loop
		bool converged_;


		// Protected Member Functions

		//- Read controls
		virtual bool read();


	public:

		// Static Data Members

			//- Run-time type information
		//TypeName("pimpleLoop");
		static const char* typeName_() { return "pimpleLoop"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from a solution control
		FoamFiniteVolume_EXPORT pimpleLoop(const solutionControl& control);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~pimpleLoop();


		// Member Functions

			// Access

				//- Maximum number of pimple correctors
		inline label nCorrPimple() const;

		//- Flat to indicate any pimple iteration
		inline bool anyPimpleIter() const;

		//- Flag to indicate the first pimple iteration
		inline bool firstPimpleIter() const;

		//- Flag to indicate the last pimple iteration
		inline bool finalPimpleIter() const;


		// Evolution

			//- Pimple loop
		FoamFiniteVolume_EXPORT bool loop(correctorConvergenceControl& convergence);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pimpleLoopI.hxx>

#endif // !_pimpleLoop_Header
