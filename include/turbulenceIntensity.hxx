#pragma once
#ifndef _turbulenceIntensity_Header
#define _turbulenceIntensity_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::turbulenceIntensity

Description
	Evaluates and writes the turbulence intensity field 'I'.

	The turbulence intensity field 'I' is the root-mean-square of the turbulent
	velocity fluctuations normalised by the local velocity magnitude:
	\f[
		I \equiv \frac{\sqrt{\frac{2}{3}\, k}}{U}
	\f]
	To avoid spurious extrema and division by 0 I is limited to 1 where the
	velocity magnitude is less than the turbulent velocity fluctuations.

	Example of function object specification:
	\verbatim
	functions
	{
		.
		.
		.
		turbulenceIntensity
		{
			type        turbulenceIntensity;
			libs        ("libfieldFunctionObjects.so");
		}
		.
		.
		.
	}
	\endverbatim

	or using the standard configuration file:
	\verbatim
	functions
	{
		.
		.
		.
		#includeFunc turbulenceIntensity
		.
		.
		.
	}
	\endverbatim

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::writeLocalObjects
	tnbLib::functionObjects::timeControl

SourceFiles
	turbulenceIntensity.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <writeLocalObjects.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class turbulenceIntensity Declaration
		\*---------------------------------------------------------------------------*/

		class turbulenceIntensity
			:
			public fvMeshFunctionObject,
			public logFiles,
			public writeLocalObjects
		{
			// Private Member Functions

				//- File header information
			virtual void writeFileHeader(const label i);


		public:

			//- Runtime type information
			TypeName("turbulenceIntensity");


			// Constructors

				//- Construct from Time and dictionary
			turbulenceIntensity
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			turbulenceIntensity(const turbulenceIntensity&) = delete;


			//- Destructor
			virtual ~turbulenceIntensity();


			// Member Functions

				//- Read the turbulenceIntensity data
			virtual bool read(const dictionary&);

			//- Calculate the turbulenceIntensity field
			virtual bool execute();

			//- Write the turbulenceIntensity field
			virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const turbulenceIntensity&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulenceIntensity_Header
