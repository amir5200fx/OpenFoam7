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
	laplacianFoam

Description
	Solves a simple Laplace equation, e.g. for thermal diffusion in a solid.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <fvOptions.hxx>
#include <simpleControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#include <setRootCaseLists.lxx>

#include <createTime.lxx>
#include <createMesh.lxx>

	simpleControl simple(mesh);

//#include "createFields.lxx"

	Info << "Reading field T\n" << endl;

	volScalarField T
	(
		IOobject
		(
			"T",
			runTime.timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	);


	Info << "Reading transportProperties\n" << endl;

	IOdictionary transportProperties
	(
		IOobject
		(
			"transportProperties",
			runTime.constant(),
			mesh,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	);


	Info << "Reading diffusivity DT\n" << endl;

	dimensionedScalar DT
	(
		transportProperties.lookup("DT")
	);

//#include <createFvOptions.lxx>

	fv::options& fvOptions(fv::options::New(mesh));

	if (!fvOptions.optionList::size())
	{
		Info << "No finite volume options present" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	Info << "\nCalculating temperature distribution\n" << endl;

	while (simple.loop(runTime))
	{
		Info << "Time = " << runTime.timeName() << nl << endl;

		while (simple.correctNonOrthogonal())
		{
			fvScalarMatrix TEqn
			(
				fvm::ddt(T) - fvm::laplacian(DT, T)
				==
				fvOptions(T)
			);

			fvOptions.constrain(TEqn);
			TEqn.solve();
			fvOptions.correct(T);
		}

#include "write.lxx"

		Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
			<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
			<< nl << endl;
	}

	Info << "End\n" << endl;

	return 0;
}


// ************************************************************************* //