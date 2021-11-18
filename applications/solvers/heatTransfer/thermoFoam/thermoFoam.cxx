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
    thermoFoam

Description
    Solver for energy transport and thermodynamics on a frozen flow field.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <rhoThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <LESModel.hxx>
#include <radiationModel.hxx>
#include <fvOptions.hxx>
#include <simpleControl.hxx>
#include <pimpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#define NO_CONTROL
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>

#include "createFields.lxx"

    const volScalarField& alphaEff = talphaEff();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nEvolving thermodynamics\n" << endl;

    if (mesh.solutionDict().found("SIMPLE"))
    {
        simpleControl simple(mesh);

        while (simple.loop(runTime))
        {
            Info << "Time = " << runTime.timeName() << nl << endl;

            while (simple.correctNonOrthogonal())
            {
#include "EEqn.lxx"
            }

            Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
                << "  ClockTime = " << runTime.elapsedClockTime() << " s"
                << nl << endl;

            runTime.write();
        }
    }
    else
    {
        pimpleControl pimple(mesh);

        while (runTime.run())
        {
            runTime++;

            Info << "Time = " << runTime.timeName() << nl << endl;

            while (pimple.correctNonOrthogonal())
            {
#include "EEqn.lxx"
            }

            Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
                << "  ClockTime = " << runTime.elapsedClockTime() << " s"
                << nl << endl;

            runTime.write();
        }
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
