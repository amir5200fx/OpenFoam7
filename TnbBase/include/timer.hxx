#pragma once
#ifndef _timer_Header
#define _timer_Header

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
	tnbLib::timer

Description
	Implements a timeout mechanism via sigalarm.

	Example usage:
	\code
		timer myTimer(5);     // 5 sec
		..
		if (timedOut(myTimer))
		{
			// timed out
		}
		else
		{
			// do something possible blocking
		}
	\endcode

	Constructor set signal handler on sigalarm and alarm(). Destructor
	clears these.

	timedOut is macro because setjmp can't be in member function of timer.
	?something to do with stack frames.

Warning
	The setjmp restores complete register state so including local vars
	held in regs. So if in blocking part something gets calced in a stack
	based variable make sure it is declared 'volatile'.

SourceFiles
	timer.C

\*---------------------------------------------------------------------------*/

#include <className.hxx>

#include <signal.h>
#include <setjmp.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Check it a timeout has occurred
//  keep setjmp in same stack frame so no function calls
#define timedOut(x) \
    (((x).newTimeOut_ > 0) ? setjmp(tnbLib::timer::envAlarm) : false)

typedef	void(*__p_sig_fn_t)(int);

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class timer Declaration
	\*---------------------------------------------------------------------------*/

	class timer
	{
		// Private data

			//- old signal
		static FoamBase_EXPORT __p_sig_fn_t oldAction_;

		//- old alarm() value
		static FoamBase_EXPORT unsigned int oldTimeOut_;


		// Private Member Functions

			//- alarm handler
		static FoamBase_EXPORT void signalHandler(int);


	public:

		// Public data

			//- Declare name of the class and its debug switch
		//ClassName("timer");
		static const char* typeName_() { return "timer"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;

		//- current time out value. Needed by macro timedOut
		unsigned int newTimeOut_;

		//- state for setjmp. Needed by macro timedOut
		static FoamBase_EXPORT jmp_buf envAlarm;


		// Constructors

			//- Construct from components.
			//  newTimeOut=0 makes it do nothing.
		FoamBase_EXPORT timer(const unsigned int newTimeOut);


		// Destructor

		FoamBase_EXPORT ~timer();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timer_Header
