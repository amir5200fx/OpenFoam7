#pragma once
#ifndef _sigStopAtWriteNow_Header
#define _sigStopAtWriteNow_Header

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
	tnbLib::sigStopAtWriteNow

Description
	Signal handler for interrupt defined by
		OptimisationSwitches::stopAtWriteNowSignal

	Write and stop the job.

SourceFiles
	sigStopAtWriteNow.C

\*---------------------------------------------------------------------------*/

#include <includeModule.hxx>

#include <signal.h>

typedef	void(*__p_sig_fn_t)(int);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Time;

	/*---------------------------------------------------------------------------*\
							   Class sigStopAtWriteNow Declaration
	\*---------------------------------------------------------------------------*/

	class sigStopAtWriteNow
	{
		// Private Data

			//- Number of signal to use
		static FoamBase_EXPORT int signal_;

		//- Pointer to Time
		static FoamBase_EXPORT Time const* runTimePtr_;

		//- Saved old signal trapping setting
		static FoamBase_EXPORT __p_sig_fn_t oldAction_;


		// Private Member Functions

		static FoamBase_EXPORT void sigHandler(int);


	public:

		//- wip. Have setter have access to signal_
		friend class addstopAtWriteNowSignalToOpt;


		// Constructors

			//- Construct null
		FoamBase_EXPORT sigStopAtWriteNow();

		//- Construct from components
		FoamBase_EXPORT sigStopAtWriteNow(const bool verbose, const Time& runTime);


		//- Destructor
		FoamBase_EXPORT ~sigStopAtWriteNow();


		// Member Functions

			//- (re)set signal catcher
		static FoamBase_EXPORT void set(const bool verbose);

		//- Is active?
		FoamBase_EXPORT bool active() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sigStopAtWriteNow_Header
