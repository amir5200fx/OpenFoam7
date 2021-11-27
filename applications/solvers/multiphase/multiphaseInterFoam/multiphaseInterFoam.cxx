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
    multiphaseInterFoam

Description
    Solver for n incompressible fluids which captures the interfaces and
    includes surface-tension and contact-angle effects for each phase, with
    optional mesh motion and mesh topology changes.

    Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <multiphaseMixture.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>

#include <turbulentTransportModel.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <CorrectPhi.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>
#include <initContinuityErrs.lxx>
#include <createDyMControls.lxx>

#include "createFields.lxx"

#include "../../../interFoam/interFoam/initCorrectPhi.lxx"
#include <createUfIfPresent.lxx>

    turbulence->validate();

#include <CourantNo.lxx>
#include <setInitialDeltaT.lxx>

    const surfaceScalarField& rhoPhi(mixture.rhoPhi());

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readDyMControls.lxx>
#include <CourantNo.lxx>
#include "../../../VoF/alphaCourantNo.lxx"
#include <setDeltaT.lxx>

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            if (pimple.firstPimpleIter() || moveMeshOuterCorrectors)
            {
                scalar timeBeforeMeshUpdate = runTime.elapsedCpuTime();

                mesh.update();

                if (mesh.changing())
                {
                    Info << "Execution time for mesh.update() = "
                        << runTime.elapsedCpuTime() - timeBeforeMeshUpdate
                        << " s" << endl;

                    gh = (g & mesh.C()) - ghRef;
                    ghf = (g & mesh.Cf()) - ghRef;

                    MRF.update();

                    if (correctPhi)
                    {
                        // Calculate absolute flux
                        // from the mapped surface velocity
                        phi = mesh.Sf() & Uf();

#include "../../../interFoam/interFoam/correctPhi.lxx"

                        // Make the flux relative to the mesh motion
                        fvc::makeRelative(phi, U);
                    }

                    mixture.correct();

                    if (checkMeshCourantNo)
                    {
#include <meshCourantNo.lxx>
                    }
                }
            }

            mixture.solve();
            rho = mixture.rho();

#include "../../../interFoam/interFoam/UEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "../../../interFoam/interFoam/pEqn.lxx"
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
