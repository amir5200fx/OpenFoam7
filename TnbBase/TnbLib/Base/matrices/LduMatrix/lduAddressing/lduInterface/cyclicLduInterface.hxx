#pragma once
#ifndef _cyclicLduInterface_Header
#define _cyclicLduInterface_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::cyclicLduInterface

Description
	An abstract base class for cyclic coupled interfaces.

SourceFiles
	cyclicLduInterface.C

\*---------------------------------------------------------------------------*/

#include <lduInterface.hxx>
#include <primitiveFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicLduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicLduInterface
	{

	public:

		//- Runtime type information
		//TypeName("cyclicLduInterface");
		static const char* typeName_() { return "cyclicLduInterface"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

		//- Destructor
		FoamBase_EXPORT virtual ~cyclicLduInterface();


		// Member Functions

			// Access

				//- Return neighbour
		FoamBase_EXPORT virtual label neighbPatchID() const = 0;

		FoamBase_EXPORT virtual bool owner() const = 0;

		//- Return processor number
		FoamBase_EXPORT virtual const cyclicLduInterface& neighbPatch() const = 0;

		//- Return face transformation tensor
		FoamBase_EXPORT virtual const tensorField& forwardT() const = 0;

		//- Return face reverse transformation tensor
		FoamBase_EXPORT virtual const tensorField& reverseT() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicLduInterface_Header
