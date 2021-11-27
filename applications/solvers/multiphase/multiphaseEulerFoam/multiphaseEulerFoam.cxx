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
    multiphaseEulerFoam

Description
    Solver for a system of many incompressible fluid phases including
    heat-transfer.

\*---------------------------------------------------------------------------*/

#include <phaseModel.hxx>

#include <fvCFD.hxx>
#include <multiphaseSystem.hxx>

#include <dragModel.hxx>
#include <heatTransferModel.hxx>
#include <singlePhaseTransportModel.hxx>
#include <turbulentTransportModel.hxx>
#include <pimpleControl.hxx>
#include <IOMRFZoneList.hxx>
#include <CorrectPhi.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>

#include "createFields.lxx"

#include <initContinuityErrs.lxx>
#include <createTimeControls.lxx>

#include "correctPhi.lxx"
#include "CourantNo.lxx"

#include <setInitialDeltaT.lxx>

    scalar slamDampCoeff
    (
        fluid.lookupOrDefault<scalar>("slamDampCoeff", 1)
    );

    dimensionedScalar maxSlamVelocity
    (
        "maxSlamVelocity",
        dimVelocity,
        fluid.lookupOrDefault<scalar>("maxSlamVelocity", great)
    );

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>
#include "CourantNo.lxx"
#include <setDeltaT.lxx>

        runTime++;
        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            turbulence->correct();
            fluid.solve();
            rho = fluid.rho();
#include "zonePhaseVolumes.lxx"

            //#include "TEqns.hxx>
#include "UEqns.lxx"

// --- Pressure corrector loop
            while (pimple.correct())
            {
#include "pEqn.lxx"
            }

#include "DDtU.lxx"
        }

        runTime.write();

        Info << "ExecutionTime = "
            << runTime.elapsedCpuTime()
            << " s\n\n" << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
