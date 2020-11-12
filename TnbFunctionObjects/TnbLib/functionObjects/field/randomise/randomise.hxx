#pragma once
#ifndef _randomise_Header
#define _randomise_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::functionObjects::randomise

Description
	Adds a random component to a field, with a specified perturbation magnitude.

	The operation can be applied to any volume field.

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	randomise.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								   Class randomise Declaration
		\*---------------------------------------------------------------------------*/

		class randomise
			:
			public fieldExpression
		{
			// Private member data

				//- The magnitude of the purturbation
			scalar magPerturbation_;


			// Private Member Functions

				//- Calculate the randomisenitude of the field and register the result
			template<class Type>
			bool calcRandomised();

			//- Calculate the randomised field and return true if successful
			FoamFunctionObjects_EXPORT virtual bool calc();


		public:

			//- Runtime type information
			//TypeName("randomise");
			static const char* typeName_() { return "randomise"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT randomise
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~randomise();


			// Member Functions

				//- Read the randomise data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <randomiseTemplates.cxx>
#endif

#include <randomiseTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_randomise_Header
