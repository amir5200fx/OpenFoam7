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
    simpleReactingParcelFoam

Description
    Steady state solver for compressible, turbulent flow with reacting,
    multiphase particle clouds and optional sources/constraints.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <basicReactingMultiphaseCloud.hxx>
#include <rhoReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <radiationModel.hxx>
#include <IOporosityModelList.hxx>
#include <fvOptions.hxx>
#include <SLGThermo.hxx>
#include <simpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>

#include "createFields.lxx"

#include "../../../combustion/reactingFoam/createFieldRefs.lxx"
#include <initContinuityErrs.lxx>

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (simple.loop(runTime))
    {
        Info << "Time = " << runTime.timeName() << nl << endl;

        parcels.evolve();

        // --- Pressure-velocity SIMPLE corrector loop
        {
#include "UEqn.lxx"
#include "YEqn.lxx"
#include "EEqn.lxx"
#include "pEqn.lxx"
        }

        turbulence->correct();

        runTime.write();

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
