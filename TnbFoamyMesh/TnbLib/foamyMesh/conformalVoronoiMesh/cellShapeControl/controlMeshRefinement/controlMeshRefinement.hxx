#pragma once
#ifndef _controlMeshRefinement_Header
#define _controlMeshRefinement_Header

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
    tnbLib::controlMeshRefinement

Description

SourceFiles
    controlMeshRefinementI.H
    controlMeshRefinement.C
    controlMeshRefinementIO.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <cellShapeControl.hxx>
#include <cellShapeControlMesh.hxx>
#include <cellSizeAndAlignmentControls.hxx>
#include <conformationSurfaces.hxx>
#include <backgroundMeshDecomposition.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                       Class controlMeshRefinement Declaration
    \*---------------------------------------------------------------------------*/

    class controlMeshRefinement
    {
        // Private Data

        const cellShapeControl& shapeController_;

        cellShapeControlMesh& mesh_;

        const cellSizeAndAlignmentControls& sizeControls_;

        const conformationSurfaces& geometryToConformTo_;


        // Private Member Functions

        FoamFoamyMesh_EXPORT scalar calcFirstDerivative
        (
            const tnbLib::point& a,
            const scalar& cellSizeA,
            const tnbLib::point& b,
            const scalar& cellSizeB
        ) const;

        scalar calcSecondDerivative
        (
            const tnbLib::point& a,
            const scalar& cellSizeA,
            const tnbLib::point& midPoint,
            const scalar& cellSizeMid,
            const tnbLib::point& b,
            const scalar& cellSizeB
        ) const
        {
            return (cellSizeA - 2 * cellSizeMid + cellSizeB) / magSqr((a - b) / 2);
        }


        FoamFoamyMesh_EXPORT bool detectEdge
        (
            const tnbLib::point& startPt,
            const tnbLib::point& endPt,
            pointHit& pointFound,
            const scalar tolSqr,
            const scalar secondDerivTolSqr
        ) const;

        FoamFoamyMesh_EXPORT pointHit findDiscontinuities(const linePointRef& l) const;


    public:

        //- Runtime type information
        ClassName("controlMeshRefinement");


        // Constructors

            //- Construct null
        FoamFoamyMesh_EXPORT controlMeshRefinement(cellShapeControl& shapeController);

        //- Disallow default bitwise copy construction
        controlMeshRefinement(const controlMeshRefinement&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~controlMeshRefinement();


        // Member Functions

            // Edit

        FoamFoamyMesh_EXPORT void initialMeshPopulation
        (
            const autoPtr<backgroundMeshDecomposition>& decomposition
        );

        FoamFoamyMesh_EXPORT label refineMesh
        (
            const autoPtr<backgroundMeshDecomposition>& decomposition
        );


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const controlMeshRefinement&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_controlMeshRefinement_Header
