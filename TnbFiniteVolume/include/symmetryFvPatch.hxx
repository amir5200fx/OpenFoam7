#pragma once
#ifndef _symmetryFvPatch_Header
#define _symmetryFvPatch_Header

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
	tnbLib::symmetryFvPatch

Description
	Symmetry patch for non-planar or multi-plane patches.

SourceFiles
	symmetryFvPatch.C

\*---------------------------------------------------------------------------*/

#include <fvPatch.hxx>
#include <symmetryPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class symmetryFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class symmetryFvPatch
		:
		public fvPatch
	{

	public:

		//- Runtime type information
		/*TypeName(symmetryPolyPatch::typeName_());*/
		static const char* typeName_() { return symmetryPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		symmetryFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryFvPatch_Header
