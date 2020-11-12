#pragma once
#ifndef _Lambda2_Header
#define _Lambda2_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::functionObjects::Lambda2

Description
	Calculates and outputs the second largest eigenvalue of the sum of the
	square of the symmetrical and anti-symmetrical parts of the velocity
	gradient tensor.

See also
	tnbLib::functionObjects::fieldExpression
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	Lambda2.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class Lambda2 Declaration
		\*---------------------------------------------------------------------------*/

		class Lambda2
			:
			public fieldExpression
		{
			// Private Member Functions

				//- Calculate the Lambda2 field and return true if successful
			FoamFunctionObjects_EXPORT virtual bool calc();


		public:

			//- Runtime type information
			//TypeName("Lambda2");
			static const char* typeName_() { return "Lambda2"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT Lambda2
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~Lambda2();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Lambda2_Header
