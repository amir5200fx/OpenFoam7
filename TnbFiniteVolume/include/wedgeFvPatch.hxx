#pragma once
#ifndef _wedgeFvPatch_Header
#define _wedgeFvPatch_Header

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
	tnbLib::wedgeFvPatch

Description
	Wedge front and back plane patch.

SourceFiles
	wedgeFvPatch.C

\*---------------------------------------------------------------------------*/

#include <fvPatch.hxx>
#include <wedgePolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class wedgeFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class wedgeFvPatch
		:
		public fvPatch
	{
		// Private Data

		const wedgePolyPatch& wedgePolyPatch_;


	public:

		//- Runtime type information
		/*TypeName(wedgePolyPatch::typeName_());*/
		static const char* typeName_() { return wedgePolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		FoamFiniteVolume_EXPORT wedgeFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm);


		// Member Functions

			// Access

				//- Return face transformation tensor
		const tensor& faceT() const
		{
			return wedgePolyPatch_.faceT();
		}

		//- Return neighbour-cell transformation tensor
		const tensor& cellT() const
		{
			return wedgePolyPatch_.cellT();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvPatch_Header
