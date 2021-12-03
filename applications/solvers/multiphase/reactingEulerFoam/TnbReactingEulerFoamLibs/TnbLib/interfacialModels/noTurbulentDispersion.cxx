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

#include <noTurbulentDispersion.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace turbulentDispersionModels
    {
        defineTypeNameAndDebug(noTurbulentDispersion, 0);
        addToRunTimeSelectionTable
        (
            turbulentDispersionModel,
            noTurbulentDispersion,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::noTurbulentDispersion::noTurbulentDispersion
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    turbulentDispersionModel(dict, pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::noTurbulentDispersion::
~noTurbulentDispersion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::turbulentDispersionModels::noTurbulentDispersion::D() const
{
    const fvMesh& mesh(this->pair_.phase1().mesh());

    return volScalarField::New
    (
        "zero",
        mesh,
        dimensionedScalar(dimD, 0)
    );
}


tnbLib::tmp<tnbLib::volVectorField>
tnbLib::turbulentDispersionModels::noTurbulentDispersion::F() const
{
    const fvMesh& mesh(this->pair_.phase1().mesh());

    return volVectorField::New
    (
        "zero",
        mesh,
        dimensionedVector(dimF, Zero)
    );
}


// ************************************************************************* //
