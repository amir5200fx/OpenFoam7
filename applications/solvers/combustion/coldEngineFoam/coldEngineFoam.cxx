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
    engineFoam

Description
    Solver for cold-flow in internal combustion engines.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <engineTime.hxx>
#include <engineMesh.hxx>
#include <psiThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <OFstream.hxx>
#include <fvOptions.hxx>
#include <pimpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#define CREATE_TIME createEngineTime.lxx
#define CREATE_MESH createEngineMesh.lxx
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createEngineTime.lxx>
#include <createEngineMesh.lxx>
#include <createControl.lxx>

#include "createFields.lxx"
#include "createFieldRefs.lxx"

#include <createRhoUf.lxx>
#include <initContinuityErrs.lxx>
#include <readEngineTimeControls.lxx>
#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>

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

        Info << "Engine time = " << runTime.theta() << runTime.unit()
            << endl;

        mesh.move();

#include <rhoEqn.lxx>

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "../../compressible/rhoPimpleFoam/UEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "../../compressible/rhoPimpleFoam/EEqn.lxx"
#include "../../compressible/rhoPimpleFoam/pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

        runTime.write();

#include "logSummary.lxx"

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
