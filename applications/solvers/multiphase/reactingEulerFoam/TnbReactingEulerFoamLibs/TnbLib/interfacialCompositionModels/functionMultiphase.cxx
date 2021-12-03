/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include <functionMultiphase.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {
        defineTypeNameAndDebug(function1, 0);
        addToRunTimeSelectionTable(saturationModel, function1, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::saturationModels::function1::function1
(
    const dictionary& dict,
    const objectRegistry& db
)
    :
    saturationModel(db),
    function_
    (
        Function1<scalar>::New("function", dict)
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::saturationModels::function1::~function1()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::function1::pSat
(
    const volScalarField& T
) const
{
    NotImplemented;
    return volScalarField::null();
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::function1::pSatPrime
(
    const volScalarField& T
) const
{
    NotImplemented;
    return volScalarField::null();
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::function1::lnPSat
(
    const volScalarField& T
) const
{
    NotImplemented;
    return volScalarField::null();
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::saturationModels::function1::Tsat
(
    const volScalarField& p
) const
{
    tmp<volScalarField> tTsat
    (
        volScalarField::New
        (
            "Tsat",
            p.mesh(),
            dimensionedScalar(dimTemperature, 0)
        )
    );

    volScalarField& Tsat = tTsat.ref();

    forAll(Tsat, celli)
    {
        Tsat[celli] = function_->value(p[celli]);
    }

    volScalarField::Boundary& TsatBf = Tsat.boundaryFieldRef();

    forAll(Tsat.boundaryField(), patchi)
    {
        scalarField& Tsatp = TsatBf[patchi];
        const scalarField& pp = p.boundaryField()[patchi];

        forAll(Tsatp, facei)
        {
            Tsatp[facei] = function_->value(pp[facei]);

        }
    }

    return tTsat;
}


// ************************************************************************* //
