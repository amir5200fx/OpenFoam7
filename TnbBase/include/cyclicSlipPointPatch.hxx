#pragma once
#ifndef _cyclicSlipPointPatch_Header
#define _cyclicSlipPointPatch_Header

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
	tnbLib::cyclicSlipPointPatch

Description
	Cyclic patch with slip constraint

SourceFiles
	cyclicSlipPointPatch.C

\*---------------------------------------------------------------------------*/

#include <cyclicPointPatch.hxx>
#include <cyclicSlipPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicSlipPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicSlipPointPatch
		:
		public cyclicPointPatch
	{

	public:

		//- Runtime type information
		//TypeName(cyclicSlipPolyPatch::typeName_());
		static const char* typeName_() { return cyclicSlipPolyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		cyclicSlipPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		)
			:
			cyclicPointPatch(patch, bm)
		{}


		// Destructor

		virtual ~cyclicSlipPointPatch()
		{}


		// Member Functions

			//- Return point unit normals.
		FoamBase_EXPORT virtual const vectorField& pointNormals() const;

		//- Accumulate the effect of constraint direction of this patch
		FoamBase_EXPORT virtual void applyConstraint
		(
			const label pointi,
			pointConstraint&
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicSlipPointPatch_Header
