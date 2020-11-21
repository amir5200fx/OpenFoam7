#pragma once
#ifndef _writeCellVolumes_Header
#define _writeCellVolumes_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::writeCellVolumes

Description
	Writes the cell-volumes volScalarField.

	Example of function object specification:
	\verbatim
	writeCellVolumes
	{
		type        writeCellVolumes;
		libs        ("libfieldFunctionObjects.so");
		...
	}
	\endverbatim

Usage
	\table
		Property  | Description                 | Required    | Default value
		type      | type name: writeCellVolumes | yes       |
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	writeCellVolumes.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class writeCellVolumes Declaration
		\*---------------------------------------------------------------------------*/

		class writeCellVolumes
			:
			public fvMeshFunctionObject
		{
		public:

			//- Runtime type information
			//TypeName("writeCellVolumes");
			static const char* typeName_() { return "writeCellVolumes"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT writeCellVolumes
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT writeCellVolumes(const writeCellVolumes&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~writeCellVolumes();


			// Member Functions

				//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the cell-centre fields
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const writeCellVolumes&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writeCellVolumes_Header
