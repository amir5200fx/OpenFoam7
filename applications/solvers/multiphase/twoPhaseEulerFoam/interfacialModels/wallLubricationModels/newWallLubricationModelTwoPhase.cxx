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

#include "wallLubricationModelTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::wallLubricationModel> tnbLib::wallLubricationModel::New
(
    const dictionary& dict,
    const phasePair& pair
)
{
    word wallLubricationModelType(dict.lookup("type"));

    Info << "Selecting wallLubricationModel for "
        << pair << ": " << wallLubricationModelType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(wallLubricationModelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown wallLubricationModelType type "
            << wallLubricationModelType << endl << endl
            << "Valid wallLubricationModel types are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(dict, pair);
}


// ************************************************************************* //
