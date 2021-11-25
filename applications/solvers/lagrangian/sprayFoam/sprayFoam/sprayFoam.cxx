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
    sprayFoam

Description
    Transient solver for compressible, turbulent flow with a spray particle
    cloud, with optional mesh motion and mesh topology changes.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <turbulenceModel.hxx>
#include <basicSprayCloud.hxx>
#include <psiReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <radiationModel.hxx>
#include <SLGThermo.hxx>
#include <pimpleControl.hxx>
#include <CorrectPhi.hxx>
#include <fvOptions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>
#include <createDyMControls.lxx>

#include "createFields.lxx"
#include "createFieldRefs.lxx"

#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>
#include <initContinuityErrs.lxx>
#include <createRhoUfIfPresent.lxx>

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readDyMControls.lxx>

        // Store divrhoU from the previous mesh so that it can be mapped
        // and used in correctPhi to ensure the corrected phi has the
        // same divergence
        autoPtr<volScalarField> divrhoU;
        if (correctPhi)
        {
            divrhoU = new volScalarField
            (
                "divrhoU",
                fvc::div(fvc::absolute(phi, rho, U))
            );
        }

#include <compressibleCourantNo.lxx>
#include <setDeltaT.lxx>

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // Store momentum to set rhoUf for introduced faces.
        autoPtr<volVectorField> rhoU;
        if (rhoUf.valid())
        {
            rhoU = new volVectorField("rhoU", rho * U);
        }

        // Store the particle positions
        parcels.storeGlobalPositions();

        // Do any mesh changes
        mesh.update();

        if (mesh.changing())
        {
            MRF.update();

            if (correctPhi)
            {
                // Calculate absolute flux from the mapped surface velocity
                phi = mesh.Sf() & rhoUf();

#include "../../../compressible/rhoPimpleFoam/correctPhi.lxx"

                // Make the fluxes relative to the mesh-motion
                fvc::makeRelative(phi, rho, U);
            }

            if (checkMeshCourantNo)
            {
#include <meshCourantNo.lxx>
            }
        }

        parcels.evolve();

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
