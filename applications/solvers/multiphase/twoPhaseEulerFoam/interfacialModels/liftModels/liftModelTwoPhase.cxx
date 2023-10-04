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

#include "liftModelTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <fvcCurl.hxx>
#include <fvcFlux.hxx>
#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(liftModel, 0);
    defineRunTimeSelectionTable(liftModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::liftModel::dimF(1, -2, -2, 0, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::liftModel::liftModel
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    pair_(pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::liftModel::~liftModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::liftModel::Fi() const
{
    return
        Cl()
        * pair_.continuous().rho()
        * (
            pair_.Ur() ^ fvc::curl(pair_.continuous().U())
            );
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::liftModel::F() const
{
    return pair_.dispersed() * Fi();
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::liftModel::Ff() const
{
    return fvc::interpolate(pair_.dispersed()) * fvc::flux(Fi());
}


// ************************************************************************* //