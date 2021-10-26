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
    globalMeshDataTest

Description
    Test global point communication

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <globalMeshData.hxx>
#include <argList.hxx>
#include <polyMesh.hxx>
#include <Time.hxx>
#include <mapDistribute.hxx>

using namespace tnbLib;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Main program:

int main(int argc, char* argv[])
{
#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createPolyMesh.lxx>

    const globalMeshData& globalData = mesh.globalData();
    const indirectPrimitivePatch& coupledPatch = globalData.coupledPatch();
    const globalIndexAndTransform& transforms = globalData.globalTransforms();


    // Test:print shared points
    {
        const mapDistribute& globalPointSlavesMap =
            globalData.globalPointSlavesMap();
        const labelListList& slaves =
            globalData.globalPointSlaves();
        const labelListList& transformedSlaves =
            globalData.globalPointTransformedSlaves();

        // Create field with my local data
        pointField coords(globalPointSlavesMap.constructSize());
        SubList<point>(coords, coupledPatch.nPoints()) =
            coupledPatch.localPoints();

        // Exchange data. Apply positional transforms.
        globalPointSlavesMap.distribute
        (
            transforms,
            coords,
            mapDistribute::transformPosition()
        );

        // Print
        forAll(slaves, pointi)
        {
            const labelList& slavePoints = slaves[pointi];

            if (slavePoints.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " coord:" << coords[pointi]
                    << " connected to untransformed slave points:" << endl;

                forAll(slavePoints, i)
                {
                    Pout << "    " << coords[slavePoints[i]] << endl;
                }
            }

            const labelList& transformedSlavePoints = transformedSlaves[pointi];

            if (transformedSlavePoints.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " coord:" << coords[pointi]
                    << " connected to transformed slave points:" << endl;

                forAll(transformedSlavePoints, i)
                {
                    Pout << "    " << coords[transformedSlavePoints[i]]
                        << endl;
                }
            }
        }
    }


    // Test:print shared edges
    {
        const mapDistribute& globalEdgeSlavesMap =
            globalData.globalEdgeSlavesMap();
        const labelListList& slaves =
            globalData.globalEdgeSlaves();
        const labelListList& transformedSlaves =
            globalData.globalEdgeTransformedSlaves();

        // Test: distribute edge centres
        pointField ec(globalEdgeSlavesMap.constructSize());
        forAll(coupledPatch.edges(), edgeI)
        {
            ec[edgeI] = coupledPatch.edges()[edgeI].centre
            (
                coupledPatch.localPoints()
            );
        }

        // Exchange data Apply positional transforms.
        globalEdgeSlavesMap.distribute
        (
            transforms,
            ec,
            mapDistribute::transformPosition()
        );

        // Print
        forAll(slaves, edgeI)
        {
            const labelList& slaveEdges = slaves[edgeI];

            if (slaveEdges.size() > 0)
            {
                Pout << "Master edge:" << edgeI
                    << " centre:" << ec[edgeI]
                    << " connected to slave edges:" << endl;

                forAll(slaveEdges, i)
                {
                    Pout << "    " << ec[slaveEdges[i]] << endl;
                }
            }
            const labelList& transformedSlaveEdges = transformedSlaves[edgeI];

            if (transformedSlaveEdges.size() > 0)
            {
                Pout << "Master edge:" << edgeI
                    << " centre:" << ec[edgeI]
                    << " connected to transformed slave edges:" << endl;

                forAll(transformedSlaveEdges, i)
                {
                    Pout << "    " << ec[transformedSlaveEdges[i]]
                        << endl;
                }
            }
        }
    }


    // Test: point to faces addressing
    {
        const mapDistribute& globalPointBoundaryFacesMap =
            globalData.globalPointBoundaryFacesMap();
        const labelListList& slaves =
            globalData.globalPointBoundaryFaces();
        const labelListList& transformedSlaves =
            globalData.globalPointTransformedBoundaryFaces();

        label nBnd = mesh.nFaces() - mesh.nInternalFaces();

        pointField fc(globalPointBoundaryFacesMap.constructSize());
        SubList<point>(fc, nBnd) =
            primitivePatch
            (
                SubList<face>
                (
                    mesh.faces(),
                    nBnd,
                    mesh.nInternalFaces()
                    ),
                mesh.points()
            ).faceCentres();

        // Exchange data
        globalPointBoundaryFacesMap.distribute
        (
            transforms,
            fc,
            mapDistribute::transformPosition()
        );

        // Print
        forAll(slaves, pointi)
        {
            const labelList& slaveFaces = slaves[pointi];

            if (slaveFaces.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " at:" << coupledPatch.localPoints()[pointi]
                    << " connected to " << slaveFaces.size()
                    << " untransformed faces:" << endl;

                forAll(slaveFaces, i)
                {
                    Pout << "    " << fc[slaveFaces[i]] << endl;
                }
            }

            const labelList& transformedSlaveFaces = transformedSlaves[pointi];

            if (transformedSlaveFaces.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " connected to " << transformedSlaveFaces.size()
                    << " transformed faces:" << endl;

                forAll(transformedSlaveFaces, i)
                {
                    Pout << "    " << fc[transformedSlaveFaces[i]] << endl;
                }
            }
        }
    }


    // Test: point to cells addressing
    {
        const labelList& boundaryCells = globalData.boundaryCells();
        const mapDistribute& globalPointBoundaryCellsMap =
            globalData.globalPointBoundaryCellsMap();
        const labelListList& slaves = globalData.globalPointBoundaryCells();
        const labelListList& transformedSlaves =
            globalData.globalPointTransformedBoundaryCells();

        pointField cc(globalPointBoundaryCellsMap.constructSize());
        forAll(boundaryCells, i)
        {
            cc[i] = mesh.cellCentres()[boundaryCells[i]];
        }

        // Exchange data
        globalPointBoundaryCellsMap.distribute
        (
            transforms,
            cc,
            mapDistribute::transformPosition()
        );

        // Print
        forAll(slaves, pointi)
        {
            const labelList& pointCells = slaves[pointi];

            if (pointCells.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " at:" << coupledPatch.localPoints()[pointi]
                    << " connected to " << pointCells.size()
                    << " untransformed boundaryCells:" << endl;

                forAll(pointCells, i)
                {
                    Pout << "    " << cc[pointCells[i]] << endl;
                }
            }

            const labelList& transformPointCells = transformedSlaves[pointi];

            if (transformPointCells.size() > 0)
            {
                Pout << "Master point:" << pointi
                    << " connected to " << transformPointCells.size()
                    << " transformed boundaryCells:" << endl;

                forAll(transformPointCells, i)
                {
                    Pout << "    " << cc[transformPointCells[i]] << endl;
                }
            }
        }
    }


    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
