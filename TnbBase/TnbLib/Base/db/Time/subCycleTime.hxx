#pragma once
#ifndef _subCycleTime_Header
#define _subCycleTime_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::subCycleTime

Description
	A class for managing sub-cycling times

SourceFiles
	subCycleTime.C

\*---------------------------------------------------------------------------*/

#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class subCycleTime Declaration
	\*---------------------------------------------------------------------------*/

	class subCycleTime
	{
		// Private Data

		Time& time_;

		label nSubCycles_;
		label subCycleIndex_;

	public:

		// Constructors

			//- Construct from original time and number of sub-cycles
		FoamBase_EXPORT subCycleTime(Time&, const label nSubCycles);


		//- Destructor
		FoamBase_EXPORT ~subCycleTime();


		// Member Functions

			//- Return true if the number of sub-cycles has been reached
		FoamBase_EXPORT bool end() const;

		//- End the sub-cycling and reset the time-state
		FoamBase_EXPORT void endSubCycle();

		//- Return the total number of sub-cycles
		label nSubCycles() const
		{
			return nSubCycles_;
		}

		//- Return the current sub-cycle index
		label index() const
		{
			return subCycleIndex_;
		}


		// Member Operators

			//- Prefix increment
		FoamBase_EXPORT subCycleTime& operator++();

		//- Postfix increment
		FoamBase_EXPORT subCycleTime& operator++(int);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_subCycleTime_Header
