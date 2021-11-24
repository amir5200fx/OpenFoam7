/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpentnbLib: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://opentnbLib.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpentnbLib Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpentnbLib.

    OpentnbLib is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpentnbLib is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpentnbLib.  If not, see <http://www.gnu.org/licenses/>.

Application
    coalChemistrytnbLib

Description
    Transient solver for compressible, turbulent flow, with coal and limestone
    particle clouds, an energy source, and combustion.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <basicThermoCloud.hxx>
#include <coalCloud.hxx>
#include <psiReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <fvOptions.hxx>
#include <radiationModel.hxx>
#include <SLGThermo.hxx>
#include <pimpleControl.hxx>
#include <pressureControl.hxx>
#include <localEulerDdtScheme.hxx>
#include <fvcSmooth.hxx>

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
#include "createFieldRefs.lxx"

#include <initContinuityErrs.lxx>

    turbulence->validate();

    if (!LTS)
    {
#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>

        if (LTS)
        {
#include "setRDeltaT.lxx"
        }
        else
        {
#include <compressibleCourantNo.lxx>
#include "setDeltaT.lxx"
        }

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        rhoEffLagrangian = coalParcels.rhoEff() + limestoneParcels.rhoEff();
        pDyn = 0.5 * rho * magSqr(U);

        coalParcels.evolve();

        limestoneParcels.evolve();

#include "rhoEqn.lxx"

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "UEqn.lxx"
#include "YEqn.lxx"
#include "EEqn.lxx"

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
