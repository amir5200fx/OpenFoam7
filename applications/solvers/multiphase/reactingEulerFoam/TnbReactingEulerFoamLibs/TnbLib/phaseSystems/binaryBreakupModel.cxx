/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include <binaryBreakupModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        defineTypeNameAndDebug(binaryBreakupModel, 0);
        defineRunTimeSelectionTable(binaryBreakupModel, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::diameterModels::binaryBreakupModel>
tnbLib::diameterModels::binaryBreakupModel::New
(
    const word& type,
    const populationBalanceModel& popBal,
    const dictionary& dict
)
{
    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(type);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown binary breakup model type "
            << type << nl << nl
            << "Valid binary breakup model types : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<binaryBreakupModel>(cstrIter()(popBal, dict));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diameterModels::binaryBreakupModel::binaryBreakupModel
(
    const populationBalanceModel& popBal,
    const dictionary& dict
)
    :
    popBal_(popBal)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::diameterModels::binaryBreakupModel::correct()
{}


// ************************************************************************* //
