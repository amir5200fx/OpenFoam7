#pragma once
#ifndef _XiReactionRate_Header
#define _XiReactionRate_Header

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
	tnbLib::functionObjects::XiReactionRate

Description
	Writes the turbulent flame-speed and reaction-rate volScalarFields for the
	Xi-based combustion models.

	Example of function object specification:
	\verbatim
	XiReactionRate
	{
		type        XiReactionRate;
		libs        ("libfieldFunctionObjects.so");
		...
	}
	\endverbatim

Usage
	\table
		Property  | Description                 | Required  | Default value
		type      | type name: XiReactionRate   | yes       |
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	XiReactionRate.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class XiReactionRate Declaration
		\*---------------------------------------------------------------------------*/

		class XiReactionRate
			:
			public fvMeshFunctionObject
		{
		public:

			//- Runtime type information
			//TypeName("XiReactionRate");
			static const char* typeName_() { return "XiReactionRate"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT XiReactionRate
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT XiReactionRate(const XiReactionRate&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~XiReactionRate();


			// Member Functions

				//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the cell-centre fields
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const XiReactionRate&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_XiReactionRate_Header
