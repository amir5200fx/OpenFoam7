#pragma once
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

\*---------------------------------------------------------------------------*/

inline tnbLib::scalar tnbLib::cv2DControls::minCellSize() const
{
    return minCellSize_;
}


inline tnbLib::scalar tnbLib::cv2DControls::minCellSize2() const
{
    return minCellSize2_;
}


inline tnbLib::scalar tnbLib::cv2DControls::maxQuadAngle() const
{
    return maxQuadAngle_;
}


inline tnbLib::scalar tnbLib::cv2DControls::nearWallAlignedDist() const
{
    return nearWallAlignedDist_;
}


inline tnbLib::scalar tnbLib::cv2DControls::nearWallAlignedDist2() const
{
    return nearWallAlignedDist2_;
}


inline tnbLib::Switch tnbLib::cv2DControls::insertSurfaceNearestPointPairs() const
{
    return insertSurfaceNearestPointPairs_;
}


inline tnbLib::Switch tnbLib::cv2DControls::mirrorPoints() const
{
    return mirrorPoints_;
}


inline tnbLib::Switch tnbLib::cv2DControls::insertSurfaceNearPointPairs() const
{
    return insertSurfaceNearPointPairs_;
}


inline tnbLib::Switch tnbLib::cv2DControls::objOutput() const
{
    return objOutput_;
}


inline tnbLib::Switch tnbLib::cv2DControls::meshedSurfaceOutput() const
{
    return meshedSurfaceOutput_;
}


inline tnbLib::Switch tnbLib::cv2DControls::randomiseInitialGrid() const
{
    return randomiseInitialGrid_;
}


inline tnbLib::scalar tnbLib::cv2DControls::randomPerturbation() const
{
    return randomPerturbation_;
}


inline tnbLib::label tnbLib::cv2DControls::maxBoundaryConformingIter() const
{
    return maxBoundaryConformingIter_;
}


inline tnbLib::scalar tnbLib::cv2DControls::span() const
{
    return span_;
}


inline tnbLib::scalar tnbLib::cv2DControls::span2() const
{
    return span2_;
}


inline tnbLib::scalar tnbLib::cv2DControls::minEdgeLen() const
{
    return minEdgeLen_;
}


inline tnbLib::scalar tnbLib::cv2DControls::minEdgeLen2() const
{
    return minEdgeLen2_;
}


inline tnbLib::scalar tnbLib::cv2DControls::maxNotchLen() const
{
    return maxNotchLen_;
}


inline tnbLib::scalar tnbLib::cv2DControls::maxNotchLen2() const
{
    return maxNotchLen2_;
}


inline tnbLib::scalar tnbLib::cv2DControls::minNearPointDist() const
{
    return minNearPointDist_;
}


inline tnbLib::scalar tnbLib::cv2DControls::minNearPointDist2() const
{
    return minNearPointDist2_;
}


inline tnbLib::scalar tnbLib::cv2DControls::ppDist() const
{
    return ppDist_;
}


// ************************************************************************* //
