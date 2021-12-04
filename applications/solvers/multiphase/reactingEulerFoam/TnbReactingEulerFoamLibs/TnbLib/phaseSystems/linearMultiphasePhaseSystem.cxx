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

#include <linearMultiphasePhaseSystem.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace blendingMethods
    {
        defineTypeNameAndDebug(linear, 0);

        addToRunTimeSelectionTable
        (
            blendingMethod,
            linear,
            dictionary
        );
    }
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blendingMethods::linear::linear
(
    const dictionary& dict,
    const wordList& phaseNames
)
    :
    blendingMethod(dict)
{
    forAllConstIter(wordList, phaseNames, iter)
    {
        const word nameFull
        (
            IOobject::groupName("minFullyContinuousAlpha", *iter)
        );

        minFullyContinuousAlpha_.insert
        (
            *iter,
            dimensionedScalar
            (
                nameFull,
                dimless,
                dict.lookup(nameFull)
            )
        );

        const word namePart
        (
            IOobject::groupName("minPartlyContinuousAlpha", *iter)
        );

        minPartlyContinuousAlpha_.insert
        (
            *iter,
            dimensionedScalar
            (
                namePart,
                dimless,
                dict.lookup(namePart)
            )
        );

        if
            (
                minFullyContinuousAlpha_[*iter]
                < minPartlyContinuousAlpha_[*iter]
                )
        {
            FatalErrorInFunction
                << "The supplied fully continuous volume fraction for "
                << *iter
                << " is less than the partly continuous value."
                << endl << exit(FatalError);
        }
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blendingMethods::linear::~linear()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::linear::f1
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    const dimensionedScalar
        minFullAlpha(minFullyContinuousAlpha_[phase2.name()]);
    const dimensionedScalar
        minPartAlpha(minPartlyContinuousAlpha_[phase2.name()]);

    return
        min
        (
            max
            (
                (phase2 - minPartAlpha)
                / (minFullAlpha - minPartAlpha + small),
                scalar(0)
            ),
            scalar(1)
        );
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::linear::f2
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    const dimensionedScalar
        minFullAlpha(minFullyContinuousAlpha_[phase1.name()]);
    const dimensionedScalar
        minPartAlpha(minPartlyContinuousAlpha_[phase1.name()]);

    return
        min
        (
            max
            (
                (phase1 - minPartAlpha)
                / (minFullAlpha - minPartAlpha + small),
                scalar(0)
            ),
            scalar(1)
        );
}


// ************************************************************************* //
