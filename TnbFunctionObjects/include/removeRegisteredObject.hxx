#pragma once
#ifndef _removeRegisteredObject_Header
#define _removeRegisteredObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::removeRegisteredObject

Description
	Removes registered objects if present in the database.

	Example of function object specification:
	\verbatim
	removeRegisteredObject1
	{
		type        removeRegisteredObject;
		libs        ("libutilityFunctionObjects.so");
		...
		objects     (obj1 obj2);
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required    | Default value
		type         | type name: removeRegisteredObject | yes |
		objects      | objects to remove       | yes         |
	\endtable

See also
	tnbLib::functionObject

SourceFiles
	removeRegisteredObject.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <wordList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class objectRegistry;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						   Class removeRegisteredObject Declaration
		\*---------------------------------------------------------------------------*/

		class removeRegisteredObject
			:
			public functionObject
		{
			// Private Data

				//- Reference to the objectRegistry
			const objectRegistry& obr_;

			//- Names of objects to control
			wordList objectNames_;


		public:

			//- Runtime type information
			//TypeName("removeRegisteredObject");
			static const char* typeName_() { return "removeRegisteredObject"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT removeRegisteredObject
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT removeRegisteredObject(const removeRegisteredObject&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~removeRegisteredObject();


			// Member Functions

				//- Read the removeRegisteredObject data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Remove the registered objects
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const removeRegisteredObject&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_removeRegisteredObject_Header
