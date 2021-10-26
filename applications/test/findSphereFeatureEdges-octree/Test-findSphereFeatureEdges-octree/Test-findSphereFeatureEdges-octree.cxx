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

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <Time.hxx>
#include <fvMesh.hxx>
#include <IStringStream.hxx>
#include <indexedOctree.hxx>
#include <treeDataEdge.hxx>
#include <OFstream.hxx>
#include <extendedFeatureEdgeMesh.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char* argv[])
{

#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>

    fileName sFeatFileName("unit_cube_rotated.extendedFeatureEdgeMesh");

    extendedFeatureEdgeMesh efem
    (
        IOobject
        (
            sFeatFileName,
            runTime.time().constant(),
            "extendedFeatureEdgeMesh",
            runTime.time(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    // Slightly extended bb. Slightly off-centred just so on symmetric
    // geometry there are less face/edge aligned items.
    treeBoundBox bb
    (
        efem.points()
    );

    bb.min() -= point(rootVSmall, rootVSmall, rootVSmall);
    bb.max() += point(rootVSmall, rootVSmall, rootVSmall);

    labelList allEdges(identity(efem.edges().size()));

    indexedOctree<treeDataEdge> edgeTree
    (
        treeDataEdge
        (
            false,          // cachebb
            efem.edges(),        // edges
            efem.points(),       // points
            allEdges        // selected edges
        ),
        bb,     // bb
        8,      // maxLevel
        10,     // leafsize
        3.0     // duplicity
    );

    Info << "Points: " << efem.points() << nl << endl;
    Info << "Edges: " << efem.edges() << nl << endl;

    Info << "Find edge labels within sphere from point (0, 0, 0):" << endl;

    Info << "    Radius = 0            : "
        << edgeTree.findSphere(point(0, 0, 0), 0) << endl;

    Info << "    Radius = 1            : "
        << edgeTree.findSphere(point(0, 0, 0), 1) << endl;

    Info << "    Radius = root(1.5)    : "
        << edgeTree.findSphere(point(0, 0, 0), 1.5) << endl;

    Info << "    Radius = root(2)      : "
        << edgeTree.findSphere(point(0, 0, 0), 2) << endl;

    Info << "    Radius = root(0.5)    : "
        << edgeTree.findSphere(point(1, 0, 0), 0.5) << endl;

    Info << "    Radius = root(0.25)   : "
        << edgeTree.findSphere(point(0, 0, 0.5), 0.25) << endl;

    treeBoundBox tbb(point(0, 0, 0), point(0.1, 0.1, 0.1));
    Info << "    Box = " << tbb << "    : "
        << edgeTree.findBox(tbb) << endl;

    treeBoundBox tbb1(point(0, 0, 0), point(1, 1, 0.1));
    Info << "    Box = " << tbb1 << "        : "
        << edgeTree.findBox(tbb1) << endl;

    treeBoundBox tbb2(point(0.3, 0, 0), point(1, 0.3, 1));
    Info << "    Box = " << tbb2 << "      : "
        << edgeTree.findBox(tbb2) << endl;

    treeBoundBox tbb3(point(-0.2, 0.5, 0), point(0.3, 0.9, 1));
    Info << "    Box = " << tbb3 << " : "
        << edgeTree.findBox(tbb3) << endl;

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
