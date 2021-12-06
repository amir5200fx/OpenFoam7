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
    twoPhaseEulerFoam

Description
    Solver for a system of 2 compressible fluid phases with one phase
    dispersed, e.g. gas bubbles in a liquid including heat-transfer.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <twoPhaseSystem.hxx>
#include <PhaseCompressibleTurbulenceModel.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <fixedValueFvsPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>

#include "createFields.lxx"
#include "createFieldRefs.lxx"

#include <createTimeControls.lxx>

#include "CourantNos.lxx"
#include <setInitialDeltaT.lxx>

    Switch faceMomentum
    (
        pimple.dict().lookupOrDefault<Switch>("faceMomentum", false)
    );

    Switch implicitPhasePressure
    (
        mesh.solverDict(alpha1.name()).lookupOrDefault<Switch>
        (
            "implicitPhasePressure", false
            )
    );

#include "createDDtU_pUf.lxx"
#include "createDDtU_pU.lxx"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>

#include "CourantNos.lxx"

#include <setDeltaT.lxx>

        runTime++;
        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            fluid.solve();
            fluid.correct();

#include "contErrs.lxx"

            if (faceMomentum)
            {
#include "UEqns_pUf.lxx"
#include "EEqns.lxx"
#include "pEqn_pUf.lxx"
#include "DDtU_pUf.lxx"
            }
            else
            {
#include "UEqns_pU.lxx"
#include "EEqns.lxx"
#include "pEqn_pU.lxx"
#include "DDtU_pU.lxx"
            }

            if (pimple.turbCorr())
            {
                fluid.correctTurbulence();
            }
        }

#include <write.lxx>

        Info << "ExecutionTime = "
            << runTime.elapsedCpuTime()
            << " s\n\n" << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
