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
    foamMeshToFluent

Description
    Writes out the OpenFOAM mesh in Fluent mesh format.

\*---------------------------------------------------------------------------*/

#include "fluentFvMesh.hxx"

#include <argList.hxx>
#include <Time.hxx>


using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
    argList::noParallel();
#include <setRootCase.lxx>
#include <createTime.lxx>

    Info << "Create mesh for time = "
        << runTime.timeName() << nl << endl;

    fluentFvMesh mesh
    (
        IOobject
        (
            fluentFvMesh::defaultRegion,
            runTime.constant(),
            runTime
        )
    );

    mesh.writeFluentMesh();

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
