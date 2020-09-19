#include <test.hxx>

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

Description

\*---------------------------------------------------------------------------*/

#include <primitiveFields.hxx>
#include <cpuTime.hxx>
#include <IOstreams.hxx>
#include <OFstream.hxx>

void tnbLib::Test_vectorSpeed()
{
	const label nIter = 100;
	const label size = 1000000;

	Info << "Initialising fields" << endl;

	vectorField
		vf1(size, vector::one),
		vf2(size, vector::one),
		vf3(size, vector::one),
		vf4(size);

	Info << "Done\n" << endl;

	{
		cpuTime executionTime;

		Info << "vectorField algebra" << endl;

		for (int j = 0; j < nIter; j++)
		{
			vf4 = vf1 + vf2 - vf3;
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << vf4[1] << endl << endl;
	}
}