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

#include "GidaspowErgunWenYuTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"
#include "ErgunTwoPhase.hxx"
#include "WenYuTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {
        defineTypeNameAndDebug(GidaspowErgunWenYu, 0);
        addToRunTimeSelectionTable(dragModel, GidaspowErgunWenYu, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModels::GidaspowErgunWenYu::GidaspowErgunWenYu
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    dragModel(dict, pair, registerObject),
    Ergun_
    (
        new Ergun
        (
            dict,
            pair,
            false
        )
    ),
    WenYu_
    (
        new WenYu
        (
            dict,
            pair,
            false
        )
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModels::GidaspowErgunWenYu::~GidaspowErgunWenYu()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::dragModels::GidaspowErgunWenYu::CdRe() const
{
    return
        pos0(pair_.continuous() - 0.8) * WenYu_->CdRe()
        + neg(pair_.continuous() - 0.8) * Ergun_->CdRe();
}


// ************************************************************************* //
