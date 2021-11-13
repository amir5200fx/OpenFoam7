#pragma once
#ifndef _mirrorFvMesh_Header
#define _mirrorFvMesh_Header

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
    tnbLib::mirrorFvMesh

Description

SourceFiles
    mirrorFvMesh.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                           Class mirrorFvMesh Declaration
    \*---------------------------------------------------------------------------*/

    class mirrorFvMesh
        :
        public fvMesh
    {
        // Private Data

            //- Mirror dictionary
        IOdictionary mirrorMeshDict_;

        //- Mirrored mesh
        autoPtr<fvMesh> mirrorMeshPtr_;

        //- Cell map
        autoPtr<labelList> cellMapPtr_;

        //- Point map
        autoPtr<labelList> pointMapPtr_;


    public:


        // Constructors

            //- Construct from IOobject
        mirrorFvMesh(const IOobject& io, const word& dictName);

        //- Disallow default bitwise copy construction
        mirrorFvMesh(const mirrorFvMesh&) = delete;


        //- Destructor
        ~mirrorFvMesh();


        // Member Functions

            //- Return reference to mirror mesh
        const fvMesh& mirrorMesh() const
        {
            return mirrorMeshPtr_();
        }

        //- Mirrored to original cell
        const labelList& cellMap() const
        {
            return cellMapPtr_();
        }

        //- Mirrored to original point
        const labelList& pointMap() const
        {
            return pointMapPtr_();
        }


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const mirrorFvMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_mirrorFvMesh_Header