#pragma once
#ifndef _wallDependentModelTwoPhase_Header
#define _wallDependentModelTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::wallDependentModel

Description
    A class which provides on-demand creation and caching of wall distance and
    wall normal fields for use by multiple models.

SourceFiles
    wallDependentModel.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class wallDependentModel Declaration
    \*---------------------------------------------------------------------------*/

    class wallDependentModel
    {
        // Private Data

            //- Reference to the mesh
        const fvMesh& mesh_;


    public:

        // Constructors

            //- Construct from a mesh
        wallDependentModel(const fvMesh& mesh);

        //- Disallow default bitwise copy construction
        wallDependentModel(const wallDependentModel&) = delete;


        //- Destructor
        virtual ~wallDependentModel();

        // Member Functions

            // Return the wall distance, creating and storing it if necessary
        const volScalarField& yWall() const;

        // Return the wall normal, creating and storing it if necessary
        const volVectorField& nWall() const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const wallDependentModel&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallDependentModelTwoPhase_Header
