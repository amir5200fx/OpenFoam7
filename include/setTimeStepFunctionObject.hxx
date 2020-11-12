#pragma once
#ifndef _setTimeStepFunctionObject_Header
#define _setTimeStepFunctionObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::setTimeStepFunctionObject

Description
	Overrides the timeStep. Can only be used with
	solvers with adjustTimeStep control (e.g. pimpleFoam). Makes no attempt
	to cooperate with other timeStep 'controllers' (maxCo, other
	functionObjects). Supports 'enabled' flag but none of the other ones
	'startTime', 'endTime', 'writeControl' etc.

SourceFiles
	setTimeStepFunctionObject.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							Class setTimeStepFunctionObject Declaration
		\*---------------------------------------------------------------------------*/

		class setTimeStepFunctionObject
			:
			public functionObject
		{
			// Private Data

				//- Reference to the time database
			const Time& time_;

			//- Time step function/table
			autoPtr<Function1<scalar>> timeStepPtr_;


		public:

			//- Runtime type information
			//TypeName("setTimeStep");
			static const char* typeName_() { return "setTimeStep"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFunctionObjects_EXPORT setTimeStepFunctionObject
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT setTimeStepFunctionObject(const setTimeStepFunctionObject&) = delete;


			// Destructor
			FoamFunctionObjects_EXPORT virtual ~setTimeStepFunctionObject();


			// Member Functions

				//- Return time database
			FoamFunctionObjects_EXPORT const Time& time() const;

			//- Override the time-step value
			FoamFunctionObjects_EXPORT virtual bool setTimeStep();

			//- Read and set the function object if its data have changed
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Called at each ++ or += of the time-loop.
			//  postProcess overrides the usual executeControl behaviour and
			//  forces execution (used in post-processing mode)
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Called at each ++ or += of the time-loop.
			//  postProcess overrides the usual writeControl behaviour and
			//  forces writing always (used in post-processing mode)
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const setTimeStepFunctionObject&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_setTimeStepFunctionObject_Header
