#pragma once
#ifndef _genericPointPatch_Header
#define _genericPointPatch_Header

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
	tnbLib::genericPointPatch

Description
	Substitute for unknown patches. Used for postprocessing when only
	basic polyPatch info is needed.

SourceFiles
	genericPointPatch.C

\*---------------------------------------------------------------------------*/

#include <facePointPatch.hxx>
#include <genericPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class genericPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class genericPointPatch
		:
		public facePointPatch
	{

	public:

		//- Runtime type information
		//TypeName(genericPolyPatch::typeName_());
		static const char* typeName_() { return genericPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		genericPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		)
			:
			facePointPatch(patch, bm)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_genericPointPatch_Header
