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
    rhoPorousSimpleFoam

Description
    Steady-state solver for turbulent flow of compressible fluids, with
    implicit or explicit porosity treatment and optional sources.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <fluidThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <simpleControl.hxx>
#include <pressureControl.hxx>
#include <fvOptions.hxx>
#include <IOporosityModelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#define CREATE_FIELDS ../rhoSimpleFoam/createFields.lxx
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>
#include "../rhoSimpleFoam/createFields.lxx"
#include "createZones.lxx"
#include <initContinuityErrs.lxx>

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (simple.loop(runTime))
    {
        Info << "Time = " << runTime.timeName() << nl << endl;

        // Pressure-velocity SIMPLE corrector
        {
#include "UEqn.lxx"
#include "../rhoSimpleFoam/EEqn.lxx"
#include "pEqn.lxx"
        }

        turbulence->correct();

        runTime.write();
        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
