#pragma once
#ifndef _systemCall_Header
#define _systemCall_Header

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
	tnbLib::functionObjects::systemCall

Description
	Executes system calls, entered in the form of a string lists.

	Calls can be made at the following points in the calculation:
	- every time step
	- every output time
	- end of the calculation

	Example of function object specification:
	\verbatim
	systemCall1
	{
		type        systemCall;
		libs        ("libutilityFunctionObjects.so");
		...
		executeCalls
		(
			"echo execute"
		);
		writeCalls
		(
			"echo \*\*\* writing data \*\*\*"
		);
		endCalls
		(
			"echo \*\*\* writing .bashrc \*\*\*"
			"cat ~/.bashrc"
			"echo \*\*\* done \*\*\*"
		);
	}
	\endverbatim

Usage
	\table
		Property     | Description              | Required    | Default value
		type         | type name: systemCall    | yes         |
		executeCalls | list of calls on execute | yes         |
		writeCalls   | list of calls on write   | yes         |
		endCalls     | list of calls on end     | yes         |
	\endtable

Note
	Since this function object executes system calls, there is a potential
	security risk.  In order to use the \c systemCall function object, the
	\c allowSystemOperations must be set to '1'; otherwise, system calls will
	not be allowed.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::timeControl

SourceFiles
	systemCall.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <stringList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class systemCall Declaration
		\*---------------------------------------------------------------------------*/

		class systemCall
			:
			public functionObject
		{
		protected:

			// Private Data

				//- List of calls to execute - every step
			stringList executeCalls_;

			//- List of calls to execute when exiting the time-loop
			stringList endCalls_;

			//- List of calls to execute - write steps
			stringList writeCalls_;


		public:

			//- Runtime type information
			//TypeName("systemCall");
			static const char* typeName_() { return "systemCall"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT systemCall
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT systemCall(const systemCall&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~systemCall();


			// Member Functions

				//- Read the system calls
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute the "executeCalls" at each time-step
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Execute the "endCalls" at the final time-loop
			FoamFunctionObjects_EXPORT virtual bool end();

			//- Write, execute the "writeCalls"
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const systemCall&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_systemCall_Header
