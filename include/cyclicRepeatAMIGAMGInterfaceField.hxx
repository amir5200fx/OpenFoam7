#pragma once
#ifndef _cyclicRepeatAMIGAMGInterfaceField_Header
#define _cyclicRepeatAMIGAMGInterfaceField_Header

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
	tnbLib::cyclicRepeatAMIGAMGInterfaceField

Description
	GAMG agglomerated repeat AMI interface field.

SourceFiles
	cyclicRepeatAMIGAMGInterfaceField.C

\*---------------------------------------------------------------------------*/


#include <cyclicAMIGAMGInterfaceField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class cyclicRepeatAMIGAMGInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicRepeatAMIGAMGInterfaceField
		:
		public cyclicAMIGAMGInterfaceField
	{
	public:

		//- Runtime type information
		//TypeName("cyclicRepeatAMI");
		static const char* typeName_() { return "cyclicRepeatAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from GAMG interface and fine level interface field
		FoamFvMesh_EXPORT cyclicRepeatAMIGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField& fineInterfaceField
		);

		//- Construct from GAMG interface and fine level interface field
		FoamFvMesh_EXPORT cyclicRepeatAMIGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicRepeatAMIGAMGInterfaceField();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicRepeatAMIGAMGInterfaceField_Header
