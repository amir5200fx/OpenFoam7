#pragma once
#ifndef _rayShooting_Header
#define _rayShooting_Header

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
    tnbLib::rayShooting

Description

SourceFiles
    rayShooting.C

\*---------------------------------------------------------------------------*/

#include <initialPointsMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                            Class rayShooting Declaration
    \*---------------------------------------------------------------------------*/

    class rayShooting
        :
        public initialPointsMethod
    {

    private:

        // Private Data

            //- Should the initial positions be randomised
        Switch randomiseInitialGrid_;

        //- Randomise the initial positions by fraction of the initialCellSize_
        scalar randomPerturbationCoeff_;


        // Private Member Functions

        FoamFoamyMesh_EXPORT void splitLine
        (
            const line<point, point>& l,
            const scalar& pert,
            DynamicList<Vb::Point>& initialPoints
        ) const;


    public:

        //- Runtime type information
        TypeName("rayShooting");

        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT rayShooting
        (
            const dictionary& initialPointsDict,
            const Time& runTime,
            Random& rndGen,
            const conformationSurfaces& geometryToConformTo,
            const cellShapeControl& cellShapeControls,
            const autoPtr<backgroundMeshDecomposition>& decomposition
        );


        //- Destructor
        virtual ~rayShooting()
        {}


        // Member Functions

            //- Return the initial points for the conformalVoronoiMesh
        FoamFoamyMesh_EXPORT virtual List<Vb::Point> initialPoints() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_rayShooting_Header
