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
	SRFPimpleFoam

Description
	Large time-step transient solver for incompressible, turbulent flow in a
	single rotating frame.

	Turbulence modelling is generic, i.e. laminar, RAS or LES may be selected.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <singlePhaseTransportModel.hxx>
#include <turbulentTransportModel.hxx>
#include <pimpleControl.hxx>
#include <SRFModel.hxx>
#include <fvOptions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>
#include <createControl.lxx>
#include <createTimeControls.lxx>
#include "createFields.lxx"
#include <initContinuityErrs.lxx>

	turbulence->validate();

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Info << "\nStarting time loop\n" << endl;

	while (runTime.run())
	{
#include <readTimeControls.lxx>
#include <CourantNo.lxx>
#include <setDeltaT.lxx>

		runTime++;

		Info << "Time = " << runTime.timeName() << nl << endl;

		// --- Pressure-velocity PIMPLE corrector loop
		while (pimple.loop())
		{
#include "UrelEqn.lxx"

			// --- Pressure corrector loop
			while (pimple.correct())
			{
#include "pEqn.lxx"
			}

			// Update the absolute velocity
			U = Urel + SRF->U();

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