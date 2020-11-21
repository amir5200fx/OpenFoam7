#pragma once
#ifndef _fvOptions_Header
#define _fvOptions_Header

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
	tnbLib::fv::options

Description
	Finite-volume options

SourceFiles
	options.C

\*---------------------------------------------------------------------------*/

#include <fvOptionList.hxx>
#include <IOdictionary.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								Class options Declaration
		\*---------------------------------------------------------------------------*/

		class options
			:
			public IOdictionary,
			public optionList
		{
			// Private Member Functions

				//- Create IO object if dictionary is present
			FoamFiniteVolume_EXPORT IOobject createIOobject(const fvMesh& mesh) const;


		public:

			// Declare name of the class and its debug switch
			//ClassName("fvOptions");
			static const char* typeName_() { return "fvOptions"; } 
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName; 
			static FoamFiniteVolume_EXPORT int debug;


			// Constructors

				//- Construct from components with list of field names
			FoamFiniteVolume_EXPORT options(const fvMesh& mesh);

			//- Disallow default bitwise copy construction
			FoamFiniteVolume_EXPORT options(const options&) = delete;

			//- Construct fvOptions and register to datbase if not present
			//  otherwise lookup and return
			static FoamFiniteVolume_EXPORT options& New(const fvMesh& mesh);


			//- Destructor
			virtual ~options()
			{}


			// Member Functions

				//- Inherit read from optionList
			using optionList::read;

			//- Read dictionary
			FoamFiniteVolume_EXPORT virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFiniteVolume_EXPORT void operator=(const options&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvOptions_Header
