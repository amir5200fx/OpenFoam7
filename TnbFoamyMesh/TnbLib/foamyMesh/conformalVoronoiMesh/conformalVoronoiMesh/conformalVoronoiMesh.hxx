#pragma once
#ifndef _conformalVoronoiMesh_Header
#define _conformalVoronoiMesh_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::conformalVoronoiMesh

Description

SourceFiles
    conformalVoronoiMeshI.H
    conformalVoronoiMesh.C
    conformalVoronoiMeshZones.C
    conformalVoronoiMeshIO.C
    conformalVoronoiMeshConformToSurface.C
    conformalVoronoiMeshFeaturePoints.C
    conformalVoronoiMeshCalcDualMesh.C
    conformalVoronoiMeshTemplates.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <CGALTriangulation3Ddefs.hxx>
#include <searchableSurfaces.hxx>
#include <conformationSurfaces.hxx>
#include <cellShapeControl.hxx>
#include <cvControls.hxx>
#include <DynamicList.hxx>
#include <PackedBoolList.hxx>
#include <Time.hxx>
#include <polyMesh.hxx>
#include <plane.hxx>
#include <SortableList.hxx>
#include <meshTools.hxx>
#include <dynamicIndexedOctree.hxx>
#include <dynamicTreeDataPoint.hxx>
#include <indexedOctree.hxx>
#include <treeDataPoint.hxx>
#include <unitConversion.hxx>
#include <transform.hxx>
#include <volFields.hxx>
#include <fvMesh.hxx>
#include <labelPair.hxx>
#include <HashSet.hxx>
#include <memInfo.hxx>
#include <point.hxx>
#include <cellSet.hxx>
#include <wallPolyPatch.hxx>
#include <processorPolyPatch.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <globalIndex.hxx>
#include <pointFeatureEdgesTypes.hxx>
#include <pointConversion.hxx>
#include <Pair.hxx>
#include <DistributedDelaunayMesh.hxx>
#include <featurePointConformer.hxx>
#include <pointPairs.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class initialPointsMethod;
    class relaxationModel;
    class faceAreaWeightModel;
    class backgroundMeshDecomposition;
    class OBJstream;

    /*---------------------------------------------------------------------------*\
                        Class conformalVoronoiMesh Declaration
    \*---------------------------------------------------------------------------*/

    class conformalVoronoiMesh
        :
        public DistributedDelaunayMesh<Delaunay>
    {
    public:

        typedef Delaunay::Vertex_handle    Vertex_handle;
        typedef Delaunay::Cell_handle      Cell_handle;
        typedef Delaunay::Edge             Edge;
        typedef Delaunay::Facet            Facet;
        typedef Delaunay::Point            Point;

        typedef List<DynamicList<Pair<labelPair>>> labelPairPairDynListList;

        typedef Tuple2<pointIndexHit, label>         pointIndexHitAndFeature;
        typedef List<pointIndexHitAndFeature>        pointIndexHitAndFeatureList;
        typedef DynamicList<pointIndexHitAndFeature> pointIndexHitAndFeatureDynList;

        // Static data

        enum dualMeshPointType
        {
            internal = 0,
            surface = 1,
            featureEdge = 2,
            featurePoint = 3,
            constrained = 4
        };

        static FoamFoamyMesh_EXPORT const NamedEnum<dualMeshPointType, 5> dualMeshPointTypeNames_;


    private:

        // Static data

        static FoamFoamyMesh_EXPORT const scalar searchConeAngle;

        static FoamFoamyMesh_EXPORT const scalar searchAngleOppositeSurface;


        // Private Data

            //- The time registry of the application
        const Time& runTime_;

        //- Random number generator
        mutable Random rndGen_;

        //- Controls for the conformal Voronoi meshing process
        cvControls foamyHexMeshControls_;

        //- All geometry of the meshing process, including surfaces to be
        //  conformed to and those to be used for refinement
        searchableSurfaces allGeometry_;

        //- The surfaces to conform to
        conformationSurfaces geometryToConformTo_;

        //- Background mesh decomposition, only available in parallel.
        autoPtr<backgroundMeshDecomposition> decomposition_;

        //- The cell shape control object
        cellShapeControl cellShapeControl_;

        //- Limiting bound box before infinity begins
        treeBoundBox limitBounds_;

        //-
        mutable pointPairs<Delaunay> ptPairs_;

        //-
        featurePointConformer ftPtConformer_;

        //- Search tree for edge point locations
        mutable autoPtr<dynamicIndexedOctree<dynamicTreeDataPoint>>
            edgeLocationTreePtr_;

        mutable DynamicList<tnbLib::point> existingEdgeLocations_;

        //- Search tree for surface point locations
        mutable autoPtr<dynamicIndexedOctree<dynamicTreeDataPoint>>
            surfacePtLocationTreePtr_;

        mutable DynamicList<tnbLib::point> existingSurfacePtLocations_;

        //- Store the surface and feature edge conformation locations to be
        //  reinserted
        List<Vb> surfaceConformationVertices_;

        //- Method for inserting initial points.  Runtime selectable.
        autoPtr<initialPointsMethod> initialPointsMethod_;

        //- Relaxation coefficient model.  Runtime selectable.
        autoPtr<relaxationModel> relaxationModel_;

        //-  Face area weight function.  Runtime selectable.
        autoPtr<faceAreaWeightModel> faceAreaWeightModel_;


        // Private Member Functions

        inline scalar defaultCellSize() const;

        //- Return the local target cell size at the given location.  Takes
        //  boolean argument to allow speed-up of queries if the point is going
        //  to be on a surface.
        inline scalar targetCellSize(const tnbLib::point& pt) const;

        //- Return the target cell size from that stored on a pair of
        //  Delaunay vertices, including the possibility that one of
        //  them is not an internalOrBoundaryPoint, and so will not
        //  have valid data.
        inline scalar averageAnyCellSize
        (
            const Vertex_handle& vA,
            const Vertex_handle& vB
        ) const;

        //- The average target cell size of a Delaunay facet, i.e., of
        //  a dual edge
        inline scalar averageAnyCellSize
        (
            const Delaunay::Finite_facets_iterator& fit
        ) const;

        //- Insert Delaunay vertices using the CGAL range insertion method,
        //  optionally check processor occupancy and distribute to other
        //  processors
        FoamFoamyMesh_EXPORT void insertInternalPoints
        (
            List<Point>& points,
            const bool distribute = false
        );

        Map<label> insertPointPairs
        (
            List<Vb>& vertices,
            bool distribute,
            bool reIndex
        );

        //- Create a point-pair at a ppDist distance either side of
        //  surface point surfPt, in the direction n
        inline void createPointPair
        (
            const scalar ppDist,
            const tnbLib::point& surfPt,
            const vector& n,
            const bool ptPair,
            DynamicList<Vb>& pts
        ) const;

        inline tnbLib::point perturbPoint(const tnbLib::point& pt) const;

        //- Create a point-pair at a ppDist distance either side of
        //  surface point surfPt, in the direction n
        inline void createBafflePointPair
        (
            const scalar ppDist,
            const tnbLib::point& surfPt,
            const vector& n,
            const bool ptPair,
            DynamicList<Vb>& pts
        ) const;

        //- Check internal point is completely inside the meshable region
        inline bool internalPointIsInside(const tnbLib::point& pt) const;

        //- Insert pairs of points on the surface with the given normals, at the
        //  specified spacing
        FoamFoamyMesh_EXPORT void insertSurfacePointPairs
        (
            const pointIndexHitAndFeatureList& surfaceHits,
            const fileName fName,
            DynamicList<Vb>& pts
        );

        //- Insert groups of points to conform to an edge given a list of
        //  pointIndexHits specifying the location and edge index of the point
        //  to be conformed to on the corresponding entry in featureHit
        FoamFoamyMesh_EXPORT void insertEdgePointGroups
        (
            const pointIndexHitAndFeatureList& edgeHits,
            const fileName fName,
            DynamicList<Vb>& pts
        );

        FoamFoamyMesh_EXPORT void createEdgePointGroupByCirculating
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        FoamFoamyMesh_EXPORT bool meshableRegion
        (
            const plane::side side,
            const extendedFeatureEdgeMesh::sideVolumeType volType
        ) const;

        FoamFoamyMesh_EXPORT bool regionIsInside
        (
            const extendedFeatureEdgeMesh::sideVolumeType volTypeA,
            const vector& normalA,
            const extendedFeatureEdgeMesh::sideVolumeType volTypeB,
            const vector& normalB,
            const vector& masterPtVec
        ) const;

        //- Create points to conform to an external edge
        FoamFoamyMesh_EXPORT void createExternalEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        //- Create points to conform to an internal edge
        FoamFoamyMesh_EXPORT void createInternalEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        //- Create points to conform to a flat edge
        FoamFoamyMesh_EXPORT void createFlatEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        //- Create points to conform to an open edge
        FoamFoamyMesh_EXPORT void createOpenEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        //- Create points to conform to multiply connected edge
        FoamFoamyMesh_EXPORT void createMultipleEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;

        //- Determine and insert point groups at the feature points
        FoamFoamyMesh_EXPORT void insertFeaturePoints(bool distribute = false);

        //- Check if a location is in exclusion range around a feature point
        FoamFoamyMesh_EXPORT bool nearFeaturePt(const tnbLib::point& pt) const;

        //- Check if a surface point is in exclusion range around a feature edge
        FoamFoamyMesh_EXPORT bool surfacePtNearFeatureEdge(const tnbLib::point& pt) const;

        //- Insert the initial points into the triangulation, based on the
        //  initialPointsMethod
        FoamFoamyMesh_EXPORT void insertInitialPoints();

        //- In parallel redistribute the backgroundMeshDecomposition and
        //  vertices to balance the number of vertices on each processor.
        //  Returns true if the background mesh changes as this removes all
        //  referred vertices, so the parallel interface may need rebuilt.
        template<class Triangulation>
        bool distributeBackground(const Triangulation& mesh);

        // Test for full containment
        FoamFoamyMesh_EXPORT void cellSizeMeshOverlapsBackground() const;

        //-
        FoamFoamyMesh_EXPORT void distribute();

        FoamFoamyMesh_EXPORT void buildCellSizeAndAlignmentMesh();

        //- Set the size and alignment data for each vertex
        FoamFoamyMesh_EXPORT void setVertexSizeAndAlignment();

        //- Builds a dual face by circulating around the supplied edge.
        FoamFoamyMesh_EXPORT face buildDualFace
        (
            const Delaunay::Finite_edges_iterator& eit
        ) const;

        FoamFoamyMesh_EXPORT boolList dualFaceBoundaryPoints
        (
            const Delaunay::Finite_edges_iterator& eit
        ) const;

        //- Finds the maximum filterCount of the dual vertices
        //  (Delaunay cells) that form the dual face produced by the
        //  supplied edge
        FoamFoamyMesh_EXPORT label maxFilterCount
        (
            const Delaunay::Finite_edges_iterator& eit
        ) const;

        //- Determines the owner and neighbour labels for dual cells
        //  corresponding to the dual face formed by the supplied
        //  Delaunay vertices.  If the dual face is a boundary face
        //  then neighbour = -1.  Returns true if the dual face
        //  created by vA -> vB needs to be reversed to be correctly
        //  orientated.
        FoamFoamyMesh_EXPORT bool ownerAndNeighbour
        (
            Vertex_handle vA,
            Vertex_handle vB,
            label& owner,
            label& neighbour
        ) const;

        //- Insert the necessary point pairs to conform to the surface, either
        //  from stored results, or trigger a re-conformation
        FoamFoamyMesh_EXPORT void conformToSurface();

        //- Decision making function for when to rebuild the surface
        //  conformation
        FoamFoamyMesh_EXPORT bool reconformToSurface() const;

        //- Determines geometrically whether a vertex is close to a surface
        //  This is an optimisation
        FoamFoamyMesh_EXPORT label findVerticesNearBoundaries();

        //- Create and insert the necessary point pairs to conform to the
        //  surface, then store the result
        FoamFoamyMesh_EXPORT void buildSurfaceConformation();

        FoamFoamyMesh_EXPORT label synchroniseEdgeTrees
        (
            const DynamicList<label>& edgeToTreeShape,
            pointIndexHitAndFeatureList& featureEdgeHits
        );

        FoamFoamyMesh_EXPORT label synchroniseSurfaceTrees
        (
            const DynamicList<label>& surfaceToTreeShape,
            pointIndexHitAndFeatureList& surfaceHits
        );

        FoamFoamyMesh_EXPORT bool surfaceLocationConformsToInside
        (
            const pointIndexHitAndFeature& info
        ) const;

        //- Check to see if dual cell specified by given vertex iterator
        //  intersects the boundary and hence reqires a point-pair
        FoamFoamyMesh_EXPORT bool dualCellSurfaceAnyIntersection
        (
            const Delaunay::Finite_vertices_iterator& vit
        ) const;

        //- Return all intersections
        FoamFoamyMesh_EXPORT bool dualCellSurfaceAllIntersections
        (
            const Delaunay::Finite_vertices_iterator& vit,
            pointIndexHitAndFeatureDynList& info
        ) const;

        //- Return false if the line is entirely outside the current processor
        //  domain, true is either point is inside, or the processor domain
        //  bounadry is intersected (i.e. the points are box outside but the
        //  line cuts.  The points will be moved onto the box where they
        //  intersect.
        FoamFoamyMesh_EXPORT bool clipLineToProc
        (
            const tnbLib::point& pt,
            tnbLib::point& a,
            tnbLib::point& b
        ) const;

        //- Find the "worst" protrusion of a dual cell through the surface,
        //  subject to the maxSurfaceProtrusion tolerance
        FoamFoamyMesh_EXPORT void dualCellLargestSurfaceProtrusion
        (
            const Delaunay::Finite_vertices_iterator& vit,
            pointIndexHit& surfHit,
            label& hitSurface
        ) const;

        FoamFoamyMesh_EXPORT void dualCellLargestSurfaceIncursion
        (
            const Delaunay::Finite_vertices_iterator& vit,
            pointIndexHit& surfHit,
            label& hitSurface
        ) const;

        //- Write out vertex-processor occupancy information for debugging
        FoamFoamyMesh_EXPORT void reportProcessorOccupancy();

        //- Write out debugging information about the surface conformation
        //  quality
//        void reportSurfaceConformationQuality();

        //- Limit the displacement of a point so that it doesn't penetrate the
        //  surface to be meshed or come too close to it
        FoamFoamyMesh_EXPORT void limitDisplacement
        (
            const Delaunay::Finite_vertices_iterator& vit,
            vector& displacement,
            label callCount = 0
        ) const;

        //- Find angle between the normals of two close surface points.
        FoamFoamyMesh_EXPORT scalar angleBetweenSurfacePoints(tnbLib::point pA, tnbLib::point pB) const;

        //- Check if a surface point is near another.
        FoamFoamyMesh_EXPORT  bool nearSurfacePoint
        (
            pointIndexHitAndFeature& pHit
        ) const;

        //- Append a point to the surface point tree and the existing list
        FoamFoamyMesh_EXPORT bool appendToSurfacePtTree
        (
            const tnbLib::point& pt
        ) const;

        //- Append a point to the edge location tree and the existing list
        FoamFoamyMesh_EXPORT bool appendToEdgeLocationTree
        (
            const tnbLib::point& pt
        ) const;

        //- Return a list of the nearest feature edge locations
        List<pointIndexHit> nearestFeatureEdgeLocations
        (
            const tnbLib::point& pt
        ) const;

        //- Check if a point is near any feature edge points.
        FoamFoamyMesh_EXPORT bool pointIsNearFeatureEdgeLocation(const tnbLib::point& pt) const;

        FoamFoamyMesh_EXPORT bool pointIsNearFeatureEdgeLocation
        (
            const tnbLib::point& pt,
            pointIndexHit& info
        ) const;

        //- Check if a point is near any surface conformation points.
        FoamFoamyMesh_EXPORT bool pointIsNearSurfaceLocation(const tnbLib::point& pt) const;

        FoamFoamyMesh_EXPORT bool pointIsNearSurfaceLocation
        (
            const tnbLib::point& pt,
            pointIndexHit& info
        ) const;

        //- Check if a location is in the exclusion range of an existing feature
        //- Edge conformation location
        FoamFoamyMesh_EXPORT bool nearFeatureEdgeLocation
        (
            const pointIndexHit& pHit,
            pointIndexHit& nearestEdgeHit
        ) const;

        //- Build or rebuild the edge location tree
        FoamFoamyMesh_EXPORT void buildEdgeLocationTree
        (
            const DynamicList<tnbLib::point>& existingEdgeLocations
        ) const;

        //- Build or rebuild the surface point location tree
        FoamFoamyMesh_EXPORT void buildSurfacePtLocationTree
        (
            const DynamicList<tnbLib::point>& existingSurfacePtLocations
        ) const;

        //- Process the surface conformation locations to decide which surface
        //  and edge conformation locations to add
        FoamFoamyMesh_EXPORT void addSurfaceAndEdgeHits
        (
            const tnbLib::point& vit,
            const pointIndexHitAndFeatureDynList& surfaceIntersections,
            scalar surfacePtReplaceDistCoeffSqr,
            scalar edgeSearchDistCoeffSqr,
            pointIndexHitAndFeatureDynList& surfaceHits,
            pointIndexHitAndFeatureDynList& featureEdgeHits,
            DynamicList<label>& surfaceToTreeShape,
            DynamicList<label>& edgeToTreeShape,
            Map<scalar>& surfacePtToEdgePtDist,
            bool firstPass
        ) const;

        //- Store the surface conformation with the indices offset to be
        //  relative to zero
        FoamFoamyMesh_EXPORT void storeSurfaceConformation();

        //- Reinsert the surface conformation re-offsetting indices to be
        //  relative to new number of internal vertices
        FoamFoamyMesh_EXPORT void reinsertSurfaceConformation();

        FoamFoamyMesh_EXPORT void checkCells();

        FoamFoamyMesh_EXPORT void checkDuals();

        FoamFoamyMesh_EXPORT void checkVertices();

        FoamFoamyMesh_EXPORT void checkCoPlanarCells() const;

        //- Dual calculation
        FoamFoamyMesh_EXPORT void calcDualMesh
        (
            pointField& points,
            labelList& boundaryPts,
            faceList& faces,
            labelList& owner,
            labelList& neighbour,
            wordList& patchNames,
            PtrList<dictionary>& patchDicts,
            pointField& cellCentres,
            labelList& cellToDelaunayVertex,
            labelListList& patchToDelaunayVertex,
            PackedBoolList& boundaryFacesToRemove
        );

        FoamFoamyMesh_EXPORT void calcNeighbourCellCentres
        (
            const polyMesh& mesh,
            const pointField& cellCentres,
            pointField& neiCc
        ) const;

        FoamFoamyMesh_EXPORT void selectSeparatedCoupledFaces
        (
            const polyMesh& mesh,
            boolList& selected
        ) const;

        //- From meshRefinementBaffles.C. Use insidePoint for a surface to
        //  determine the cell zone.
        FoamFoamyMesh_EXPORT void findCellZoneInsideWalk
        (
            const polyMesh& mesh,
            const labelList& locationSurfaces,
            const labelList& faceToSurface,
            labelList& cellToSurface
        ) const;

        //- Calculate the cell zones from cellCentres using all closed surfaces
        FoamFoamyMesh_EXPORT labelList calcCellZones(const pointField& cellCentres) const;

        //- Calculate the face zones
        FoamFoamyMesh_EXPORT void calcFaceZones
        (
            const polyMesh& mesh,
            const pointField& cellCentres,
            const labelList& cellToSurface,
            labelList& faceToSurface,
            boolList& flipMap
        ) const;

        //- Add zones to the polyMesh
        FoamFoamyMesh_EXPORT void addZones(polyMesh& mesh, const pointField& cellCentres) const;

        //- Tet mesh calculation
        FoamFoamyMesh_EXPORT void calcTetMesh
        (
            pointField& points,
            labelList& pointToDelaunayVertex,
            faceList& faces,
            labelList& owner,
            labelList& neighbour,
            wordList& patchNames,
            PtrList<dictionary>& patchDicts
        );

        //- Determines if the dual face constructed by the Delaunay
        //  edge is a boundary face
        inline bool isBoundaryDualFace
        (
            const Delaunay::Finite_edges_iterator& eit
        ) const;

        //- Which processors are attached to the dual edge represented by this
        //  Delaunay facet
        inline List<label> processorsAttached
        (
            const Delaunay::Finite_facets_iterator& fit
        ) const;

        //- Determines if the edge constructed from the face is on
        //  a processor patch
        inline bool isParallelDualEdge
        (
            const Delaunay::Finite_facets_iterator& fit
        ) const;

        //- Determines if the dual face constructed by the Delaunay
        //  edge is a processor boundary face
        inline bool isProcBoundaryEdge
        (
            const Delaunay::Finite_edges_iterator& eit
        ) const;

        //- Merge vertices that are identical
        FoamFoamyMesh_EXPORT void mergeIdenticalDualVertices
        (
            const pointField& pts,
            labelList& boundaryPts
        );

        FoamFoamyMesh_EXPORT label mergeIdenticalDualVertices
        (
            const pointField& pts,
            Map<label>& dualPtIndexMap
        ) const;

        //- Identify the face labels of the deferred collapse faces
        FoamFoamyMesh_EXPORT void deferredCollapseFaceSet
        (
            labelList& owner,
            labelList& neighbour,
            const HashSet<labelPair, labelPair::Hash<>>& deferredCollapseFaces
        ) const;

        //- Check whether the cell sizes are fine enough. Creates a polyMesh.
        FoamFoamyMesh_EXPORT void checkCellSizing();

        //- Find all cells with a patch face that is not near the surface. The
        //  allowed offset is the fraction of the target cell size.
        FoamFoamyMesh_EXPORT labelHashSet findOffsetPatchFaces
        (
            const polyMesh& mesh,
            const scalar allowedOffset
        ) const;

        //- Create a polyMesh and check its quality, reports which
        //  elements damage the mesh quality, allowing backtracking.
        FoamFoamyMesh_EXPORT labelHashSet checkPolyMeshQuality(const pointField& pts) const;

        FoamFoamyMesh_EXPORT label classifyBoundaryPoint(Cell_handle cit) const;

        //- Index all of the Delaunay cells and calculate their
        //- Dual points
        FoamFoamyMesh_EXPORT void indexDualVertices
        (
            pointField& pts,
            labelList& boundaryPts
        );

        //- Re-index all of the Delaunay cells
        FoamFoamyMesh_EXPORT void reindexDualVertices
        (
            const Map<label>& dualPtIndexMap,
            labelList& boundaryPts
        );

        FoamFoamyMesh_EXPORT label createPatchInfo
        (
            wordList& patchNames,
            PtrList<dictionary>& patchDicts
        ) const;

        FoamFoamyMesh_EXPORT vector calcSharedPatchNormal(Cell_handle c1, Cell_handle c2) const;

        FoamFoamyMesh_EXPORT bool boundaryDualFace(Cell_handle c1, Cell_handle c2) const;

        //- Create all of the internal and boundary faces
        FoamFoamyMesh_EXPORT void createFacesOwnerNeighbourAndPatches
        (
            const pointField& pts,
            faceList& faces,
            labelList& owner,
            labelList& neighbour,
            wordList& patchNames,
            PtrList<dictionary>& patchDicts,
            labelListList& patchPointPairSlaves,
            PackedBoolList& boundaryFacesToRemove,
            bool includeEmptyPatches = false
        ) const;

        //- Sort the faces, owner and neighbour lists into
        //  upper-triangular order.  For internal faces only, use
        //  before adding patch faces
        FoamFoamyMesh_EXPORT void sortFaces
        (
            faceList& faces,
            labelList& owner,
            labelList& neighbour
        ) const;

        //- Sort the processor patches so that the faces are in the same order
        //  on both processors
        FoamFoamyMesh_EXPORT void sortProcPatches
        (
            List<DynamicList<face>>& patchFaces,
            List<DynamicList<label>>& patchOwners,
            List<DynamicList<label>>& patchPointPairSlaves,
            labelPairPairDynListList& patchSortingIndices
        ) const;

        //- Add the faces and owner information for the patches
        FoamFoamyMesh_EXPORT void addPatches
        (
            const label nInternalFaces,
            faceList& faces,
            labelList& owner,
            PtrList<dictionary>& patchDicts,
            PackedBoolList& boundaryFacesToRemove,
            const List<DynamicList<face>>& patchFaces,
            const List<DynamicList<label>>& patchOwners,
            const List<DynamicList<bool>>& indirectPatchFace
        ) const;

        //- Remove points that are no longer used by any faces
        FoamFoamyMesh_EXPORT void removeUnusedPoints
        (
            faceList& faces,
            pointField& pts,
            labelList& boundaryPts
        ) const;

        //- Remove dual cells that are not used by any faces. Return compaction
        //  map.
        FoamFoamyMesh_EXPORT labelList removeUnusedCells
        (
            labelList& owner,
            labelList& neighbour
        ) const;

        //- Create an empty fvMesh
        autoPtr<fvMesh> createDummyMesh
        (
            const IOobject& io,
            const wordList& patchNames,
            const PtrList<dictionary>& patchDicts
        ) const;

        //- Create a polyMesh from points.
        autoPtr<polyMesh> createPolyMeshFromPoints(const pointField& pts) const;

        FoamFoamyMesh_EXPORT void checkProcessorPatchesMatch
        (
            const PtrList<dictionary>& patchDicts
        ) const;

        FoamFoamyMesh_EXPORT void reorderPoints
        (
            pointField& points,
            labelList& boundaryPts,
            faceList& faces,
            const label nInternalFaces
        ) const;

        //- Rotate the faces on processor patches if necessary
        FoamFoamyMesh_EXPORT void reorderProcessorPatches
        (
            const word& meshName,
            const fileName& instance,
            const pointField& points,
            faceList& faces,
            labelList& owner,
            labelList& neighbour,
            const wordList& patchNames,
            const PtrList<dictionary>& patchDicts
        ) const;

        FoamFoamyMesh_EXPORT void writePointPairs(const fileName& fName) const;


    public:

        //- Runtime type information
        /*ClassName("conformalVoronoiMesh");*/
        static const char* typeName_() { return "conformalVoronoiMesh"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;


        // Constructors

            //- Construct from Time and foamyHexMeshDict
        FoamFoamyMesh_EXPORT conformalVoronoiMesh
        (
            const Time& runTime,
            const dictionary& foamyHexMeshDict
        );

        //- Disallow default bitwise copy construction
        conformalVoronoiMesh(const conformalVoronoiMesh&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~conformalVoronoiMesh();


        // Member Functions

        FoamFoamyMesh_EXPORT void initialiseForMotion();

        FoamFoamyMesh_EXPORT void initialiseForConformation();

        //- Move the vertices according to the controller, re-conforming to the
        //  surface as required
        FoamFoamyMesh_EXPORT void move();

        //        //- Which other processors does each sphere overlap
        //        labelListList overlapsProc
        //        (
        //            const List<tnbLib::point>& centres,
        //            const List<scalar>& radiusSqrs
        //        ) const;


                // Access

                    //- Return the Time object
        inline const Time& time() const;

        //- Return the random number generator
        inline Random& rndGen() const;

        //- Return the allGeometry object
        inline const searchableSurfaces& allGeometry() const;

        //- Return the conformationSurfaces object
        inline const conformationSurfaces& geometryToConformTo() const;

        //- Return the backgroundMeshDecomposition
        inline const backgroundMeshDecomposition& decomposition() const;

        //- Return the cellShapeControl object
        inline const cellShapeControl& cellShapeControls() const;

        //- Return the foamyHexMeshControls object
        inline const cvControls& foamyHexMeshControls() const;


        // Query

            //- Return the local point pair separation at the given location
        inline scalar pointPairDistance(const tnbLib::point& pt) const;

        //- Return the local mixed feature point placement distance
        inline scalar mixedFeaturePointDistance
        (
            const tnbLib::point& pt
        ) const;

        //- Return the square of the local feature point exclusion distance
        inline scalar featurePointExclusionDistanceSqr
        (
            const tnbLib::point& pt
        ) const;

        //- Return the square of the local feature edge exclusion distance
        inline scalar featureEdgeExclusionDistanceSqr
        (
            const tnbLib::point& pt
        ) const;

        //- Return the square of the local surface point exclusion distance
        inline scalar surfacePtExclusionDistanceSqr
        (
            const tnbLib::point& pt
        ) const;

        //- Return the square of the local surface search distance
        inline scalar surfaceSearchDistanceSqr(const tnbLib::point& pt) const;

        //- Return the local maximum surface protrusion distance
        inline scalar maxSurfaceProtrusion(const tnbLib::point& pt) const;

        //- Call the appropriate function to conform to an edge
        FoamFoamyMesh_EXPORT void createEdgePointGroup
        (
            const extendedFeatureEdgeMesh& feMesh,
            const pointIndexHit& edHit,
            DynamicList<Vb>& pts
        ) const;


        // Write

            //- Write the elapsedCpuTime and memory usage, with an optional
            //  description
        static FoamFoamyMesh_EXPORT void timeCheck
        (
            const Time& runTime,
            const string& description = string::null,
            const bool check = true
        );

        FoamFoamyMesh_EXPORT void timeCheck
        (
            const string& description = string::null
        ) const;

        //- Prepare data and call writeMesh for polyMesh and
        //  tetDualMesh
        FoamFoamyMesh_EXPORT void writeMesh(const fileName& instance);

        //- Write mesh to disk
        FoamFoamyMesh_EXPORT void writeMesh
        (
            const word& meshName,
            const fileName& instance,
            pointField& points,
            labelList& boundaryPts,
            faceList& faces,
            labelList& owner,
            labelList& neighbour,
            const wordList& patchNames,
            const PtrList<dictionary>& patchDicts,
            const pointField& cellCentres,
            PackedBoolList& boundaryFacesToRemove
        ) const;

        //- Calculate and write a field of the target cell size,
        //  target cell volume, actual cell volume and equivalent
        //  actual cell size (cbrt(actual cell volume)).
        FoamFoamyMesh_EXPORT void writeCellSizes(const fvMesh& mesh) const;

        FoamFoamyMesh_EXPORT void writeCellAlignments(const fvMesh& mesh) const;

        //- Calculate and write the cell centres.
        FoamFoamyMesh_EXPORT void writeCellCentres(const fvMesh& mesh) const;

        //- Find the cellSet of the boundary cells which have points that
        //  protrude out of the surface beyond a tolerance.
        FoamFoamyMesh_EXPORT labelHashSet findRemainingProtrusionSet(const polyMesh& mesh) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const conformalVoronoiMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <conformalVoronoiMeshI.hxx>

//#ifdef NoRepository
//#include "conformalVoronoiMeshTemplates.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_conformalVoronoiMesh_Header
