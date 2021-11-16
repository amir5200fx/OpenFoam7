#pragma once
#ifndef _indexedVertexOps_Header
#define _indexedVertexOps_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

Namespace
    CGAL::indexedVertexOps

Description

SourceFiles
    indexedVertexOpsTemplates.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace CGAL
{

    /*---------------------------------------------------------------------------*\
                        Namespace indexedVertexOps Declaration
    \*---------------------------------------------------------------------------*/

    namespace indexedVertexOps
    {

        //- Return the target cell size from that stored on a pair of Delaunay vertices,
        //  using a mean function.
        template<class VertexType>
        tnbLib::scalar averageCellSize(const VertexType& vA, const VertexType& vB);


        template<class VertexType>
        inline bool uninitialised(const VertexType& v);

    } // End namespace indexedVertexOps


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace CGAL

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <indexedVertexOpsI.hxx>

#endif // !_indexedVertexOps_Header
