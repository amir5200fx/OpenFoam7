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

#include <phasePair.hxx>
#include <rhoThermo.hxx>

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::interfaceCompositionModel>
tnbLib::interfaceCompositionModel::New
(
    const dictionary& dict,
    const phasePair& pair
)
{
    word interfaceCompositionModelType
    (
        word(dict.lookup("type"))
        + "<"
        + pair.phase1().thermo().type()
        + ","
        + pair.phase2().thermo().type()
        + ">"
    );

    Info << "Selecting interfaceCompositionModel for "
        << pair << ": " << interfaceCompositionModelType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(interfaceCompositionModelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown interfaceCompositionModelType type "
            << interfaceCompositionModelType << endl << endl
            << "Valid interfaceCompositionModel types are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(dict, pair);
}


// ************************************************************************* //
