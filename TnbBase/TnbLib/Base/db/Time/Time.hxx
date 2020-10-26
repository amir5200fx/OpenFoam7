#pragma once
#ifndef _Time_Header
#define _Time_Header

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
	tnbLib::Time

Description
	Class to control time during OpenFOAM simulations that is also the
	top-level objectRegistry.

SourceFiles
	Time.C
	TimeIO.C
	findInstance.C

\*---------------------------------------------------------------------------*/

#include <TimePaths.hxx>
#include <objectRegistry.hxx>
#include <unwatchedIOdictionary.hxx>
#include <FIFOStack.hxx>
#include <clock.hxx>
#include <cpuTime.hxx>
#include <TimeState.hxx>
#include <Switch.hxx>
#include <instantList.hxx>
#include <NamedEnum.hxx>
#include <typeInfo.hxx>
#include <dlLibraryTable.hxx>
#include <functionObjectList.hxx>
#include <sigWriteNow.hxx>
#include <sigStopAtWriteNow.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class argList;

	/*---------------------------------------------------------------------------*\
								 Class Time Declaration
	\*---------------------------------------------------------------------------*/

	class Time
		:
		public clock,
		public cpuTime,
		public TimePaths,
		public objectRegistry,
		public TimeState
	{
		// Private Data

			//- Any loaded dynamic libraries. Make sure to construct before
			//  reading controlDict.
		dlLibraryTable libs_;

		//- The controlDict
		unwatchedIOdictionary controlDict_;

	public:

		//- Write control options
		enum class writeControl
		{
			timeStep,
			runTime,
			adjustableRunTime,
			clockTime,
			cpuTime
		};

		//- Stop-run control options
		enum class stopAtControl
		{
			endTime,    //!< stop when Time reaches the prescribed endTime
			noWriteNow, //!< set endTime to stop immediately w/o writing
			writeNow,   //!< set endTime to stop immediately w/ writing
			nextWrite   //!< stop the next time data are written
		};

		//- Supported time directory name formats
		enum class format
		{
			general = 0,
			fixed = ios_base::fixed,
			scientific = ios_base::scientific
		};


	protected:

		// Protected data

		label  startTimeIndex_;
		scalar startTime_;
		mutable scalar endTime_;

		static FoamBase_EXPORT const NamedEnum<stopAtControl, 4> stopAtControlNames_;
		mutable stopAtControl stopAt_;

		static FoamBase_EXPORT const NamedEnum<writeControl, 5> writeControlNames_;
		writeControl writeControl_;

		scalar writeInterval_;

		label  purgeWrite_;
		mutable FIFOStack<word> previousWriteTimes_;

		// One-shot writing
		bool writeOnce_;

		//- Is the time currently being sub-cycled?
		bool subCycling_;

		//- If time is being sub-cycled this is the previous TimeState
		autoPtr<TimeState> prevTimeState_;


		// Signal handlers for writing

			//- Enable one-shot writing upon signal
		sigWriteNow sigWriteNow_;

		//- Enable write and clean exit upon signal
		sigStopAtWriteNow sigStopAtWriteNow_;


		//- Time directory name format
		static FoamBase_EXPORT format format_;

		//- Time directory name precision
		static FoamBase_EXPORT int precision_;

		//- Maximum time directory name precision
		static FoamBase_EXPORT const int maxPrecision_;

		//- Adjust the time step so that writing occurs at the specified time
		FoamBase_EXPORT void adjustDeltaT();

		//- Set the controls from the current controlDict
		FoamBase_EXPORT void setControls();

		//- Read the control dictionary and set the write controls etc.
		FoamBase_EXPORT virtual void readDict();


	private:

		//- Default write option
		IOstream::streamFormat writeFormat_;

		//- Default output file format version number
		IOstream::versionNumber writeVersion_;

		//- Default output compression
		IOstream::compressionType writeCompression_;

		//- Default graph format
		word graphFormat_;

		//- Is runtime modification of dictionaries allowed?
		Switch runTimeModifiable_;

		//- Function objects executed at start and on ++, +=
		mutable functionObjectList functionObjects_;


	public:

		//TypeName("time");
		static const char* typeName_() { return "time"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- The default control dictionary name (normally "controlDict")
		static word controlDictName;


		// Constructors

			//- Construct given name of dictionary to read and argument list
		FoamBase_EXPORT Time
		(
			const word& name,
			const argList& args,
			const word& systemName = "system",
			const word& constantName = "constant"
		);

		//- Construct given name of dictionary to read, rootPath and casePath
		FoamBase_EXPORT Time
		(
			const word& name,
			const fileName& rootPath,
			const fileName& caseName,
			const word& systemName = "system",
			const word& constantName = "constant",
			const bool enableFunctionObjects = true
		);

		//- Construct given dictionary, rootPath and casePath
		FoamBase_EXPORT Time
		(
			const dictionary& dict,
			const fileName& rootPath,
			const fileName& caseName,
			const word& systemName = "system",
			const word& constantName = "constant",
			const bool enableFunctionObjects = true
		);

		//- Construct given endTime, rootPath and casePath
		FoamBase_EXPORT Time
		(
			const fileName& rootPath,
			const fileName& caseName,
			const word& systemName = "system",
			const word& constantName = "constant",
			const bool enableFunctionObjects = true
		);


		//- Destructor
		FoamBase_EXPORT virtual ~Time();


		// Member Functions

			// Database functions

				//- Return root path
		const fileName& rootPath() const
		{
			return TimePaths::rootPath();
		}

		//- Return case name
		const fileName& caseName() const
		{
			return TimePaths::caseName();
		}

		//- Return path
		fileName path() const
		{
			return rootPath() / caseName();
		}

		const dictionary& controlDict() const
		{
			return controlDict_;
		}

		virtual const fileName& dbDir() const
		{
			return fileName::null;
		}

		//- Return current time path
		fileName timePath() const
		{
			return path() / timeName();
		}

		//- Default write format
		IOstream::streamFormat writeFormat() const
		{
			return writeFormat_;
		}

		//- Default write version number
		IOstream::versionNumber writeVersion() const
		{
			return writeVersion_;
		}

		//- Default write compression
		IOstream::compressionType writeCompression() const
		{
			return writeCompression_;
		}

		//- Default graph format
		const word& graphFormat() const
		{
			return graphFormat_;
		}

		//- Supports re-reading
		const Switch& runTimeModifiable() const
		{
			return runTimeModifiable_;
		}

		//- Read control dictionary, update controls and time
		FoamBase_EXPORT virtual bool read();

		//- Read the objects that have been modified
		FoamBase_EXPORT void readModifiedObjects();

		//- Return the location of "dir" containing the file "name".
		//  (eg, used in reading mesh data)
		//  If name is null, search for the directory "dir" only.
		//  Does not search beyond stopInstance (if set) or constant.
		FoamBase_EXPORT word findInstance
		(
			const fileName& dir,
			const word& name = word::null,
			const IOobject::readOption rOpt = IOobject::MUST_READ,
			const word& stopInstance = word::null
		) const;

		//- Search the case for valid time directories
		FoamBase_EXPORT instantList times() const;

		//- Search the case for the time directory path
		//  corresponding to the given instance
		FoamBase_EXPORT word findInstancePath(const fileName& path, const instant&) const;

		//- Search the case for the time directory path
		//  corresponding to the given instance
		FoamBase_EXPORT word findInstancePath(const instant&) const;

		//- Search the case for the time closest to the given time
		FoamBase_EXPORT instant findClosestTime(const scalar) const;

		//- Search instantList for the time index closest to the given time
		static FoamBase_EXPORT label findClosestTimeIndex
		(
			const instantList&,
			const scalar,
			const word& constantName = "constant"
		);

		//- Write time dictionary to the \<time\>/uniform directory
		FoamBase_EXPORT virtual bool writeTimeDict() const;

		//- Write using given format, version and compression
		FoamBase_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat,
			IOstream::versionNumber,
			IOstream::compressionType,
			const bool write
		) const;

		//- Write the objects now (not at end of iteration) and continue
		//  the run
		FoamBase_EXPORT bool writeNow();

		//- Write the objects now (not at end of iteration) and end the run
		FoamBase_EXPORT bool writeAndEnd();

		//- Write the objects once (one shot) and continue the run
		FoamBase_EXPORT void writeOnce();


		// Access

			//- Return time name of given scalar time
			//  formatted with given precision
		static FoamBase_EXPORT word timeName
		(
			const scalar,
			const int precision = precision_
		);

		//- Return current time name
		FoamBase_EXPORT virtual word timeName() const;

		//- Search a given directory for valid time directories
		static FoamBase_EXPORT instantList findTimes
		(
			const fileName&,
			const word& constantName = "constant"
		);

		//- Return start time index
		FoamBase_EXPORT virtual label startTimeIndex() const;

		//- Return start time
		FoamBase_EXPORT virtual dimensionedScalar startTime() const;

		//- Return end time
		FoamBase_EXPORT virtual dimensionedScalar endTime() const;

		//- Return the list of function objects
		const functionObjectList& functionObjects() const
		{
			return functionObjects_;
		}

		//- External access to the loaded libraries
		const dlLibraryTable& libs() const
		{
			return libs_;
		}

		//- External access to the loaded libraries
		dlLibraryTable& libs()
		{
			return libs_;
		}

		//- Return true if time currently being sub-cycled, otherwise false
		bool subCycling() const
		{
			return subCycling_;
		}

		//- Return previous TimeState if time is being sub-cycled
		const TimeState& prevTimeState() const
		{
			return prevTimeState_();
		}


		// Check

			//- Return true if run should continue without any side effects
		FoamBase_EXPORT virtual bool running() const;

		//- Return true if run should continue,
		//  also invokes the functionObjectList::end() method
		//  when the time goes out of range
		//  \note
		//  For correct behaviour, the following style of time-loop
		//  is recommended:
		//  \code
		//      while (runTime.run())
		//      {
		//          runTime++;
		//          solve;
		//          runTime.write();
		//      }
		//  \endcode
		FoamBase_EXPORT virtual bool run() const;

		//- Return true if run should continue and if so increment time
		//  also invokes the functionObjectList::end() method
		//  when the time goes out of range
		//  \note
		//  For correct behaviour, the following style of time-loop
		//  is recommended:
		//  \code
		//      while (runTime.loop())
		//      {
		//          solve;
		//          runTime.write();
		//      }
		//  \endcode
		FoamBase_EXPORT virtual bool loop();

		//- Return true if end of run,
		//  does not invoke any functionObject methods
		//  \note
		//      The rounding heuristics near endTime mean that
		//      \code run() \endcode and \code !end() \endcode may
		//      not yield the same result
		FoamBase_EXPORT virtual bool end() const;


		// Edit

			//- Adjust the current stopAtControl. Note that this value
			//  only persists until the next time the dictionary is read.
			//  Return true if the stopAtControl changed.
		FoamBase_EXPORT virtual bool stopAt(const stopAtControl) const;

		//- Reset the time and time-index to those of the given time
		FoamBase_EXPORT virtual void setTime(const Time&);

		//- Reset the time and time-index
		FoamBase_EXPORT virtual void setTime(const instant&, const label newIndex);

		//- Reset the time and time-index
		FoamBase_EXPORT virtual void setTime
		(
			const dimensionedScalar&,
			const label newIndex
		);

		//- Reset the time and time-index
		FoamBase_EXPORT virtual void setTime(const scalar, const label newIndex);

		//- Reset end time
		FoamBase_EXPORT virtual void setEndTime(const dimensionedScalar&);

		//- Reset end time
		FoamBase_EXPORT virtual void setEndTime(const scalar);

		//- Reset time step
		FoamBase_EXPORT virtual void setDeltaT(const dimensionedScalar&);

		//- Reset time step
		FoamBase_EXPORT virtual void setDeltaT(const scalar);

		//- Reset time step without additional adjustment or modification
		//  by function objects
		FoamBase_EXPORT virtual void setDeltaTNoAdjust(const scalar);

		//- Set time to sub-cycle for the given number of steps
		FoamBase_EXPORT virtual TimeState subCycle(const label nSubCycles);

		//- Reset time after sub-cycling back to previous TimeState
		FoamBase_EXPORT virtual void endSubCycle();

		//- Return non-const access to the list of function objects
		functionObjectList& functionObjects()
		{
			return functionObjects_;
		}


		// Member Operators

			//- Set deltaT to that specified and increment time via operator++()
		FoamBase_EXPORT virtual Time& operator+=(const dimensionedScalar&);

		//- Set deltaT to that specified and increment time via operator++()
		FoamBase_EXPORT virtual Time& operator+=(const scalar);

		//- Prefix increment,
		//  also invokes the functionObjectList::start() or
		//  functionObjectList::execute() method, depending on the time-index
		FoamBase_EXPORT virtual Time& operator++();

		//- Postfix increment, this is identical to the prefix increment
		FoamBase_EXPORT virtual Time& operator++(int);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Time_Header
