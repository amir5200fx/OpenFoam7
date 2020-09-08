#pragma once
#ifndef _interpolationCellPatchConstrained_Header
#define _interpolationCellPatchConstrained_Header

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
	tnbLib::interpolationCellPatchConstrained

Description
	Uses the cell value for any point in the cell apart from a boundary face
	where it uses the boundary value directly.
	Note: will not work on an empty patch.

\*---------------------------------------------------------------------------*/

#include <interpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class interpolationCellPatchConstrained Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCellPatchConstrained
		:
		public interpolation<Type>
	{

	public:

		//- Runtime type information
		TypeName("cellPatchConstrained");


		// Constructors

			//- Construct from components
		interpolationCellPatchConstrained
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Member Functions

			//- Interpolate field to the given point in the given cell
		Type interpolate
		(
			const vector& position,
			const label celli,
			const label facei = -1
		) const;

		//- Interpolate field to the given coordinates in the tetrahedron
		//  defined by the given indices. This is an optimisation which skips
		//  calculating the position, as cell interpolation doesn't need it.
		inline Type interpolate
		(
			const barycentric& coordinates,
			const tetIndices& tetIs,
			const label facei = -1
		) const
		{
			return interpolate(vector::zero, tetIs.cell(), facei);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationCellPatchConstrainedI.hxx>

//#ifdef NoRepository
//#include <interpolationCellPatchConstrained.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCellPatchConstrained_Header
