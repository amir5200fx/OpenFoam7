#pragma once
#ifndef _dsmcFields_Header
#define _dsmcFields_Header

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
	tnbLib::functionObjects::dsmcFields

Description
	Calculate intensive fields:
	- UMean
	- translationalT
	- internalT
	- overallT
	from averaged extensive fields from a DSMC calculation.

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	dsmcFields.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class dsmcFields Declaration
		\*---------------------------------------------------------------------------*/

		class dsmcFields
			:
			public fvMeshFunctionObject
		{
		public:

			//- Runtime type information
			//TypeName("dsmcFields");
			static const char* typeName_() { return "dsmcFields"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT dsmcFields
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT dsmcFields(const dsmcFields&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~dsmcFields();


			// Member Functions

				//- Read the dsmcFields data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Calculate and write the DSMC fields
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const dsmcFields&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dsmcFields_Header
