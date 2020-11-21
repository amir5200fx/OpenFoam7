#pragma once
#ifndef _pimpleControl_Header
#define _pimpleControl_Header

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
	tnbLib::pimpleControl

Description
	Pimple control class. Provides time-loop control methods which exit the
	simulation once convergence criteria have been reached. Also provides
	Pimple-loop control methods which exit the iteration once corrector
	convergence criteria have been met. Example usage:

	\verbatim
	pimpleControl pimple(mesh);

	while (pimple.run(runTime))
	{
		// pre-time-increment operations ...

		runTime ++;
		Info<< "Time = " << runTime.timeName() << nl << endl;

		while (pimple.loop())
		{
			// solve ...
		}

		// post-solve operations ...
	}
	\endverbatim

SourceFiles
	pimpleControlI.H
	pimpleControl.C

\*---------------------------------------------------------------------------*/

#include <pimpleNoLoopControl.hxx>
#include <pimpleLoop.hxx>
#include <singleRegionConvergenceControl.hxx>
#include <singleRegionCorrectorConvergenceControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class pimpleControl Declaration
	\*---------------------------------------------------------------------------*/

	class pimpleControl
		:
		public pimpleNoLoopControl,
		public pimpleLoop
	{
	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("pimpleControl");
		static const char* typeName_() { return "pimpleControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from a mesh and the name of the algorithm
		FoamFiniteVolume_EXPORT pimpleControl(fvMesh& mesh, const word& algorithmName = "PIMPLE");


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~pimpleControl();


		// Member Functions

			// IO

				//- Read controls
		FoamFiniteVolume_EXPORT virtual bool read();

		// Access

			//- Flag to indicate whether to solve the turbulence
		inline bool turbCorr() const;

		// Evolution

			//- Pimple loop
		FoamFiniteVolume_EXPORT bool loop();

		//- Time run loop
		FoamFiniteVolume_EXPORT bool run(Time& time);

		//- Time loop loop
		FoamFiniteVolume_EXPORT bool loop(Time& time);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pimpleControlI.hxx>

#endif // !_pimpleControl_Header
