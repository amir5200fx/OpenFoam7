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
	rhoPimpleFoam

Description
	Transient solver for turbulent flow of compressible fluids for HVAC and
	similar applications, with optional mesh motion and mesh topology changes.

	Uses the flexible PIMPLE (PISO-SIMPLE) solution for time-resolved and
	pseudo-transient simulations.

\*---------------------------------------------------------------------------*/

#include <Base_Module.hxx>
#include <DynamicMesh_Module.hxx>
#include <FiniteVolume_Module.hxx>
#include <FvMesh_Module.hxx>
#include <ThermophysicalModels_Module.hxx>
#include <TransportModels_Module.hxx>
#include <Turbulence_Module.hxx>
#include <FunctionObjects_Module.hxx>

#include <fvCFD.hxx>
#include <dynamicFvMesh.hxx>
#include <fluidThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <pimpleControl.hxx>
#include <pressureControl.hxx>
#include <CorrectPhi.hxx>
#include <fvOptions.hxx>
#include <localEulerDdtScheme.hxx>
#include <fvcSmooth.hxx>

#include <fieldAverage.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createDynamicFvMesh.lxx>
#include <createDyMControls.lxx>
#include <initContinuityErrs.lxx>
#include <createFields.lxx>
#include <createFieldRefs.lxx>
#include <createRhoUfIfPresent.lxx>

	turbulence->validate();

	if (!LTS)
	{
#include <compressibleCourantNo.lxx>
#include <setInitialDeltaT.lxx>
	}
	
	functionObjects::fieldAverage ff("ff", runTime, dictionary());

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Info << "\nStarting time loop\n" << endl;

	while (runTime.run())
	{
#include <readDyMControls.lxx>

		// Store divrhoU from the previous mesh so that it can be mapped
		// and used in correctPhi to ensure the corrected phi has the
		// same divergence
		autoPtr<volScalarField> divrhoU;
		if (correctPhi)
		{
			divrhoU = new volScalarField
			(
				"divrhoU",
				fvc::div(fvc::absolute(phi, rho, U))
			);
		}

		if (LTS)
		{
#include <setRDeltaT.lxx>
		}
		else
		{
#include <compressibleCourantNo.lxx>
#include <setDeltaT.lxx>
		}

		runTime++;

		Info << "Time = " << runTime.timeName() << nl << endl;

		// --- Pressure-velocity PIMPLE corrector loop
		while (pimple.loop())
		{
			if (pimple.firstPimpleIter() || moveMeshOuterCorrectors)
			{
				// Store momentum to set rhoUf for introduced faces.
				autoPtr<volVectorField> rhoU;
				if (rhoUf.valid())
				{
					rhoU = new volVectorField("rhoU", rho*U);
				}

				// Do any mesh changes
				mesh.update();

				if (mesh.changing())
				{
					MRF.update();

					if (correctPhi)
					{
						// Calculate absolute flux
						// from the mapped surface velocity
						phi = mesh.Sf() & rhoUf();

#include <correctPhi.lxx>

						// Make the fluxes relative to the mesh-motion
						fvc::makeRelative(phi, rho, U);
					}

					if (checkMeshCourantNo)
					{
#include <meshCourantNo.lxx>
					}
				}
			}

			if (pimple.firstPimpleIter() && !pimple.simpleRho())
			{
#include <rhoEqn.lxx>
			}

#include <UEqn.lxx>
#include <EEqn.lxx>

			// --- Pressure corrector loop
			while (pimple.correct())
			{
				if (pimple.consistent())
				{
#include <pcEqn.lxx>
				}
				else
				{
#include <pEqn.lxx>
				}
			}

			if (pimple.turbCorr())
			{
				turbulence->correct();
			}
		}

		rho = thermo.rho();

		runTime.write();

		Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
			<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
			<< nl << endl;
	}

	Info << "End\n" << endl;

	return 0;
}


// ************************************************************************* //