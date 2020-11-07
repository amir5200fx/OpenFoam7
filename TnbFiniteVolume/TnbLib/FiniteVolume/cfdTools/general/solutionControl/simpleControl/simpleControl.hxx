#pragma once
#ifndef _simpleControl_Header
#define _simpleControl_Header

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
	tnbLib::simpleControl

Description
	Simple control class. Provides time-loop control methods which exit the
	simulation once convergence criteria have been reached. Example usage:

	\verbatim
	simpleControl simple(mesh);

	while (simple.loop(runTime))
	{
		Info<< "Time = " << runTime.timeName() << nl << endl;

		// solve ...
	}
	\endverbatim

SourceFiles
	simpleControl.C

\*---------------------------------------------------------------------------*/

#include <fluidSolutionControl.hxx>
#include <singleRegionConvergenceControl.hxx>

#define SIMPLE_CONTROL

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class simpleControl Declaration
	\*---------------------------------------------------------------------------*/

	class simpleControl
		:
		public fluidSolutionControl,
		public singleRegionConvergenceControl
	{
	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("simpleControl");
		static const char* typeName_() { return "simpleControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from a mesh and the name of the algorithm
		FoamFiniteVolume_EXPORT simpleControl(fvMesh& mesh, const word& algorithmName = "SIMPLE");


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~simpleControl();


		// Member Functions

			// IO

				//- Read controls
		FoamFiniteVolume_EXPORT virtual bool read();


		// Evolution

		//- Time run loop
		FoamFiniteVolume_EXPORT bool run(Time& time);

		//- Time loop loop
		FoamFiniteVolume_EXPORT bool loop(Time& time);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_simpleControl_Header
