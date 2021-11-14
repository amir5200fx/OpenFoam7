#pragma once
#ifndef _backgroundMeshDecomposition_Header
#define _backgroundMeshDecomposition_Header
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
    tnbLib::backgroundMeshDecomposition

Description
    Store a background polyMesh to use for the decomposition of space and
    queries for parallel conformalVoronoiMesh.

    The requirements are:

    - To have a decomposition of space which can quickly interrogate an
      arbitrary location from any processor to reliably and unambiguously
      determine which processor owns the space that the point is in, i.e. as
      the vertices move, or need inserted as part of the surface conformation,
      send them to the correct proc.

    - To be able to be dynamically built, refined and redistributed to other
      procs the partitioning as the meshing progresses to balance the load.

    - To be able to query whether a sphere (the circumsphere of a Delaunay tet)
      overlaps any part of the space defined by the structure, and whether a
      ray (Voronoi edge) penetrates any part of the space defined by the
      structure, this is what determines if points get referred to a processor.

SourceFiles
    backgroundMeshDecompositionI.H
    backgroundMeshDecomposition.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <fvMesh.hxx>
#include <hexRef8.hxx>
#include <cellSet.hxx>
#include <meshTools.hxx>
#include <polyTopoChange.hxx>
#include <mapPolyMesh.hxx>
#include <decompositionMethod.hxx>
#include <fvMeshDistribute.hxx>
#include <removeCells.hxx>
#include <mapDistributePolyMesh.hxx>
#include <globalIndex.hxx>
#include <treeBoundBox.hxx>
#include <primitivePatch.hxx>
#include <face.hxx>
#include <labelList.hxx>
#include <pointField.hxx>
#include <indexedOctree.hxx>
#include <treeDataPrimitivePatch.hxx>
#include <volumeType.hxx>
#include <CGALTriangulation3Ddefs.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    typedef PrimitivePatch<faceList, const pointField> bPatch;
    typedef treeDataPrimitivePatch<bPatch> treeDataBPatch;

    class Time;
    class Random;
    class conformationSurfaces;

    /*---------------------------------------------------------------------------*\
                      Class backgroundMeshDecomposition Declaration
    \*---------------------------------------------------------------------------*/

    class backgroundMeshDecomposition
    {
        // Private Data

            //- Method details dictionary
            // dictionary coeffsDict_;

            //- Reference to runtime
        const Time& runTime_;

        //- Reference to surface
        const conformationSurfaces& geometryToConformTo_;

        //- Random number generator
        Random& rndGen_;

        //- Mesh stored on for this processor, specifying the domain that it
        //  is responsible for.
        fvMesh mesh_;

        //- Refinement object
        hexRef8 meshCutter_;

        //- Patch containing an independent representation of the surface of the
        //  mesh of this processor
        autoPtr<bPatch> boundaryFacesPtr_;

        //- Search tree for the boundaryFaces_ patch
        autoPtr<indexedOctree<treeDataBPatch>> bFTreePtr_;

        //- The bounds of all background meshes on all processors
        treeBoundBoxList allBackgroundMeshBounds_;

        //- The overall bounds of all of the background meshes, used to test if
        //  a point that is not found on any processor is in the domain at all
        treeBoundBox globalBackgroundBounds_;

        //- Decomposition dictionary
        IOdictionary decomposeDict_;

        //- Decomposition method
        autoPtr<decompositionMethod> decomposerPtr_;

        //- Merge distance required by fvMeshDistribute
        scalar mergeDist_;

        //- Scale of a cell span vs cell size used to decide to refine a cell
        scalar spanScale_;

        //- Smallest minimum cell size allowed, i.e. to avoid high initial
        //  refinement of areas of small size
        scalar minCellSizeLimit_;

        //- Minimum normal level of refinement
        label minLevels_;

        //- How fine should the initial sample of the volume a box be to
        //  investigate the local cell size
        label volRes_;

        //- Allowed factor above the average cell weight before a background
        //  cell needs to be split
        scalar maxCellWeightCoeff_;


        // Private Member Functions

        FoamFoamyMesh_EXPORT void initialRefinement();

        //- Print details of the decomposed mesh
        FoamFoamyMesh_EXPORT void printMeshData(const polyMesh& mesh) const;

        //- Estimate the number of vertices that will be in this cell, returns
        //  true if the cell is to be split because of the density ratio inside
        //  it
        FoamFoamyMesh_EXPORT bool refineCell
        (
            label celli,
            volumeType volType,
            scalar& weightEstimate
        ) const;

        //- Select cells for refinement at the surface of the geometry to be
        //  meshed
        FoamFoamyMesh_EXPORT labelList selectRefinementCells
        (
            List<volumeType>& volumeStatus,
            volScalarField& cellWeights
        ) const;

        //- Build the surface patch and search tree
        FoamFoamyMesh_EXPORT void buildPatchAndTree();


    public:

        //- Runtime type information
       /* ClassName("backgroundMeshDecomposition");*/
        static const char* typeName_() { return "backgroundMeshDecomposition"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;

        // Constructors

            //- Construct from components in foamyHexMesh operation
        FoamFoamyMesh_EXPORT backgroundMeshDecomposition
        (
            const Time& runTime,
            Random& rndGen,
            const conformationSurfaces& geometryToConformTo,
            const dictionary& coeffsDict
        );

        //- Disallow default bitwise copy construction
        backgroundMeshDecomposition
        (
            const backgroundMeshDecomposition&
        ) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~backgroundMeshDecomposition();


        // Member Functions

            //- Build a mapDistribute for the supplied destination processor data
        static FoamFoamyMesh_EXPORT autoPtr<mapDistribute> buildMap(const List<label>& toProc);

        //- Redistribute the background mesh based on a supplied weight field,
        //  returning a map to use to redistribute vertices.
        FoamFoamyMesh_EXPORT autoPtr<mapDistributePolyMesh> distribute
        (
            volScalarField& cellWeights
        );

        //- Distribute supplied the points to the appropriate processor
        template<class PointType>
        autoPtr<mapDistribute> distributePoints(List<PointType>& points) const;

        //- Is the given position inside the domain of this decomposition
        FoamFoamyMesh_EXPORT bool positionOnThisProcessor(const point& pt) const;

        //- Are the given positions inside the domain of this decomposition
        FoamFoamyMesh_EXPORT boolList positionOnThisProcessor(const List<point>& pts) const;

        //- Does the given box overlap the faces of the boundary of this
        //  processor
        FoamFoamyMesh_EXPORT bool overlapsThisProcessor(const treeBoundBox& box) const;

        //- Does the given sphere overlap the faces of the boundary of this
        //  processor
        FoamFoamyMesh_EXPORT bool overlapsThisProcessor
        (
            const point& centre,
            const scalar radiusSqr
        ) const;

        //- Find nearest intersection of line between start and end, (exposing
        //  underlying indexedOctree)
        FoamFoamyMesh_EXPORT pointIndexHit findLine
        (
            const point& start,
            const point& end
        ) const;

        //- Find any intersection of line between start and end, (exposing
        //  underlying indexedOctree)
        FoamFoamyMesh_EXPORT pointIndexHit findLineAny
        (
            const point& start,
            const point& end
        ) const;

        //- What processor is the given position on?
        template<class PointType>
        labelList processorPosition(const List<PointType>& pts) const;

        //- What is the nearest processor to the given position?
        FoamFoamyMesh_EXPORT labelList processorNearestPosition(const List<point>& pts) const;

        //- Which processors are intersected by the line segment, returns all
        //  processors whose boundary patch is intersected by the sphere.  By
        //  default this does not return the processor that the query is
        //  launched from, it is assumed that the point is on that processor.
        //  The index data member of the pointIndexHit is replaced with the
        //  processor index.
        FoamFoamyMesh_EXPORT List<List<pointIndexHit>> intersectsProcessors
        (
            const List<point>& starts,
            const List<point>& ends,
            bool includeOwnProcessor = false
        ) const;

        FoamFoamyMesh_EXPORT bool overlapsOtherProcessors
        (
            const point& centre,
            const scalar& radiusSqr
        ) const;

        FoamFoamyMesh_EXPORT labelList overlapProcessors
        (
            const point& centre,
            const scalar radiusSqr
        ) const;


        // Access

            //- Return access to the underlying mesh
        inline const fvMesh& mesh() const;

        //- Return access to the underlying tree
        inline const indexedOctree<treeDataBPatch>& tree() const;

        //- Return the boundBox of this processor
        inline const treeBoundBox& procBounds() const;

        //- Return the cell level of the underlying mesh
        inline const labelList& cellLevel() const;

        //- Return the point level of the underlying mesh
        inline const labelList& pointLevel() const;

        //- Return the current decomposition method
        inline const decompositionMethod& decomposer() const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const backgroundMeshDecomposition&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <backgroundMeshDecompositionI.hxx>

//#ifdef NoRepository
//#include "backgroundMeshDecompositionTemplates.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
