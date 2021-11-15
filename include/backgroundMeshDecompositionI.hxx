#pragma once
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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::fvMesh& tnbLib::backgroundMeshDecomposition::mesh() const
{
    return mesh_;
}


const tnbLib::indexedOctree<tnbLib::treeDataBPatch>&
tnbLib::backgroundMeshDecomposition::tree() const
{
    return bFTreePtr_();
}


const tnbLib::treeBoundBox&
tnbLib::backgroundMeshDecomposition::procBounds() const
{
    return allBackgroundMeshBounds_[Pstream::myProcNo()];
}


const tnbLib::labelList& tnbLib::backgroundMeshDecomposition::cellLevel() const
{
    return meshCutter_.cellLevel();
}


const tnbLib::labelList& tnbLib::backgroundMeshDecomposition::pointLevel() const
{
    return meshCutter_.pointLevel();
}


const tnbLib::decompositionMethod&
tnbLib::backgroundMeshDecomposition::decomposer() const
{
    return decomposerPtr_();
}


// ************************************************************************* //
