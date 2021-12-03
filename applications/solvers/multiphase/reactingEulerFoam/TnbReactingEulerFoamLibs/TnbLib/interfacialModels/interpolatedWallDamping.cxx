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

#include <interpolatedWallDamping.hxx>

#include <phasePair.hxx>
#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallDampingModels
    {
        defineTypeNameAndDebug(interpolated, 0);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallDampingModels::interpolated::interpolated
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    wallDampingModel(dict, pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallDampingModels::interpolated::~interpolated()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::wallDampingModels::interpolated::damp
(
    const tmp<volScalarField>& F
) const
{
    return limiter() * F;
}


tnbLib::tmp<tnbLib::volVectorField>
tnbLib::wallDampingModels::interpolated::damp
(
    const tmp<volVectorField>& F
) const
{
    return limiter() * F;
}


tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::wallDampingModels::interpolated::damp
(
    const tmp<surfaceScalarField>& Ff
) const
{
    return fvc::interpolate(limiter()) * Ff;
}


// ************************************************************************* //
