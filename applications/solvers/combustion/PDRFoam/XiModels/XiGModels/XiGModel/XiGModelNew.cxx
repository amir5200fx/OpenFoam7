/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpentnbLib: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://opentnbLib.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpentnbLib Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpentnbLib.

    OpentnbLib is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpentnbLib is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpentnbLib.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "XiGModel.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::XiGModel> tnbLib::XiGModel::New
(
    const dictionary& propDict,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
{
    const word modelType(propDict.lookup("XiGModel"));

    Info << "Selecting flame-wrinkling model " << modelType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown XiGModel type "
            << modelType << nl << nl
            << "Valid XiGModels are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<XiGModel>(cstrIter()(propDict, thermo, turbulence, Su));
}


// ************************************************************************* //
