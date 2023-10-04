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

#include "AntalTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallLubricationModels
    {
        defineTypeNameAndDebug(Antal, 0);
        addToRunTimeSelectionTable
        (
            wallLubricationModel,
            Antal,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallLubricationModels::Antal::Antal
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    wallLubricationModel(dict, pair),
    Cw1_("Cw1", dimless, dict),
    Cw2_("Cw2", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallLubricationModels::Antal::~Antal()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::wallLubricationModels::Antal::Fi() const
{
    volVectorField Ur(pair_.Ur());

    const volVectorField& n(nWall());

    return
        max
        (
            dimensionedScalar(dimless / dimLength, 0),
            Cw1_ / pair_.dispersed().d() + Cw2_ / yWall()
        )
        * pair_.continuous().rho()
        * magSqr(Ur - (Ur & n) * n)
        * n;
}


// ************************************************************************* //
