/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
    moveDynamicMesh

Description
    Mesh motion and topological mesh changes utility.

\*---------------------------------------------------------------------------*/

#include "checkGeometry.hxx"

#include <argList.hxx>
#include <Time.hxx>
#include <dynamicFvMesh.hxx>
#include <pimpleControl.hxx>
#include <vtkSurfaceWriter.hxx>
#include <cyclicAMIPolyPatch.hxx>
#include <PatchTools.hxx>


using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <addRegionOption.lxx>
    argList::addBoolOption
    (
        "checkAMI",
        "check AMI weights"
    );

#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createNamedDynamicFvMesh.lxx>

    const bool checkAMI = args.optionFound("checkAMI");

    if (checkAMI)
    {
        Info << "Writing VTK files with weights of AMI patches." << nl << endl;
    }

    pimpleControl pimple(mesh);

    bool moveMeshOuterCorrectors
    (
        pimple.dict().lookupOrDefault<Switch>("moveMeshOuterCorrectors", false)
    );

    while (runTime.loop())
    {
        Info << "Time = " << runTime.timeName() << endl;

        while (pimple.loop())
        {
            if (pimple.firstPimpleIter() || moveMeshOuterCorrectors)
            {
                mesh.update();
            }
        }

        mesh.checkMesh(true);

        if (checkAMI)
        {
            writeAMIWeightsSums(mesh);
        }

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
