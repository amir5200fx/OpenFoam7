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
    dnsFoam

Description
    Direct numerical simulation solver for boxes of isotropic turbulence.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <force.hxx>
#include <Kmesh.hxx>
#include <UOprocess.hxx>
#include <fft.hxx>
#include <calcEk.hxx>
#include <graph.hxx>
#include <writeFile.hxx>
#include <pisoControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMeshNoClear.lxx>
#include <createControl.lxx>
#include "createFields.lxx"
#include <initContinuityErrs.lxx>

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Info << nl << "Starting time loop" << endl;

	while (runTime.loop())
	{
		Info << "Time = " << runTime.timeName() << nl << endl;

		force.primitiveFieldRef() = ReImSum
		(
			fft::reverseTransform
			(
				K / (mag(K) + 1.0e-6) ^ forceGen.newField(), K.nn()
			)
		);

#include "globalProperties.lxx"

		fvVectorMatrix UEqn
		(
			fvm::ddt(U)
			+ fvm::div(phi, U)
			- fvm::laplacian(nu, U)
			==
			force
		);

		solve(UEqn == -fvc::grad(p));


		// --- PISO loop
		while (piso.correct())
		{
			volScalarField rAU(1.0 / UEqn.A());
			surfaceScalarField rAUf("rAUf", fvc::interpolate(rAU));
			volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p));
			surfaceScalarField phiHbyA
			(
				"phiHbyA",
				fvc::flux(HbyA)
				+ rAUf * fvc::ddtCorr(U, phi)
			);

			// Update the pressure BCs to ensure flux consistency
			constrainPressure(p, U, phiHbyA, rAUf);

			fvScalarMatrix pEqn
			(
				fvm::laplacian(rAUf, p) == fvc::div(phiHbyA)
			);

			pEqn.solve();

			phi = phiHbyA - pEqn.flux();

#include <continuityErrs.lxx>

			U = HbyA - rAU * fvc::grad(p);
			U.correctBoundaryConditions();
		}

		runTime.write();

		if (runTime.writeTime())
		{
			calcEk(U, K).write
			(
				runTime.path()
				/ functionObjects::writeFile::outputPrefix
				/ "graphs"
				/ runTime.timeName(),
				"Ek",
				runTime.graphFormat()
			);
		}

		Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
			<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
			<< nl << endl;
	}

	Info << "End\n" << endl;

	return 0;
}


// ************************************************************************* //
