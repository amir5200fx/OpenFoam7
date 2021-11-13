#pragma once
#ifndef _cellSizeAndAlignmentControls_Header
#define _cellSizeAndAlignmentControls_Header

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
    tnbLib::cellSizeAndAlignmentControls

Description

SourceFiles
    cellSizeAndAlignmentControls.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <dictionary.hxx>
#include <cellSizeAndAlignmentControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                         Class cellSizeAndAlignmentControls Declaration
    \*---------------------------------------------------------------------------*/

    class cellSizeAndAlignmentControls
    {
        // Private Data

        const dictionary& shapeControlDict_;

        const conformationSurfaces& geometryToConformTo_;

        PtrList<cellSizeAndAlignmentControl> controlFunctions_;

        const scalar defaultCellSize_;


        // Private Member Functions

        FoamFoamyMesh_EXPORT bool evalCellSizeFunctions
        (
            const point& pt,
            scalar& minSize,
            label& maxPriority
        ) const;

        //- Disallow default bitwise copy construction
        cellSizeAndAlignmentControls
        (
            const cellSizeAndAlignmentControls&
        ) = delete;

        //- Disallow default bitwise assignment
        void operator=(const cellSizeAndAlignmentControls&) = delete;


    public:

        //- Runtime type information
        ClassName("cellSizeAndAlignmentControls");


        // Constructors

            //- Construct from dictionary
        FoamFoamyMesh_EXPORT cellSizeAndAlignmentControls
        (
            const Time& runTime,
            const dictionary& shapeControlDict,
            const conformationSurfaces& geometryToConformTo,
            const scalar& defaultCellSize
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~cellSizeAndAlignmentControls();


        // Member Functions

            // Access

        inline const PtrList<cellSizeAndAlignmentControl>&
            controlFunctions() const
        {
            return controlFunctions_;
        }

        inline const conformationSurfaces& geometryToConformTo() const
        {
            return geometryToConformTo_;
        }


        // Query

        FoamFoamyMesh_EXPORT scalar cellSize(const point& pt) const;

        FoamFoamyMesh_EXPORT scalar cellSize(const point& pt, label& maxPriority) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_cellSizeAndAlignmentControls_Header
