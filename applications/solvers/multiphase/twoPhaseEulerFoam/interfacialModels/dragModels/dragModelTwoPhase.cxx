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

#include "dragModelTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"
#include "swarmCorrectionTwoPhase.hxx"

#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(dragModel, 0);
    defineRunTimeSelectionTable(dragModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::dragModel::dimK(1, -3, -1, 0, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModel::dragModel
(
    const phasePair& pair,
    const bool registerObject
)
    :
    regIOobject
    (
        IOobject
        (
            IOobject::groupName(typeName, pair.name()),
            pair.phase1().mesh().time().timeName(),
            pair.phase1().mesh(),
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            registerObject
        )
    ),
    pair_(pair)
{}


tnbLib::dragModel::dragModel
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    regIOobject
    (
        IOobject
        (
            IOobject::groupName(typeName, pair.name()),
            pair.phase1().mesh().time().timeName(),
            pair.phase1().mesh(),
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            registerObject
        )
    ),
    pair_(pair),
    swarmCorrection_
    (
        swarmCorrection::New
        (
            dict.subDict("swarmCorrection"),
            pair
        )
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModel::~dragModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::dragModel::Ki() const
{
    return
        0.75
        * CdRe()
        * swarmCorrection_->Cs()
        * pair_.continuous().rho()
        * pair_.continuous().nu()
        / sqr(pair_.dispersed().d());
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::dragModel::K() const
{
    return max(pair_.dispersed(), pair_.dispersed().residualAlpha()) * Ki();
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::dragModel::Kf() const
{
    return
        max
        (
            fvc::interpolate(pair_.dispersed()),
            pair_.dispersed().residualAlpha()
        ) * fvc::interpolate(Ki());
}


bool tnbLib::dragModel::writeData(Ostream& os) const
{
    return os.good();
}


// ************************************************************************* //
