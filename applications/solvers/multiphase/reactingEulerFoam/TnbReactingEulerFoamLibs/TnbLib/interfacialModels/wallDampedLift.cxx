/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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

#include <wallDampedLift.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace liftModels
    {
        defineTypeNameAndDebug(wallDamped, 0);
        addToRunTimeSelectionTable(liftModel, wallDamped, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::liftModels::wallDamped::wallDamped
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    liftModel(dict, pair),
    liftModel_(liftModel::New(dict.subDict("lift"), pair)),
    wallDampingModel_
    (
        wallDampingModel::New(dict.subDict("wallDamping"), pair)
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::liftModels::wallDamped::~wallDamped()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::liftModels::wallDamped::Cl() const
{
    return wallDampingModel_->damp(liftModel_->Cl());
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::liftModels::wallDamped::Fi() const
{
    return wallDampingModel_->damp(liftModel_->Fi());
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::liftModels::wallDamped::F() const
{
    return wallDampingModel_->damp(liftModel_->F());
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::liftModels::wallDamped::Ff() const
{
    return wallDampingModel_->damp(liftModel_->Ff());
}


// ************************************************************************* //
