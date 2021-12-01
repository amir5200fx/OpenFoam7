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

#include <Lavieville.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace partitioningModels
        {
            defineTypeNameAndDebug(Lavieville, 0);
            addToRunTimeSelectionTable
            (
                partitioningModel,
                Lavieville,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::partitioningModels::
Lavieville::Lavieville(const dictionary& dict)
    :
    partitioningModel(),
    alphaCrit_(readScalar(dict.lookup("alphaCrit")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::partitioningModels::
Lavieville::~Lavieville()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::wallBoilingModels::partitioningModels::
Lavieville::fLiquid
(
    const scalarField& alphaLiquid
) const
{
    return
        pos0(alphaLiquid - alphaCrit_)
        * (
            1 - 0.5 * exp(-20 * (alphaLiquid - alphaCrit_))
            )
        + neg(alphaLiquid - alphaCrit_)
        * (
            0.5 * pow(alphaLiquid / alphaCrit_, 20 * alphaCrit_)
            );
}


void tnbLib::wallBoilingModels::partitioningModels::
Lavieville::write(Ostream& os) const
{
    partitioningModel::write(os);
    writeEntry(os, "alphaCrit", alphaCrit_);
}


// ************************************************************************* //
