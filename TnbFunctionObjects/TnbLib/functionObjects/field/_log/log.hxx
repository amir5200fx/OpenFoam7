#pragma once
#ifndef _log_Header
#define _log_Header

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
	tnbLib::functionObjects::log

Description
	Calculates the natural logarithm of the specified scalar field.

	Performs \f$ln(max(x, a))\f$ where \f$x\f$ is the field and \f$a\f$ an
	optional clip to handle 0 or negative \f$x\f$.

See also
	tnbLib::functionObjects::fieldExpression
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	log.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class log Declaration
		\*---------------------------------------------------------------------------*/

		class log
			:
			public fieldExpression
		{
			// Private Data

				//- Optional clip (default is 0)
			scalar clip_;


			// Private Member Functions

				//- Calculate the log field and return true if successful
			FoamFunctionObjects_EXPORT virtual bool calc();


		public:

			//- Runtime type information
			//TypeName("log");
			static const char* typeName_() { return "log"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT log
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~log();


			// Member Functions

				//- Read the randomise data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_log_Header
