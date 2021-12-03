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

#include <TomiyamaKataokaZunSakaguchi.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {
        defineTypeNameAndDebug(TomiyamaKataokaZunSakaguchi, 0);
        addToRunTimeSelectionTable
        (
            dragModel,
            TomiyamaKataokaZunSakaguchi,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModels::TomiyamaKataokaZunSakaguchi::TomiyamaKataokaZunSakaguchi
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    dragModel(dict, pair, registerObject),
    residualRe_("residualRe", dimless, dict),
    residualEo_("residualEo", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModels::TomiyamaKataokaZunSakaguchi::~TomiyamaKataokaZunSakaguchi()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::dragModels::TomiyamaKataokaZunSakaguchi::CdRe() const
{
    volScalarField Re(pair_.Re());
    volScalarField Eo(max(pair_.Eo(), residualEo_));

    return
        max
        (
            24 * (1 + 0.15 * pow(Re, 0.687)) / max(Re, residualRe_),
            8 * Eo / (3 * (Eo + 4.0))
        )
        * max(pair_.Re(), residualRe_);
}


// ************************************************************************* //
