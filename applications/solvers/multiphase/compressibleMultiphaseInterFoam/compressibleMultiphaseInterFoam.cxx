/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
    compressibleMultiphaseInterFoam

Description
    Solver for n compressible, non-isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Turbulence modelling is generic, i.e.  laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <multiphaseMixtureThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <pimpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>
#include <createTimeControls.lxx>

#include "createFields.lxx"

#include <CourantNo.lxx>
#include <setInitialDeltaT.lxx>

    volScalarField& p = mixture.p();
    volScalarField& T = mixture.T();

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>
#include <CourantNo.lxx>
#include <../../../VoF/alphaCourantNo.lxx>
#include <setDeltaT.lxx>

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            mixture.solve();

            solve(fvm::ddt(rho) + fvc::div(mixture.rhoPhi()));

#include "UEqn.lxx"
#include "TEqn.lxx"

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
