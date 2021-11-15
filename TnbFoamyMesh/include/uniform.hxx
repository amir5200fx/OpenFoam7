#pragma once
#ifndef _uniform_Header
#define _uniform_Header

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
    tnbLib::uniform

Description

SourceFiles
    uniform.C

\*---------------------------------------------------------------------------*/

#include <cellSizeFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class uniform Declaration
    \*---------------------------------------------------------------------------*/

    class uniform
        :
        public cellSizeFunction
    {

    private:

        // Private Data


    public:

        //- Runtime type information
        /*TypeName("uniform");*/
        static const char* typeName_() { return "uniform"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };

        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT uniform
        (
            const dictionary& initialPointsDict,
            const searchableSurface& surface,
            const scalar& defaultCellSize,
            const labelList regionIndices
        );


        //- Destructor
        virtual ~uniform()
        {}


        // Member Functions

        FoamFoamyMesh_EXPORT virtual bool sizeLocations
        (
            const pointIndexHit& hitPt,
            const vector& n,
            pointField& shapePts,
            scalarField& shapeSizes
        ) const;

        //- Modify scalar argument to the cell size specified by function.
        //  Return a boolean specifying if the function was used, i.e. false if
        //  the point was not in range of the surface for a spatially varying
        //  size.
        FoamFoamyMesh_EXPORT virtual bool cellSize
        (
            const point& pt,
            scalar& size
        ) const;

        //- Adapt local cell size. Return true if anything changed.
        FoamFoamyMesh_EXPORT virtual bool setCellSize
        (
            const pointField& pts
        );
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_uniform_Header
