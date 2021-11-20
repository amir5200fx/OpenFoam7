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
    faceAgglomerate

Description

    Agglomerate boundary faces using the pairPatchAgglomeration algorithm.
    It writes a map from the fine to coarse grid.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>
#include <volFields.hxx>
#include <CompactListList.hxx>
#include <unitConversion.hxx>
#include <pairPatchAgglomeration.hxx>
#include <labelListIOList.hxx>
#include <syncTools.hxx>
#include <globalIndex.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <addRegionOption.lxx>
#include <addDictOption.lxx>
#include <setRootCase.lxx>
#include <createTime.lxx>
#include <createNamedMesh.lxx>

    const word dictName("viewFactorsDict");

#include <setConstantMeshDictionaryIO.lxx>

    // Read control dictionary
    const IOdictionary agglomDict(dictIO);

    bool writeAgglom = readBool(agglomDict.lookup("writeFacesAgglomeration"));


    const polyBoundaryMesh& boundary = mesh.boundaryMesh();

    labelListIOList finalAgglom
    (
        IOobject
        (
            "finalAgglom",
            mesh.facesInstance(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            false
        ),
        boundary.size()
    );

    label nCoarseFaces = 0;

    forAllConstIter(dictionary, agglomDict, iter)
    {
        labelList patchids = boundary.findIndices(iter().keyword());
        forAll(patchids, i)
        {
            label patchi = patchids[i];
            const polyPatch& pp = boundary[patchi];
            if (!pp.coupled())
            {
                Info << "\nAgglomerating patch : " << pp.name() << endl;
                pairPatchAgglomeration agglomObject
                (
                    pp,
                    agglomDict.subDict(pp.name())
                );
                agglomObject.agglomerate();
                finalAgglom[patchi] =
                    agglomObject.restrictTopBottomAddressing();

                if (finalAgglom[patchi].size())
                {
                    nCoarseFaces += max(finalAgglom[patchi] + 1);
                }
            }
        }
    }


    // - All patches which are not agglomarated are identity for finalAgglom
    forAll(boundary, patchid)
    {
        if (finalAgglom[patchid].size() == 0)
        {
            finalAgglom[patchid] = identity(boundary[patchid].size());
        }
    }

    // Sync agglomeration across coupled patches
    labelList nbrAgglom(mesh.nFaces() - mesh.nInternalFaces(), -1);

    forAll(boundary, patchid)
    {
        const polyPatch& pp = boundary[patchid];
        if (pp.coupled())
        {
            finalAgglom[patchid] = identity(pp.size());
            forAll(pp, i)
            {
                nbrAgglom[pp.start() - mesh.nInternalFaces() + i] =
                    finalAgglom[patchid][i];
            }
        }
    }

    syncTools::swapBoundaryFaceList(mesh, nbrAgglom);
    forAll(boundary, patchid)
    {
        const polyPatch& pp = boundary[patchid];
        if (pp.coupled() && !refCast<const coupledPolyPatch>(pp).owner())
        {
            forAll(pp, i)
            {
                finalAgglom[patchid][i] =
                    nbrAgglom[pp.start() - mesh.nInternalFaces() + i];
            }
        }
    }

    finalAgglom.write();

    if (writeAgglom)
    {
        globalIndex index(nCoarseFaces);
        volScalarField facesAgglomeration
        (
            IOobject
            (
                "facesAgglomeration",
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar(dimless, 0)
        );

        volScalarField::Boundary& facesAgglomerationBf =
            facesAgglomeration.boundaryFieldRef();

        label coarsePatchIndex = 0;
        forAll(boundary, patchid)
        {
            const polyPatch& pp = boundary[patchid];
            if (pp.size() > 0)
            {
                fvPatchScalarField& bFacesAgglomeration =
                    facesAgglomerationBf[patchid];

                forAll(bFacesAgglomeration, j)
                {
                    bFacesAgglomeration[j] =
                        index.toGlobal
                        (
                            Pstream::myProcNo(),
                            finalAgglom[patchid][j] + coarsePatchIndex
                        );
                }

                coarsePatchIndex += max(finalAgglom[patchid]) + 1;
            }
        }

        Info << "\nWriting facesAgglomeration" << endl;
        facesAgglomeration.write();
    }

    Info << "End\n" << endl;
    return 0;
}


// ************************************************************************* //
