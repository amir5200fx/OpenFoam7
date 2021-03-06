#pragma once
#ifndef _faceCollapser_Header
#define _faceCollapser_Header

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
	tnbLib::faceCollapser

Description
	Collapses faces into edges. Used to remove sliver faces (faces with small
	area but non-zero span).

	Passed in as
	- face label
	- the two indices in the face (fpA, fpB) which delimit the vertices to be
	  kept.

	Takes the vertices outside the range fpA..fpB and projects them onto the
	kept edges (edges using kept vertices only).

	Note:
	- Use in combination with edge collapse to cleanup meshes.
	- Can not remove cells so will mess up trying to remove a face on a tet.
	- WIP. Should be combined with edge collapsing and cell collapsing into
	  proper 'collapser'.
	- Caller is responsible for making sure kept vertices (fpA..fpB) for one
	  face are not the vertices to be removed for another face.

SourceFiles
	faceCollapser.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <point.hxx>
#include <Map.hxx>
#include <HashSet.hxx>
#include <typeInfo.hxx>
#include <edgeList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class polyTopoChange;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
							   Class faceCollapser Declaration
	\*---------------------------------------------------------------------------*/

	class faceCollapser
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;


		// Static Functions

			//- Insert labelList into labelHashSet. Optional excluded element.
		static FoamDynamicMesh_EXPORT void insert
		(
			const labelList& elems,
			const label excludeElem,
			labelHashSet& set
		);

		//- Find edge amongst candidate edges.
		static FoamDynamicMesh_EXPORT label findEdge
		(
			const edgeList& edges,
			const labelList& edgeLabels,
			const label v0,
			const label v1
		);


		// Private Member Functions

			//- Replace vertices in face
		FoamDynamicMesh_EXPORT void filterFace
		(
			const Map<labelList>& splitEdges,
			const label facei,
			polyTopoChange& meshMod
		) const;


	public:

		//- Runtime type information
		//ClassName("faceCollapser");
		static const char* typeName_() { return "faceCollapser"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;


		// Constructors

			//- Construct from mesh.
		FoamDynamicMesh_EXPORT faceCollapser(const polyMesh& mesh);

		//- Disallow default bitwise copy construction
		faceCollapser(const faceCollapser&) = delete;


		// Member Functions

			// Edit

				//- Collapse faces along endpoints. Play commands into
				//  polyTopoChange to create mesh.
		FoamDynamicMesh_EXPORT void setRefinement
		(
			const labelList& faceLabels,
			const labelList& fpA,
			const labelList& fpB,
			polyTopoChange&
		) const;

		//- Update stored quantities for new mesh labels.
		void updateMesh(const mapPolyMesh&)
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const faceCollapser&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_faceCollapser_Header
