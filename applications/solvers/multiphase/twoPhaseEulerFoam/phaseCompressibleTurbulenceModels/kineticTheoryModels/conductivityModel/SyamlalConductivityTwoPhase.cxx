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

#include "SyamlalConductivityTwoPhase.hxx"

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace conductivityModels
        {
            defineTypeNameAndDebug(Syamlal, 0);

            addToRunTimeSelectionTable
            (
                conductivityModel,
                Syamlal,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::conductivityModels::Syamlal::Syamlal
(
    const dictionary& dict
)
    :
    conductivityModel(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::conductivityModels::Syamlal::~Syamlal()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::kineticTheoryModels::conductivityModels::Syamlal::kappa
(
    const volScalarField& alpha1,
    const volScalarField& Theta,
    const volScalarField& g0,
    const volScalarField& rho1,
    const volScalarField& da,
    const dimensionedScalar& e
) const
{
    const scalar sqrtPi = sqrt(constant::mathematical::pi);

    return rho1 * da * sqrt(Theta) *
        (
            2.0 * sqr(alpha1) * g0 * (1.0 + e) / sqrtPi
            + (9.0 / 8.0) * sqrtPi * g0 * 0.25 * sqr(1.0 + e) * (2.0 * e - 1.0) * sqr(alpha1)
            / (49.0 / 16.0 - 33.0 * e / 16.0)
            + (15.0 / 32.0) * sqrtPi * alpha1 / (49.0 / 16.0 - 33.0 * e / 16.0)
            );
}


// ************************************************************************* //
