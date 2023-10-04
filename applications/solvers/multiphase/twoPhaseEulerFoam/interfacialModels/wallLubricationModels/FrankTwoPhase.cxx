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

#include "FrankTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallLubricationModels
    {
        defineTypeNameAndDebug(Frank, 0);
        addToRunTimeSelectionTable
        (
            wallLubricationModel,
            Frank,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallLubricationModels::Frank::Frank
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    wallLubricationModel(dict, pair),
    Cwd_("Cwd", dimless, dict),
    Cwc_("Cwc", dimless, dict),
    p_(readScalar(dict.lookup("p")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallLubricationModels::Frank::~Frank()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::wallLubricationModels::Frank::Fi() const
{
    volVectorField Ur(pair_.Ur());

    const volVectorField& n(nWall());
    const volScalarField& y(yWall());

    volScalarField Eo(pair_.Eo());
    volScalarField yTilde(y / (Cwc_ * pair_.dispersed().d()));

    return
        (
            pos0(Eo - 1.0) * neg(Eo - 5.0) * exp(-0.933 * Eo + 0.179)
            + pos0(Eo - 5.0) * neg(Eo - 33.0) * (0.00599 * Eo - 0.0187)
            + pos0(Eo - 33.0) * 0.179
            )
        * max
        (
            dimensionedScalar(dimless / dimLength, 0),
            (1.0 - yTilde) / (Cwd_ * y * pow(yTilde, p_ - 1.0))
        )
        * pair_.continuous().rho()
        * magSqr(Ur - (Ur & n) * n)
        * n;
}


// ************************************************************************* //
