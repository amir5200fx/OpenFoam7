/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

#include <Beetstra.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {
        defineTypeNameAndDebug(Beetstra, 0);
        addToRunTimeSelectionTable(dragModel, Beetstra, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModels::Beetstra::Beetstra
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    dragModel(dict, pair, registerObject),
    residualRe_("residualRe", dimless, dict.lookup("residualRe"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModels::Beetstra::~Beetstra()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::dragModels::Beetstra::CdRe() const
{
    volScalarField alpha1
    (
        max(pair_.dispersed(), pair_.continuous().residualAlpha())
    );

    volScalarField alpha2
    (
        max(scalar(1) - pair_.dispersed(), pair_.continuous().residualAlpha())
    );

    volScalarField Res(alpha2 * pair_.Re());

    volScalarField ResLim
    (
        "ReLim",
        max(Res, residualRe_)
    );

    volScalarField F0
    (
        "F0",
        10 * alpha1 / sqr(alpha2) + sqr(alpha2) * (1 + 1.5 * sqrt(alpha1))
    );

    volScalarField F1
    (
        "F1",
        0.413 * Res / (24 * sqr(alpha2)) * (1.0 / alpha2
            + 3 * alpha1 * alpha2 + 8.4 * pow(ResLim, -0.343))
        / (1 + pow(10.0, 3 * alpha1) * pow(ResLim, -(1 + 4 * alpha1) / 2.0))
    );

    return 24 * alpha2 * (F0 + F1);
}


// ************************************************************************* //
