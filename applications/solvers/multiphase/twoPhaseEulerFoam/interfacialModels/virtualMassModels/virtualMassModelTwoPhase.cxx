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

#include "virtualMassModelTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(virtualMassModel, 0);
    defineRunTimeSelectionTable(virtualMassModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::virtualMassModel::dimK(dimDensity);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::virtualMassModel::virtualMassModel
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
    pair_(pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::virtualMassModel::~virtualMassModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::virtualMassModel::Ki() const
{
    return Cvm() * pair_.continuous().rho();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::virtualMassModel::K() const
{
    return pair_.dispersed() * Ki();
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::virtualMassModel::Kf() const
{
    return
        fvc::interpolate(pair_.dispersed()) * fvc::interpolate(Ki());
}


bool tnbLib::virtualMassModel::writeData(Ostream& os) const
{
    return os.good();
}


// ************************************************************************* //
