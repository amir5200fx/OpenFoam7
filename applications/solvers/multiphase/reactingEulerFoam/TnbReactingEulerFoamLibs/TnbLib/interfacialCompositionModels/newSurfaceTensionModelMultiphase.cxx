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

#include <surfaceTensionModelMultiphase.hxx>

#include <phasePair.hxx>

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::surfaceTensionModel >
tnbLib::surfaceTensionModel::New
(
    const dictionary& dict,
    const phasePair& pair
)
{
    word surfaceTensionModelType(dict.lookup("type"));

    Info << "Selecting surfaceTensionModel for "
        << pair << ": " << surfaceTensionModelType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(surfaceTensionModelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown surfaceTensionModelType type "
            << surfaceTensionModelType << endl << endl
            << "Valid surfaceTensionModel types are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(dict, pair, true);
}


// ************************************************************************* //
