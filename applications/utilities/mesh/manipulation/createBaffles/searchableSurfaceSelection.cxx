/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

#include "searchableSurfaceSelection.hxx"

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>
#include <searchableSurface.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace faceSelections
    {
        defineTypeNameAndDebug(searchableSurfaceSelection, 0);
        addToRunTimeSelectionTable
        (
            faceSelection,
            searchableSurfaceSelection,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceSelections::searchableSurfaceSelection::searchableSurfaceSelection
(
    const word& name,
    const fvMesh& mesh,
    const dictionary& dict
)
    :
    faceSelection(name, mesh, dict),
    surfacePtr_
    (
        searchableSurface::New
        (
            word(dict.lookup("surface")),
            IOobject
            (
                dict.lookupOrDefault("name", mesh.objectRegistry::db().name()),
                mesh.time().constant(),
                "triSurface",
                mesh.objectRegistry::db(),
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            ),
            dict
        )
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceSelections::searchableSurfaceSelection::~searchableSurfaceSelection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceSelections::searchableSurfaceSelection::select
(
    const label zoneID,
    labelList& faceToZoneID,
    boolList& faceToFlip
) const
{
    // Get cell-cell centre vectors

    pointField start(mesh_.nFaces());
    pointField end(mesh_.nFaces());

    // Internal faces
    for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
    {
        start[facei] = mesh_.cellCentres()[mesh_.faceOwner()[facei]];
        end[facei] = mesh_.cellCentres()[mesh_.faceNeighbour()[facei]];
    }

    // Boundary faces
    vectorField neighbourCellCentres;
    syncTools::swapBoundaryCellPositions
    (
        mesh_,
        mesh_.cellCentres(),
        neighbourCellCentres
    );

    const polyBoundaryMesh& pbm = mesh_.boundaryMesh();

    forAll(pbm, patchi)
    {
        const polyPatch& pp = pbm[patchi];

        if (pp.coupled())
        {
            forAll(pp, i)
            {
                label facei = pp.start() + i;
                start[facei] = mesh_.cellCentres()[mesh_.faceOwner()[facei]];
                end[facei] = neighbourCellCentres[facei - mesh_.nInternalFaces()];
            }
        }
        else
        {
            forAll(pp, i)
            {
                label facei = pp.start() + i;
                start[facei] = mesh_.cellCentres()[mesh_.faceOwner()[facei]];
                end[facei] = mesh_.faceCentres()[facei];
            }
        }
    }

    List<pointIndexHit> hits;
    surfacePtr_().findLine(start, end, hits);
    pointField normals;
    surfacePtr_().getNormal(hits, normals);

    //- Note: do not select boundary faces.

    for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
    {
        if (hits[facei].hit())
        {
            faceToZoneID[facei] = zoneID;
            vector d = end[facei] - start[facei];
            faceToFlip[facei] = ((normals[facei] & d) < 0);
        }
    }
    forAll(pbm, patchi)
    {
        const polyPatch& pp = pbm[patchi];

        if (pp.coupled())
        {
            forAll(pp, i)
            {
                label facei = pp.start() + i;
                if (hits[facei].hit())
                {
                    faceToZoneID[facei] = zoneID;
                    vector d = end[facei] - start[facei];
                    faceToFlip[facei] = ((normals[facei] & d) < 0);
                }
            }
        }
    }

    faceSelection::select(zoneID, faceToZoneID, faceToFlip);
}


// ************************************************************************* //
