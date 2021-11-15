#pragma once
#ifndef _layeredEngineMesh_Header
#define _layeredEngineMesh_Header

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
    tnbLib::layeredEngineMesh

Description
    tnbLib::layeredEngineMesh

SourceFiles
    layeredEngineMesh.C

\*---------------------------------------------------------------------------*/

#include <engineMesh.hxx>
#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class layeredEngineMesh Declaration
    \*---------------------------------------------------------------------------*/

    class layeredEngineMesh
        :
        public engineMesh
    {
        // Private Data

        dimensionedScalar pistonLayers_;


    public:

        //- Runtime type information
        /*TypeName("layered");*/
        static const char* typeName_() { return "layered"; }
        static FoamEngine_EXPORT const ::tnbLib::word typeName;
        static FoamEngine_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Constructors

            //- Construct from IOobject
        FoamEngine_EXPORT layeredEngineMesh(const IOobject& io);

        //- Disallow default bitwise copy construction
        layeredEngineMesh(const layeredEngineMesh&) = delete;


        //- Destructor
        FoamEngine_EXPORT ~layeredEngineMesh();


        // Member Functions

            // Edit

        FoamEngine_EXPORT void move();


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const layeredEngineMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_layeredEngineMesh_Header
