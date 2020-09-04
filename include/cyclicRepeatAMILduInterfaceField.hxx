#pragma once
#ifndef _cyclicRepeatAMILduInterfaceField_Header
#define _cyclicRepeatAMILduInterfaceField_Header

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
	tnbLib::cyclicRepeatAMILduInterfaceField

Description
	Abstract base class for overlapping AMI coupled interfaces

SourceFiles
	cyclicRepeatAMILduInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMILduInterfaceField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class cyclicRepeatAMILduInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicRepeatAMILduInterfaceField
		:
		public cyclicAMILduInterfaceField
	{

	public:

		//- Runtime type information
		TypeName("cyclicRepeatAMILduInterfaceField");


		// Constructors

			//- Construct null
		cyclicRepeatAMILduInterfaceField()
		{}


		//- Destructor
		virtual ~cyclicRepeatAMILduInterfaceField();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicRepeatAMILduInterfaceField_Header
