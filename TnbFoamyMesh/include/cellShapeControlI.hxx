#pragma once
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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::cellShapeControlMesh&
tnbLib::cellShapeControl::shapeControlMesh()
{
    return shapeControlMesh_;
}


inline const tnbLib::cellShapeControlMesh&
tnbLib::cellShapeControl::shapeControlMesh() const
{
    return shapeControlMesh_;
}


inline const tnbLib::scalar& tnbLib::cellShapeControl::defaultCellSize() const
{
    return defaultCellSize_;
}


inline const tnbLib::cellAspectRatioControl&
tnbLib::cellShapeControl::aspectRatio() const
{
    return aspectRatio_;
}


inline const tnbLib::cellSizeAndAlignmentControls&
tnbLib::cellShapeControl::sizeAndAlignment() const
{
    return sizeAndAlignment_;
}


inline const tnbLib::scalar& tnbLib::cellShapeControl::minimumCellSize() const
{
    return minimumCellSize_;
}


// ************************************************************************* //
