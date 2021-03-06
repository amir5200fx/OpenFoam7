#pragma once
#ifndef _combineFaces_Header
#define _combineFaces_Header

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
	tnbLib::combineFaces

Description
	Combines boundary faces into single face. The faces get the patch
	of the first face ('the master')

SourceFiles
	combineFaces.C

\*---------------------------------------------------------------------------*/

#include <indirectPrimitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class polyTopoChange;
	class mapPolyMesh;
	class face;

	/*---------------------------------------------------------------------------*\
							   Class combineFaces Declaration
	\*---------------------------------------------------------------------------*/

	class combineFaces
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Whether undoable
		const bool undoable_;

		//- If undoable: masterface for every set.
		labelList masterFace_;

		//- If undoable: per set the vertices of all the faces in the set.
		List<faceList> faceSetsVertices_;

		//- If undoable: saved point labels.
		labelList savedPointLabels_;

		//- If undoable: saved coordinates of above points.
		pointField savedPoints_;



		// Private Member Functions

			//- Test if face is convex. Allow slight concavity through
			//  minConcaveCos.
		static FoamDynamicMesh_EXPORT bool convexFace
		(
			const scalar minConcaveCos,
			const pointField&,
			const face&
		);

		//- Test if set of faces (in primitivePatch) can be combined into
		//  single face. Uses convexFace.
		static FoamDynamicMesh_EXPORT bool validFace
		(
			const scalar minConcaveCos,
			const indirectPrimitivePatch&
		);

		//- Create cell-local map from face to region (formed by merging faces
		//  across edges)
		FoamDynamicMesh_EXPORT void regioniseFaces
		(
			const scalar minCos,
			const labelHashSet& patchIDs,
			const label celli,
			const labelList& cEdges,
			Map<label>& faceRegion
		) const;

		//- Does merging faces invalidate (unmerged) neighbouring faces?
		FoamDynamicMesh_EXPORT bool faceNeighboursValid
		(
			const label celli,
			const Map<label>& faceRegion
		) const;


	public:

		//- Runtime type information
		//ClassName("combineFaces");
		static const char* typeName_() { return "combineFaces"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;


		// Constructors

			//- Construct from mesh
		FoamDynamicMesh_EXPORT combineFaces(const polyMesh& mesh, const bool undoable = false);

		//- Disallow default bitwise copy construction
		combineFaces(const combineFaces&) = delete;


		// Member Functions

			// Access

				//- If undoable: masterface for every set.
		const labelList& masterFace() const
		{
			return masterFace_;
		}

		//- If undoable: set of original point labels of stored points
		const labelList& savedPointLabels() const
		{
			return savedPointLabels_;
		}


		// Helper functions

			//- Extract lists of all (non-coupled) boundary faces on selected
			//  patches and cells that can be merged. Uses getFaceRegions.
		FoamDynamicMesh_EXPORT labelListList getMergeSets
		(
			const scalar featureCos,
			const scalar minConcaveCos,
			const labelHashSet& patchIDs,
			const labelHashSet& boundaryCells
		) const;

		//- Extract lists of all (non-coupled) boundary faces on selected
		//  patches that can be merged. Uses getFaceRegions.
		FoamDynamicMesh_EXPORT labelListList getMergeSets
		(
			const scalar featureCos,
			const scalar minConcaveCos,
			const labelHashSet& patchIDs
		) const;

		//- Extract lists of all (non-coupled) boundary faces that can
		//  be merged. Uses getFaceRegions.
		FoamDynamicMesh_EXPORT labelListList getMergeSets
		(
			const scalar featureCos,
			const scalar minConcaveCos
		) const;

		//- Gets outside of patch as a face (in mesh point labels)
		static FoamDynamicMesh_EXPORT face getOutsideFace(const indirectPrimitivePatch&);


		// Topology changes

			//- Play commands into polyTopoChange to combine faces. Gets
			//  labelListList of sets of faces to combine. Does no check
			//  for whether resulting face is legal.
		FoamDynamicMesh_EXPORT void setRefinement
		(
			const labelListList&,
			polyTopoChange&
		);

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT void updateMesh(const mapPolyMesh&);

		//- Play commands into polyTopoChange to reinsert original faces.
		//  No other topo changes can be done in between setRefinement and
		//  setUnrefinement. Can be called multiple times to undo parts
		//  of the last setRefinement call.
		//  Gets the master face labels whose sets need to be restored.
		//  Returns maps from added restored point to
		//  original point label (i.e. content of savedPointLabels_).
		//  (only restoredPoints are actually set; rest are just for
		//   generalness)
		FoamDynamicMesh_EXPORT void setUnrefinement
		(
			const labelList& masterFaces,
			polyTopoChange& meshMod,
			Map<label>& restoredPoints,
			Map<label>& restoredFaces,
			Map<label>& restoredCells
		);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const combineFaces&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_combineFaces_Header
