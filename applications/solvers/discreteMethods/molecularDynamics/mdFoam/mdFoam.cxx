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
    mdFoam

Description
    Molecular dynamics solver for fluid dynamics.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <md.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#define NO_CONTROL
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include "createFields.lxx"
#include <temperatureAndPressureVariables.lxx>

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    label nAveragingSteps = 0;

    Info << "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        nAveragingSteps++;

        Info << "Time = " << runTime.timeName() << endl;

        molecules.evolve();

#include <meanMomentumEnergyAndNMols.lxx>
#include <temperatureAndPressure.lxx>

        runTime.write();

        if (runTime.writeTime())
        {
            nAveragingSteps = 0;
        }

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
