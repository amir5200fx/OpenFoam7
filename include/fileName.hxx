#pragma once
#ifndef _fileName_Header
#define _fileName_Header

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
	tnbLib::fileName

Description
	A class for handling file names.

	A fileName is a string of characters without whitespace or quotes.
	A fileName can be
	  - constructed from a char*, a string or a word
	  - concatenated by adding a '/' separator
	  - decomposed into the path, name or component list
	  - interrogated for type and access mode

	The string::expand() method expands environment variables, etc,

SourceFiles
	fileName.C
	fileNameIO.C

\*---------------------------------------------------------------------------*/

#include <word.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class T> class List;
	typedef List<word> wordList;

	// Forward declaration of friend functions and operators

	class fileName;

	FoamBase_EXPORT Istream& operator>>(Istream&, fileName&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const fileName&);


	//- Enumeration of file types
	enum class fileType
	{
		undefined,
		file,
		directory,
		link
	};


	/*---------------------------------------------------------------------------*\
							  Class fileName Declaration
	\*---------------------------------------------------------------------------*/

	class fileName
		:
		public string
	{
		// Private Member Functions

			//- Strip invalid characters
		inline void stripInvalid();


	public:

		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT int debug;

		//- An empty fileName
		static FoamBase_EXPORT const fileName null;


		// Constructors

			//- Construct null
		inline fileName();

		//- Copy constructor
		inline fileName(const fileName&);

		//- Move constructor
		inline fileName(fileName&&);

		//- Copy constructor of word
		inline fileName(const word&);

		//- Copy constructor of string
		inline fileName(const string&);

		//- Copy constructor of std::string
		inline fileName(const std::string&);

		//- Copy constructor of character array
		inline fileName(const char*);

		//- Construct by concatenating elements of wordList separated by '/'
		FoamBase_EXPORT explicit fileName(const wordList&);

		//- Construct from Istream
		FoamBase_EXPORT fileName(Istream&);


		// Member Functions

			//- Is this character valid for a fileName?
		inline static bool valid(char);

		//- Cleanup file name
		//
		// * Removes repeated slashes
		//       /abc////def        -->   /abc/def
		//
		// * Removes '/./'
		//       /abc/def/./ghi/.   -->   /abc/def/./ghi
		//       abc/def/./         -->   abc/def
		//
		// * Removes '/../'
		//       /abc/def/../ghi/jkl/nmo/..   -->   /abc/ghi/jkl
		//       abc/../def/ghi/../jkl        -->   abc/../def/jkl
		//
		// * Removes trailing '/'
		//
		FoamBase_EXPORT bool clean();

		//- Cleanup file name
		//  eg, remove repeated slashes, etc.
		FoamBase_EXPORT fileName clean() const;


		// Interrogation

			//- Return the file type: file, directory, undefined or
			//  link (only if followLink=false)
		FoamBase_EXPORT fileType type
		(
			const bool checkVariants = true,
			const bool followLink = true
		) const;

		//- Return true if file name is absolute
		FoamBase_EXPORT bool isAbsolute() const;

		//- Convert from relative to absolute
		FoamBase_EXPORT fileName& toAbsolute();


		// Decomposition

			//- Return file name (part beyond last /)
			//
			//  Behaviour compared to /usr/bin/basename:
			//    Input           name()          basename
			//    -----           ------          --------
			//    "foo"           "foo"           "foo"
			//    "/foo"          "foo"           "foo"
			//    "foo/bar"       "bar"           "bar"
			//    "/foo/bar"      "bar"           "bar"
			//    "/foo/bar/"     ""              "bar"
			//
		FoamBase_EXPORT word name() const;

		//- Return file name (part beyond last /), substitute for FOAM_CASE
		FoamBase_EXPORT string caseName() const;

		//- Return file name, optionally without extension
		FoamBase_EXPORT word name(const bool noExt) const;

		//- Return directory path name (part before last /)
		//
		//  Behaviour compared to /usr/bin/dirname:
		//    input           path()          dirname
		//    -----           ------          -------
		//    "foo"           "."             "."
		//    "/foo"          "/"             "foo"
		//    "foo/bar"       "foo"           "foo"
		//    "/foo/bar"      "/foo"          "/foo"
		//    "/foo/bar/"     "/foo/bar/"     "/foo"
		//
		FoamBase_EXPORT fileName path() const;

		//- Return file name without extension (part before last .)
		FoamBase_EXPORT fileName lessExt() const;

		//- Return file name extension (part after last .)
		FoamBase_EXPORT word ext() const;

		//- Return path components as wordList
		//
		//  Behaviour:
		//    Input           components()
		//    -----           ------
		//    "foo"           1("foo")
		//    "/foo"          1("foo")
		//    "foo/bar"       2("foo", "bar")
		//    "/foo/bar"      2("foo", "bar")
		//    "/foo/bar/"     2("foo", "bar")
		FoamBase_EXPORT wordList components(const char delimiter = '/') const;

		//- Return a single component of the path
		FoamBase_EXPORT word component(const size_type, const char delimiter = '/') const;


		// Member Operators

			// Assignment

		FoamBase_EXPORT void operator=(const fileName&);
		FoamBase_EXPORT void operator=(fileName&&);
		FoamBase_EXPORT void operator=(const word&);
		FoamBase_EXPORT void operator=(const string&);
		FoamBase_EXPORT void operator=(const std::string&);
		FoamBase_EXPORT void operator=(const char*);


		// IOstream Operators

		friend FoamBase_EXPORT Istream& operator>>(Istream&, fileName&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const fileName&);
	};


	//- Assemble words and fileNames as pathnames by adding a '/' separator
	FoamBase_EXPORT fileName operator/(const string&, const string&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fileNameI.hxx>

#endif // !_fileName_Header
