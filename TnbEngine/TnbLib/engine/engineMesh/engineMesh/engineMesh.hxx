#pragma once
#ifndef _engineMesh_Header
#define _engineMesh_Header

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
    tnbLib::engineMesh

Description
    tnbLib::engineMesh

SourceFiles
    engineMesh.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <engineTime.hxx>
#include <fvMesh.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class engineMesh Declaration
    \*---------------------------------------------------------------------------*/

    class engineMesh
        :
        public fvMesh
    {
    protected:

        // Protected data

        const engineTime& engineDB_;

        label pistonIndex_;
        label linerIndex_;
        label cylinderHeadIndex_;

        dimensionedScalar deckHeight_;
        dimensionedScalar pistonPosition_;


    public:

        //- Runtime type information
        TypeName("engineMesh");


        // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            engineMesh,
            IOobject,
            (const IOobject& io),
            (io)
        );


        // Constructors

            //- Construct from objectRegistry, and read/write options
        explicit engineMesh(const IOobject& io);

        //- Disallow default bitwise copy construction
        engineMesh(const engineMesh&) = delete;


        // Selectors

            //- Select null constructed
        static autoPtr<engineMesh> New(const IOobject& io);


        //- Destructor
        virtual ~engineMesh();


        // Member Functions

            // Edit

        virtual void move() = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const engineMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_engineMesh_Header
