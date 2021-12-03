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

#include <AntoineExtended.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {
        defineTypeNameAndDebug(AntoineExtended, 0);
        addToRunTimeSelectionTable
        (
            saturationModel,
            AntoineExtended,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::saturationModels::AntoineExtended::AntoineExtended
(
    const dictionary& dict,
    const objectRegistry& db
)
    :
    Antoine(dict, db),
    D_("D", dimless, dict),
    F_("F", dimless, dict),
    E_("E", dimless / pow(dimTemperature, F_), dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::saturationModels::AntoineExtended::~AntoineExtended()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::AntoineExtended::pSat
(
    const volScalarField& T
) const
{
    return
        dimensionedScalar(dimPressure / pow(dimTemperature, D_), 1)
        * exp(A_ + B_ / (C_ + T) + E_ * pow(T, F_))
        * pow(T, D_);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::AntoineExtended::pSatPrime
(
    const volScalarField& T
) const
{
    return pSat(T) * ((D_ + E_ * F_ * pow(T, F_)) / T - B_ / sqr(C_ + T));
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::AntoineExtended::lnPSat
(
    const volScalarField& T
) const
{
    return
        A_
        + B_ / (C_ + T)
        + D_ * log(T * dimensionedScalar(dimless / dimTemperature, 1))
        + E_ * pow(T, F_);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::AntoineExtended::Tsat
(
    const volScalarField& p
) const
{
    NotImplemented;

    return volScalarField::null();
}


// ************************************************************************* //
