#pragma once
#ifndef _fileMonitor_Header
#define _fileMonitor_Header

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
	tnbLib::fileMonitor

Description
	Checking for changes to files.

Note
	The default is to use stat to get the timestamp.

	Compile with FOAM_USE_INOTIFY to use the inotify
	(Linux specific, since 2.6.13) framework. The problem is that inotify does
	not work on nfs3 mounted directories!!

SourceFiles
	fileMonitor.C

\*---------------------------------------------------------------------------*/

#include <NamedEnum.hxx>
#include <className.hxx>
#include <DynamicList.hxx>

#include <sys/types.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fileMonitor;
	class fileMonitorWatcher;

	/*---------------------------------------------------------------------------*\
							 Class fileMonitor Declaration
	\*---------------------------------------------------------------------------*/

	class fileMonitor
	{

	public:

		// Public data types

			//- Enumeration defining the file state.
		enum fileState
		{
			UNMODIFIED = 0,
			MODIFIED = 1,
			DELETED = 2
		};

		static const NamedEnum<fileState, 3> fileStateNames_;


	private:

		// Private Data

			//- Whether to use inotify (requires -DFOAM_USE_INOTIFY, see above)
		const bool useInotify_;

		//- State for all watchFds based on local files
		mutable DynamicList<fileState> localState_;

		//- State for all watchFds - synchronised
		mutable DynamicList<fileState> state_;

		//- Filename for all watchFds
		DynamicList<fileName> watchFile_;

		//- Free watchFds
		DynamicList<label> freeWatchFds_;

		//- Watch mechanism (stat or inotify)
		mutable autoPtr<fileMonitorWatcher> watcher_;


		// Private Member Functions

			//- Update localState_ from any events.
		FoamBase_EXPORT void checkFiles() const;


	public:

		// Declare name of the class and its debug switch
		//ClassName("fileMonitor");
		static const char* typeName_() { return "fileMonitor"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;

		// Constructors

			//- Construct null
		FoamBase_EXPORT fileMonitor(const bool useInotify);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT fileMonitor(const fileMonitor&) = delete;


		//- Destructor
		FoamBase_EXPORT ~fileMonitor();


		// Member Functions

			//- Add file to watch. Return watch descriptor
		FoamBase_EXPORT label addWatch(const fileName&);

		//- Remove file to watch. Return true if successful
		FoamBase_EXPORT bool removeWatch(const label watchFd);

		//- Get name of file being watched
		FoamBase_EXPORT const fileName& getFile(const label watchFd) const;

		//- Check state using handle
		FoamBase_EXPORT fileState getState(const label watchFd) const;

		//- Check state of all files. Updates state_.
		FoamBase_EXPORT void updateStates
		(
			const bool masterOnly,
			const bool syncPar
		) const;

		//- Reset state (e.g. after having read it) using handle
		FoamBase_EXPORT void setUnmodified(const label watchFd);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const fileMonitor&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fileMonitor_Header
