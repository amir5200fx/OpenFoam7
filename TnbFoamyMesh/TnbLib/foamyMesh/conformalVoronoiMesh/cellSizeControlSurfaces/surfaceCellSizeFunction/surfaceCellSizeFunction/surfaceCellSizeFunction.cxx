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

#include <surfaceCellSizeFunction.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(surfaceCellSizeFunction, 0);
    defineRunTimeSelectionTable(surfaceCellSizeFunction, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceCellSizeFunction::surfaceCellSizeFunction
(
    const word& type,
    const dictionary& surfaceCellSizeFunctionDict,
    const searchableSurface& surface,
    const scalar& defaultCellSize
)
    :
    dictionary(surfaceCellSizeFunctionDict),
    surface_(surface),
    coeffsDict_(optionalSubDict(type + "Coeffs")),
    defaultCellSize_(defaultCellSize),
    refinementFactor_
    (
        lookupOrDefault<scalar>("refinementFactor", 1.0)
    )
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::surfaceCellSizeFunction> tnbLib::surfaceCellSizeFunction::New
(
    const dictionary& surfaceCellSizeFunctionDict,
    const searchableSurface& surface,
    const scalar& defaultCellSize
)
{
    word surfaceCellSizeFunctionTypeName
    (
        surfaceCellSizeFunctionDict.lookup("surfaceCellSizeFunction")
    );

    Info << indent << "Selecting surfaceCellSizeFunction "
        << surfaceCellSizeFunctionTypeName << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(surfaceCellSizeFunctionTypeName);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown surfaceCellSizeFunction type "
            << surfaceCellSizeFunctionTypeName
            << endl << endl
            << "Valid surfaceCellSizeFunction types are :" << endl
            << dictionaryConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<surfaceCellSizeFunction>
        (
            cstrIter()(surfaceCellSizeFunctionDict, surface, defaultCellSize)
            );
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceCellSizeFunction::~surfaceCellSizeFunction()
{}


// ************************************************************************* //
