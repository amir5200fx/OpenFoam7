#pragma once
#ifndef _timeSelector_Header
#define _timeSelector_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::timeSelector

Description
	A List of scalarRange for selecting times.

	The timeSelector provides a convenient means of selecting multiple
	times. A typical use would be the following:

	\verbatim
	timeSelector::addOptions();
	// add other options
	#include "setRootCase.H"
	#include "createTime.H"
	instantList timeDirs = timeSelector::select0(runTime, args);
	...
	forAll(timeDirs, timeI)
	{
		...
	}
	\endverbatim

	The result program would receive \b -time, @b -latestTime, @b -constant
	and \b -noZero options. The @b -constant option explicitly includes the
	\c constant/ directory in the time list and the \b -noZero option
	explicitly excludes the \c 0/ directory from the time list.

	There may however also be many cases in which neither the \c constant/
	directory nor the \c 0/ directory contain particularly relevant
	information. This might occur, for example, when post-processing
	results. In this case, addOptions is called with optional boolean
	arguments.

	\verbatim
	timeSelector::addOptions(false, true);
	\endverbatim

	The first argument avoids adding the \b -constant option. The second
	argument adds an additional \b -withZero option and also prevents the
	\c 0/ directory from being included in the default time range and in the
	\b -latestTime selection.

SourceFiles
	timeSelector.C

\*---------------------------------------------------------------------------*/

#include <scalarRanges.hxx>
#include <instantList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class argList;
	class Time;

	/*---------------------------------------------------------------------------*\
							Class timeSelector Declaration
	\*---------------------------------------------------------------------------*/

	class timeSelector
		:
		public scalarRanges
	{
	public:

		// Constructors

			//- Construct Null
		FoamBase_EXPORT timeSelector();

		//- Construct from Istream
		FoamBase_EXPORT timeSelector(Istream&);


		// Member Functions

			//- Return true if the given instant is within the ranges
		FoamBase_EXPORT bool selected(const instant&) const;

		//- Return the set of selected instants in the given list that are
		//  within the ranges
		FoamBase_EXPORT List<bool> selected(const instantList&) const;

		//- Select a list of Time values that are within the ranges
		FoamBase_EXPORT instantList select(const instantList&) const;

		//- Select a list of Time values that are within the ranges
		FoamBase_EXPORT void inplaceSelect(instantList&) const;

		//- Add the options handled by timeSelector to argList::validOptions
		//
		// \param constant
		//   Add the \b -constant option to include the \c constant/ directory
		//
		// \param withZero
		//   Enable the \b -withZero option and alter the normal time selection
		//   behaviour (and \b -latestTime behaviour) to exclude the \c 0/
		//   directory. The \c 0/ directory will only be included when
		//   \b -withZero is specified.
		//   The \b -noZero option has precedence over the @b -withZero option.
		static FoamBase_EXPORT void addOptions
		(
			const bool constant = true,
			const bool withZero = false
		);

		//- Return the set of times selected based on the argList options
		static FoamBase_EXPORT instantList select
		(
			const instantList&,
			const argList& args,
			const word& constantName = "constant"
		);

		//- Return the set of times selected based on the argList options
		//  also set the runTime to the first instance or the
		//  \c constant/ directory if no instances are specified or available
		static FoamBase_EXPORT instantList select0
		(
			Time& runTime,
			const argList& args
		);

		//- If any time option provided return the set of times (as select0)
		//  otherwise return just the current time.
		//  Also set the runTime to the first instance
		static FoamBase_EXPORT instantList selectIfPresent
		(
			Time& runTime,
			const argList& args
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeSelector_Header
