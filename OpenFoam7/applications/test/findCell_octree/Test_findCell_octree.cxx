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

\*---------------------------------------------------------------------------*/

#include <argList.hxx>
#include <Time.hxx>
#include <fvMesh.hxx>
#include <IStringStream.hxx>
#include <indexedOctree.hxx>
#include <treeDataCell.hxx>
#include <OFstream.hxx>

void tnbLib::Test_findCell_octree(int argc, char* argv[])
{
	argList::validArgs.append("point (x y z)");

#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>

	label nReps = 10000;

	const point sample = args.argRead<point>(1);

	const polyMesh::cellDecomposition decompMode = polyMesh::CELL_TETS;

	treeBoundBox meshBb(mesh.bounds());

	// Calculate typical cell related size to shift bb by.
	scalar typDim = meshBb.avgDim() / (2.0 * tnbLib::cbrt(scalar(mesh.nCells())));

	treeBoundBox shiftedBb
	(
		meshBb.min(),
		meshBb.max() + vector(typDim, typDim, typDim)
	);

	Info << "Mesh" << endl;
	Info << "   bounding box           : " << meshBb << endl;
	Info << "   bounding box (shifted) : " << shiftedBb << endl;
	Info << "   typical dimension      : " << shiftedBb.typDim() << endl;

	Info << "Initialised mesh in "
		<< runTime.cpuTimeIncrement() << " s" << endl;

	{
		indexedOctree<treeDataCell> ioc
		(
			treeDataCell(true, mesh, decompMode), // FACEDIAGTETS),
			shiftedBb,
			10,         // maxLevel
			100,        // leafsize
			10.0        // duplicity
		);

		for (label i = 0; i < nReps - 1; i++)
		{
			if ((i % 100) == 0)
			{
				Info << "indexed octree for " << i << endl;
			}
			ioc.findInside(sample);
		}

		Info << "Point:" << sample << " is in shape "
			<< ioc.findInside(sample)
			<< ", where the possible cells were:" << nl
			<< ioc.findIndices(sample)
			<< endl;

		Info << "Found in indexedOctree " << nReps << " times in "
			<< runTime.cpuTimeIncrement() << " s" << endl;
	}

	{
		for (label i = 0; i < nReps - 1; i++)
		{
			if ((i % 100) == 0)
			{
				Info << "linear search for " << i << endl;
			}
			mesh.findCell(sample, decompMode);
		}

		Info << "Point:" << sample << " is in cell  "
			<< mesh.findCell(sample, decompMode) << endl;

		Info << "Found in mesh.findCell " << nReps << " times in "
			<< runTime.cpuTimeIncrement() << " s" << endl;
	}

	Info << "End\n" << endl;
}