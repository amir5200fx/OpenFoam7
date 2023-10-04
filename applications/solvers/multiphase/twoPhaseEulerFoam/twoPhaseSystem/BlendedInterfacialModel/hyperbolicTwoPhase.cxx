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

#include "hyperbolicTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace blendingMethods
    {
        defineTypeNameAndDebug(hyperbolic, 0);

        addToRunTimeSelectionTable
        (
            blendingMethod,
            hyperbolic,
            dictionary
        );
    }
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blendingMethods::hyperbolic::hyperbolic
(
    const dictionary& dict,
    const wordList& phaseNames
)
    :
    blendingMethod(dict),
    transitionAlphaScale_
    (
        "transitionAlphaScale",
        dimless,
        dict.lookup("transitionAlphaScale")
    )
{
    forAllConstIter(wordList, phaseNames, iter)
    {
        const word name(IOobject::groupName("maxDispersedAlpha", *iter));

        maxDispersedAlpha_.insert
        (
            *iter,
            dimensionedScalar
            (
                name,
                dimless,
                dict.lookup(name)
            )
        );
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blendingMethods::hyperbolic::~hyperbolic()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::hyperbolic::f1
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    return
        (
            1
            + tanh
            (
                (4 / transitionAlphaScale_)
                * (phase1 - maxDispersedAlpha_[phase1.name()])
            )
            ) / 2;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::hyperbolic::f2
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    return
        (
            1
            + tanh
            (
                (4 / transitionAlphaScale_)
                * (maxDispersedAlpha_[phase2.name()] - phase2)
            )
            ) / 2;
}


// ************************************************************************* //
