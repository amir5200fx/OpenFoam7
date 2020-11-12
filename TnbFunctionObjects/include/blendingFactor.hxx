#pragma once
#ifndef _blendingFactor_Header
#define _blendingFactor_Header

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
	tnbLib::functionObjects::blendingFactor

Description
	Calculates and outputs the blendingFactor as used by the bended convection
	schemes.  The output is a volume field (cells) whose value is calculated via
	the maximum blending factor for any cell face.

See also
	tnbLib::functionObjects::fieldExpression
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	blendingFactor.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								  Class blendingFactor Declaration
		\*---------------------------------------------------------------------------*/

		class blendingFactor
			:
			public fieldExpression
		{
			// Private member data

				//- Name of flux field, default is "phi"
			word phiName_;


			// Private Member Functions

				//- Calculate the blending factor field
			template<class Type>
			bool calcBF();

			//- Calculate the blending factor field and return true if successful
			FoamFunctionObjects_EXPORT virtual bool calc();


		public:

			//- Runtime type information
			//TypeName("blendingFactor");
			static const char* typeName_() { return "blendingFactor"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT blendingFactor
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~blendingFactor();


			// Member Functions

				//- Read the blendingFactor data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <blendingFactorTemplates.cxx>
#endif

#include <blendingFactorTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blendingFactor_Header
