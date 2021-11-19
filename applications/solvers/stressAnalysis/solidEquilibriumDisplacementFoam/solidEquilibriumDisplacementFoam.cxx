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
    solidEquilibriumDisplacementFoam

Description
    Steady-state segregated finite-volume solver of linear-elastic,
    small-strain deformation of a solid body, with optional thermal
    diffusion and thermal stresses.

    Simple linear elasticity structural analysis code.
    Solves for the displacement vector field D, also generating the
    stress tensor field sigma.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#define NO_CONTROL
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>

#include "createControls.lxx"
#include "createFields.lxx"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nCalculating displacement field\n" << endl;

    while (runTime.loop())
    {
        Info << "Iteration: " << runTime.value() << nl << endl;

#include "readSteadyStressFoamControls.lxx"

        solve
        (
            fvm::laplacian(2 * mu + lambda, Dcorr, "laplacian(DD,Dcorr)")
            + fvc::div(sigmaExp + sigmaD)
        );

        D += accFac * Dcorr;

        {
            volTensorField gradDcorr(fvc::grad(Dcorr));

            sigmaExp =
                (lambda - mu) * gradDcorr + mu * gradDcorr.T()
                + (lambda * I) * tr(gradDcorr);

            sigmaD += accFac * (mu * twoSymm(gradDcorr) + (lambda * I) * tr(gradDcorr));
        }

#include "calculateStress.lxx"
#include "kineticEnergyLimiter.lxx"

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
