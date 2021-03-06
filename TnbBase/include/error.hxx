#pragma once
#ifndef _error_Header
#define _error_Header

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
	tnbLib::error

Description
	Class to handle errors and exceptions in a simple, consistent stream-based
	manner.

	The error class is globally instantiated with a title string. Errors,
	messages and other data are piped to the messageStream class in the
	standard manner.  Manipulators are supplied for exit and abort which may
	terminate the program or throw an exception depending on whether the
	exception handling has been switched on (off by default).

Usage
	\code
		error << "message1" << "message2" << FoamDataType << exit(errNo);
		error << "message1" << "message2" << FoamDataType << abort();
	\endcode

SourceFiles
	error.C

\*---------------------------------------------------------------------------*/

#include <messageStream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class error;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const error&);


	/*---------------------------------------------------------------------------*\
								Class error Declaration
	\*---------------------------------------------------------------------------*/

	class error
		:
		public std::exception,
		public messageStream
	{

	protected:

		// Protected data

		string functionName_;
		string sourceFileName_;
		label sourceFileLineNumber_;

		bool abort_;

		bool throwExceptions_;
		OStringStream* messageStreamPtr_;

	public:

		// Constructors

			//- Construct from title string
		FoamBase_EXPORT error(const string& title);

		//- Construct from dictionary
		FoamBase_EXPORT error(const dictionary&);

		//- Copy constructor
		FoamBase_EXPORT error(const error&);


		//- Destructor
		FoamBase_EXPORT virtual ~error() throw();


		// Member Functions

		FoamBase_EXPORT string message() const;

		const string& functionName() const
		{
			return functionName_;
		}

		const string& sourceFileName() const
		{
			return sourceFileName_;
		}

		label sourceFileLineNumber() const
		{
			return sourceFileLineNumber_;
		}

		void throwExceptions()
		{
			throwExceptions_ = true;
		}

		void dontThrowExceptions()
		{
			throwExceptions_ = false;
		}

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT OSstream& operator()
			(
				const string& functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT operator OSstream&();

		//- Explicitly convert to OSstream for << operations
		FoamBase_EXPORT OSstream& operator()()
		{
			return operator OSstream&();
		}

		//- Create and return a dictionary
		FoamBase_EXPORT operator dictionary() const;


		//- Helper function to print a stack (if OpenFOAM IO not yet
		//  initialised)
		static FoamBase_EXPORT void safePrintStack(std::ostream&);

		//- Helper function to print a stack
		static FoamBase_EXPORT void printStack(Ostream&);

		//- Exit : can be called for any error to exit program.
		//  Prints stack before exiting.
		FoamBase_EXPORT void exit(const int errNo = 1);

		//- Abort : used to stop code for fatal errors.
		//  Prints stack before exiting.
		FoamBase_EXPORT void abort();


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const error&);
	};


	// Forward declaration of friend functions and operators
	class IOerror;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const IOerror&);


	/*---------------------------------------------------------------------------*\
							   Class IOerror Declaration
	\*---------------------------------------------------------------------------*/

	//- Report an I/O error
	class IOerror
		:
		public error
	{
		// Private Data

		string ioFileName_;
		label ioStartLineNumber_;
		label ioEndLineNumber_;


	public:

		// Constructors

			//- Construct from title string
		FoamBase_EXPORT IOerror(const string& title);

		//- Construct from dictionary
		FoamBase_EXPORT IOerror(const dictionary&);


		//- Destructor
		FoamBase_EXPORT virtual ~IOerror() throw();


		// Member Functions

		const string& ioFileName() const
		{
			return ioFileName_;
		}

		label ioStartLineNumber() const
		{
			return ioStartLineNumber_;
		}

		label ioEndLineNumber() const
		{
			return ioEndLineNumber_;
		}

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const string& ioFileName,
				const label ioStartLineNumber = -1,
				const label ioEndLineNumber = -1
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const IOstream&
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		FoamBase_EXPORT OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const dictionary&
				);

		//- Print basic message and exit. Uses cerr if streams not constructed
		//  yet (at startup). Use in startup parsing instead of FatalError.
		static FoamBase_EXPORT void SafeFatalIOError
		(
			const char* functionName,
			const char* sourceFileName,
			const int sourceFileLineNumber,
			const IOstream&,
			const string& msg
		);

		//- Create and return a dictionary
		FoamBase_EXPORT operator dictionary() const;


		//- Exit : can be called for any error to exit program
		FoamBase_EXPORT void exit(const int errNo = 1);

		//- Abort : used to stop code for fatal errors
		FoamBase_EXPORT void abort();


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const IOerror&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Global error declarations: defined in error.C

	FoamBase_EXPORT extern error   FatalError;
	FoamBase_EXPORT extern IOerror FatalIOError;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Convenience macros to add the file name and line number to the function name

//- Report an error message using tnbLib::FatalError
//  for functionName in file __FILE__ at line __LINE__
#define FatalErrorIn(functionName)                                             \
    ::tnbLib::FatalError((functionName), __FILE__, __LINE__)

//- Report an error message using tnbLib::FatalError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define FatalErrorInFunction FatalErrorIn(FUNCTION_NAME)


//- Report an error message using tnbLib::FatalIOError
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define FatalIOErrorIn(functionName, ios)                                      \
    ::tnbLib::FatalIOError((functionName), __FILE__, __LINE__, (ios))

//- Report an error message using tnbLib::FatalIOError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define FatalIOErrorInFunction(ios) FatalIOErrorIn(FUNCTION_NAME, ios)


//- Report an error message using tnbLib::FatalIOError
//  (or cerr if FatalIOError not yet constructed)
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SafeFatalIOErrorIn(functionName, ios, msg)                             \
    ::tnbLib::IOerror::SafeFatalIOError                                          \
    ((functionName), __FILE__, __LINE__, (ios), (msg))

//- Report an error message using tnbLib::FatalIOError
//  (or cerr if FatalIOError not yet constructed)
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SafeFatalIOErrorInFunction(ios, msg)                                   \
    SafeFatalIOErrorIn(FUNCTION_NAME, ios, msg)


//- Issue a FatalErrorIn for a function not currently implemented.
//  The functionName is printed and then abort is called.
//
//  This macro can be particularly useful when methods must be defined to
//  complete the interface of a derived class even if they should never be
//  called for this derived class.
#define notImplemented(functionName)                                           \
    FatalErrorIn(functionName)                                                 \
        << "Not implemented" << ::tnbLib::abort(FatalError);

//- Issue a FatalErrorIn for a function not currently implemented.
//  The FUNCTION_NAME is printed and then abort is called.
//
//  This macro can be particularly useful when methods must be defined to
//  complete the interface of a derived class even if they should never be
//  called for this derived class.
#define NotImplemented notImplemented(FUNCTION_NAME)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <errorManip.hxx>

#endif // !_error_Header
