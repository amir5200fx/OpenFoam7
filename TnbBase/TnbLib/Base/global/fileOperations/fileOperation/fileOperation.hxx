#pragma once
#ifndef _fileOperation_Header
#define _fileOperation_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::fileOperation

\*---------------------------------------------------------------------------*/

#include <ISstream.hxx>
#include <Ostream.hxx>
#include <autoPtr.hxx>
#include <fileNameList.hxx>
#include <instantList.hxx>
#include <fileMonitor.hxx>
#include <labelList.hxx>
#include <Switch.hxx>
#include <tmpNrc.hxx>
#include <NamedEnum.hxx>

#include <typeInfo.hxx>  // added by amir
#include <runTimeSelectionTables.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class IOobject;
	class regIOobject;
	class objectRegistry;
	class Time;

	typedef long mode_t; // added by amir

	/*---------------------------------------------------------------------------*\
							 Class fileOperation Declaration
	\*---------------------------------------------------------------------------*/

	class fileOperation
	{
	public:

		//- Enumeration for the location of an IOobject
		enum pathType
		{
			NOTFOUND,               // not found
			ABSOLUTE,               // instance is absolute directory
			OBJECT,                 // io.objectPath() exists
			WRITEOBJECT,            // write path exists
			PROCUNCOLLATED,         // objectPath exists in processor0
			PROCBASEOBJECT,         // objectPath exists in specified, constant
									// processorsDir (usually 'processorsDDD')
									PROCOBJECT,             // objectPath exists in locally differing
															// processorsDir (e.g. 'processorsDDD_0-1')
															PARENTOBJECT,           // parent of object path
															FINDINSTANCE,           // file found in time directory
															PROCUNCOLLATEDINSTANCE, // as PROCUNCOLLATED but with instance
															PROCBASEINSTANCE,       // as PROCBASEOBJECT but with instance
															PROCINSTANCE            // as PROCOBJECT but with instance
		};

		static FoamBase_EXPORT const NamedEnum<pathType, 12> pathTypeNames_;

		//- Description of processor directory naming:
		//  - processor directory naming
		//  - whether directory contains a range
		//    (so differs on different processors)
		//  - index in range
		typedef Tuple2<fileName, Tuple2<pathType, label>> dirIndex;

		typedef List<dirIndex> dirIndexList;


	protected:

		// Protected data

			//- Communicator to use
		const label comm_;

		//- Detected processors directories
		mutable HashTable<dirIndexList> procsDirs_;

		//- file-change monitor for all registered files
		mutable autoPtr<fileMonitor> monitorPtr_;


		// Protected Member Functions

		FoamBase_EXPORT fileMonitor& monitor() const;

		//- Sort directory entries according to time value
		static FoamBase_EXPORT instantList sortTimes(const fileNameList&, const word&);

		//- Merge two times
		static FoamBase_EXPORT void mergeTimes
		(
			const instantList& extraTimes,
			const word& constantName,
			instantList& times
		);

		//- Helper: check for file (isFile) or directory (!isFile)
		static FoamBase_EXPORT bool isFileOrDir(const bool isFile, const fileName&);

		//- Detect presence of processorsDDD
		FoamBase_EXPORT void cacheProcessorsPath(const fileName& fName) const;

		//- Lookup name of processorsDDD using cache. Return empty fileName
		//  if not found
		FoamBase_EXPORT tmpNrc<dirIndexList> lookupProcessorsPath(const fileName&) const;

		//- Does ioobject exist. Is either a directory (empty name()) or
		//  a file
		FoamBase_EXPORT bool exists(IOobject& io) const;


	public:

		// Static data

			//- Return the processors directory name (usually "processors")
		static FoamBase_EXPORT word processorsBaseDir;

		//- Default fileHandler
		static FoamBase_EXPORT word defaultFileHandler;


		// Public data types

			//- Runtime type information
		//TypeName("fileOperation");
		static const char* typeName_() { return "fileOperation"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Static fileOperation
		static FoamBase_EXPORT autoPtr<fileOperation> fileHandlerPtr_;


		// Constructors

			//- Construct null
		FoamBase_EXPORT fileOperation(const label comm);


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			fileOperation,
			word,
			(
				const bool verbose
				),
				(verbose)
		);*/

		typedef autoPtr<fileOperation> (*wordConstructorPtr)(const bool verbose);
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamBase_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamBase_EXPORT void constructwordConstructorTables();
		static FoamBase_EXPORT void destroywordConstructorTables();

		template <class fileOperationType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<fileOperation> New(const bool verbose)
			{
				return autoPtr<fileOperation>(new fileOperationType(verbose));
			}

			addwordConstructorToTable(const word& lookup = fileOperationType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "fileOperation" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class fileOperationType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<fileOperation> New(const bool verbose)
			{
				return autoPtr<fileOperation>(new fileOperationType(verbose));
			}

			addRemovablewordConstructorToTable(const word& lookup = fileOperationType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable() { if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); } }
		};;


		// Selectors

			//- Select type
		static FoamBase_EXPORT autoPtr<fileOperation> New(const word& type, const bool verbose);


		//- Destructor
		FoamBase_EXPORT virtual ~fileOperation();


		// Member Functions

			// OSSpecific equivalents

				//- Make directory
		FoamBase_EXPORT virtual bool mkDir(const fileName&, mode_t = 0777) const = 0;

		//- Set the file mode
		FoamBase_EXPORT virtual bool chMod(const fileName&, const mode_t) const = 0;

		//- Return the file mode
		FoamBase_EXPORT virtual mode_t mode
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Return the file type: directory, file or link
		FoamBase_EXPORT virtual fileType type
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Does the name exist (as directory or file) in the file system?
		//  Optionally enable/disable check for gzip file.
		FoamBase_EXPORT virtual bool exists
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Does the name exist as a directory in the file system?
		FoamBase_EXPORT virtual bool isDir
		(
			const fileName&,
			const bool followLink = true
		) const = 0;

		//- Does the name exist as a file in the file system?
		//  Optionally enable/disable check for gzip file.
		FoamBase_EXPORT virtual bool isFile
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Return size of file
		FoamBase_EXPORT virtual off_t fileSize
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Return time of last file modification
		FoamBase_EXPORT virtual time_t lastModified
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Return time of last file modification
		FoamBase_EXPORT virtual double highResLastModified
		(
			const fileName&,
			const bool checkVariants = true,
			const bool followLink = true
		) const = 0;

		//- Read a directory and return the entries as a string list
		FoamBase_EXPORT virtual fileNameList readDir
		(
			const fileName&,
			const fileType = fileType::file,
			const bool filterVariants = true,
			const bool followLink = true
		) const = 0;

		//- Copy, recursively if necessary, the source to the destination
		FoamBase_EXPORT virtual bool cp
		(
			const fileName& src,
			const fileName& dst,
			const bool followLink = true
		) const = 0;

		//- Create a softlink. dst should not exist. Returns true if
		//  successful.
		FoamBase_EXPORT virtual bool ln(const fileName& src, const fileName& dst) const = 0;

		//- Rename src to dst
		FoamBase_EXPORT virtual bool mv
		(
			const fileName& src,
			const fileName& dst,
			const bool followLink = false
		) const = 0;

		//- Rename to a corresponding backup file
		//  If the backup file already exists, attempt with
		//  "01" .. "99" suffix
		FoamBase_EXPORT virtual bool mvBak
		(
			const fileName&,
			const std::string& ext = "bak"
		) const = 0;

		//- Remove a file, returning true if successful otherwise false
		FoamBase_EXPORT virtual bool rm(const fileName&) const = 0;

		//- Remove a directory and its contents
		FoamBase_EXPORT virtual bool rmDir(const fileName&) const = 0;

		// //- Open a shared library. Return handle to library. Print error
		// //  message if library cannot be loaded (check = true)
		// virtual void* dlOpen
		// (
		//     const fileName& lib,
		//     const bool check = true
		// ) const = 0;


	// (reg)IOobject functinality

		//- Generate disk file name for object. Opposite of filePath.
		//  Optional wanted typeName.
		FoamBase_EXPORT virtual fileName objectPath
		(
			const IOobject& io,
			const word& typeName
		) const;

		//- Search for an object. checkGlobal : also check undecomposed case
		//  Optional wanted typeName.
		FoamBase_EXPORT virtual fileName filePath
		(
			const bool checkGlobal,
			const IOobject&,
			const word& typeName
		) const = 0;

		//- Search for a directory. checkGlobal : also check undecomposed
		//  case
		FoamBase_EXPORT virtual fileName dirPath
		(
			const bool checkGlobal,
			const IOobject&
		) const = 0;

		//- Search directory for objects. Used in IOobjectList.
		FoamBase_EXPORT virtual fileNameList readObjects
		(
			const objectRegistry& db,
			const fileName& instance,
			const fileName& local,
			word& newInstance
		) const;

		//- Read object header from supplied file
		FoamBase_EXPORT virtual bool readHeader
		(
			IOobject&,
			const fileName&,
			const word& typeName
		) const = 0;

		//- Reads header for regIOobject and returns an ISstream
		//  to read the contents.
		FoamBase_EXPORT virtual autoPtr<ISstream> readStream
		(
			regIOobject&,
			const fileName&,
			const word& typeName,
			const bool read = true
		) const = 0;

		//- Top-level read
		FoamBase_EXPORT virtual bool read
		(
			regIOobject&,
			const bool masterOnly,
			const IOstream::streamFormat format,
			const word& typeName
		) const = 0;

		//- Writes a regIOobject (so header, contents and divider).
		//  Returns success state. Default action is to write to
		//  the objectPath using writeData. If !write the
		//  file does not need to be written (this is used e.g. to
		//  suppress empty local lagrangian data)
		FoamBase_EXPORT virtual bool writeObject
		(
			const regIOobject&,
			IOstream::streamFormat format = IOstream::ASCII,
			IOstream::versionNumber version = IOstream::currentVersion,
			IOstream::compressionType compression = IOstream::UNCOMPRESSED,
			const bool write = true
		) const;


		// Filename (not IOobject) operations

			//- Search for a file or directory. Use IOobject version in
			//  preference
		FoamBase_EXPORT virtual fileName filePath(const fileName&) const;

		//- Generate an ISstream that reads a file
		FoamBase_EXPORT virtual autoPtr<ISstream> NewIFstream(const fileName&) const = 0;

		//- Generate an Ostream that writes a file
		FoamBase_EXPORT virtual autoPtr<Ostream> NewOFstream
		(
			const fileName& pathname,
			IOstream::streamFormat format = IOstream::ASCII,
			IOstream::versionNumber version = IOstream::currentVersion,
			IOstream::compressionType compression = IOstream::UNCOMPRESSED,
			const bool write = true
		) const = 0;


		// File modification checking

			//- Add watching of a file. Returns handle
		FoamBase_EXPORT virtual label addWatch(const fileName&) const;

		//- Remove watch on a file (using handle)
		FoamBase_EXPORT virtual bool removeWatch(const label) const;

		//- Find index (or -1) of file in list of handles
		FoamBase_EXPORT virtual label findWatch
		(
			const labelList& watchIndices,
			const fileName&
		) const;

		//- Helper: add watches for list of regIOobjects
		FoamBase_EXPORT virtual void addWatches(regIOobject&, const fileNameList&) const;

		//- Get name of file being watched (using handle)
		FoamBase_EXPORT virtual fileName getFile(const label) const;

		//- Update state of all files
		FoamBase_EXPORT virtual void updateStates
		(
			const bool masterOnly,
			const bool syncPar
		) const;

		//- Get current state of file (using handle)
		FoamBase_EXPORT virtual fileMonitor::fileState getState(const label) const;

		//- Set current state of file (using handle) to unmodified
		FoamBase_EXPORT virtual void setUnmodified(const label) const;


		// Other

			//- Actual name of processors dir (for use in mode PROCOBJECT,
			//  PROCINSTANCE)
		FoamBase_EXPORT virtual word processorsDir(const IOobject& io) const
		{
			return processorsBaseDir;
		}

		//- Actual name of processors dir (for use in mode PROCOBJECT,
		//  PROCINSTANCE)
		FoamBase_EXPORT virtual word processorsDir(const fileName&) const
		{
			return processorsBaseDir;
		}

		//- Set number of processor directories/results. Only used in
		//  decomposePar
		FoamBase_EXPORT virtual void setNProcs(const label nProcs);

		//- Get number of processor directories/results. Used for e.g.
		//  reconstructPar, argList checking
		FoamBase_EXPORT virtual label nProcs
		(
			const fileName& dir,
			const fileName& local = ""
		) const;

		//- Get sorted list of times
		FoamBase_EXPORT virtual instantList findTimes(const fileName&, const word&) const;

		//- Find instance where IOobject is. Fails if cannot be found
		//  and readOpt() is MUST_READ/MUST_READ_IF_MODIFIED. Otherwise
		//  returns stopInstance.
		FoamBase_EXPORT virtual IOobject findInstance
		(
			const IOobject& io,
			const scalar startValue,
			const word& stopInstance
		) const;

		//- Callback for time change
		virtual void setTime(const Time&) const
		{}

		//- Forcibly wait until all output done. Flush any cached data
		FoamBase_EXPORT virtual void flush() const;

		//- Generate path (like io.path) from root+casename with any
		//  'processorXXX' replaced by procDir (usually 'processsors')
		FoamBase_EXPORT fileName processorsCasePath
		(
			const IOobject&,
			const word& procDir
		) const;

		//- Generate path (like io.path) with provided instance and any
		//  'processorXXX' replaced by procDir (usually 'processsors')
		FoamBase_EXPORT fileName processorsPath
		(
			const IOobject&,
			const word& instance,
			const word& procDir
		) const;

		//- Operating on fileName: replace processorXXX with procDir
		FoamBase_EXPORT fileName processorsPath(const fileName&, const word& procDir) const;

		//- Split fileName into part before 'processor' and part after.
		//  Returns -1 or processor number and optionally number
		//  of processors. Use with care.
		//  - path/"processor"+tnbLib::name(proci)/local reconstructs input
		//  - path/"processors"+tnbLib::name(nProcs)/local reconstructs
		//    collated processors equivalence
		static FoamBase_EXPORT label splitProcessorPath
		(
			const fileName&,
			fileName& path,
			fileName& procDir,
			fileName& local,
			label& groupStart,
			label& groupSize,
			label& nProcs
		);

		//- Detect processor number from '/aa/bb/processorDDD/cc'
		static FoamBase_EXPORT label detectProcessorPath(const fileName&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Global declarations: defined in fileOperation.C

	//- Get current file handler
	FoamBase_EXPORT const fileOperation& fileHandler();

	//- Reset file handler
	FoamBase_EXPORT void fileHandler(autoPtr<fileOperation>&);

	//- Recursively search the given directory for the file
	//  returning the path relative to the directory or
	//  fileName::null if not found
	FoamBase_EXPORT fileName search(const word& file, const fileName& directory);

	//- Copy all the files from the source to the target directory
	FoamBase_EXPORT void cpFiles(const fileName& srcDir, const fileName& targetDir);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fileOperation_Header
