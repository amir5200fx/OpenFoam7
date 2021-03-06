#pragma once
#ifndef _cyclicRepeatAMILduInterface_Header
#define _cyclicRepeatAMILduInterface_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::cyclicRepeatAMILduInterface

Description
	An abstract base class for overlapping AMI coupled interfaces

SourceFiles
	cyclicRepeatAMILduInterface.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMILduInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicRepeatAMILduInterface Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicRepeatAMILduInterface
		:
		public cyclicAMILduInterface
	{

	public:

		//- Runtime type information
		//TypeName("cyclicRepeatAMILduInterface");
		static const char* typeName_() { return "cyclicRepeatAMILduInterface"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		cyclicRepeatAMILduInterface()
		{}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicRepeatAMILduInterface();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicRepeatAMILduInterface_Header
