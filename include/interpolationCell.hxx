#pragma once
#ifndef _interpolationCell_Header
#define _interpolationCell_Header

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
	tnbLib::interpolationCell

Description
	Uses the cell value for any point in the cell

\*---------------------------------------------------------------------------*/

#include <interpolation.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamInterpolationCell_EXPORT __declspec(dllexport)
#else
#ifdef FoamInterpolationCell_EXPORT_DEFINE
#define FoamInterpolationCell_EXPORT __declspec(dllexport)
#else
#define FoamInterpolationCell_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class interpolationCell Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolationCell
		:
		public interpolation<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("cell");*/
		static const char* typeName_() { return "cell"; }
		static const ::tnbLib::word typeName;
		static int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		interpolationCell
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

#include <interpolationCellI.hxx>

//#ifdef NoRepository
//#include <interpolationCell.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationCell_Header
