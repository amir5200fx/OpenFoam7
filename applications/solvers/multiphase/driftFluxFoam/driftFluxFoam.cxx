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
    driftFluxFoam

Description
    Solver for 2 incompressible fluids using the mixture approach with the
    drift-flux approximation for relative motion of the phases.

    Used for simulating the settling of the dispersed phase and other similar
    separation problems.

\*---------------------------------------------------------------------------*/

#include "incompressibleTwoPhaseInteractingMixture.hxx"

#include <fvCFD.hxx>
#include <CMULES.hxx>
#include <subCycle.hxx>

#include "relativeVelocityModel.hxx"

#include <turbulenceModel.hxx>
#include <CompressibleTurbulenceModel.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <gaussLaplacianScheme.hxx>
#include <uncorrectedSnGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>
#include <createTimeControls.lxx>

#include "createFields.lxx"

#include <initContinuityErrs.lxx>

    volScalarField& alpha2(mixture.alpha2());
    const dimensionedScalar& rho1 = mixture.rhod();
    const dimensionedScalar& rho2 = mixture.rhoc();
    relativeVelocityModel& UdmModel(UdmModelPtr());

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>
#include <CourantNo.lxx>
#include <setDeltaT.lxx>

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "alphaControls.lxx"

            UdmModel.correct();

#include "alphaEqnSubCycle.lxx"

            mixture.correct();

#include "UEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
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
