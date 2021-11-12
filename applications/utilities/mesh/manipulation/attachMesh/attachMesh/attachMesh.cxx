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
    attachMesh

Description
    Attach topologically detached mesh using prescribed mesh modifiers.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <polyMesh.hxx>
#include <Time.hxx>
#include <attachPolyTopoChanger.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <addOverwriteOption.lxx>
    argList::noParallel();

#include <setRootCase.lxx>
#include <createTime.lxx>
    runTime.functionObjects().off();
#include <createPolyMesh.lxx>
    const word oldInstance = mesh.pointsInstance();

    const bool overwrite = args.optionFound("overwrite");

    if (!overwrite)
    {
        runTime++;
    }

    Info << "Time = " << runTime.timeName() << nl
        << "Attaching sliding interface" << endl;

    attachPolyTopoChanger(mesh).attach();

    if (overwrite)
    {
        mesh.setInstance(oldInstance);
    }
    mesh.write();

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
