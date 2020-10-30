#pragma once
#ifndef _cpuTime_Header
#define _cpuTime_Header

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
	tnbLib::cpuTime

Description
	Starts timing CPU usage and return elapsed time from start.

See also
	clockTime

SourceFiles
	cpuTime.C

\*---------------------------------------------------------------------------*/

#include <includeModule.hxx>

#include <ctime>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class cpuTime Declaration
\*---------------------------------------------------------------------------*/

	class cpuTime
	{
		// Private data

		std::clock_t startTime_;
		mutable std::clock_t lastTime_;
		mutable std::clock_t newTime_;

		static FoamBase_EXPORT void getTime(std::clock_t& t);

		static FoamBase_EXPORT double timeDifference
		(
			const std::clock_t& start,
			const std::clock_t& end
		);


	public:

		// Constructors

			//- Construct from components
		FoamBase_EXPORT cpuTime();


		// Member Functions

			// Access

				//- Returns CPU time from start of run
		FoamBase_EXPORT double elapsedCpuTime() const;

		//- Returns CPU time from last call of cpuTimeIncrement()
		FoamBase_EXPORT double cpuTimeIncrement() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_cpuTime_Header
