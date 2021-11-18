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
	pimpleFoam

Description
	Transient solver for incompressible, turbulent flow of Newtonian fluids,
	with optional mesh motion and mesh topology changes.

	Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <singlePhaseTransportModel.hxx>
#include <turbulentTransportModel.hxx>
#include <pimpleControl.hxx>
#include <CorrectPhi.hxx>
#include <fvOptions.hxx>
#include <localEulerDdtScheme.hxx>
#include <fvcSmooth.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>
#include <initContinuityErrs.lxx>
#include <createDyMControls.lxx>
#include "createFields.lxx"
#include <createUfIfPresent.lxx>

	turbulence->validate();

	if (!LTS)
	{
#include "CourantNo.lxx"
#include "setInitialDeltaT.lxx"
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Info << "\nStarting time loop\n" << endl;

	while (runTime.run())
	{
#include <readDyMControls.lxx>

		if (LTS)
		{
#include "setRDeltaT.lxx"
		}
		else
		{
#include "CourantNo.lxx"
#include "setDeltaT.lxx"
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
					MRF.update();

					if (correctPhi)
					{
						// Calculate absolute flux
						// from the mapped surface velocity
						phi = mesh.Sf() & Uf();

#include "correctPhi.lxx"

						// Make the flux relative to the mesh motion
						fvc::makeRelative(phi, U);
					}

					if (checkMeshCourantNo)
					{
#include <meshCourantNo.lxx>
					}
				}
			}

#include "UEqn.lxx"

			// --- Pressure corrector loop
			while (pimple.correct())
			{
#include "pEqn.lxx"
			}

			if (pimple.turbCorr())
			{
				laminarTransport.correct();
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