#pragma once
#ifndef _fvMotionSolverEngineMesh_Header
#define _fvMotionSolverEngineMesh_Header

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
    tnbLib::fvMotionSolverEngineMesh

Description
    tnbLib::fvMotionSolverEngineMesh

SourceFiles
    fvMotionSolverEngineMesh.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <engineMesh.hxx>
#include <velocityComponentLaplacianFvMotionSolver.hxx>
#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class fvMotionSolverEngineMesh Declaration
    \*---------------------------------------------------------------------------*/

    class fvMotionSolverEngineMesh
        :
        public engineMesh
    {
        // Private Data

        dimensionedScalar pistonLayers_;

        //- Mesh-motion solver to solve for the "z" component of the cell-centre
        //  displacements
        velocityComponentLaplacianFvMotionSolver motionSolver_;


    public:

        //- Runtime type information
        /*TypeName("fvMotionSolver");*/
        static const char* typeName_() { return "fvMotionSolver"; }
        static FoamEngine_EXPORT const ::tnbLib::word typeName;
        static FoamEngine_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Constructors

            //- Construct from IOobject
        FoamEngine_EXPORT fvMotionSolverEngineMesh(const IOobject& io);

        //- Disallow default bitwise copy construction
        fvMotionSolverEngineMesh(const fvMotionSolverEngineMesh&) = delete;


        //- Destructor
        FoamEngine_EXPORT ~fvMotionSolverEngineMesh();


        // Member Functions

            // Edit

        FoamEngine_EXPORT void move();


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const fvMotionSolverEngineMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_fvMotionSolverEngineMesh_Header
