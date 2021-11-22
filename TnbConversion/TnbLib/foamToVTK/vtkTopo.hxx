#pragma once
#ifndef _vtkTopo_Header
#define _vtkTopo_Header

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
    tnbLib::vtkTopo

Description
    Polyhedral cell decomposition for VTK.

SourceFiles
    vtkTopo.C

\*---------------------------------------------------------------------------*/

#include <Conversion_Module.hxx>

#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class polyMesh;

    /*---------------------------------------------------------------------------*\
                               Class vtkTopo Declaration
    \*---------------------------------------------------------------------------*/

    class vtkTopo
    {
        // Private Data

        const polyMesh& mesh_;

        //- Vertices per cell (including added cells) in vtk ordering
        labelListList vertLabels_;

        //- Cell types (including added cells) in vtk numbering
        labelList cellTypes_;

        labelList addPointCellLabels_;

        labelList superCells_;


    public:

        // Public static data

             //- Equivalent to enumeration in "vtkCellType.h"
        enum vtkTypes
        {
            VTK_TRIANGLE = 5,
            VTK_POLYGON = 7,
            VTK_QUAD = 9,

            VTK_TETRA = 10,
            VTK_HEXAHEDRON = 12,
            VTK_WEDGE = 13,
            VTK_PYRAMID = 14,
            VTK_POLYHEDRON = 42
        };

        //- Enable/disable polyhedron decomposition. Default = true
        static bool decomposePoly;


        // Constructors

            //- Construct from components
        vtkTopo(const polyMesh&);

        //- Disallow default bitwise copy construction
        vtkTopo(const vtkTopo&) = delete;


        // Member Functions

            // Access

        const labelListList& vertLabels() const
        {
            return vertLabels_;
        }

        const labelList& cellTypes() const
        {
            return cellTypes_;
        }

        const labelList& addPointCellLabels() const
        {
            return addPointCellLabels_;
        }

        const labelList& superCells() const
        {
            return superCells_;
        }


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const vtkTopo&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_vtkTopo_Header
