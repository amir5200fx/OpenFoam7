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

#include <ArdenBuck.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {
        defineTypeNameAndDebug(ArdenBuck, 0);
        addToRunTimeSelectionTable(saturationModel, ArdenBuck, dictionary);
    }
}

static const tnbLib::dimensionedScalar zeroC("", tnbLib::dimTemperature, 273.15);
static const tnbLib::dimensionedScalar A("", tnbLib::dimPressure, 611.21);
static const tnbLib::dimensionedScalar B("", tnbLib::dimless, 18.678);
static const tnbLib::dimensionedScalar C("", tnbLib::dimTemperature, 234.5);
static const tnbLib::dimensionedScalar D("", tnbLib::dimTemperature, 257.14);

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::ArdenBuck::xByTC
(
    const volScalarField& TC
) const
{
    return (B - TC / C) / (D + TC);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::saturationModels::ArdenBuck::ArdenBuck
(
    const dictionary& dict,
    const objectRegistry& db
)
    :
    saturationModel(db)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::saturationModels::ArdenBuck::~ArdenBuck()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::ArdenBuck::pSat
(
    const volScalarField& T
) const
{
    volScalarField TC(T - zeroC);

    return A * exp(TC * xByTC(TC));
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::ArdenBuck::pSatPrime
(
    const volScalarField& T
) const
{
    volScalarField TC(T - zeroC);

    volScalarField x(xByTC(TC));

    return A * exp(TC * x) * (D * x - TC / C) / (D + TC);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::ArdenBuck::lnPSat
(
    const volScalarField& T
) const
{
    volScalarField TC(T - zeroC);

    return log(A.value()) + TC * xByTC(TC);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::ArdenBuck::Tsat
(
    const volScalarField& p
) const
{
    NotImplemented;

    return volScalarField::null();
}


// ************************************************************************* //
