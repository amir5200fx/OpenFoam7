#pragma once
#ifndef _timeActivatedFileUpdate_Header
#define _timeActivatedFileUpdate_Header

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
	tnbLib::functionObjects::timeActivatedFileUpdate

Description
	Performs a file copy/replacement once a specified time has been reached.

	Example usage to update the fvSolution dictionary at various times
	throughout the calculation:

	\verbatim
	fileUpdate1
	{
		type              timeActivatedFileUpdate;
		libs              ("libutilityFunctionObjects.so");
		writeControl      timeStep;
		writeInterval     1;
		fileToUpdate      "$FOAM_CASE/system/fvSolution";
		timeVsFile
		(
			(-1 "$FOAM_CASE/system/fvSolution.0")
			(0.10 "$FOAM_CASE/system/fvSolution.10")
			(0.20 "$FOAM_CASE/system/fvSolution.20")
			(0.35 "$FOAM_CASE/system/fvSolution.35")
		);
	}
	\endverbatim

SourceFiles
	timeActivatedFileUpdate.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <Tuple2.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Time;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						  Class timeActivatedFileUpdate Declaration
		\*---------------------------------------------------------------------------*/

		class timeActivatedFileUpdate
			:
			public functionObject
		{
			// Private Data

				//- Reference to Time
			const Time& time_;

			//- Name of file to update
			fileName fileToUpdate_;

			//- List of times vs filenames
			List<Tuple2<scalar, fileName>> timeVsFile_;

			//- Index of last file copied
			label lastIndex_;


			// Private Member Functions

				//- Update file
			FoamFunctionObjects_EXPORT void updateFile();

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT timeActivatedFileUpdate(const timeActivatedFileUpdate&) = delete;

			//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const timeActivatedFileUpdate&) = delete;


		public:

			//- Runtime type information
			//TypeName("timeActivatedFileUpdate");
			static const char* typeName_() { return "timeActivatedFileUpdate"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT timeActivatedFileUpdate
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~timeActivatedFileUpdate();


			// Member Functions

				//- Read the timeActivatedFileUpdate data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute file updates
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool write();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeActivatedFileUpdate_Header
