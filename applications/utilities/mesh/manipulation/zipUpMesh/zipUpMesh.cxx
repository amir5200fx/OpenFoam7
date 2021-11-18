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

Application
    zipUpMesh

Description
    Reads in a mesh with hanging vertices and zips up the cells to guarantee
    that all polyhedral cells of valid shape are closed.

    Meshes with hanging vertices may occur as a result of split
    hex mesh conversion or integration or coupled math face pairs.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <Time.hxx>
#include <polyMesh.hxx>
#include <polyMeshZipUpCells.hxx>
#include <boolList.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <addRegionOption.lxx>

#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createNamedPolyMesh.lxx>

    if (polyMeshZipUpCells(mesh))
    {
        Info << "Writing zipped-up polyMesh to " << mesh.facesInstance() << endl;
        mesh.write();
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //