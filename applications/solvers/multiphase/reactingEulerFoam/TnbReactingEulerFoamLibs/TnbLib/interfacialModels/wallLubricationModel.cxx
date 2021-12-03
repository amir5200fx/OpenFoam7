/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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

#define FoamRegisterDebugSwitch_EXPORT_DEFINE  // added by Payvand

#include <wallLubricationModel.hxx>

#include <phasePair.hxx>
#include <fvcFlux.hxx>
#include <surfaceInterpolate.hxx>
#include <wallFvPatch.hxx>
#include <BlendedInterfacialModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(wallLubricationModel, 0);
    defineBlendedInterfacialModelTypeNameAndDebug(wallLubricationModel, 0);
    defineRunTimeSelectionTable(wallLubricationModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::wallLubricationModel::dimF(1, -2, -2, 0, 0);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::wallLubricationModel::zeroGradWalls
(
    tmp<volVectorField> tFi
) const
{
    volVectorField& Fi = tFi.ref();
    const fvPatchList& patches = Fi.mesh().boundary();

    volVectorField::Boundary& FiBf = Fi.boundaryFieldRef();

    forAll(patches, patchi)
    {
        if (isA<wallFvPatch>(patches[patchi]))
        {
            fvPatchVectorField& Fiw = FiBf[patchi];
            Fiw = Fiw.patchInternalField();
        }
    }

    return tFi;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallLubricationModel::wallLubricationModel
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    wallDependentModel(pair.phase1().mesh()),
    pair_(pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallLubricationModel::~wallLubricationModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::wallLubricationModel::F() const
{
    return pair_.dispersed() * Fi();
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::wallLubricationModel::Ff() const
{
    return fvc::interpolate(pair_.dispersed()) * fvc::flux(Fi());
}


// ************************************************************************* //
