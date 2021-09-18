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
    refineHexMesh

Description
    Refines a hex mesh by 2x2x2 cell splitting.

\*---------------------------------------------------------------------------*/
#include <includeAllModules.hxx>

#include <fvMesh.hxx>
#include <pointMesh.hxx>
#include <argList.hxx>
#include <Time.hxx>
#include <hexRef8.hxx>
#include <cellSet.hxx>
#include <OFstream.hxx>
#include <meshTools.hxx>
#include <IFstream.hxx>
#include <polyTopoChange.hxx>
#include <mapPolyMesh.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <pointFields.hxx>
#include <ReadFields.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include "addOverwriteOption.lxx"
#include "addRegionOption.lxx"
    argList::validArgs.append("cellSet");
    argList::addBoolOption
    (
        "minSet",
        "remove cells from input cellSet to keep to 2:1 ratio"
        " (default is to extend set)"
    );
    argList::addBoolOption
    (
        "noFields",
        "do not update fields"
    );

#include "setRootCase.lxx"
#include "createTime.lxx"
    runTime.functionObjects().off();

    const bool overwrite = args.optionFound("overwrite");
    const bool minSet = args.optionFound("minSet");
    const bool fields = !args.optionFound("noFields");

#include "createNamedMesh.lxx"
    const word oldInstance = mesh.pointsInstance();

    word cellSetName(args.args()[1]);

    Info << "Reading cells to refine from cellSet " << cellSetName
        << nl << endl;

    cellSet cellsToRefine(mesh, cellSetName);

    Info << "Read " << returnReduce(cellsToRefine.size(), sumOp<label>())
        << " cells to refine from cellSet " << cellSetName << nl
        << endl;


    // Read objects in time directory
    IOobjectList objects(mesh, runTime.timeName());

    if (fields) Info << "Reading geometric fields" << nl << endl;

#include "readVolFields.lxx"
#include "readSurfaceFields.lxx"
#include "readPointFields.lxx"

    Info << endl;


    // Construct refiner without unrefinement. Read existing point/cell level.
    hexRef8 meshCutter(mesh);

    // Some stats
    Info << "Read mesh:" << nl
        << "    cells:" << mesh.globalData().nTotalCells() << nl
        << "    faces:" << mesh.globalData().nTotalFaces() << nl
        << "    points:" << mesh.globalData().nTotalPoints() << nl
        << "    cellLevel :"
        << " min:" << gMin(meshCutter.cellLevel())
        << " max:" << gMax(meshCutter.cellLevel()) << nl
        << "    pointLevel :"
        << " min:" << gMin(meshCutter.pointLevel())
        << " max:" << gMax(meshCutter.pointLevel()) << nl
        << endl;


    // Maintain 2:1 ratio
    labelList newCellsToRefine
    (
        meshCutter.consistentRefinement
        (
            cellsToRefine.toc(),
            !minSet                 // extend set
        )
    );

    // Mesh changing engine.
    polyTopoChange meshMod(mesh);

    // Play refinement commands into mesh changer.
    meshCutter.setRefinement(newCellsToRefine, meshMod);

    if (!overwrite)
    {
        runTime++;
    }

    // Create mesh, return map from old to new mesh.
    autoPtr<mapPolyMesh> map = meshMod.changeMesh(mesh, false);

    // Update fields
    mesh.updateMesh(map);

    // Update numbering of cells/vertices.
    meshCutter.updateMesh(map);

    // Optionally inflate mesh
    if (map().hasMotionPoints())
    {
        mesh.movePoints(map().preMotionPoints());
    }

    Info << "Refined from " << returnReduce(map().nOldCells(), sumOp<label>())
        << " to " << mesh.globalData().nTotalCells() << " cells." << nl << endl;

    if (overwrite)
    {
        mesh.setInstance(oldInstance);
        meshCutter.setInstance(oldInstance);
    }
    Info << "Writing mesh to " << runTime.timeName() << endl;

    mesh.write();
    meshCutter.write();

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
