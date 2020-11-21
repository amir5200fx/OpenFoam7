#pragma once
#ifndef _triSurface_Header
#define _triSurface_Header

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
	tnbLib::triSurface

Description
	Triangulated surface description with patch information.

SourceFiles
	triSurface.C

\*---------------------------------------------------------------------------*/

#include <primitivePatch.hxx>
#include <pointField.hxx>
#include <labelledTri.hxx>
#include <boolList.hxx>
#include <geometricSurfacePatchList.hxx>
#include <surfacePatchList.hxx>
#include <triFaceList.hxx>
#include <triadField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Time;
	class IFstream;


	// Forward declaration of friend functions and operators

	class triSurface;

	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const triSurface&);


	/*---------------------------------------------------------------------------*\
							   Class triSurface Declaration
	\*---------------------------------------------------------------------------*/

	class triSurface
		:
		public PrimitivePatch<::tnbLib::List<labelledTri>, pointField>
	{
		// Private Typedefs

		//- Typedefs for convenience
		typedef labelledTri Face;
		typedef PrimitivePatch<::tnbLib::List<labelledTri>, pointField>
			ParentType;


		// Private Data

			//- The number of bytes in the STL header
		static const int STLheaderSize = 80;

		//- Patch information (face ordering nFaces/startFace only used
		//  during reading and writing)
		geometricSurfacePatchList patches_;


		// Demand driven private data.

			//- Edge-face addressing (sorted)
		mutable labelListList* sortedEdgeFacesPtr_;

		//- Label of face that 'owns' edge (i.e. e.vec() is righthanded walk
		//  along face)
		mutable labelList* edgeOwnerPtr_;


		// Private Member Functions

			//- Calculate sorted edgeFaces
		FoamFvMesh_EXPORT void calcSortedEdgeFaces() const;

		//- Calculate owner
		FoamFvMesh_EXPORT void calcEdgeOwner() const;

		//- Sort faces according to region. Returns patch list
		//  and sets faceMap to index of labelledTri inside *this.
		FoamFvMesh_EXPORT surfacePatchList calcPatches(labelList& faceMap) const;

		//- Sets default values for patches
		FoamFvMesh_EXPORT void setDefaultPatches();

		//- Function to stitch the triangles by removing duplicate points.
		//  Returns true if any points merged
		FoamFvMesh_EXPORT bool stitchTriangles
		(
			const scalar tol = small,
			const bool verbose = false
		);

		FoamFvMesh_EXPORT scalar pointNormalWeight
		(
			const triFace& f,
			const label pi,
			const vector& fa,
			const pointField& points
		) const;

		//- Return the surface point normals
		FoamFvMesh_EXPORT tmp<vectorField> weightedPointNormals() const;

		//- Return the curvature of surface at the points
		FoamFvMesh_EXPORT tmp<triadField> pointCoordSys(const vectorField& pointNormals) const;


		//- Read in tnbLib format
		FoamFvMesh_EXPORT bool read(Istream&);

		//- Generic read routine. Chooses reader based on extension.
		FoamFvMesh_EXPORT bool read(const fileName&, const word& ext, const bool check = true);

		FoamFvMesh_EXPORT bool readSTL(const fileName&);
		FoamFvMesh_EXPORT bool readSTLASCII(const fileName&);
		FoamFvMesh_EXPORT bool readSTLBINARY(const fileName&);
		FoamFvMesh_EXPORT bool readGTS(const fileName&);
		FoamFvMesh_EXPORT bool readOBJ(const fileName&);
		FoamFvMesh_EXPORT bool readOFF(const fileName&);
		FoamFvMesh_EXPORT bool readTRI(const fileName&);
		FoamFvMesh_EXPORT bool readAC(const fileName&);
		FoamFvMesh_EXPORT bool readNAS(const fileName&);
		FoamFvMesh_EXPORT bool readVTK(const fileName&);

		//- Generic write routine. Chooses writer based on extension.
		FoamFvMesh_EXPORT void write(const fileName&, const word& ext, const bool sort) const;

		//- Write to Ostream in ASCII STL format.
		//  Each region becomes 'solid' 'endsolid' block.
		FoamFvMesh_EXPORT void writeSTLASCII(const bool writeSorted, Ostream&) const;

		//- Write to std::ostream in BINARY STL format
		FoamFvMesh_EXPORT void writeSTLBINARY(std::ostream&) const;

		//- Write to Ostream in GTS (Gnu Tri Surface library)
		//  format.
		FoamFvMesh_EXPORT void writeGTS(const bool writeSorted, Ostream&) const;

		//- Write to Ostream in OBJ (Lightwave) format.
		//  writeSorted=true: sort faces acc. to region and write as single
		//  group. =false: write in normal order.
		FoamFvMesh_EXPORT void writeOBJ(const bool writeSorted, Ostream&) const;

		//- Write to Ostream in OFF (Geomview) format.
		//  writeSorted=true: sort faces acc. to region and write as single
		//  group. =false: write in normal order.
		FoamFvMesh_EXPORT void writeOFF(const bool writeSorted, Ostream&) const;

		//- Write to VTK legacy format.
		FoamFvMesh_EXPORT void writeVTK(const bool writeSorted, Ostream&) const;

		//- Write to Ostream in TRI (AC3D) format
		//  Ac3d .tri format (unmerged triangle format)
		FoamFvMesh_EXPORT void writeTRI(const bool writeSorted, Ostream&) const;

		//- Write to Ostream in SMESH (tetgen) format
		FoamFvMesh_EXPORT void writeSMESH(const bool writeSorted, Ostream&) const;

		//- Write to Ostream in AC3D format. Always sorted by patch.
		FoamFvMesh_EXPORT void writeAC(Ostream&) const;


		// Static private functions

			//- Convert faces to labelledTri. All get same region.
		static FoamFvMesh_EXPORT List<labelledTri> convertToTri
		(
			const faceList&,
			const label defaultRegion = 0
		);

		//- Convert triFaces to labelledTri. All get same region.
		static FoamFvMesh_EXPORT List<labelledTri> convertToTri
		(
			const triFaceList&,
			const label defaultRegion = 0
		);

		//- Helper function to print triangle info
		static FoamFvMesh_EXPORT void printTriangle
		(
			Ostream&,
			const tnbLib::string& pre,
			const labelledTri&,
			const pointField&
		);

		//- Read non-comment line
		static FoamFvMesh_EXPORT string getLineNoComment(IFstream&);


	protected:

		// Protected Member Functions

			//- Non-const access to global points
		pointField& storedPoints()
		{
			return const_cast<pointField&>(ParentType::points());
		}

		//- Non-const access to the faces
		List<Face>& storedFaces()
		{
			return static_cast<List<Face>&>(*this);
		}


	public:

		// Public Typedefs

			//- Placeholder only, but do not remove - it is needed for GeoMesh
		typedef bool BoundaryMesh;


		//- Runtime type information
		/*ClassName("triSurface");*/
		static const char* typeName_() { return "triSurface"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Static

			//- Name of triSurface directory to use.
		static FoamFvMesh_EXPORT fileName triSurfInstance(const Time&);


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT triSurface();

		//- Construct from triangles, patches, points.
		FoamFvMesh_EXPORT triSurface
		(
			const List<labelledTri>&,
			const geometricSurfacePatchList&,
			const pointField&
		);

		//- Construct from triangles, patches, points. Reuse storage.
		FoamFvMesh_EXPORT triSurface
		(
			List<labelledTri>&,
			const geometricSurfacePatchList&,
			pointField&,
			const bool reuse
		);

		//- Construct from triangles, patches, points.
		FoamFvMesh_EXPORT triSurface
		(
			List<labelledTri>&&,
			const geometricSurfacePatchList&,
			List<point>&&
		);

		//- Construct from triangles, points. Set patchnames to default.
		FoamFvMesh_EXPORT triSurface(const List<labelledTri>&, const pointField&);

		//- Construct from triangles, points. Set region to 0 and default
		//  patchName.
		FoamFvMesh_EXPORT triSurface(const triFaceList&, const pointField&);

		//- Construct from file name (uses extension to determine type)
		FoamFvMesh_EXPORT triSurface(const fileName&);

		//- Construct from Istream
		FoamFvMesh_EXPORT triSurface(Istream&);

		//- Construct from objectRegistry
		FoamFvMesh_EXPORT triSurface(const Time& d);

		//- Copy constructor
		FoamFvMesh_EXPORT triSurface(const triSurface&);

		//- Move constructor
		FoamFvMesh_EXPORT triSurface(triSurface&&);


		//- Destructor
		FoamFvMesh_EXPORT ~triSurface();

		FoamFvMesh_EXPORT void clearOut();

		FoamFvMesh_EXPORT void clearTopology();

		FoamFvMesh_EXPORT void clearPatchMeshAddr();


		// Member Functions

			// Access

		const geometricSurfacePatchList& patches() const
		{
			return patches_;
		}

		geometricSurfacePatchList& patches()
		{
			return patches_;
		}

		//- Return edge-face addressing sorted (for edges with more than
		//  2 faces) according to the angle around the edge.
		//  Orientation is anticlockwise looking from
		//  edge.vec(localPoints())
		FoamFvMesh_EXPORT const labelListList& sortedEdgeFaces() const;

		//- If 2 face neighbours: label of face where ordering of edge
		//  is consistent with righthand walk.
		//  If 1 neighbour: label of only face.
		//  If >2 neighbours: undetermined.
		FoamFvMesh_EXPORT const labelList& edgeOwner() const;


		// Edit

			//- Move points
		FoamFvMesh_EXPORT virtual void movePoints(const pointField&);

		//- Scale points. A non-positive factor is ignored
		FoamFvMesh_EXPORT virtual void scalePoints(const scalar);

		//- Check/remove duplicate/degenerate triangles
		FoamFvMesh_EXPORT void checkTriangles(const bool verbose);

		//- Check triply (or more) connected edges.
		FoamFvMesh_EXPORT void checkEdges(const bool verbose);

		//- Remove non-valid triangles
		FoamFvMesh_EXPORT void cleanup(const bool verbose);

		//- Fill faceZone with currentZone for every face reachable
		//  from facei without crossing edge marked in borderEdge.
		//  Note: faceZone has to be sized nFaces before calling this fun.
		FoamFvMesh_EXPORT void markZone
		(
			const boolList& borderEdge,
			const label facei,
			const label currentZone,
			labelList& faceZone
		) const;

		//- (size and) fills faceZone with zone of face. Zone is area
		//  reachable by edge crossing without crossing borderEdge
		//  (bool for every edge in surface). Returns number of zones.
		FoamFvMesh_EXPORT label markZones
		(
			const boolList& borderEdge,
			labelList& faceZone
		) const;

		//- 'Create' sub mesh, including only faces for which
		//  boolList entry is true
		//  Sets: pointMap: from new to old localPoints
		//        faceMap: new to old faces
		FoamFvMesh_EXPORT void subsetMeshMap
		(
			const boolList& include,
			labelList& pointMap,
			labelList& faceMap
		) const;

		//- Return new surface. Returns pointMap, faceMap from
		//  subsetMeshMap
		FoamFvMesh_EXPORT triSurface subsetMesh
		(
			const boolList& include,
			labelList& pointMap,
			labelList& faceMap
		) const;


		// Conversion

			//- Return the list of triangles as a faceList
		FoamFvMesh_EXPORT faceList faces() const;


		// Analysis

			//- Return the curvature of surface at the points
		FoamFvMesh_EXPORT tmp<scalarField> curvature() const;


		// Write

			//- Write to Ostream in simple FOAM format
		FoamFvMesh_EXPORT void write(Ostream&) const;

		//- Generic write routine. Chooses writer based on extension.
		FoamFvMesh_EXPORT void write(const fileName&, const bool sortByRegion = false) const;

		//- Write to database
		FoamFvMesh_EXPORT void write(const Time&) const;

		//- Write some statistics
		FoamFvMesh_EXPORT void writeStats(Ostream&) const;


		// Member Operators

		FoamFvMesh_EXPORT void operator=(const triSurface&);
		FoamFvMesh_EXPORT void operator=(triSurface&&);


		// Ostream Operator

		FoamFvMesh_EXPORT friend Ostream& operator<<(Ostream&, const triSurface&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurface_Header
