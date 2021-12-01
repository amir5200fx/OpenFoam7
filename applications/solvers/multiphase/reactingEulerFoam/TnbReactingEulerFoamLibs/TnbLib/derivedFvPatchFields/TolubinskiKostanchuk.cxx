/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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

#include <TolubinskiKostanchuk.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace departureDiameterModels
        {
            defineTypeNameAndDebug(TolubinskiKostanchuk, 0);
            addToRunTimeSelectionTable
            (
                departureDiameterModel,
                TolubinskiKostanchuk,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureDiameterModels::
TolubinskiKostanchuk::TolubinskiKostanchuk
(
    const dictionary& dict
)
    :
    departureDiameterModel(),
    dRef_(dict.lookupOrDefault<scalar>("dRef", 6e-4)),
    dMax_(dict.lookupOrDefault<scalar>("dMax", 0.0014)),
    dMin_(dict.lookupOrDefault<scalar>("dMin", 1e-6))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureDiameterModels::
TolubinskiKostanchuk::~TolubinskiKostanchuk()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::wallBoilingModels::departureDiameterModels::
TolubinskiKostanchuk::dDeparture
(
    const phaseModel& liquid,
    const phaseModel& vapor,
    const label patchi,
    const scalarField& Tl,
    const scalarField& Tsatw,
    const scalarField& L
) const
{
    return max(min(dRef_ * exp(-(Tsatw - Tl) / 45), dMax_), dMin_);
}


void tnbLib::wallBoilingModels::departureDiameterModels::
TolubinskiKostanchuk::write(Ostream& os) const
{
    departureDiameterModel::write(os);
    writeEntry(os, "dRef", dRef_);
    writeEntry(os, "dMax", dMax_);
    writeEntry(os, "dMin", dMin_);
}


// ************************************************************************* //
