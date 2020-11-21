#pragma once
#ifndef _multiRegionSolutionControl_Header
#define _multiRegionSolutionControl_Header

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
	tnbLib::multiRegionSolutionControl

Description
	Multi-region-specific derivation of the solution control class

SourceFiles
	multiRegionSolutionControl.C

\*---------------------------------------------------------------------------*/

#include <solutionControl.hxx>
#include <fvSolution.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class multiRegionSolutionControl Declaration
	\*---------------------------------------------------------------------------*/

	class multiRegionSolutionControl
		:
		public solutionControl
	{
		// Private Data

		//- Solution instance
		const fvSolution solution_;


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("multiRegionSolutionControl");
		static const char* typeName_() { return "multiRegionSolutionControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from a time and the name of the algorithm
		FoamFiniteVolume_EXPORT multiRegionSolutionControl(const Time& time, const word& algorithmName);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~multiRegionSolutionControl();


		// Member Functions

		// Access

		//- Return the solution dictionary
		FoamFiniteVolume_EXPORT virtual const dictionary& dict() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_multiRegionSolutionControl_Header
