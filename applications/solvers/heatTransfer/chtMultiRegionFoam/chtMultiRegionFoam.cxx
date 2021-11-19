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
    chtMultiRegionFoam

Description
    Solver for steady or transient fluid flow and solid heat conduction, with
    conjugate heat transfer between regions, buoyancy effects, turbulence,
    reactions and radiation modelling.

\*---------------------------------------------------------------------------*/

#include "compressibleCourantNo.hxx"
#include "solidRegionDiffNo.hxx"

#include <fvCFD.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <rhoReactionThermo.hxx>
#include <CombustionModelTemplate.hxx>
#include <fixedGradientFvPatchFields.hxx>
#include <regionProperties.hxx>

#include <solidThermo.hxx>
#include <radiationModel.hxx>
#include <fvOptions.hxx>
#include <coordinateSystem.hxx>
#include <pimpleMultiRegionControl.hxx>
#include <pressureControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
using namespace tnbLib;

int main(int argc, char* argv[])
{
#define NO_CONTROL
#define CREATE_MESH createMeshesPostProcess.lxx
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include "createMeshes.lxx"
#include "createFields.lxx"
#include "initContinuityErrs.lxx"
    pimpleMultiRegionControl pimples(fluidRegions, solidRegions);
#include "createFluidPressureControls.lxx"
#include "createTimeControls.lxx"
#include "readSolidTimeControls.lxx"
#include "compressibleMultiRegionCourantNo.lxx"
#include "solidRegionDiffusionNo.lxx"
#include "setInitialMultiRegionDeltaT.lxx"


    while (pimples.run(runTime))
    {
#include <readTimeControls.lxx>
#include "readSolidTimeControls.lxx"

#include "compressibleMultiRegionCourantNo.lxx"
#include "solidRegionDiffusionNo.lxx"
#include "setMultiRegionDeltaT.lxx"

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        // --- PIMPLE loop
        while (pimples.loop())
        {
            forAll(fluidRegions, i)
            {
                Info << "\nSolving for fluid region "
                    << fluidRegions[i].name() << endl;
#include "setRegionFluidFields.lxx"
#include "solveFluid.lxx"
            }

            forAll(solidRegions, i)
            {
                Info << "\nSolving for solid region "
                    << solidRegions[i].name() << endl;
#include "setRegionSolidFields.lxx"
#include "solveSolid.lxx"
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
