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
    interMixingFoam

Description
    Solver for 3 incompressible fluids, two of which are miscible, using a VOF
    method to capture the interface, with optional mesh motion and mesh topology
    changes including adaptive re-meshing.

\*---------------------------------------------------------------------------*/
#include "immiscibleIncompressibleThreePhaseMixture.hxx"

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <CMULES.hxx>
#include <localEulerDdtScheme.hxx>
#include <subCycle.hxx>
#include <turbulentTransportModel.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <CorrectPhi.hxx>
#include <fvcSmooth.hxx>

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

#include "../interFoam/initCorrectPhi.lxx"
#include <createUfIfPresent.lxx>

    turbulence->validate();

    if (!LTS)
    {
#include <readTimeControls.lxx>
#include <CourantNo.lxx>
#include <setInitialDeltaT.lxx>
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readDyMControls.lxx>

        if (LTS)
        {
#include "../../VoF/setRDeltaT.lxx"
        }
        else
        {
#include <CourantNo.lxx>
#include "../../VoF/alphaCourantNo.lxx"
#include <setDeltaT.lxx>


        }

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            if (pimple.firstPimpleIter() || moveMeshOuterCorrectors)
            {
                mesh.update();

                if (mesh.changing())
                {
                    gh = (g & mesh.C()) - ghRef;
                    ghf = (g & mesh.Cf()) - ghRef;

                    MRF.update();

                    if (correctPhi)
                    {
                        // Calculate absolute flux
                        // from the mapped surface velocity
                        phi = mesh.Sf() & Uf();

#include "../interFoam/correctPhi.lxx"

                        // Make the flux relative to the mesh motion
                        fvc::makeRelative(phi, U);

                        mixture.correct();
                    }

                    if (checkMeshCourantNo)
                    {
#include <meshCourantNo.lxx>
                    }
                }
            }

#include "alphaControls.lxx"
#include "alphaEqnSubCycle.lxx"

            mixture.correct();

#include "../interFoam/UEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "../interFoam/pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

#include <continuityErrs.lxx>

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
