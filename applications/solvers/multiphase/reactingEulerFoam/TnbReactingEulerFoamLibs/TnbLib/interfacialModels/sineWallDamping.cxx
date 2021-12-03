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

#include <sineWallDamping.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallDampingModels
    {
        defineTypeNameAndDebug(sine, 0);
        addToRunTimeSelectionTable
        (
            wallDampingModel,
            sine,
            dictionary
        );
    }
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::wallDampingModels::sine::limiter() const
{
    return sin
    (
        constant::mathematical::piByTwo
        * min(yWall() / (Cd_ * pair_.dispersed().d()), scalar(1))
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallDampingModels::sine::sine
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    interpolated(dict, pair),
    Cd_("Cd", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallDampingModels::sine::~sine()
{}


// ************************************************************************* //
