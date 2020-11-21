#pragma once
#ifndef _dynamicRefineFvMesh_Header
#define _dynamicRefineFvMesh_Header

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
	tnbLib::dynamicRefineFvMesh

Description
	A fvMesh with built-in refinement.

	Determines which cells to refine/unrefine and does all in update().


		// How often to refine
		refineInterval  1;
		// Field to be refinement on
		field           alpha.water;
		// Refine field in between lower..upper
		lowerRefineLevel 0.001;
		upperRefineLevel 0.999;
		// If value < unrefineLevel (default=great) unrefine
		// unrefineLevel   10;
		// Have slower than 2:1 refinement
		nBufferLayers   1;
		// Refine cells only up to maxRefinement levels
		maxRefinement   2;
		// Stop refinement if maxCells reached
		maxCells        200000;
		// Flux field and corresponding velocity field. Fluxes on changed
		// faces get recalculated by interpolating the velocity. Use 'none'
		// on surfaceScalarFields that do not need to be reinterpolated, use
		// NaN to detect use of mapped variable
		correctFluxes
		(
			(phi none)  // NaN)   // none)
			(nHatf none)   // none)
			(rho*phi none)   // none)
			(ghf none)  // NaN)   // none)
		);
		// Write the refinement level as a volScalarField
		dumpLevel       true;


SourceFiles
	dynamicRefineFvMesh.C

\*---------------------------------------------------------------------------*/

#include <dynamicFvMesh.hxx>
#include <hexRef8.hxx>
#include <PackedBoolList.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class dynamicRefineFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicRefineFvMesh
		:
		public dynamicFvMesh
	{
	protected:

		//- Mesh cutting engine
		hexRef8 meshCutter_;

		//- Dump cellLevel for postprocessing
		Switch dumpLevel_;

		//- Fluxes to map
		HashTable<word> correctFluxes_;

		//- Number of refinement/unrefinement steps done so far.
		label nRefinementIterations_;

		//- Protected cells (usually since not hexes)
		PackedBoolList protectedCell_;


		// Protected Member Functions

			//- Count set/unset elements in packedlist.
		static FoamDynamicMesh_EXPORT label count(const PackedBoolList&, const unsigned int);

		//- Calculate cells that cannot be refined since would trigger
		//  refinement of protectedCell_ (since 2:1 refinement cascade)
		FoamDynamicMesh_EXPORT void calculateProtectedCells(PackedBoolList& unrefineableCell) const;

		//- Read the projection parameters from dictionary
		FoamDynamicMesh_EXPORT void readDict();


		//- Refine cells. Update mesh and fields.
		FoamDynamicMesh_EXPORT autoPtr<mapPolyMesh> refine(const labelList&);

		//- Unrefine cells. Gets passed in centre points of cells to combine.
		FoamDynamicMesh_EXPORT autoPtr<mapPolyMesh> unrefine(const labelList&);


		// Selection of cells to un/refine

			//- Calculates approximate value for refinement level so
			//  we don't go above maxCell
		FoamDynamicMesh_EXPORT scalar getRefineLevel
		(
			const label maxCells,
			const label maxRefinement,
			const scalar refineLevel,
			const scalarField&
		) const;

		//- Get per cell max of connected point
		FoamDynamicMesh_EXPORT scalarField maxPointField(const scalarField&) const;

		//- Get point max of connected cell
		FoamDynamicMesh_EXPORT scalarField maxCellField(const volScalarField&) const;

		FoamDynamicMesh_EXPORT scalarField cellToPoint(const scalarField& vFld) const;

		FoamDynamicMesh_EXPORT scalarField error
		(
			const scalarField& fld,
			const scalar minLevel,
			const scalar maxLevel
		) const;

		//- Select candidate cells for refinement
		FoamDynamicMesh_EXPORT virtual void selectRefineCandidates
		(
			const scalar lowerRefineLevel,
			const scalar upperRefineLevel,
			const scalarField& vFld,
			PackedBoolList& candidateCell
		) const;

		//- Subset candidate cells for refinement
		FoamDynamicMesh_EXPORT virtual labelList selectRefineCells
		(
			const label maxCells,
			const label maxRefinement,
			const PackedBoolList& candidateCell
		) const;

		//- Select points that can be unrefined.
		FoamDynamicMesh_EXPORT virtual labelList selectUnrefinePoints
		(
			const scalar unrefineLevel,
			const PackedBoolList& markedCell,
			const scalarField& pFld
		) const;

		//- Extend markedCell with cell-face-cell.
		FoamDynamicMesh_EXPORT void extendMarkedCells(PackedBoolList& markedCell) const;

		//- Check all cells have 8 anchor points
		FoamDynamicMesh_EXPORT void checkEightAnchorPoints
		(
			PackedBoolList& protectedCell,
			label& nProtected
		) const;


	public:

		//- Runtime type information
		//TypeName("dynamicRefineFvMesh");
		static const char* typeName_() { return "dynamicRefineFvMesh"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		explicit FoamDynamicMesh_EXPORT dynamicRefineFvMesh(const IOobject& io);

		//- Disallow default bitwise copy construction
		dynamicRefineFvMesh(const dynamicRefineFvMesh&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~dynamicRefineFvMesh();


		// Member Functions

			//- Direct access to the refinement engine
		const hexRef8& meshCutter() const
		{
			return meshCutter_;
		}

		//- Cells which should not be refined/unrefined
		const PackedBoolList& protectedCell() const
		{
			return protectedCell_;
		}

		//- Cells which should not be refined/unrefined
		PackedBoolList& protectedCell()
		{
			return protectedCell_;
		}

		//- Update the mesh for both mesh motion and topology change
		FoamDynamicMesh_EXPORT virtual bool update();


		// Writing

			//- Write using given format, version and compression
		FoamDynamicMesh_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat fmt,
			IOstream::versionNumber ver,
			IOstream::compressionType cmp,
			const bool write = true
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const dynamicRefineFvMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicRefineFvMesh_Header
