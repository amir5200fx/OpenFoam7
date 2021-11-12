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
    autoPatch

Description
    Divides external faces into patches based on (user supplied) feature
    angle.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <polyMesh.hxx>
#include <Time.hxx>
#include <boundaryMesh.hxx>
#include <repatchPolyTopoChanger.hxx>
#include <unitConversion.hxx>
#include <OFstream.hxx>
#include <ListOps.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Get all feature edges.
void collectFeatureEdges(const boundaryMesh& bMesh, labelList& markedEdges)
{
    markedEdges.setSize(bMesh.mesh().nEdges());

    label markedI = 0;

    forAll(bMesh.featureSegments(), i)
    {
        const labelList& segment = bMesh.featureSegments()[i];

        forAll(segment, j)
        {
            label featEdgeI = segment[j];

            label meshEdgeI = bMesh.featureToEdge()[featEdgeI];

            markedEdges[markedI++] = meshEdgeI;
        }
    }
    markedEdges.setSize(markedI);
}



int main(int argc, char* argv[])
{
#include <addOverwriteOption.lxx>
    argList::noParallel();
    argList::validArgs.append("feature angle[0-180]");

#include <setRootCase.lxx>
#include <createTime.lxx>
    runTime.functionObjects().off();
#include <createPolyMesh.lxx>
    const word oldInstance = mesh.pointsInstance();

    Info << "Mesh read in = "
        << runTime.cpuTimeIncrement()
        << " s\n" << endl << endl;


    const scalar featureAngle = args.argRead<scalar>(1);
    const bool overwrite = args.optionFound("overwrite");

    const scalar minCos = tnbLib::cos(degToRad(featureAngle));

    Info << "Feature:" << featureAngle << endl
        << "minCos :" << minCos << endl
        << endl;

    //
    // Use boundaryMesh to reuse all the featureEdge stuff in there.
    //

    boundaryMesh bMesh;
    bMesh.read(mesh);

    // Set feature angle (calculate feature edges)
    bMesh.setFeatureEdges(minCos);

    // Collect all feature edges as edge labels
    labelList markedEdges;

    collectFeatureEdges(bMesh, markedEdges);



    // (new) patch ID for every face in mesh.
    labelList patchIDs(bMesh.mesh().size(), -1);

    //
    // Fill patchIDs with values for every face by floodfilling without
    // crossing feature edge.
    //

    // Current patch number.
    label newPatchi = bMesh.patches().size();

    label suffix = 0;

    while (true)
    {
        // Find first unset face.
        label unsetFacei = findIndex(patchIDs, -1);

        if (unsetFacei == -1)
        {
            // All faces have patchID set. Exit.
            break;
        }

        // Found unset face. Create patch for it.
        word patchName;
        do
        {
            patchName = "auto" + name(suffix++);
        } while (bMesh.findPatchID(patchName) != -1);

        bMesh.addPatch(patchName);

        bMesh.changePatchType(patchName, "patch");


        // Fill visited with all faces reachable from unsetFacei.
        boolList visited(bMesh.mesh().size());

        bMesh.markFaces(markedEdges, unsetFacei, visited);


        // Assign all visited faces to current patch
        label nVisited = 0;

        forAll(visited, facei)
        {
            if (visited[facei])
            {
                nVisited++;

                patchIDs[facei] = newPatchi;
            }
        }

        Info << "Assigned " << nVisited << " faces to patch " << patchName
            << endl << endl;

        newPatchi++;
    }



    const PtrList<boundaryPatch>& patches = bMesh.patches();

    // Create new list of patches with old ones first
    List<polyPatch*> newPatchPtrList(patches.size());

    newPatchi = 0;

    // Copy old patches
    forAll(mesh.boundaryMesh(), patchi)
    {
        const polyPatch& patch = mesh.boundaryMesh()[patchi];

        newPatchPtrList[newPatchi] =
            patch.clone
            (
                mesh.boundaryMesh(),
                newPatchi,
                patch.size(),
                patch.start()
            ).ptr();

        newPatchi++;
    }

    // Add new ones with empty size.
    for (label patchi = newPatchi; patchi < patches.size(); patchi++)
    {
        const boundaryPatch& bp = patches[patchi];

        newPatchPtrList[newPatchi] = polyPatch::New
        (
            polyPatch::typeName,
            bp.name(),
            0,
            mesh.nFaces(),
            newPatchi,
            mesh.boundaryMesh()
        ).ptr();

        newPatchi++;
    }

    if (!overwrite)
    {
        runTime++;
    }


    // Change patches
    repatchPolyTopoChanger polyMeshRepatcher(mesh);
    polyMeshRepatcher.changePatches(newPatchPtrList);


    // Change face ordering

    // Since bMesh read from mesh there is one to one mapping so we don't
    // have to do the geometric stuff.
    const labelList& meshFace = bMesh.meshFace();

    forAll(patchIDs, facei)
    {
        label meshFacei = meshFace[facei];

        polyMeshRepatcher.changePatchID(meshFacei, patchIDs[facei]);
    }

    polyMeshRepatcher.repatch();

    // Write resulting mesh
    if (overwrite)
    {
        mesh.setInstance(oldInstance);
    }

    // Set the precision of the points data to 10
    IOstream::defaultPrecision(max(10u, IOstream::defaultPrecision()));

    mesh.write();

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
