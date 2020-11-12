#pragma once
#ifndef _writeObjects_Header
#define _writeObjects_Header

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
	tnbLib::functionObjects::writeObjects

Description
	Allows specification of different writing frequency of objects registered
	to the database.

	It has similar functionality as the main time database through the
	\c writeControl setting:
	  - timeStep
	  - writeTime
	  - adjustableRunTime
	  - runTime
	  - clockTime
	  - cpuTime

	It also has the ability to write the selected objects that were defined
	with the respective write mode for the requested \c writeOption, namely:
	\vartable
		autoWrite | objects set to write at output time
		noWrite   | objects set to not write by default
		anyWrite  | any option of the previous two
	\endvartable

	Example of function object specification:
	\verbatim
	writeObjects1
	{
		type        writeObjects;
		libs        ("libutilityFunctionObjects.so");
		...
		objects     (obj1 obj2);
		writeOption anyWrite;
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required     | Default value
		type         | type name: writeObjects | yes          |
		objects      | objects to write        | yes          |
		writeOption  | only those with this write option | no | anyWrite
	\endtable

	Note: Regular expressions can also be used in \c objects.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::writeObjectsBase
	tnbLib::functionObjects::timeControl

SourceFiles
	writeObjects.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <writeObjectsBase.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						   Class writeObjects Declaration
		\*---------------------------------------------------------------------------*/

		class writeObjects
			:
			public functionObject,
			public writeObjectsBase
		{
		public:

			// Public data types

				//- Re-enumeration defining the write options, based on the original
				//  ones at IOobject::writeOption
			enum class writeOption
			{
				AUTO_WRITE,
				NO_WRITE,
				ANY_WRITE
			};

			static FoamFunctionObjects_EXPORT const NamedEnum<writeOption, 3> writeOptionNames_;

		private:

			// Private Data

				//- To only write objects of defined writeOption
			writeOption writeOption_;


			// Private Member Functions

				//- Write the requested registered IO object
			FoamFunctionObjects_EXPORT virtual void writeObject(const regIOobject& obj);


		public:

			//- Runtime type information
			//TypeName("writeObjects");
			static const char* typeName_() { return "writeObjects"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT writeObjects
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT writeObjects(const writeObjects&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~writeObjects();


			// Member Functions

				//- Read the writeObjects data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the registered objects
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const writeObjects&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writeObjects_Header
