#pragma once
#ifndef _OSspecific_Header
#define _OSspecific_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

InNamespace
	Foam

Description
	Functions used by OpenFOAM that are specific to POSIX compliant
	operating systems and need to be replaced or emulated on other systems.

SourceFiles
	POSIX.C

\*---------------------------------------------------------------------------*/

#include <fileNameList.hxx>

#include <sys/types.h>
#include <sys/stat.h>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef long PID_T;
	typedef long mode_t;

	//- Return the PID of this process
	//#ifdef mingw
	//	int pid();
	//#else
	//	PID_T pid();
	//#endif

	FoamBase_EXPORT int pid();

	//- Return the parent PID of this process
	FoamBase_EXPORT PID_T ppid();

	//- Return the group PID of this process
	FoamBase_EXPORT PID_T pgid();

	//- Return true if environment variable of given name is defined
	FoamBase_EXPORT bool env(const word&);

	//- Return environment variable of given name
	//  Return string() if the environment is undefined
	FoamBase_EXPORT string getEnv(const word&);

	//- Set an environment variable
	FoamBase_EXPORT bool setEnv(const word& name, const string& value, const bool overwrite);

	//- Return the system's host name
	FoamBase_EXPORT word hostName();

	//- Return the user's login name
	FoamBase_EXPORT word userName();

	//- Is user administrator
	FoamBase_EXPORT bool isAdministrator();

	//- Return home directory path name for the current user
	FoamBase_EXPORT fileName home();

	//- Return home directory path name for a particular user
	FoamBase_EXPORT fileName home(const word& userName);

	//- Return current working directory path name
	FoamBase_EXPORT fileName cwd();

	//- Change the current directory to the one given and return true,
	//  else return false
	FoamBase_EXPORT bool chDir(const fileName& dir);

	//- Search for @em name in the following hierarchy:
	//  -# site-wide settings:
	//    - $WM_PROJECT_INST_DIR/site/\<VERSION\>
	//      <em>for version-specific files</em>
	//    - $WM_PROJECT_INST_DIR/site/
	//      <em>for version-independent files</em>
	//  -# shipped settings:
	//    - $WM_PROJECT_DIR/etc/
	//
	//  @return the full path name or fileName() if the name cannot be found
	//  Optionally abort if the file cannot be found
	//fileName findEtcFile(const fileName&, bool mandatory = false);

	//- Make a directory and return an error if it could not be created
	//  and does not already exist
	FoamBase_EXPORT bool mkDir(const fileName&, mode_t = 0777);

	//- Set the file mode
	FoamBase_EXPORT bool chMod(const fileName&, const mode_t);

	//- Return the file mode
	FoamBase_EXPORT mode_t mode(const fileName& name, const bool checkVariants = true, const bool followLink = true);

	//- Return the file type: DIRECTORY or FILE
	FoamBase_EXPORT fileType type(const fileName&, const bool checkVariants = true, const bool followLink = true);

	//- Does the name exist (as DIRECTORY or FILE) in the file system?
	//  Optionally enable/disable check for gzip file.
	FoamBase_EXPORT bool exists(const fileName&, const bool checkGzip = true, const bool followLink = true);

	//- Does the name exist as a DIRECTORY in the file system?
	FoamBase_EXPORT bool isDir(const fileName&, const bool followLink = true);

	//- Does the name exist as a FILE in the file system?
	//  Optionally enable/disable check for gzip file.
	FoamBase_EXPORT bool isFile(const fileName&, const bool checkGzip = true, const bool followLink = true);

	//- Return size of file
	FoamBase_EXPORT off_t fileSize(const fileName&, const bool checkGzip = true, const bool followLink = true);

	//- Return time of last file modification
	FoamBase_EXPORT time_t lastModified(const fileName&, const bool checkGzip = true, const bool followLink = true);

	//- Return time of last file modification
	FoamBase_EXPORT double highResLastModified
	(
		const fileName&,
		const bool checkVariants = true,
		const bool followLink = true
	);

	//- Read a directory and return the entries as a string list
	FoamBase_EXPORT fileNameList readDir
	(
		const fileName&,
		const fileType = fileType::file,
		const bool filtergz = true,
		const bool followLink = true
	);

	//- Copy, recursively if necessary, the source to the destination
	FoamBase_EXPORT bool cp(const fileName& src, const fileName& dst, const bool followLink = true);

	//- Create a soft link. dst should not exist. Returns true if successful.
	FoamBase_EXPORT bool ln(const fileName& src, const fileName& dst);

	//- Rename src to dst
	FoamBase_EXPORT bool mv(const fileName& src, const fileName& dst, const bool followLink = false);

	//- Rename to a corresponding backup file
	//  If the backup file already exists, attempt with "01" .. "99" suffix
	FoamBase_EXPORT bool mvBak(const fileName&, const std::string& ext = "bak");

	//- Remove a file, returning true if successful otherwise false
	FoamBase_EXPORT bool rm(const fileName&);

	//- Remove a directory and its contents
	FoamBase_EXPORT bool rmDir(const fileName&);

	//- Sleep for the specified number of seconds
	FoamBase_EXPORT unsigned int sleep(const unsigned int);

	//- Close file descriptor
	FoamBase_EXPORT void fdClose(const int);

	//- Check if machine is up by pinging given port
	FoamBase_EXPORT bool ping(const word&, const label port, const label timeOut);

	//- Check if machine is up by pinging port 22 (ssh) and 222 (rsh)
	FoamBase_EXPORT bool ping(const word&, const label timeOut = 10);

	//- Execute the specified command
	FoamBase_EXPORT int system(const std::string& command);

	//- Open a shared library. Return handle to library. Print error message
//  if library cannot be loaded (check = true)
	FoamBase_EXPORT void* dlOpen(const fileName& lib, const bool check = true);

	//- Close a dlopened library using handle. Return true if successful
	FoamBase_EXPORT bool dlClose(void*);

	//- Lookup a symbol in a dlopened library using handle to library
	FoamBase_EXPORT void* dlSym(void* handle, const std::string& symbol);

	//- Report if symbol in a dlopened library could be found
	FoamBase_EXPORT bool dlSymFound(void* handle, const std::string& symbol);

	//- Return all loaded libraries
	FoamBase_EXPORT fileNameList dlLoaded();

	// Low level random numbers. Use Random class instead.

	//- Seed random number generator.
	FoamBase_EXPORT void osRandomSeed(const label seed);

	//- Return random integer (uniform distribution between 0 and 2^31)
	FoamBase_EXPORT label osRandomInteger();

	//- Return random double precision (uniform distribution between 0 and 1)
	FoamBase_EXPORT scalar osRandomDouble();

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_OSspecific_Header
