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

#include "CarnahanStarlingRadialTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace radialModels
        {
            defineTypeNameAndDebug(CarnahanStarling, 0);

            addToRunTimeSelectionTable
            (
                radialModel,
                CarnahanStarling,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::radialModels::CarnahanStarling::CarnahanStarling
(
    const dictionary& dict
)
    :
    radialModel(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::radialModels::CarnahanStarling::~CarnahanStarling()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::kineticTheoryModels::radialModels::CarnahanStarling::g0
(
    const volScalarField& alpha,
    const dimensionedScalar& alphaMinFriction,
    const dimensionedScalar& alphaMax
) const
{

    return
        1.0 / (1.0 - alpha)
        + 3.0 * alpha / (2.0 * sqr(1.0 - alpha))
        + sqr(alpha) / (2.0 * pow3(1.0 - alpha));
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::kineticTheoryModels::radialModels::CarnahanStarling::g0prime
(
    const volScalarField& alpha,
    const dimensionedScalar& alphaMinFriction,
    const dimensionedScalar& alphaMax
) const
{
    return
        2.5 / sqr(1.0 - alpha)
        + 4.0 * alpha / pow3(1.0 - alpha)
        + 1.5 * sqr(alpha) / pow4(1.0 - alpha);
}


// ************************************************************************* //