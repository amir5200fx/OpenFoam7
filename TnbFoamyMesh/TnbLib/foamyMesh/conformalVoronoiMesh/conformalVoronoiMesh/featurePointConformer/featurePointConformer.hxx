#pragma once
#ifndef _featurePointConformer_Header
#define _featurePointConformer_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
    tnbLib::featurePointConformer

Description
    The Delaunay vertices required to conform to a feature point can be
    determined upon initialisation because the feature points are fixed and
    do not change throughout the meshing process.

SourceFiles
    featurePointConformerI.H
    featurePointConformer.C
    featurePointConformerSpecialisations.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <CGALTriangulation3Ddefs.hxx>
#include <vector.hxx>
#include <DynamicList.hxx>
#include <List.hxx>
#include <extendedFeatureEdgeMesh.hxx>
#include <pointPairs.hxx>
#include <scalar.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class conformalVoronoiMesh;
    class cvControls;
    class conformationSurfaces;
    class pointFeatureEdgesTypes;
    class backgroundMeshDecomposition;

    /*---------------------------------------------------------------------------*\
                       Class featurePointConformer Declaration
    \*---------------------------------------------------------------------------*/

    class featurePointConformer
    {
        // Static data

            //- Tolerance within which two lines are said to be parallel.
        static FoamFoamyMesh_EXPORT const scalar tolParallel;


        // Private Data

            //- Reference to the mesher.
        const conformalVoronoiMesh& foamyHexMesh_;

        //- Reference to the mesher controls.
        const cvControls& foamyHexMeshControls_;

        //- Reference to the conformation surfaces.
        const conformationSurfaces& geometryToConformTo_;

        //- Store the feature constraining points, to be reinserted after a
        //  triangulation clear.
        List<Vb> featurePointVertices_;

        //-
        mutable pointPairs<Delaunay> ftPtPairs_;


        // Private Member Functions

            //- Calculate the shared face normal between two edges geometrically.
        FoamFoamyMesh_EXPORT vector sharedFaceNormal
        (
            const extendedFeatureEdgeMesh& feMesh,
            const label edgeI,
            const label nextEdgeI
        ) const;

        FoamFoamyMesh_EXPORT label getSign(const extendedFeatureEdgeMesh::edgeStatus eStatus) const;

        FoamFoamyMesh_EXPORT bool createSpecialisedFeaturePoint
        (
            const extendedFeatureEdgeMesh& feMesh,
            const labelList& pEds,
            const pointFeatureEdgesTypes& pFEdgesTypes,
            const List<extendedFeatureEdgeMesh::edgeStatus>& allEdStat,
            const label ptI,
            DynamicList<Vb>& pts
        ) const;


        FoamFoamyMesh_EXPORT void addMasterAndSlavePoints
        (
            const DynamicList<point>& masterPoints,
            const DynamicList<indexedVertexEnum::vertexType>& masterPointsTypes,
            const Map<DynamicList<autoPtr<plane>>>& masterPointReflections,
            DynamicList<Vb>& pts,
            const label ptI
        ) const;

        //- Helper function for conforming to feature points
        FoamFoamyMesh_EXPORT void createMasterAndSlavePoints
        (
            const extendedFeatureEdgeMesh& feMesh,
            const label ptI,
            DynamicList<Vb>& pts
        ) const;

        FoamFoamyMesh_EXPORT void createMixedFeaturePoints(DynamicList<Vb>& pts) const;

        //- Create the points that will conform to the feature
        FoamFoamyMesh_EXPORT void createFeaturePoints(DynamicList<Vb>& pts);


    public:

        //- Runtime type information
        ClassName("featurePointConformer");


        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT explicit featurePointConformer
        (
            const conformalVoronoiMesh& foamyHexMesh
        );

        //- Disallow default bitwise copy construction
        featurePointConformer(const featurePointConformer&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~featurePointConformer();


        // Member Functions

            // Access

                //- Return the feature point vertices for insertion into the
                //  triangulation.
        inline const List<Vb>& featurePointVertices() const;

        //- Return the feature point pair table
        inline const pointPairs<Delaunay>& featurePointPairs() const;


        // Edit

            //- Distribute the feature point vertices according to the
            //  supplied background mesh
        FoamFoamyMesh_EXPORT void distribute(const backgroundMeshDecomposition& decomposition);

        //- Reindex the feature point pairs using the map.
        FoamFoamyMesh_EXPORT void reIndexPointPairs(const Map<label>& oldToNewIndices);


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const featurePointConformer&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <featurePointConformerI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_featurePointConformer_Header
