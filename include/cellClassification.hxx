#pragma once
#ifndef _cellClassification_Header
#define _cellClassification_Header

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
	tnbLib::cellClassification

Description
	'Cuts' a mesh with a surface.

	Divides cells into three types
	- cut, i.e. any of the edges of the cell is split or any edge of the
	  surface pierces any of the faces of the cell.
	- outside: cell can be reached by Meshwave from any of the supplied
			   outside points (without crossing any cut cell)
	- inside:  all other.

	Used in various meshing programs.

	Has various utility functions to deal with 'features' on this level
	where the mesh still has all inside and outside cells.

	\par Concepts

	- point classification:
		- point used by meshType cells only
		- point used by non-meshType cells only
		- point used by both types ('mixed')

	- hanging cells: meshType cells using mixed points only.
	  These cells would have all their vertices on the surface when
	  extracting the meshType cells.

	- regionEdges: edges where the cells using it are of mixed type.
	  Or more precise when walking around the edge and looking at the
	  different types of the cells there are more than two regions with
	  same type.

	Seen from above:
	\verbatim
	Ok:
		 A | A
		   |
		 --+---
		   |
		 B | B

	Not ok:
		 A | B
		   |
		---+---
		   |
		 B | A
	\endverbatim

	because this latter situation would cause the surface after subsetting
	type A or B to be multiply connected across this edge. And also when
	snapping the edge end points to the surface it might cause some twisted
	faces if the surface is normal to the edge (and smoothing the surface
	would not help since the points on the edge would be 'pulled' from two
	different sides)

	- regionPoints: like regionEdges but now for points.
	  Points where subsetting the mesh would cause a multiply connected
	  outside surface (connected across point, not edge)


SourceFiles
	cellClassification.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <Map.hxx>
#include <boolList.hxx>
#include <labelList.hxx>
#include <faceList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurfaceSearch;
	class meshSearch;
	class polyMesh;
	class primitiveMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellClassification Declaration
	\*---------------------------------------------------------------------------*/

	class cellClassification
		:
		public labelList
	{

	public:

		// Public data types

			//- Type of cell.
		enum cType
		{
			NOTSET,
			INSIDE,     // Inside of surface
			OUTSIDE,    // Outside ,,
			CUT         // cut by surface
		};


		//- Enumeration defining the whether points are use by cells of
		//  a certain type.
		enum pointStatus
		{
			UNSET,
			MESH,       // points used by meshType cells
			NONMESH,    //    ,,          non-mesh type cells
			MIXED       //    ,,          both types of cell
		};

	private:

		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;


		// Private Static Functions

			//- Count number of occurrences of elem in list
		static FoamFvMesh_EXPORT label count(const labelList& elems, const label elem);

		// Private Member Functions

			//- Mark all faces intersected by or intersecting surface
		FoamFvMesh_EXPORT boolList markFaces(const triSurfaceSearch&) const;

		//- Divide cells into cut/inside/outside by using MeshWave from cut
		//  faces. No check is done on whether outsidePts are in different
		//  domains.
		FoamFvMesh_EXPORT void markCells
		(
			const meshSearch& queryMesh,
			const boolList& piercedFace,
			const pointField& outsidePts
		);

		//- Use cell status to classify points as being internal to meshType,
		//  internal to non-meshType or on border of both.
		FoamFvMesh_EXPORT void classifyPoints
		(
			const label meshType,
			const labelList& cellType,
			List<pointStatus>& pointSide
		) const;

		//- Return true if cell uses only points with status=mixed
		FoamFvMesh_EXPORT bool usesMixedPointsOnly
		(
			const List<pointStatus>&,
			const label celli
		) const;

		//- Get faces (and its 'owner') in between cells of differing type
		// (meshType and non-meshType).
		FoamFvMesh_EXPORT void getMeshOutside(const label meshType, faceList&, labelList&) const;

	public:

		// Static Data Members
		//ClassName("cellClassification");
		static const char* typeName_() { return "cellClassification"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;

		// Constructors

			//- Construct from mesh and surface and point(s) on outside
		FoamFvMesh_EXPORT cellClassification
		(
			const polyMesh& mesh,
			const meshSearch& meshQuery,
			const triSurfaceSearch& surfQuery,
			const pointField& outsidePoints
		);

		//- Construct from mesh and type for every cell.
		//  Used to be able to reuse filling routines below.
		FoamFvMesh_EXPORT cellClassification(const polyMesh& mesh, const labelList& cellType);

		//- Copy constructor
		FoamFvMesh_EXPORT cellClassification(const cellClassification&);


		// Member Functions

		const polyMesh& mesh() const
		{
			return mesh_;
		}

		FoamFvMesh_EXPORT label trimCutCells
		(
			const label nLayers,
			const label meshType,
			const label fillType
		);

		//- Sets vertex neighbours of meshType cells to fillType
		FoamFvMesh_EXPORT label growSurface(const label meshType, const label fillType);

		//- Find hanging cells (cells with all points on outside) and set their
		//  type to fillType.
		//  Iterate until nothing changed. Returns total number of cells
		//  changed (in all iterations)
		FoamFvMesh_EXPORT label fillHangingCells
		(
			const label meshType,
			const label fillType,
			const label maxIter
		);

		//- Find regionEdges and fill one neighbour. Iterate until nothing
		//  changes. Returns total number of cells changed.
		FoamFvMesh_EXPORT label fillRegionEdges
		(
			const label meshType,
			const label fillType,
			const label maxIter
		);

		//- Find regionPoints and fill all neighbours. Iterate until nothing
		//  changes. Returns total number of cells changed.
		FoamFvMesh_EXPORT label fillRegionPoints
		(
			const label meshType,
			const label fillType,
			const label maxIter
		);

		//- Write statistics on cell types to Ostream
		FoamFvMesh_EXPORT void writeStats(Ostream& os) const;


		// Member Operators

		FoamFvMesh_EXPORT void operator=(const cellClassification&);

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellClassification_Header
