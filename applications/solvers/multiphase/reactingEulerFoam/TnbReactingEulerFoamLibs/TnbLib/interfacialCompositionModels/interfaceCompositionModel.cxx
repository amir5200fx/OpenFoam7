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

#include <interfaceCompositionModel.hxx>

#include <phaseModel.hxx>
#include <phasePair.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(interfaceCompositionModel, 0);
    defineRunTimeSelectionTable(interfaceCompositionModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::interfaceCompositionModel::interfaceCompositionModel
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    pair_(pair),
    speciesNames_(dict.lookup("species"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::interfaceCompositionModel::~interfaceCompositionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::hashedWordList& tnbLib::interfaceCompositionModel::species() const
{
    return speciesNames_;
}


bool tnbLib::interfaceCompositionModel::transports
(
    word& speciesName
) const
{
    if (this->speciesNames_.contains(speciesName))
    {
        return true;
    }

    return false;
}


// ************************************************************************* //