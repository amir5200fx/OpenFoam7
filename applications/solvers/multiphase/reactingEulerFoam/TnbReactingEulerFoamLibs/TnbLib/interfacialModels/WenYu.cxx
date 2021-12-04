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

#include <WenYu.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {
        defineTypeNameAndDebug(WenYu, 0);
        addToRunTimeSelectionTable(dragModel, WenYu, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModels::WenYu::WenYu
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    dragModel(dict, pair, registerObject),
    residualRe_("residualRe", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModels::WenYu::~WenYu()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::dragModels::WenYu::CdRe() const
{
    volScalarField alpha2
    (
        max(scalar(1) - pair_.dispersed(), pair_.continuous().residualAlpha())
    );

    volScalarField Res(alpha2 * pair_.Re());
    volScalarField CdsRes
    (
        neg(Res - 1000) * 24 * (1.0 + 0.15 * pow(Res, 0.687))
        + pos0(Res - 1000) * 0.44 * max(Res, residualRe_)
    );

    return
        CdsRes
        * pow(alpha2, -3.65)
        * max(pair_.continuous(), pair_.continuous().residualAlpha());
}


// ************************************************************************* //