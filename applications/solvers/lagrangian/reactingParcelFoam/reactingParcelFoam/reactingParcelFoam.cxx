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
    reactingParcelFoam

Description
    Transient solver for compressible, turbulent flow with a reacting,
    multiphase particle cloud, and surface film modelling.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <basicReactingMultiphaseCloud.hxx>
#include <surfaceFilmModel.hxx>
#include <rhoReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <radiationModel.hxx>
#include <SLGThermo.hxx>
#include <fvOptions.hxx>
#include <pimpleControl.hxx>
#include <pressureControl.hxx>
#include <localEulerDdtScheme.hxx>
#include <fvcSmooth.hxx>

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

#include "setMultiRegionDeltaT.lxx"
        }

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        parcels.evolve();
        surfaceFilm.evolve();

        if (solvePrimaryRegion)
        {
            if (pimple.nCorrPimple() <= 1)
            {
#include "rhoEqn.lxx"
            }

            // --- PIMPLE loop
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
        }

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End" << endl;

    return 0;
}


// ************************************************************************* //
