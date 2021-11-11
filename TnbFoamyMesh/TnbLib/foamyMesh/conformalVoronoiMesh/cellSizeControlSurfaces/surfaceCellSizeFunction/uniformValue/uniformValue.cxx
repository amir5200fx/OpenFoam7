/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include <uniformValue.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(uniformValue, 0);
    addToRunTimeSelectionTable
    (
        surfaceCellSizeFunction,
        uniformValue,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformValue::uniformValue
(
    const dictionary& cellSizeFunctionDict,
    const searchableSurface& surface,
    const scalar& defaultCellSize
)
    :
    surfaceCellSizeFunction
    (
        typeName,
        cellSizeFunctionDict,
        surface,
        defaultCellSize
    ),
    surfaceCellSize_
    (
        readScalar(coeffsDict().lookup("surfaceCellSizeCoeff"))* defaultCellSize
    )
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::uniformValue::interpolate
(
    const point& pt,
    const label index
) const
{
    return surfaceCellSize_;
}


// ************************************************************************* //
