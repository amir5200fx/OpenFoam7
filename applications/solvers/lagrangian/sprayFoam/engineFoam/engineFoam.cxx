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
    engineFoam

Description
    Transient solver for compressible, turbulent engine flow with a spray
    particle cloud.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <engineTime.hxx>
#include <engineMesh.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <basicSprayCloud.hxx>
#include <psiReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <radiationModel.hxx>
#include <SLGThermo.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#define CREATE_TIME createEngineTime.lxx
#define CREATE_MESH createEngineMesh.lxx
#define CREATE_FIELDS ../sprayFoam/createFields.lxx

#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createEngineTime.lxx>
#include <createEngineMesh.lxx>
#include <createControl.lxx>
#include <readEngineTimeControls.lxx>

 #include "../sprayFoam/createFields.lxx"
 #include "../sprayFoam/createFieldRefs.lxx"

#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>
#include <initContinuityErrs.lxx>
#include <createRhoUfIfPresent.lxx>

#include "startSummary.lxx"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readEngineTimeControls.lxx>
#include <compressibleCourantNo.lxx>
#include <setDeltaT.lxx>

        runTime++;

        Info << "Engine time = " << runTime.theta() << runTime.unit() << endl;

        mesh.move();

        parcels.evolve();

#include <rhoEqn.lxx>

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {

#include "../sprayFoam/UEqn.lxx"
#include "../sprayFoam/YEqn.lxx"
#include "../sprayFoam/EEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "../sprayFoam/pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

#include "logSummary.lxx"

        rho = thermo.rho();

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
