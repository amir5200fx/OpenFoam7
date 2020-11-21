#pragma once
#ifndef _uncollatedFileOperation_Header
#define _uncollatedFileOperation_Header

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
	tnbLib::fileOperations::uncollatedFileOperation

Description
	fileOperation that assumes file operations are local.

\*---------------------------------------------------------------------------*/

#include <fileOperation.hxx>
#include <OSspecific.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileOperations
	{

		/*---------------------------------------------------------------------------*\
							 Class uncollatedFileOperation Declaration
		\*---------------------------------------------------------------------------*/

		class uncollatedFileOperation
			:
			public fileOperation
		{
			// Private Member Functions

				//- Search for an object.
				//    checkGlobal : also check undecomposed case
				//    isFile      : true:check for file  false:check for directory
			FoamBase_EXPORT fileName filePathInfo
			(
				const bool checkGlobal,
				const bool isFile,
				const IOobject&
			) const;


		public:

			//- Runtime type information
			//TypeName("uncollated");
			static const char* typeName_() { return "uncollated"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct null
			FoamBase_EXPORT uncollatedFileOperation(const bool verbose);


			//- Destructor
			FoamBase_EXPORT virtual ~uncollatedFileOperation();


			// Member Functions

				// OSSpecific equivalents

					//- Make directory
			FoamBase_EXPORT virtual bool mkDir(const fileName&, mode_t = 0777) const;

			//- Set the file mode
			FoamBase_EXPORT virtual bool chMod(const fileName&, const mode_t) const;

			//- Return the file mode
			FoamBase_EXPORT virtual mode_t mode
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Return the file type: directory, file or link
			FoamBase_EXPORT virtual fileType type
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Does the name exist (as directory or file) in the file system?
			//  Optionally enable/disable check for gzip file.
			FoamBase_EXPORT virtual bool exists
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Does the name exist as a directory in the file system?
			FoamBase_EXPORT virtual bool isDir
			(
				const fileName&,
				const bool followLink = true
			) const;

			//- Does the name exist as a FILE in the file system?
			//  Optionally enable/disable check for gzip file.
			FoamBase_EXPORT virtual bool isFile
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Return size of file
			FoamBase_EXPORT virtual off_t fileSize
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Return time of last file modification
			FoamBase_EXPORT virtual time_t lastModified
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Return time of last file modification
			FoamBase_EXPORT virtual double highResLastModified
			(
				const fileName&,
				const bool checkVariants = true,
				const bool followLink = true
			) const;

			//- Read a directory and return the entries as a string list
			FoamBase_EXPORT virtual fileNameList readDir
			(
				const fileName&,
				const fileType = fileType::file,
				const bool filtergz = true,
				const bool followLink = true
			) const;

			//- Copy, recursively if necessary, the source to the destination
			FoamBase_EXPORT virtual bool cp
			(
				const fileName& src,
				const fileName& dst,
				const bool followLink = true
			) const;

			//- Create a softlink. dst should not exist. Returns true if
		   //  successful.
			FoamBase_EXPORT virtual bool ln(const fileName& src, const fileName& dst) const;

			//- Rename src to dst
			FoamBase_EXPORT virtual bool mv
			(
				const fileName& src,
				const fileName& dst,
				const bool followLink = false
			) const;

			//- Rename to a corresponding backup file
			//  If the backup file already exists, attempt with
			//  "01" .. "99" suffix
			FoamBase_EXPORT virtual bool mvBak
			(
				const fileName&,
				const std::string& ext = "bak"
			) const;

			//- Remove a file, returning true if successful otherwise false
			FoamBase_EXPORT virtual bool rm(const fileName&) const;

			//- Remove a directory and its contents
			FoamBase_EXPORT virtual bool rmDir(const fileName&) const;

			//            //- Open a shared library. Return handle to library. Print error
			//            //  message if library cannot be loaded (check = true)
			//            virtual void* dlOpen
			//            (
			//                const fileName& lib,
			//                const bool check = true
			//            ) const;


					// (reg)IOobject functinality

						//- Search for an object. checkGlobal : also check undecomposed case
			FoamBase_EXPORT virtual fileName filePath
			(
				const bool checkGlobal,
				const IOobject&,
				const word& typeName
			) const;

			//- Search for a directory. checkGlobal : also check undecomposed
			//  case
			FoamBase_EXPORT virtual fileName dirPath
			(
				const bool checkGlobal,
				const IOobject&
			) const;

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
			) const;

			//- Reads header for regIOobject and returns an ISstream
			//  to read the contents.
			FoamBase_EXPORT virtual autoPtr<ISstream> readStream
			(
				regIOobject&,
				const fileName&,
				const word& typeName,
				const bool read = true
			) const;

			//- Top-level read
			FoamBase_EXPORT virtual bool read
			(
				regIOobject&,
				const bool masterOnly,
				const IOstream::streamFormat format,
				const word& typeName
			) const;

			//- Generate an ISstream that reads a file
			FoamBase_EXPORT virtual autoPtr<ISstream> NewIFstream(const fileName&) const;

			//- Generate an Ostream that writes a file
			FoamBase_EXPORT virtual autoPtr<Ostream> NewOFstream
			(
				const fileName& pathname,
				IOstream::streamFormat format = IOstream::ASCII,
				IOstream::versionNumber version = IOstream::currentVersion,
				IOstream::compressionType compression = IOstream::UNCOMPRESSED,
				const bool write = true
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileOperations
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uncollatedFileOperation_Header
