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
    cavitatingFoam

Description
    Transient cavitation code based on the homogeneous equilibrium model
    from which the compressibility of the liquid/vapour "mixture" is obtained,
    with optional mesh motion and mesh topology changes.

    Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <barotropicCompressibilityModel.hxx>
#include <incompressibleTwoPhaseMixture.hxx>
#include <turbulentTransportModel.hxx>
#include <CorrectPhi.hxx>
#include <pimpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>

#include "createControls.lxx"
#include "createFields.lxx"

#include <createUfIfPresent.lxx>

#include "createPcorrTypes.lxx"
#include "CourantNo.lxx"
#include "setInitialDeltaT.lxx"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include "readControls.lxx"

        {
#include "CourantNo.lxx"
#include "setDeltaT.lxx"

            runTime++;

            Info << "Time = " << runTime.timeName() << nl << endl;

            // Do any mesh changes
            mesh.update();

            if (mesh.changing() && correctPhi)
            {
                // Calculate absolute flux from the mapped surface velocity
                phi = mesh.Sf() & Uf();

#include "correctPhi.lxx"

                // Make the flux relative to the mesh motion
                fvc::makeRelative(phi, U);
            }
        }

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "rhoEqn.lxx"
#include "alphavPsi.lxx"
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
