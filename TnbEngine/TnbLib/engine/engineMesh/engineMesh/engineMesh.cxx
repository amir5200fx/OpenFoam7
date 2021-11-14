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

#include <engineMesh.hxx>

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(engineMesh, 0);
    defineRunTimeSelectionTable(engineMesh, IOobject);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::engineMesh::engineMesh(const IOobject& io)
    :
    fvMesh(io),
    engineDB_(refCast<const engineTime>(time())),
    pistonIndex_(-1),
    linerIndex_(-1),
    cylinderHeadIndex_(-1),
    deckHeight_("deckHeight", dimLength, great),
    pistonPosition_("pistonPosition", dimLength, -great)
{
    bool foundPiston = false;
    bool foundLiner = false;
    bool foundCylinderHead = false;

    forAll(boundary(), i)
    {
        if (boundary()[i].name() == "piston")
        {
            pistonIndex_ = i;
            foundPiston = true;
        }
        else if (boundary()[i].name() == "liner")
        {
            linerIndex_ = i;
            foundLiner = true;
        }
        else if (boundary()[i].name() == "cylinderHead")
        {
            cylinderHeadIndex_ = i;
            foundCylinderHead = true;
        }
    }

    reduce(foundPiston, orOp<bool>());
    reduce(foundLiner, orOp<bool>());
    reduce(foundCylinderHead, orOp<bool>());

    if (!foundPiston)
    {
        FatalErrorInFunction
            << "cannot find piston patch"
            << exit(FatalError);
    }

    if (!foundLiner)
    {
        FatalErrorInFunction
            << "cannot find liner patch"
            << exit(FatalError);
    }

    if (!foundCylinderHead)
    {
        FatalErrorInFunction
            << "cannot find cylinderHead patch"
            << exit(FatalError);
    }

    {
        if (pistonIndex_ != -1)
        {
            pistonPosition_.value() = -great;
            if (boundary()[pistonIndex_].patch().localPoints().size())
            {
                pistonPosition_.value() =
                    max(boundary()[pistonIndex_].patch().localPoints()).z();
            }
        }
        reduce(pistonPosition_.value(), maxOp<scalar>());

        if (cylinderHeadIndex_ != -1)
        {
            deckHeight_.value() = great;
            if (boundary()[cylinderHeadIndex_].patch().localPoints().size())
            {
                deckHeight_.value() = min
                (
                    boundary()[cylinderHeadIndex_].patch().localPoints()
                ).z();
            }
        }
        reduce(deckHeight_.value(), minOp<scalar>());

        Info << "deckHeight: " << deckHeight_.value() << nl
            << "piston position: " << pistonPosition_.value() << endl;
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::engineMesh::~engineMesh()
{}

// ************************************************************************* //
