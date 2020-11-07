#pragma once
#ifndef _cellToCellStencil_Header
#define _cellToCellStencil_Header

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
	tnbLib::cellToCellStencil

Description
	baseclass for extended cell centred addressing. Contains per cell a
	list of neighbouring cells and/or boundaryfaces in global addressing.

SourceFiles
	cellToCellStencil.C

\*---------------------------------------------------------------------------*/

#include <globalIndex.hxx>
#include <boolList.hxx>
#include <HashSet.hxx>
#include <indirectPrimitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						  Class cellToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class cellToCellStencil
		:
		public labelListList
	{
		// Private Data

		const polyMesh& mesh_;

		//- Global numbering for cells and boundary faces
		const globalIndex globalNumbering_;


	protected:

		//- Merge two lists.
		//  Guarantee global0, global1 are first.
		static FoamFiniteVolume_EXPORT void merge
		(
			const label global0,
			const label global1,
			const labelList& listA,
			labelList& listB
		);

		//- Merge two lists and guarantee globalI is first.
		static FoamFiniteVolume_EXPORT void merge
		(
			const label globalI,
			const labelList& pGlobals,
			labelList& cCells
		);

		//- Valid boundary faces (not empty and not coupled)
		FoamFiniteVolume_EXPORT void validBoundaryFaces(boolList& isValidBFace) const;

		//- Return patch of all coupled faces.
		autoPtr<indirectPrimitivePatch> allCoupledFacesPatch() const;

		//- Combine operator for labelLists
		class unionEqOp
		{
		public:
			FoamFiniteVolume_EXPORT void operator()(labelList& x, const labelList& y) const;
		};

		//- Collect cell neighbours of faces in global numbering
		FoamFiniteVolume_EXPORT void insertFaceCells
		(
			const label exclude0,
			const label exclude1,
			const boolList& nonEmptyFace,
			const labelList& faceLabels,
			labelHashSet& globals
		) const;

		//- Collect cell neighbours of faces in global numbering
		FoamFiniteVolume_EXPORT labelList calcFaceCells
		(
			const boolList& nonEmptyFace,
			const labelList& faceLabels,
			labelHashSet& globals
		) const;


	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT explicit cellToCellStencil(const polyMesh&);


		// Member Functions

		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Global numbering for cells and boundary faces
		const globalIndex& globalNumbering() const
		{
			return globalNumbering_;
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellToCellStencil_Header
