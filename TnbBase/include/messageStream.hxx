#pragma once
#ifndef _messageStream_Header
#define _messageStream_Header

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
	tnbLib::messageStream

Description
	Class to handle messaging in a simple, consistent stream-based
	manner.

	The messageStream class is globaly instantiated with a title string a
	given severity, which controls the program termination, and a number of
	errors before termination.  Errors, messages and other data are piped to
	the messageStream class in the standard manner.

Usage
	\code
		messageStream
			<< "message1" << "message2" << FoamDataType << endl;
	\endcode

SourceFiles
	messageStream.C

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <tnbString.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class IOstream;
	class Ostream;
	class OSstream;
	class OStringStream;
	class dictionary;

	/*---------------------------------------------------------------------------*\
							   Class messageStream Declaration
	\*---------------------------------------------------------------------------*/

	class messageStream
	{

	public:

		//- Severity flags
		enum errorSeverity
		{
			INFO,       // Debugging information in event of error
			WARNING,    // Warning of possible problem
			SERIOUS,    // A serious problem (data corruption?)
			FATAL       // Oh bugger!
		};


	protected:

		// Private Data

		string title_;
		errorSeverity severity_;
		int maxErrors_;
		int errorCount_;


	public:

		// Debug switches

		static int level;


		// Constructors

			//- Construct from components
		messageStream
		(
			const string& title,
			errorSeverity,
			const int maxErrors = 0
		);


		//- Construct from dictionary
		messageStream(const dictionary&);


		// Member Functions

			//- Return the title of this error type
		const string& title() const
		{
			return title_;
		}

		//- Return the maximum number of errors before program termination
		int maxErrors() const
		{
			return maxErrors_;
		}

		//- Return non-const access to the maximum number of errors before
		//  program termination to enable user to reset it
		int& maxErrors()
		{
			return maxErrors_;
		}

		//- Convert to OSstream
		//  Prints to Pout for the master stream
		OSstream& masterStream(const label communicator);


		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		OSstream& operator()
			(
				const string& functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		OSstream& operator()
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
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const IOstream&
				);

		//- Convert to OSstream
		//  Prints basic message and returns OSstream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const dictionary&
				);

		//- Convert to OSstream for << operations
		operator OSstream&();

		//- Explicitly convert to OSstream for << operations
		OSstream& operator()()
		{
			return operator OSstream&();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Global error declarations: defined in messageStream.C

	extern messageStream SeriousError;
	extern messageStream Warning;
	extern messageStream Info;
	extern bool writeInfoHeader;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Convenience macros to add the file name and line number to the function name

// Compiler provided function name string:
//     for gcc-compatible compilers use __PRETTY_FUNCTION__
//     otherwise use the standard __func__
#ifdef __GNUC__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define FUNCTION_NAME __func__
#endif


//- Report an error message using tnbLib::SeriousError
//  for functionName in file __FILE__ at line __LINE__
#define SeriousErrorIn(functionName)                                           \
    ::tnbLib::SeriousError((functionName), __FILE__, __LINE__)

//- Report an error message using tnbLib::SeriousError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define SeriousErrorInFunction SeriousErrorIn(FUNCTION_NAME)


//- Report an IO error message using tnbLib::SeriousError
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SeriousIOErrorIn(functionName, ios)                                    \
    ::tnbLib::SeriousError((functionName), __FILE__, __LINE__, ios)

//- Report an IO error message using tnbLib::SeriousError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SeriousIOErrorInFunction(ios) SeriousIOErrorIn(FUNCTION_NAME, ios)


//- Report a warning using tnbLib::Warning
//  for functionName in file __FILE__ at line __LINE__
#define WarningIn(functionName)                                                \
    ::tnbLib::Warning((functionName), __FILE__, __LINE__)

//- Report a warning using tnbLib::Warning
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define WarningInFunction WarningIn(FUNCTION_NAME)


//- Report an IO warning using tnbLib::Warning
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOWarningIn(functionName, ios)                                         \
    ::tnbLib::Warning((functionName), __FILE__, __LINE__, (ios))

//- Report an IO warning using tnbLib::Warning
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOWarningInFunction(ios) IOWarningIn(FUNCTION_NAME, ios)


//- Report an information message using tnbLib::Info
//  for functionName in file __FILE__ at line __LINE__
#define TnbInfoIn(functionName)                                                   \
    ::tnbLib::Info((functionName), __FILE__, __LINE__)

//- Report an information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define InfoInFunction TnbInfoIn(FUNCTION_NAME)

//- Report write to tnbLib::Info if the local log switch is true
#define InfoHeader                                                             \
    if (::tnbLib::writeInfoHeader) Info

//- Report write to tnbLib::Info if the local log switch is true
#define TnbLog                                                                    \
    if (log) Info


//- Report an IO information message using tnbLib::Info
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOInfoIn(functionName, ios)                                            \
    ::tnbLib::Info((functionName), __FILE__, __LINE__, (ios))

//- Report an IO information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOInfoInFunction(ios) IOInfoIn(FUNCTION_NAME, ios)


//- Report an information message using tnbLib::Info
//  if the local debug switch is true
#define DebugInfo                                                              \
    if (debug) Info

//- Report an information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  if the local debug switch is true
#define DebugInFunction                                                        \
    if (debug) InfoInFunction

//- Report a variable name and value
//  using tnbLib::Pout in file __FILE__ at line __LINE__
#define DebugVar(var)                                                          \
{                                                                              \
    ::tnbLib::string oldPrefix(::tnbLib::Pout.prefix());                           \
    ::tnbLib::Pout<< "["<< __FILE__ << ":" << __LINE__ << "] ";                  \
    ::tnbLib::Pout.prefix() = oldPrefix + #var " ";                              \
    ::tnbLib::Pout<< var << ::tnbLib::endl;                                        \
    ::tnbLib::Pout.prefix() = oldPrefix;                                         \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_messageStream_Header
