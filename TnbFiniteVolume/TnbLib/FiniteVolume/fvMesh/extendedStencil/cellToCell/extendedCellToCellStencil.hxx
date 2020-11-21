#pragma once
#ifndef _extendedCellToCellStencil_Header
#define _extendedCellToCellStencil_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::extendedCellToCellStencil

Description
	Baseclass for cell-to-cell stencils

SourceFiles
	extendedCellToCellStencil.C
	extendedCellToCellStencilTemplates.C

\*---------------------------------------------------------------------------*/

#include <mapDistribute.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class globalIndex;

	/*---------------------------------------------------------------------------*\
					  Class extendedCellToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class extendedCellToCellStencil
	{
	protected:

		// Protected data

		const polyMesh& mesh_;

	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit extendedCellToCellStencil(const polyMesh&);


		// Member Functions

			//- Sum surface field contributions to create cell values
		template<class Type, class WeightType>
		static
			tmp
			<
			GeometricField
			<
			typename outerProduct<WeightType, Type>::type,
			fvPatchField,
			volMesh
			>
			> weightedSum
			(
				const mapDistribute& map,
				const labelListList& stencil,
				const GeometricField<Type, fvPatchField, volMesh>& fld,
				const List<List<WeightType>>& stencilWeights
			);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <extendedCellToCellStencilI.hxx>

//#ifdef NoRepository
//#include <extendedCellToCellStencilTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_extendedCellToCellStencil_Header
