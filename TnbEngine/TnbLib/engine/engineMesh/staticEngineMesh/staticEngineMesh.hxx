#pragma once
#ifndef _staticEngineMesh_Header
#define _staticEngineMesh_Header

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
    tnbLib::staticEngineMesh

Description
    tnbLib::staticEngineMesh

SourceFiles
    staticEngineMesh.C

\*---------------------------------------------------------------------------*/

#include <engineMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class staticEngineMesh Declaration
    \*---------------------------------------------------------------------------*/

    class staticEngineMesh
        :
        public engineMesh
    {
    public:

        //- Runtime type information
        TypeName("static");


        // Constructors

            //- Construct from IOobject
        staticEngineMesh(const IOobject& io);

        //- Disallow default bitwise copy construction
        staticEngineMesh(const staticEngineMesh&) = delete;


        //- Destructor
        ~staticEngineMesh();


        // Member Functions

            // Edit

        void move();


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const staticEngineMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_staticEngineMesh_Header