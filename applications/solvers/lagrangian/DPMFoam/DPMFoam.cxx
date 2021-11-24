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
    DPMFoam

Description
    Transient solver for the coupled transport of a single kinematic particle
    cloud including the effect of the volume fraction of particles on the
    continuous phase, with optional mesh motion and mesh topology changes.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <singlePhaseTransportModel.hxx>
#include <PhaseIncompressibleTurbulenceModel.hxx>
#include <pimpleControl.hxx>
#include <CorrectPhi.hxx>

#ifdef MPPIC
#include "basicKinematicMPPICCloud.hxx>
#define basicKinematicTypeCloud basicKinematicMPPICCloud
#else
#include <basicKinematicCollidingCloud.hxx>
#define basicKinematicTypeCloud basicKinematicCollidingCloud
#endif

using namespace tnbLib;

int main(int argc, char* argv[])
{
    argList::addOption
    (
        "cloudName",
        "name",
        "specify alternative cloud name. default is 'kinematicCloud'"
    );

#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>
#include <createDyMControls.lxx>

#include "createFields.lxx"
#include "createUcfIfPresent.lxx"

#include <initContinuityErrs.lxx>

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readDyMControls.lxx>

#include "CourantNo.lxx"

#include <setDeltaT.lxx>

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // Store the particle positions
        kinematicCloud.storeGlobalPositions();

        mesh.update();

        if (mesh.changing())
        {
            if (correctPhi)
            {
                // Calculate absolute flux from the mapped surface velocity
                phic = mesh.Sf() & Ucf();

#include "correctPhic.lxx"

                // Make the flux relative to the mesh motion
                fvc::makeRelative(phic, Uc);
            }

            if (checkMeshCourantNo)
            {
#include <meshCourantNo.lxx>
            }
        }

        continuousPhaseTransport.correct();
        muc = rhoc * continuousPhaseTransport.nu();

        Info << "Evolving " << kinematicCloud.name() << endl;
        kinematicCloud.evolve();

        // Update continuous phase volume fraction field
        alphac = max(1.0 - kinematicCloud.theta(), alphacMin);
        alphac.correctBoundaryConditions();
        alphacf = fvc::interpolate(alphac);
        alphaPhic = alphacf * phic;

        fvVectorMatrix cloudSU(kinematicCloud.SU(Uc));
        volVectorField cloudVolSUSu
        (
            IOobject
            (
                "cloudVolSUSu",
                runTime.timeName(),
                mesh
            ),
            mesh,
            dimensionedVector
            (
                "0",
                cloudSU.dimensions() / dimVolume,
                Zero
            ),
            zeroGradientFvPatchVectorField::typeName
        );

        cloudVolSUSu.primitiveFieldRef() = -cloudSU.source() / mesh.V();
        cloudVolSUSu.correctBoundaryConditions();
        cloudSU.source() = Zero;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "UcEqn.lxx"

            // --- PISO loop
            while (pimple.correct())
            {
#include "pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                continuousPhaseTurbulence->correct();
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
