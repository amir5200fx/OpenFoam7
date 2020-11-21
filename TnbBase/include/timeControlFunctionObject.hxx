#pragma once
#ifndef _timeControlFunctionObject_Header
#define _timeControlFunctionObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::timeControl

Description

Note
	Since the timeIndex is used directly from tnbLib::Time, it is unaffected
	by user-time conversions. For example, tnbLib::engineTime might cause \a
	writeInterval to be degrees crank angle, but the functionObject
	execution \a interval would still be in timestep.

SourceFiles
	timeControlFunctionObject.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <dictionary.hxx>
#include <timeControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						 Class timeControl Declaration
		\*---------------------------------------------------------------------------*/

		class timeControl
			:
			public functionObject
		{
			// Private Data

				//- Reference to the time database
			const Time& time_;

			//- Input dictionary
			dictionary dict_;


			// Optional user inputs

				//- Activation time - defaults to -vGreat
			scalar startTime_;

			//- De-activation time - defaults to vGreat
			scalar endTime_;

			//- Number of steps before the dump-time during which deltaT
			//  may be changed (valid for adjustableRunTime)
			label nStepsToStartTimeChange_;


			//- Execute controls
			tnbLib::timeControl executeControl_;

			//- Write controls
			tnbLib::timeControl writeControl_;

			//- The functionObject to execute
			autoPtr<functionObject> foPtr_;


			// Private Member Functions

				//- Read relevant dictionary entries
			FoamBase_EXPORT void readControls();

			//- Returns true if within time bounds
			FoamBase_EXPORT bool active() const;


		public:

			//- Runtime type information
			//TypeName("timeControl");
			static const char* typeName_() { return "timeControl"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamBase_EXPORT timeControl
			(
				const word& name,
				const Time&,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamBase_EXPORT timeControl(const timeControl&) = delete;


			// Member Functions

				// Access

					//- Return time database
			inline const Time& time() const;

			//- Return the input dictionary
			inline const dictionary& dict() const;

			//- Return the execute control object
			inline const tnbLib::timeControl& executeControl() const;

			//- Return the write control object
			inline const tnbLib::timeControl& writeControl() const;

			//- Return the functionObject filter
			inline const functionObject& filter() const;


			// Function object control

				//- Called at each ++ or += of the time-loop.
				//  postProcess overrides the usual executeControl behaviour and
				//  forces execution (used in post-processing mode)
			FoamBase_EXPORT virtual bool execute();

			//- Called at each ++ or += of the time-loop.
			//  postProcess overrides the usual writeControl behaviour and
			//  forces writing (used in post-processing mode)
			FoamBase_EXPORT virtual bool write();

			//- Called when Time::run() determines that the time-loop exits
			FoamBase_EXPORT virtual bool end();

			//- Return the time to the next write
			FoamBase_EXPORT virtual scalar timeToNextWrite();

			//- Read and set the function object if its data have changed
			FoamBase_EXPORT virtual bool read(const dictionary&);

			//- Update for changes of mesh
			FoamBase_EXPORT virtual void updateMesh(const mapPolyMesh& mpm);

			//- Update for changes of mesh
			FoamBase_EXPORT virtual void movePoints(const polyMesh& mesh);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const timeControl&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <timeControlFunctionObjectI.hxx>

#endif // !_timeControlFunctionObject_Header
