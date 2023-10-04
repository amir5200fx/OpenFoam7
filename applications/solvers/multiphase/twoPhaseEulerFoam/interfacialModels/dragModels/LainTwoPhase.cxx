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

#include "LainTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {
        defineTypeNameAndDebug(Lain, 0);
        addToRunTimeSelectionTable(dragModel, Lain, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dragModels::Lain::Lain
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    dragModel(dict, pair, registerObject)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dragModels::Lain::~Lain()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::dragModels::Lain::CdRe() const
{
    volScalarField Re(pair_.Re());

    return
        neg(Re - 1.5) * 16.0
        + pos0(Re - 1.5) * neg(Re - 80.0) * 14.9 * pow(Re, 0.22)
        + pos0(Re - 80.0) * neg(Re - 1500.0) * 48 * (1.0 - 2.21 / sqrt(max(Re, small)))
        + pos0(Re - 1500.0) * 2.61 * Re;
}


// ************************************************************************* //
