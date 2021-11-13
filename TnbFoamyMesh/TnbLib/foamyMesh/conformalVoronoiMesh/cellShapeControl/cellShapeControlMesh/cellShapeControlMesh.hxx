#pragma once
#ifndef _cellShapeControlMesh_Header
#define _cellShapeControlMesh_Header
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
    tnbLib::cellShapeControlMesh

Description

SourceFiles
    cellShapeControlMeshI.H
    cellShapeControlMesh.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <Time.hxx>
#include <scalar.hxx>
#include <point.hxx>
#include <tensor.hxx>
#include <triad.hxx>
#include <fileName.hxx>
#include <searchableSurfaces.hxx>
#include <conformationSurfaces.hxx>
#include <DistributedDelaunayMesh.hxx>
#include <CGALTriangulation3Ddefs.hxx>
#include <backgroundMeshDecomposition.hxx>
#include <boundBox.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class cellSizeAndAlignmentControls;

    /*---------------------------------------------------------------------------*\
                          Class cellShapeControlMesh Declaration
    \*---------------------------------------------------------------------------*/

    class cellShapeControlMesh
        :
        public DistributedDelaunayMesh<CellSizeDelaunay>
    {
    public:

        typedef CellSizeDelaunay::Cell_handle      Cell_handle;
        typedef CellSizeDelaunay::Vertex_handle    Vertex_handle;
        typedef CellSizeDelaunay::Point            Point;


    private:

        // Private Data

        const Time& runTime_;

        mutable Cell_handle oldCellHandle_;

        const scalar defaultCellSize_;


    public:

        //- Runtime type information
        ClassName("cellShapeControlMesh");

        //- Return the mesh sub-directory name (usually "cellShapeControlMesh")
        static FoamFoamyMesh_EXPORT word meshSubDir;


        // Constructors

        FoamFoamyMesh_EXPORT explicit cellShapeControlMesh(const Time& runTime);

        //- Disallow default bitwise copy construction
        cellShapeControlMesh(const cellShapeControlMesh&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~cellShapeControlMesh();


        // Member Functions

            // Query

        const Time& time() const
        {
            return runTime_;
        }

        //- Calculate and return the barycentric coordinates for
        //  interpolating quantities on the background mesh
        FoamFoamyMesh_EXPORT void barycentricCoords
        (
            const tnbLib::point& pt,
            barycentric& bary,
            Cell_handle& ch
        ) const;

        FoamFoamyMesh_EXPORT boundBox bounds() const;


        // Edit

        FoamFoamyMesh_EXPORT label removePoints();

        //- Get the centres of all the tets
        tmp<pointField> cellCentres() const;

        inline Vertex_handle insert
        (
            const tnbLib::point& pt,
            const scalar& size,
            const triad& alignment,
            const tnbLib::indexedVertexEnum::vertexType type = Vb::vtInternal
        );

        inline Vertex_handle insertFar
        (
            const tnbLib::point& pt
        );

        FoamFoamyMesh_EXPORT void distribute(const backgroundMeshDecomposition& decomposition);

        FoamFoamyMesh_EXPORT tensorField dumpAlignments() const;

        FoamFoamyMesh_EXPORT void writeTriangulation();

        FoamFoamyMesh_EXPORT void write() const;

        FoamFoamyMesh_EXPORT label estimateCellCount
        (
            const autoPtr<backgroundMeshDecomposition>& decomposition
        ) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellShapeControlMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cellShapeControlMeshI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif

// ************************************************************************* //
