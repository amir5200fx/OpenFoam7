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
    compressibleInterFilmFoam

Description
    Solver for 2 compressible, non-isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach
    and surface film modelling.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

    Turbulence modelling is generic, i.e.  laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <PhaseCompressibleTurbulenceModel.hxx>
#include <fvCFD.hxx>
#include <CMULES.hxx>
#include <EulerDdtScheme.hxx>
#include <localEulerDdtScheme.hxx>
#include <CrankNicolsonDdtScheme.hxx>
#include <subCycle.hxx>
#include <twoPhaseMixtureThermo.hxx>
#include <compressibleInterPhaseTransportModel.hxx>
#include <pimpleControl.hxx>
#include <SLGThermo.hxx>
#include <surfaceFilmModel.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <fvcSmooth.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{

#define CREATE_FIELDS ../../compressibleInterFoam/createFields.lxx
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>
#include <createTimeControls.lxx>
#include "../../compressibleInterFoam/createFields.lxx"

#include "createSurfaceFilmModel.lxx"

    volScalarField& p = mixture.p();
    volScalarField& T = mixture.T();
    const volScalarField& psi1 = mixture.thermo1().psi();
    const volScalarField& psi2 = mixture.thermo2().psi();

    regionModels::surfaceFilmModel& surfaceFilm = tsurfaceFilm();

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
#include <readTimeControls.lxx>

        if (LTS)
        {
#include "../../../VoF/setRDeltaT.lxx"
        }
        else
        {
#include <CourantNo.lxx>
#include "../../../VoF/alphaCourantNo.lxx"
#include <setDeltaT.lxx>
        }

        runTime++;

        Info << "Time = " << runTime.timeName() << nl << endl;

        surfaceFilm.evolve();

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include <alphaControls.lxx>
#include "../../compressibleInterFoam/compressibleAlphaEqnSubCycle.lxx"

            turbulence.correctPhasePhi();

            volScalarField::Internal Srho(surfaceFilm.Srho());
            contErr -= posPart(Srho);

#include "../../compressibleInterFoam/UEqn.lxx"
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
