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

#include <extrude2DMesh.hxx>

#include <polyMesh.hxx>
#include <polyTopoChange.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(extrude2DMesh, 0);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::extrude2DMesh::check2D() const
{
    const faceList& faces = mesh_.faces();
    forAll(faces, facei)
    {
        if (faces[facei].size() != 2)
        {
            FatalErrorInFunction
                << "Face " << facei << " size " << faces[facei].size()
                << " is not of size 2: mesh is not a valid two-dimensional "
                << "mesh" << exit(FatalError);
        }
    }
}


//void tnbLib::extrude2DMesh::findExtrudeDirection()
//{
//    scalar minRange = great;

//    for (direction dir = 0; dir < 3; dir++)
//    {
//        scalarField cmpts(mesh_.points().component(dir));

//        scalar range = max(cmpts)-min(cmpts);

//        Info<< "Direction:" << dir << " range:" << range << endl;

//        if (range < minRange)
//        {
//            minRange = range;
//            extrudeDir_ = dir;
//        }
//    }

//    Info<< "Extruding in direction " << extrudeDir_
//        << " with thickness " << thickness_ << nl
//        << endl;
//}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extrude2DMesh::extrude2DMesh
(
    polyMesh& mesh,
    const dictionary& dict,
    const extrudeModel& model
)
    :
    mesh_(mesh),
    dict_(dict),
    // patchDict_(dict.subDict("patchInfo")),
    model_(model),
    modelType_(dict.lookup("extrudeModel")),
    patchType_(dict.lookup("patchType")),
    frontPatchi_(-1),
    backPatchi_(-1)
{
    check2D();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::extrude2DMesh::~extrude2DMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::extrude2DMesh::addFrontBackPatches()
{
    const polyBoundaryMesh& patches = mesh_.boundaryMesh();

    frontPatchi_ = patches.findPatchID("front");
    backPatchi_ = patches.findPatchID("back");

    // Add patch.
    List<polyPatch*> newPatches(patches.size() + 2);

    forAll(patches, patchi)
    {
        const polyPatch& pp = patches[patchi];

        newPatches[patchi] =
            pp.clone
            (
                patches,
                newPatches.size(),
                pp.size(),
                pp.start()
            ).ptr();
    }

    if (frontPatchi_ == -1)
    {
        frontPatchi_ = patches.size();

        newPatches[frontPatchi_] =
            polyPatch::New
            (
                patchType_,
                "front",
                0,
                mesh_.nFaces(),
                frontPatchi_,
                patches
            ).ptr();

        //        newPatches[frontPatchi_] = polyPatch::New
        //        (
        //            "front",
        //            patchDict_,
        //            frontPatchi_,
        //            patches
        //        ).ptr();

        Info << "Adding patch " << newPatches[frontPatchi_]->name()
            << " at index " << frontPatchi_
            << " for front faces." << nl << endl;
    }

    if (backPatchi_ == -1)
    {
        backPatchi_ = patches.size() + 1;

        newPatches[backPatchi_] =
            polyPatch::New
            (
                patchType_,
                "back",
                0,
                mesh_.nFaces(),
                backPatchi_,
                patches
            ).ptr();

        //        newPatches[frontPatchi_] = polyPatch::New
        //        (
        //            "back",
        //            patchDict_,
        //            backPatchi_,
        //            patches
        //        ).ptr();

        Info << "Adding patch " << newPatches[backPatchi_]->name()
            << " at index " << backPatchi_
            << " for back faces." << nl << endl;
    }

    mesh_.removeBoundary();
    mesh_.addPatches(newPatches);
}


void tnbLib::extrude2DMesh::setRefinement
(
    polyTopoChange& meshMod
)
{
    const label nLayers = model_.nLayers();
    const pointField& points = mesh_.points();
    label nFaces = 0;

    for (label layer = 0; layer < nLayers; ++layer)
    {
        label offset = layer * mesh_.nCells();

        forAll(mesh_.cells(), celli)
        {
            meshMod.addCell
            (
                -1,     // masterPointID,
                -1,     // masterEdgeID,
                -1,     // masterFaceID,
                celli + offset,  // masterCellID,
                mesh_.cellZones().whichZone(celli)  // zoneID
            );
        }
    }


    // Generate points
    // ~~~~~~~~~~~~~~~

    for (label layer = 0; layer <= nLayers; ++layer)
    {
        label offset = layer * points.size();

        forAll(points, pointi)
        {
            // Don't need the surface normal for either linearDirection or
            // wedge. Will need to add to be able to use others.
            point newPoint = model_
            (
                points[pointi],
                vector(),
                layer
            );

            meshMod.addPoint
            (
                newPoint,
                pointi + offset,
                -1,             // zoneID
                true            // inCell
            );
        }

        Pout << "Added " << points.size() << " points to layer "
            << layer << endl;
    }


    // Generate faces
    // ~~~~~~~~~~~~~~

    const faceList& faces = mesh_.faces();
    const polyBoundaryMesh& patches = mesh_.boundaryMesh();

    for (label layer = 0; layer < nLayers; ++layer)
    {
        label currentLayerOffset = layer * mesh_.nPoints();
        label nextLayerOffset = currentLayerOffset + mesh_.nPoints();

        for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
        {
            label zoneID = mesh_.faceZones().whichZone(facei);
            bool zoneFlip = false;
            if (zoneID != -1)
            {
                const faceZone& fZone = mesh_.faceZones()[zoneID];
                zoneFlip = fZone.flipMap()[fZone.whichFace(facei)];
            }

            face newFace(4);
            const face& f = faces[facei];
            newFace[0] = f[0] + currentLayerOffset;
            newFace[1] = f[1] + currentLayerOffset;
            newFace[2] = f[1] + nextLayerOffset;
            newFace[3] = f[0] + nextLayerOffset;

            //{
            //    vector n = newFace.normal(pointField(meshMod.points()));
            //    label own = mesh_.faceOwner()[facei];
            //    const labelList& ownPoints = mesh_.cellPoints()[own];
            //    point ownCc = sum(pointField(mesh_.points(), ownPoints))/ownPoints.size();
            //    label nei = mesh_.faceNeighbour()[facei];
            //    const labelList& neiPoints = mesh_.cellPoints()[nei];
            //    point neiCc = sum(pointField(mesh_.points(), neiPoints))/neiPoints.size();
            //    vector d = neiCc - ownCc;

            //    Pout<< "face:" << facei << " at:" << f.centre(mesh_.points()) << endl
            //        << "    own:" << own << " at:" << ownCc << endl
            //        << "    nei:" << nei << " at:" << neiCc << endl
            //        << "    sign:" << (n & d) << endl
            //        << endl;
            //}

            label offset = layer * mesh_.nCells();

            meshMod.addFace
            (
                newFace,
                mesh_.faceOwner()[facei] + offset,       // own
                mesh_.faceNeighbour()[facei] + offset,   // nei
                -1,                             // masterPointID
                -1,                             // masterEdgeID
                nFaces++,    // masterFaceID
                false,                          // flipFaceFlux
                -1,                             // patchID
                zoneID,                         // zoneID
                zoneFlip                        // zoneFlip
            );

            if (debug)
            {
                Info << newFace << " "
                    << mesh_.faceOwner()[facei] + offset << " "
                    << mesh_.faceNeighbour()[facei] + offset << " "
                    << nFaces - 1
                    << endl;
            }
        }
    }

    forAll(patches, patchi)
    {
        for (label layer = 0; layer < nLayers; layer++)
        {
            label currentLayerOffset = layer * mesh_.nPoints();
            label nextLayerOffset = currentLayerOffset + mesh_.nPoints();

            label startFacei = patches[patchi].start();
            label endFacei = startFacei + patches[patchi].size();

            for (label facei = startFacei; facei < endFacei; facei++)
            {
                label zoneID = mesh_.faceZones().whichZone(facei);
                bool zoneFlip = false;
                if (zoneID != -1)
                {
                    const faceZone& fZone = mesh_.faceZones()[zoneID];
                    zoneFlip = fZone.flipMap()[fZone.whichFace(facei)];
                }

                face newFace(4);
                const face& f = faces[facei];
                newFace[0] = f[0] + currentLayerOffset;
                newFace[1] = f[1] + currentLayerOffset;
                newFace[2] = f[1] + nextLayerOffset;
                newFace[3] = f[0] + nextLayerOffset;

                label offset = layer * mesh_.nCells();

                meshMod.addFace
                (
                    newFace,
                    mesh_.faceOwner()[facei] + offset,       // own
                    -1,                                      // nei
                    -1,                                      // masterPointID
                    -1,                                      // masterEdgeID
                    nFaces++,                                // masterFaceID
                    false,                                   // flipFaceFlux
                    patchi,                                  // patchID
                    zoneID,                                  // zoneID
                    zoneFlip                                 // zoneFlip
                );

                if (debug)
                {
                    Info << newFace << " "
                        << mesh_.faceOwner()[facei] + offset << " "
                        << nFaces - 1
                        << endl;
                }
            }
        }
    }

    // Add extra internal faces that need special treatment for owners and
    // neighbours.
    forAll(mesh_.cells(), celli)
    {
        const cell& cFaces = mesh_.cells()[celli];

        face frontFace(cFaces.size());

        // Make a loop out of faces.
        label nextFacei = cFaces[0];

        const face& f = faces[nextFacei];

        label nextPointi;
        if (mesh_.faceOwner()[nextFacei] == celli)
        {
            frontFace[0] = f[0];
            nextPointi = f[1];
        }
        else
        {
            frontFace[0] = f[1];
            nextPointi = f[0];
        }


        for (label i = 1; i < frontFace.size(); i++)
        {
            frontFace[i] = nextPointi;

            // Find face containing pointi
            forAll(cFaces, cFacei)
            {
                label facei = cFaces[cFacei];
                if (facei != nextFacei)
                {
                    const face& f = faces[facei];

                    if (f[0] == nextPointi)
                    {
                        nextPointi = f[1];
                        nextFacei = facei;
                        break;
                    }
                    else if (f[1] == nextPointi)
                    {
                        nextPointi = f[0];
                        nextFacei = facei;
                        break;
                    }
                }
            }
        }

        for (label layer = 0; layer < nLayers - 1; ++layer)
        {
            // Offset to create front face.
            forAll(frontFace, fp)
            {
                frontFace[fp] += mesh_.nPoints();
            }

            label offset = layer * mesh_.nCells();

            label nei = -1;
            if (layer != nLayers - 1)
            {
                nei = celli + offset + mesh_.nCells();
            }

            meshMod.addFace
            (
                frontFace,
                celli + offset,                 // own
                nei,                            // nei
                -1,                             // masterPointID
                -1,                             // masterEdgeID
                nFaces++,                       // masterFaceID
                false,                          // flipFaceFlux
                -1,                             // patchID
                -1,                             // zoneID
                false                           // zoneFlip
            );

            if (debug)
            {
                Info << frontFace << " "
                    << celli + offset << " "
                    << nei << " "
                    << nFaces - 1
                    << endl;
            }
        }
    }

    // Generate front and back faces
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    forAll(mesh_.cells(), celli)
    {
        const cell& cFaces = mesh_.cells()[celli];

        face frontFace(cFaces.size());

        // Make a loop out of faces.
        label nextFacei = cFaces[0];

        const face& f = faces[nextFacei];

        label nextPointi;
        if (mesh_.faceOwner()[nextFacei] == celli)
        {
            frontFace[0] = f[0];
            nextPointi = f[1];
        }
        else
        {
            frontFace[0] = f[1];
            nextPointi = f[0];
        }


        for (label i = 1; i < frontFace.size(); i++)
        {
            frontFace[i] = nextPointi;

            // Find face containing pointi
            forAll(cFaces, cFacei)
            {
                label facei = cFaces[cFacei];
                if (facei != nextFacei)
                {
                    const face& f = faces[facei];

                    if (f[0] == nextPointi)
                    {
                        nextPointi = f[1];
                        nextFacei = facei;
                        break;
                    }
                    else if (f[1] == nextPointi)
                    {
                        nextPointi = f[0];
                        nextFacei = facei;
                        break;
                    }
                }
            }
        }

        // Add back face.
        meshMod.addFace
        (
            frontFace.reverseFace(),
            celli,                          // own
            -1,                             // nei
            -1,                             // masterPointID
            -1,                             // masterEdgeID
            nFaces++,                       // masterFaceID
            false,                          // flipFaceFlux
            backPatchi_,                    // patchID
            -1,                             // zoneID
            false                           // zoneFlip
        );

        if (debug)
        {
            Info << nl << frontFace.reverseFace() << " "
                << celli << " "
                << nFaces - 1
                << endl;
        }

        // Offset to create front face.
        forAll(frontFace, fp)
        {
            frontFace[fp] += mesh_.nPoints() * (nLayers);
        }

        label offset = (nLayers - 1) * mesh_.nCells();

        meshMod.addFace
        (
            frontFace,
            celli + offset,                 // own
            -1,                             // nei
            -1,                             // masterPointID
            -1,                             // masterEdgeID
            nFaces++,                       // masterFaceID
            false,                          // flipFaceFlux
            frontPatchi_,                   // patchID
            -1,                             // zoneID
            false                           // zoneFlip
        );

        if (debug)
        {
            Info << frontFace << " "
                << celli + offset << " "
                << nFaces - 1
                << endl;
        }
    }
}


// ************************************************************************* //
