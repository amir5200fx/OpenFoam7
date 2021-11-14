#pragma once
#ifndef _cellShapeControl_Header
#define _cellShapeControl_Header

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
    tnbLib::cellShapeControl

Description

SourceFiles
    cellShapeControlI.H
    cellShapeControl.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <tensor.hxx>
#include <point.hxx>
#include <primitiveFieldsFwd.hxx>
#include <pointFieldFwd.hxx>
#include <Time.hxx>
#include <searchableSurfaces.hxx>
#include <conformationSurfaces.hxx>
#include <cellAspectRatioControl.hxx>
#include <cellSizeAndAlignmentControls.hxx>
#include <cellShapeControlMesh.hxx>
#include <backgroundMeshDecomposition.hxx>
#include <cvControls.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


    /*---------------------------------------------------------------------------*\
                         Class cellShapeControl Declaration
    \*---------------------------------------------------------------------------*/

    class cellShapeControl
        :
        public dictionary
    {
        // Private Data

        const Time& runTime_;

        const searchableSurfaces& allGeometry_;

        const conformationSurfaces& geometryToConformTo_;

        const scalar defaultCellSize_;

        const scalar minimumCellSize_;

        cellShapeControlMesh shapeControlMesh_;

        cellAspectRatioControl aspectRatio_;

        cellSizeAndAlignmentControls sizeAndAlignment_;


    public:

        //- Runtime type information
       /* ClassName("cellShapeControl");*/
        static const char* typeName_() { return "cellShapeControl"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;


        // Constructors

            //- Construct from dictionary and references to conformalVoronoiMesh and
            //  searchableSurfaces
        FoamFoamyMesh_EXPORT cellShapeControl
        (
            const Time& runTime,
            const cvControls& foamyHexMeshControls,
            const searchableSurfaces& allGeometry,
            const conformationSurfaces& geometryToConformTo
        );

        //- Disallow default bitwise copy construction
        cellShapeControl(const cellShapeControl&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~cellShapeControl();


        // Member Functions

            // Access

        inline const scalar& defaultCellSize() const;

        inline cellShapeControlMesh& shapeControlMesh();

        inline const cellShapeControlMesh& shapeControlMesh() const;

        inline const cellAspectRatioControl& aspectRatio() const;

        inline const cellSizeAndAlignmentControls& sizeAndAlignment() const;

        inline const scalar& minimumCellSize() const;


        // Query

            //- Return the cell size at the given location
        FoamFoamyMesh_EXPORT scalar cellSize(const point& pt) const;

        FoamFoamyMesh_EXPORT scalarField cellSize(const pointField& pts) const;

        //- Return the cell alignment at the given location
        FoamFoamyMesh_EXPORT tensor cellAlignment(const point& pt) const;

        FoamFoamyMesh_EXPORT void cellSizeAndAlignment
        (
            const point& pt,
            scalar& size,
            tensor& alignment
        ) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellShapeControl&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cellShapeControlI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
