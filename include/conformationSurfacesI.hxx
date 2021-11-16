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

const tnbLib::searchableSurfaces& tnbLib::conformationSurfaces::geometry() const
{
    return allGeometry_;
}


const tnbLib::PtrList<tnbLib::extendedFeatureEdgeMesh>&
tnbLib::conformationSurfaces::features() const
{
    return features_;
}


const tnbLib::point& tnbLib::conformationSurfaces::locationInMesh() const
{
    return locationInMesh_;
}


const tnbLib::labelList& tnbLib::conformationSurfaces::surfaces() const
{
    return surfaces_;
}


const tnbLib::List<tnbLib::word>& tnbLib::conformationSurfaces::patchNames() const
{
    return patchNames_;
}


const tnbLib::PtrList<tnbLib::surfaceZonesInfo>&
tnbLib::conformationSurfaces::surfZones() const
{
    return surfZones_;
}


const tnbLib::PtrList<tnbLib::dictionary>&
tnbLib::conformationSurfaces::patchInfo() const
{
    return patchInfo_;
}


const tnbLib::treeBoundBox& tnbLib::conformationSurfaces::globalBounds() const
{
    return globalBounds_;
}


// ************************************************************************* //
