#pragma once
#ifndef _smoothAlignmentSolver_Header
#define _smoothAlignmentSolver_Header

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
    tnbLib::smoothAlignmentSolver

Description

SourceFiles
    smoothAlignmentSolverI.H
    smoothAlignmentSolver.C
    smoothAlignmentSolverIO.C

\*---------------------------------------------------------------------------*/

#include <cellShapeControlMesh.hxx>
#include <triadField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                       Class smoothAlignmentSolver Declaration
    \*---------------------------------------------------------------------------*/

    class smoothAlignmentSolver
    {
        // Private Data

        cellShapeControlMesh& mesh_;


        // Private Member Functions

        template<class Triangulation, class Type>
        tmp<Field<Type>> filterFarPoints
        (
            const Triangulation& mesh,
            const Field<Type>& field
        );

        template<class Triangulation>
        autoPtr<mapDistribute> buildMap
        (
            const Triangulation& mesh,
            labelListList& pointPoints
        );

        template<class Triangulation>
        autoPtr<mapDistribute> buildReferredMap
        (
            const Triangulation& mesh,
            labelList& indices
        );

        template<class Triangulation>
        tmp<triadField> buildAlignmentField(const Triangulation& mesh);

        template<class Triangulation>
        tmp<pointField> buildPointField(const Triangulation& mesh);

        //- Apply the fixed alignments to the triad
        FoamFoamyMesh_EXPORT void applyBoundaryConditions
        (
            const triad& fixedAlignment,
            triad& t
        ) const;


    public:

        // Constructors

            //- Construct null
        FoamFoamyMesh_EXPORT smoothAlignmentSolver(cellShapeControlMesh& mesh);

        //- Disallow default bitwise copy construction
        smoothAlignmentSolver(const smoothAlignmentSolver&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT ~smoothAlignmentSolver();


        // Member Functions

            // Edit

                //- Smooth the alignments on the mesh
        FoamFoamyMesh_EXPORT void smoothAlignments(const label maxSmoothingIterations);


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const smoothAlignmentSolver&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_smoothAlignmentSolver_Header
