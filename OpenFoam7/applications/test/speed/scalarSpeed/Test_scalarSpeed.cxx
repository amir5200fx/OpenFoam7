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
#include <Random.hxx>
#include <cpuTime.hxx>
#include <IOstreams.hxx>
#include <OFstream.hxx>

void tnbLib::Test_scalarSpeed()
{
	Info << "Initialising fields" << endl;

	const label nIter = 100;
	const label size = 10000000;
	const label rndAddrSkip = 40;
	const label redFac = 6;
	const label redSize = size / redFac;
	Random genAddr(100);

	double* f1 = new double[size];
	double* f2 = new double[size];
	double* f3 = new double[size];
	double* f4 = new double[size];
	double* fr = new double[redSize];
	label* addr = new label[size];
	label* redAddr = new label[size];
	label* redAddr2 = new label[size];

	for (label i = 0; i < size; i++)
	{
		f1[i] = 1.0;
		f2[i] = 1.0;
		f3[i] = 1.0;
		addr[i] = i;
		redAddr[i] = i / redFac;
		redAddr2[i] = (size - i - 1) / redFac;
	}

	for (label i = 0; i < size; i += rndAddrSkip)
	{
		addr[i] = genAddr.sampleAB<label>(0, size);
	}

	for (label i = 0; i < redSize; i++)
	{
		fr[i] = 1.0;
	}

	Info << "Done\n" << endl;

	{
		Info << "Single loop combined operation (expression templates)"
			<< endl;

		cpuTime executionTime;

		for (int j = 0; j < nIter; j++)
		{
			for (label i = 0; i < size; i++)
			{
				f4[i] = f1[i] + f2[i] - f3[i];
			}
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << f4[1] << endl << endl;
	}

	{
		Info << "Single loop combined operation with indirect addressing"
			<< endl;

		cpuTime executionTime;

		for (int j = 0; j < nIter; j++)
		{
			for (label i = 0; i < size; i++)
			{
				f4[addr[i]] = f1[addr[i]] + f2[addr[i]] - f3[addr[i]];
			}
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << f4[1] << endl << endl;
	}

	{
		Info << "Single loop reduction operation"
			<< endl;

		cpuTime executionTime;
		label redOffset = (size - 1) / redFac;

		for (int j = 0; j < nIter; j++)
		{
			for (label i = 0; i < size; i++)
			{
				label j = i / redFac;
				fr[j] += f1[i];
				fr[redOffset - j] -= f2[i];
			}
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << fr[1] << endl << endl;
	}

	{
		Info << "Single loop reduction operation with indirect addressing"
			<< endl;

		cpuTime executionTime;

		for (int j = 0; j < nIter; j++)
		{
			for (label i = 0; i < size; i++)
			{
				fr[redAddr[i]] += f1[i];
				fr[redAddr2[i]] -= f2[i];
			}
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << fr[1] << endl << endl;
	}

	{
		Info << "Separate loops ?= operations" << endl;

		cpuTime executionTime;

		for (int j = 0; j < nIter; j++)
		{
			for (label i = 0; i < size; i++)
			{
				f4[i] = f1[i];
			}
			for (label i = 0; i < size; i++)
			{
				f4[i] += f2[i];
			}
			for (label i = 0; i < size; i++)
			{
				f4[i] -= f3[i];
			}
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << f4[1] << endl << endl;
	}

	{
		Info << "OpenFOAM field algebra" << endl;

		scalarField
			sf1(size, 1.0),
			sf2(size, 1.0),
			sf3(size, 1.0),
			sf4(size);

		cpuTime executionTime;

		for (int j = 0; j < nIter; j++)
		{
			// sf4 = sf1 + sf2 - sf3;
			sf4 = sf1;
			sf4 += sf2;
			sf4 -= sf3;
		}

		Info << "ExecutionTime = "
			<< executionTime.elapsedCpuTime()
			<< " s\n" << endl;

		Snull << sf4[1] << endl << endl;
	}
}