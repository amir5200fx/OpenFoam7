#pragma once
#ifndef _cyclicRepeatAMIFvPatch_Header
#define _cyclicRepeatAMIFvPatch_Header

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
	tnbLib::cyclicRepeatAMIFvPatch

Description
	Repeating patch for Arbitrary Mesh Interface (AMI)

SourceFiles
	cyclicRepeatAMIFvPatch.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMIFvPatch.hxx>
#include <cyclicRepeatAMIPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicRepeatAMIFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicRepeatAMIFvPatch
		:
		public cyclicAMIFvPatch
	{
	public:

		//- Runtime type information
		/*TypeName(cyclicRepeatAMIPolyPatch::typeName_());*/
		static const char* typeName_() { return cyclicRepeatAMIPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		cyclicRepeatAMIFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			cyclicAMIFvPatch(patch, bm)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicRepeatAMIFvPatch_Header

