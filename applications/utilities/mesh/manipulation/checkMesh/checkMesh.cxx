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
    checkMesh

Description
    Checks validity of a mesh.

Usage
    \b checkMesh [OPTION]

    Options:
      - \par -allGeometry
        Checks all (including non finite-volume specific) geometry

      - \par -allTopology
        Checks all (including non finite-volume specific) addressing

      - \par -meshQuality
        Checks against user defined (in \a system/meshQualityDict) quality
        settings

      - \par -region \<name\>
        Specify an alternative mesh region.

      - \par -writeSets \<surfaceFormat\>
        Reconstruct all cellSets and faceSets geometry and write to
        postProcessing directory according to surfaceFormat
        (e.g. vtk or ensight). Additionally reconstructs all pointSets and
        writes as vtk format.

\*---------------------------------------------------------------------------*/
#include <includeAllModules.hxx>

#include <argList.hxx>
#include <timeSelector.hxx>
#include <Time.hxx>
#include <polyMesh.hxx>
#include <globalMeshData.hxx>
#include <surfaceWriter.hxx>
#include <vtkSetWriter.hxx>
#include <IOdictionary.hxx>

#include "checkTools.hxx"
#include "checkTopology.hxx"
#include "checkGeometry.hxx"
#include "checkMeshQuality.hxx"
#include "printMeshStats.hxx"

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
    timeSelector::addOptions();
#include <addRegionOption.lxx>
    argList::addBoolOption
    (
        "noTopology",
        "skip checking the mesh topology"
    );
    argList::addBoolOption
    (
        "allGeometry",
        "include bounding box checks"
    );
    argList::addBoolOption
    (
        "allTopology",
        "include extra topology checks"
    );
    argList::addBoolOption
    (
        "meshQuality",
        "read user-defined mesh quality criterions from system/meshQualityDict"
    );
    argList::addOption
    (
        "writeSets",
        "surfaceFormat",
        "reconstruct and write all faceSets and cellSets in selected format"
    );

#include <setRootCase.lxx>
#include <createTime.lxx>
    instantList timeDirs = timeSelector::select0(runTime, args);
#include <createNamedPolyMesh.lxx>

    const bool noTopology = args.optionFound("noTopology");
    const bool allGeometry = args.optionFound("allGeometry");
    const bool allTopology = args.optionFound("allTopology");
    const bool meshQuality = args.optionFound("meshQuality");

    word surfaceFormat;
    const bool writeSets = args.optionReadIfPresent("writeSets", surfaceFormat);

    if (noTopology)
    {
        Info << "Disabling all topology checks." << nl << endl;
    }
    if (allTopology)
    {
        Info << "Enabling all (cell, face, edge, point) topology checks."
            << nl << endl;
    }
    if (allGeometry)
    {
        Info << "Enabling all geometry checks." << nl << endl;
    }
    if (meshQuality)
    {
        Info << "Enabling user-defined geometry checks." << nl << endl;
    }
    if (writeSets)
    {
        Info << "Reconstructing and writing " << surfaceFormat
            << " representation"
            << " of all faceSets and cellSets." << nl << endl;
    }


    autoPtr<IOdictionary> qualDict;
    if (meshQuality)
    {
        qualDict.reset
        (
            new IOdictionary
            (
                IOobject
                (
                    "meshQualityDict",
                    mesh.time().system(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            )
        );
    }


    autoPtr<surfaceWriter> surfWriter;
    autoPtr<writer<scalar>> setWriter;
    if (writeSets)
    {
        surfWriter = surfaceWriter::New(surfaceFormat);
        setWriter = writer<scalar>::New(vtkSetWriter<scalar>::typeName);
    }


    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        polyMesh::readUpdateState state = mesh.readUpdate();

        if
            (
                !timeI
                || state == polyMesh::TOPO_CHANGE
                || state == polyMesh::TOPO_PATCH_CHANGE
                )
        {
            Info << "Time = " << runTime.timeName() << nl << endl;

            // Reconstruct globalMeshData
            mesh.globalData();

            printMeshStats(mesh, allTopology);

            label nFailedChecks = 0;

            if (!noTopology)
            {
                nFailedChecks += checkTopology
                (
                    mesh,
                    allTopology,
                    allGeometry,
                    surfWriter,
                    setWriter
                );
            }

            nFailedChecks += checkGeometry
            (
                mesh,
                allGeometry,
                surfWriter,
                setWriter
            );

            if (meshQuality)
            {
                nFailedChecks += checkMeshQuality(mesh, qualDict(), surfWriter);
            }


            // Note: no reduction in nFailedChecks necessary since is
            //       counter of checks, not counter of failed cells,faces etc.

            if (nFailedChecks == 0)
            {
                Info << "\nMesh OK.\n" << endl;
            }
            else
            {
                Info << "\nFailed " << nFailedChecks << " mesh checks.\n"
                    << endl;
            }
        }
        else if (state == polyMesh::POINTS_MOVED)
        {
            Info << "Time = " << runTime.timeName() << nl << endl;

            label nFailedChecks = checkGeometry
            (
                mesh,
                allGeometry,
                surfWriter,
                setWriter
            );

            if (meshQuality)
            {
                nFailedChecks += checkMeshQuality(mesh, qualDict(), surfWriter);
            }


            if (nFailedChecks)
            {
                Info << "\nFailed " << nFailedChecks << " mesh checks.\n"
                    << endl;
            }
            else
            {
                Info << "\nMesh OK.\n" << endl;
            }
        }
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
