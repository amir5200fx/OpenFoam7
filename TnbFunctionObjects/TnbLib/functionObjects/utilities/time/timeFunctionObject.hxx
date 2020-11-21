#pragma once
#ifndef _timeFunctionObject_Header
#define _timeFunctionObject_Header

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
	tnbLib::functionObjects::time

Description
	Writes run time, CPU time and clock time
	and optionally the CPU and clock times per time step.

	Example of function object specification:
	\verbatim
	time
	{
		type            time;

		libs            ("libutilityFunctionObjects.so");

		writeControl    timeStep;
		writeInterval   1;

		perTimeStep     no;
	}
	\endverbatim

See also
	tnbLib::functionObject
	tnbLib::regionFunctionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	time.C

\*---------------------------------------------------------------------------*/

#include <regionFunctionObject.hxx>
#include <logFiles.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class time Declaration
		\*---------------------------------------------------------------------------*/

		class time
			:
			public regionFunctionObject,
			public logFiles
		{
			// Private member data

				//- Switch to write CPU and clock times per time-step
			Switch perTimeStep_;

			//- Previous time-step CPU time
			scalar cpuTime0_;

			//- Previous time-step clock time
			scalar clockTime0_;


		protected:

			// Protected Member Functions

				//- Output file header information
			FoamFunctionObjects_EXPORT virtual void writeFileHeader(const label i);


		public:

			//- Runtime type information
			//TypeName("time");
			static const char* typeName_() { return "time"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT time
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT time(const time&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~time();


			// Member Functions

				//- Read the controls
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the time
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const time&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeFunctionObject_Header
