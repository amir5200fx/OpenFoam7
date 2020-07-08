#pragma once
#ifndef _emptyPointPatch_Header
#define _emptyPointPatch_Header

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
	tnbLib::emptyPointPatch

Description
	Empty plane patch.

SourceFiles
	emptyPointPatch.C

\*---------------------------------------------------------------------------*/

#include <facePointPatch.hxx>
#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class emptyPointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class emptyPointPatch
		:
		public facePointPatch
	{

	public:

		//- Runtime type information
		TypeName(emptyPolyPatch::typeName_());


		// Constructors

			//- Construct from polyPatch
		emptyPointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		)
			:
			facePointPatch(patch, bm)
		{}


		// Member Functions

			//- Return the constraint type this pointPatch implements.
		virtual const word& constraintType() const
		{
			return type();
		}

		//- Accumulate the effect of constraint direction of this patch
		virtual void applyConstraint
		(
			const label pointi,
			pointConstraint&
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyPointPatch_Header
