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
    PDRFoam

Description
    Solver for compressible premixed/partially-premixed combustion with
    turbulence modelling.

    Combusting RANS code using the b-Xi two-equation model.
    Xi may be obtained by either the solution of the Xi transport
    equation or from an algebraic expression.  Both approaches are
    based on Gulder's flame speed correlation which has been shown
    to be appropriate by comparison with the results from the
    spectral model.

    Strain effects are incorporated directly into the Xi equation
    but not in the algebraic approximation.  Further work need to be
    done on this issue, particularly regarding the enhanced removal rate
    caused by flame compression.  Analysis using results of the spectral
    model will be required.

    For cases involving very lean Propane flames or other flames which are
    very strain-sensitive, a transport equation for the laminar flame
    speed is present.  This equation is derived using heuristic arguments
    involving the strain time scale and the strain-rate at extinction.
    the transport velocity is the same as that for the Xi equation.

    For large flames e.g. explosions additional modelling for the flame
    wrinkling due to surface instabilities may be applied.

    PDR (porosity/distributed resistance) modelling is included to handle
    regions containing blockages which cannot be resolved by the mesh.

    The fields used by this solver are:

    betav:  Volume porosity
    Lobs:   Average diameter of obstacle in cell (m)
    Aw:     Obstacle surface area per unit volume (1/m)
    CR:     Drag tensor (1/m)
    CT:     Turbulence generation parameter (1/m)
    Nv:     Number of obstacles in cell per unit volume (m^-2)
    nsv:    Tensor whose diagonal indicates the number to subtract from
            Nv to get the number of obstacles crossing the flow in each
            direction.

\*---------------------------------------------------------------------------*/

#include <XiModel.hxx>
#include <fvCFD.hxx>
#include <psiuReactionThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <laminarFlameSpeed.hxx>
#include <PDRDragModel.hxx>
#include <ignition.hxx>
#include <Switch.hxx>
#include <bound.hxx>
#include <pimpleControl.hxx>
#include <fvOptions.hxx>
#include <LESdelta.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>

#include "readCombustionProperties.lxx"

#include <readGravitationalAcceleration.lxx>

#include "createFields.lxx"
#include "createFieldRefs.lxx"

#include <initContinuityErrs.lxx>
#include <createTimeControls.lxx>
#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>

    turbulence->validate();
    scalar StCoNum = 0.0;

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
#include <readTimeControls.lxx>
#include <compressibleCourantNo.lxx>

#include "setDeltaT.lxx"

        runTime++;
        Info << "\n\nTime = " << runTime.timeName() << endl;

#include "rhoEqn.lxx"

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
#include "UEqn.lxx"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
#include "bEqn.lxx"
#include "ftEqn.lxx"
#include "EauEqn.lxx"
#include "EaEqn.lxx"

                if (!ign.ignited())
                {
                    thermo.heu() == thermo.he();
                }

#include "pEqn.lxx"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

        runTime.write();

        Info << "\nExecutionTime = "
            << runTime.elapsedCpuTime()
            << " s\n" << endl;
    }

    Info << "\n end\n";

    return 0;
}


// ************************************************************************* //
