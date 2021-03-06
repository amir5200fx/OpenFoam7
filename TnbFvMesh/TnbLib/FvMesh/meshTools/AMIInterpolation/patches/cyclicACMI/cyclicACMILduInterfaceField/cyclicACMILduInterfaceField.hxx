#pragma once
#ifndef _cyclicACMILduInterfaceField_Header
#define _cyclicACMILduInterfaceField_Header

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
	tnbLib::cyclicACMILduInterfaceField

Description
	Abstract base class for cyclic ACMI coupled interfaces

SourceFiles
	cyclicACMILduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMILduInterfaceField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class cyclicACMILduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicACMILduInterfaceField
		:
		public cyclicAMILduInterfaceField
	{

	public:

		//- Runtime type information
		//TypeName("cyclicACMILduInterfaceField");
		static const char* typeName_() { return "cyclicACMILduInterfaceField"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		cyclicACMILduInterfaceField()
		{}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicACMILduInterfaceField();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicACMILduInterfaceField_Header
