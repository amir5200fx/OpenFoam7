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

#include <noBlending.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace blendingMethods
    {
        defineTypeNameAndDebug(noBlending, 0);

        addToRunTimeSelectionTable
        (
            blendingMethod,
            noBlending,
            dictionary
        );
    }
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blendingMethods::noBlending::noBlending
(
    const dictionary& dict,
    const wordList& phaseNames
)
    :
    blendingMethod(dict),
    continuousPhase_(dict.lookup("continuousPhase"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blendingMethods::noBlending::~noBlending()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::noBlending::f1
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    const fvMesh& mesh(phase1.mesh());

    return volScalarField::New
    (
        "f",
        mesh,
        dimensionedScalar(dimless, phase2.name() == continuousPhase_)
    );
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::blendingMethods::noBlending::f2
(
    const phaseModel& phase1,
    const phaseModel& phase2
) const
{
    const fvMesh& mesh(phase1.mesh());

    return volScalarField::New
    (
        "f",
        mesh,
        dimensionedScalar(dimless, phase1.name() == continuousPhase_)
    );
}


// ************************************************************************* //
