#pragma once
#ifndef _cellAspectRatioControl_Header
#define _cellAspectRatioControl_Header
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
    tnbLib::cellAspectRatioControl

Description

SourceFiles
    cellAspectRatioControl.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <dictionary.hxx>
#include <vector.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


    /*---------------------------------------------------------------------------*\
                         Class cellAspectRatioControl Declaration
    \*---------------------------------------------------------------------------*/

    class cellAspectRatioControl
    {
        // Private Data

        const dictionary aspectRatioDict_;

        const scalar aspectRatio_;

        vector aspectRatioDirection_;


    public:

        // Constructors

            //- Construct from dictionary
        FoamFoamyMesh_EXPORT cellAspectRatioControl(const dictionary& motionDict);

        //- Disallow default bitwise copy construction
        cellAspectRatioControl(const cellAspectRatioControl&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~cellAspectRatioControl();


        // Member Functions

            // Query

        FoamFoamyMesh_EXPORT void updateCellSizeAndFaceArea
        (
            vector& alignmentDir,
            scalar& targetFaceArea,
            scalar& targetCellSize
        ) const;

        FoamFoamyMesh_EXPORT void updateDeltaVector
        (
            const vector& alignmentDir,
            const scalar targetCellSize,
            const scalar rABMag,
            vector& delta
        ) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellAspectRatioControl&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
