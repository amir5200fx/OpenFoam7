#pragma once
#ifndef _symmetryPlaneFvPatch_Header
#define _symmetryPlaneFvPatch_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::symmetryPlaneFvPatch

Description
	Symmetry-plane patch.

SourceFiles
	symmetryPlaneFvPatch.C

\*---------------------------------------------------------------------------*/

#include <fvPatch.hxx>
#include <symmetryPlanePolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class symmetryPlaneFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class symmetryPlaneFvPatch
		:
		public fvPatch
	{
		// Private Data

			//- Local reference cast into the symmetryPlane patch
		const symmetryPlanePolyPatch& symmetryPlanePolyPatch_;


	public:

		//- Runtime type information
		/*TypeName(symmetryPlanePolyPatch::typeName_());*/
		static const char* typeName_() { return symmetryPlanePolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		symmetryPlaneFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm),
			symmetryPlanePolyPatch_
			(
				refCast<const symmetryPlanePolyPatch>(patch)
			)
		{}


		// Member Functions

			//- Return symmetry plane normal
		const vector& n() const
		{
			return symmetryPlanePolyPatch_.n();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryPlaneFvPatch_Header
