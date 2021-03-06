#pragma once
#ifndef _geomDecomp_Header
#define _geomDecomp_Header

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
	tnbLib::geomDecomp

Description
	Geometrical domain decomposition

SourceFiles
	geomDecomp.C

\*---------------------------------------------------------------------------*/

#include <decompositionMethod.hxx>
#include <VectorTemplate.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class geomDecomp Declaration
	\*---------------------------------------------------------------------------*/

	class geomDecomp
		:
		public decompositionMethod
	{

	protected:

		// Protected data

		const dictionary& geomDecomDict_;

		Vector<label> n_;
		scalar delta_;
		tensor rotDelta_;

	public:

		// Constructors

			//- Construct given the decomposition dictionary
			//  and the derived type name
		FoamParallel_EXPORT geomDecomp
		(
			const dictionary& decompositionDict,
			const word& derivedType
		);

		//- Return for every coordinate the wanted processor number.
		FoamParallel_EXPORT virtual labelList decompose
		(
			const pointField& points,
			const scalarField& pointWeights
		) = 0;

		//- Like decompose but with uniform weights on the points
		FoamParallel_EXPORT virtual labelList decompose(const pointField&) = 0;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_geomDecomp_Header
