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
    uncoupledKinematicParcelFoam

Description
    Transient solver for the passive transport of a single kinematic
    particle cloud, with optional mesh motion and mesh topology changes.

    Uses a pre-calculated velocity field to evolve the cloud.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <singlePhaseTransportModel.hxx>
#include <turbulentTransportModel.hxx>
#include <basicKinematicCollidingCloud.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
    argList::addOption
    (
        "cloudName",
        "name",
        "specify alternative cloud name. default is 'kinematicCloud'"
    );

#define NO_CONTROL
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>

#include "createFields.lxx"

#include <CourantNo.lxx>

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info << "Time = " << runTime.timeName() << nl << endl;

        kinematicCloud.storeGlobalPositions();

        mesh.update();

        if (mesh.changing())
        {
            U.correctBoundaryConditions();
        }

        laminarTransport.correct();

        Info << "Evolving " << kinematicCloud.name() << endl;
        mu = laminarTransport.nu() * rhoInfValue;

        kinematicCloud.evolve();

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
