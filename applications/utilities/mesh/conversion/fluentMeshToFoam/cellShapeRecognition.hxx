#pragma once
#ifndef _cellShapeRecognition_Header
#define _cellShapeRecognition_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

InClass
    tnbLib::cellShapeRecognition

Description

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <cellShape.hxx>
#include <cellModeller.hxx>
#include <faceList.hxx>
#include <PtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    cellShape extrudedTriangleCellShape
    (
        const label cellIndex,
        const labelList& faceLabels,
        const faceList& faces,
        const labelList& owner,
        const labelList& neighbour,
        const label pointOffset,
        faceList& frontAndBackFaces
    );


    cellShape extrudedQuadCellShape
    (
        const label cellIndex,
        const labelList& faceLabels,
        const faceList& faces,
        const labelList& owner,
        const labelList& neighbour,
        const label pointOffset,
        faceList& frontAndBackFaces
    );


    cellShape create3DCellShape
    (
        const label cellIndex,
        const labelList& faceLabels,
        const faceList& faces,
        const labelList& owner,
        const labelList& neighbour,
        const label fluentCellModelID
    );


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellShapeRecognition_Header
