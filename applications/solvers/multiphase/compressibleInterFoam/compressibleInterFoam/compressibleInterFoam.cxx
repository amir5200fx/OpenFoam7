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
    compressibleInterFoam

Description
    Solver for 2 compressible, non-isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach,
    with optional mesh motion and mesh topology changes including adaptive
    re-meshing.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Either mixture or two-phase transport modelling may be selected.  In the
    mixture approach a single laminar, RAS or LES model is selected to model the
    momentum stress.  In the Euler-Euler two-phase approach separate laminar,
    RAS or LES selected models are selected for each of the phases.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>
#include <compressibleInterPhaseTransportModel.hxx>

#include <PhaseCompressibleTurbulenceModel.hxx>
#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <CMULES.hxx>
#include <EulerDdtScheme.hxx>
#include <localEulerDdtScheme.hxx>
#include <CrankNicolsonDdtScheme.hxx>
#include <subCycle.hxx>

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

#include <CourantNo.lxx>
#include <setInitialDeltaT.lxx>
#include <createUfIfPresent.lxx>

    volScalarField& p = mixture.p();
    volScalarField& T = mixture.T();
    const volScalarField& psi1 = mixture.thermo1().psi();
    const volScalarField& psi2 = mixture.thermo2().psi();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readDyMControls.lxx>

        // Store divU from the previous mesh so that it can be mapped
        // and used in correctPhi to ensure the corrected phi has the
        // same divergence
        volScalarField divU("divU0", fvc::div(fvc::absolute(phi, U)));

        if (LTS)
        {
#include <../../../VoF/setRDeltaT.lxx>
        }
        else
        {
#include <CourantNo.lxx>
#include <../../../VoF/alphaCourantNo.lxx>
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

#include "correctPhi.lxx"

                        // Make the fluxes relative to the mesh motion
                        fvc::makeRelative(phi, U);
                    }

                    mixture.correct();

                    if (checkMeshCourantNo)
                    {
#include <meshCourantNo.lxx>
                    }
                }
            }

            divU = fvc::div(fvc::absolute(phi, U));

#include <alphaControls.lxx>
#include "compressibleAlphaEqnSubCycle.lxx"

            turbulence.correctPhasePhi();

#include "UEqn.lxx"
#include "TEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence.correct();
            }
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
