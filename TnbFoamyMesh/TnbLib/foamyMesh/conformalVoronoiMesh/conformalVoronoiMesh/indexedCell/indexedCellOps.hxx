#pragma once
#ifndef _indexedCellOps_Header
#define _indexedCellOps_Header

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
    CGAL::indexedCellOps

Description

SourceFiles
    indexedCellOpsTemplates.C

\*---------------------------------------------------------------------------*/
#include <FoamyMesh_Module.hxx>
#include <label.hxx>
#include <FixedList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace CGAL
{

    /*---------------------------------------------------------------------------*\
                         Namespace indexedCellOps Declaration
    \*---------------------------------------------------------------------------*/

    namespace indexedCellOps
    {

        //- Does the Dual vertex form part of a processor patch
        template<class CellType>
        tnbLib::label dualVertexMasterProc(const CellType& c);

        template<class CellType>
        tnbLib::FixedList<tnbLib::label, 4> processorsAttached(const CellType& c);

    } // End namespace indexedCellOps


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace CGAL

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_indexedCellOps_Header
