#pragma once
#ifndef _emptyFvPatch_Header
#define _emptyFvPatch_Header

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
	tnbLib::emptyFvPatch

Description
	A patch which will not exist in the fvMesh. Typical example is a front and
	back plane of a 2-D geometry

SourceFiles
	emptyFvPatch.C

\*---------------------------------------------------------------------------*/

#include <fvPatch.hxx>
#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class emptyFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class emptyFvPatch
		:
		public fvPatch
	{
		// Private Data

			//- face-cell addressing
		const labelList::subList faceCells_;


	public:

		//- Runtime type information
		/*TypeName(emptyPolyPatch::typeName_());*/
		static const char* typeName_() { return emptyPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		FoamFiniteVolume_EXPORT emptyFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm);


		// Member Functions

			// Access

		virtual label size() const
		{
			return 0;
		}

		//- Return faceCells
		FoamFiniteVolume_EXPORT virtual const labelUList& faceCells() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvPatch_Header
