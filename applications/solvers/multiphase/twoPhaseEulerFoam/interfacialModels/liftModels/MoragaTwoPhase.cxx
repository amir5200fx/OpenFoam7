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

#include "MoragaTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace liftModels
    {
        defineTypeNameAndDebug(Moraga, 0);
        addToRunTimeSelectionTable(liftModel, Moraga, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::liftModels::Moraga::Moraga
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    liftModel(dict, pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::liftModels::Moraga::~Moraga()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::liftModels::Moraga::Cl() const
{
    volScalarField Re(pair_.Re());

    volScalarField sqrSr
    (
        sqr(pair_.dispersed().d())
        / pair_.continuous().nu()
        * mag(fvc::grad(pair_.continuous().U()))
    );

    if
        (
            min(Re).value() < 1200.0
            || max(Re).value() > 18800.0
            || min(sqrSr).value() < 0.0016
            || max(sqrSr).value() > 0.04
            )
    {
        WarningInFunction
            << "Re and/or Sr are out of the range of applicability of the "
            << "Moraga model. Clamping to range bounds"
            << endl;
    }

    Re.min(1200.0);
    Re.max(18800.0);

    sqrSr.min(0.0016);
    sqrSr.max(0.04);

    return 0.2 * exp(-Re * sqrSr / 3.6e5 - 0.12) * exp(Re * sqrSr / 3.0e7);
}


// ************************************************************************* //
