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

#include "SyamlalRogersOBrienPressureTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace granularPressureModels
        {
            defineTypeNameAndDebug(SyamlalRogersOBrien, 0);

            addToRunTimeSelectionTable
            (
                granularPressureModel,
                SyamlalRogersOBrien,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::granularPressureModels::SyamlalRogersOBrien::
SyamlalRogersOBrien
(
    const dictionary& dict
)
    :
    granularPressureModel(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::kineticTheoryModels::granularPressureModels::SyamlalRogersOBrien::
~SyamlalRogersOBrien()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::kineticTheoryModels::granularPressureModels::SyamlalRogersOBrien::
granularPressureCoeff
(
    const volScalarField& alpha1,
    const volScalarField& g0,
    const volScalarField& rho1,
    const dimensionedScalar& e
) const
{

    return 2.0 * rho1 * (1.0 + e) * sqr(alpha1) * g0;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::kineticTheoryModels::granularPressureModels::SyamlalRogersOBrien::
granularPressureCoeffPrime
(
    const volScalarField& alpha1,
    const volScalarField& g0,
    const volScalarField& g0prime,
    const volScalarField& rho1,
    const dimensionedScalar& e
) const
{
    return rho1 * alpha1 * (1.0 + e) * (4.0 * g0 + 2.0 * g0prime * alpha1);
}


// ************************************************************************* //
