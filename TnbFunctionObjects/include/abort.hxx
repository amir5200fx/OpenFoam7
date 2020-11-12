#pragma once
#ifndef _abort_Header
#define _abort_Header

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
	tnbLib::functionObjects::abort

Description
	Watches for presence of the named file in the $FOAM_CASE directory
	and aborts the calculation if it is present.

	Currently the following action types are supported:
	- noWriteNow
	- writeNow
	- nextWrite

SourceFiles
	abort.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							  Class abort Declaration
		\*---------------------------------------------------------------------------*/

		class abort
			:
			public functionObject
		{
		public:

			// Public data

				//- Enumeration defining the type of action
			enum class actionType
			{
				noWriteNow,    //!< stop immediately without writing data
				writeNow,      //!< write data and stop immediately
				nextWrite      //!< stop the next time data are written
			};

		private:

			// Private Data

				//- Reference to the Time
			const Time& time_;

			//- The fully-qualified name of the abort file
			fileName abortFile_;

			//- Action type names
			static FoamFunctionObjects_EXPORT const NamedEnum<actionType, 3> actionTypeNames_;

			//- The type of action
			actionType action_;


			// Private Member Functions

				//- Remove abort file.
			FoamFunctionObjects_EXPORT void removeFile() const;


		public:

			//- Runtime type information
			//TypeName("abort");
			static const char* typeName_() { return "abort"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT abort
			(
				const word& name,
				const Time& runTime,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT abort(const abort&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~abort();


			// Member Functions

				//- Read the dictionary settings
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute, check existence of abort file and take action
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Execute, check existence of abort file and take action
			FoamFunctionObjects_EXPORT virtual bool write();

			//- Execute at the final time-loop, used for cleanup
			FoamFunctionObjects_EXPORT virtual bool end();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const abort&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_abort_Header
