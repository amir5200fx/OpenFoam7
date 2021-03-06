#pragma once
#ifndef _timeControl_Header
#define _timeControl_Header

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
	tnbLib::timeControl

Description
	General time dependent execution controller.
	The default to execute every time-step.

SourceFiles
	timeControl.C

\*---------------------------------------------------------------------------*/

#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class timeControl Declaration
	\*---------------------------------------------------------------------------*/

	class timeControl
	{
	public:

		//- The time control options
		enum class timeControls
		{
			timeStep,           //!< execution is coupled to the time-step
			writeTime,          //!< execution is coupled to the write-time
			outputTime,         //!< execution is coupled to the output-time
			adjustableRunTime,  //!< Adjust time step for execution
			runTime,            //!< run time for execution
			clockTime,          //!< clock time for execution
			cpuTime,            //!< cpu time for execution
			none                //!< no execution
		};


	private:

		// Private Data

			//- Time object
		const Time& time_;

		//- Prefix
		const word prefix_;

		//- String representation of timeControls enums
		static FoamBase_EXPORT const NamedEnum<timeControls, 8> timeControlNames_;

		//- Type of time control
		timeControls timeControl_;

		//- Execution interval steps for timeStep mode
		//  a value <= 1 means execute at every time step
		label intervalSteps_;

		//- Execution interval
		scalar interval_;

		//- Index of previous execution
		label executionIndex_;


	public:

		// Constructors

			//- Construct from Time object and dictionary
		FoamBase_EXPORT timeControl
		(
			const Time&,
			const dictionary&,
			const word& prefix
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT timeControl(const timeControl&) = delete;


		//- Destructor
		FoamBase_EXPORT ~timeControl();


		// Member Functions

			//- Read from dictionary
		FoamBase_EXPORT void read(const dictionary&);

		//- Return Time
		inline const Time& time() const;

		//- Flag to indicate whether to execute
		FoamBase_EXPORT bool execute();

		//- Return control
		inline timeControls control() const;

		//- Return interval
		inline scalar interval() const;

		//- Return the index of the previous execution
		inline label executionIndex() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const timeControl&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <timeControlI.hxx>

#endif // !_timeControl_Header
