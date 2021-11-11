/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

#include <cellSizeCalculationType.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <triSurfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(cellSizeCalculationType, 0);
    defineRunTimeSelectionTable(cellSizeCalculationType, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellSizeCalculationType::cellSizeCalculationType
(
    const word& type,
    const dictionary& cellSizeCalculationTypeDict,
    const triSurfaceMesh& surface,
    const scalar& defaultCellSize
)
    :
    cellSizeCalculationTypeDict_(cellSizeCalculationTypeDict),
    surface_(surface),
    defaultCellSize_(defaultCellSize)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::cellSizeCalculationType> tnbLib::cellSizeCalculationType::New
(
    const dictionary& cellSizeCalculationTypeDict,
    const triSurfaceMesh& surface,
    const scalar& defaultCellSize
)
{
    word cellSizeCalculationTypeTypeName
    (
        cellSizeCalculationTypeDict.lookup("cellSizeCalculationType")
    );

    Info << indent << "Selecting cellSizeCalculationType "
        << cellSizeCalculationTypeTypeName << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(cellSizeCalculationTypeTypeName);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown cellSizeCalculationType type "
            << cellSizeCalculationTypeTypeName
            << endl << endl
            << "Valid cellSizeCalculationType types are :" << endl
            << dictionaryConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<cellSizeCalculationType>
        (
            cstrIter()(cellSizeCalculationTypeDict, surface, defaultCellSize)
            );
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellSizeCalculationType::~cellSizeCalculationType()
{}


// ************************************************************************* //
