/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpentnbLib: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://opentnbLib.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpentnbLib Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpentnbLib.

    OpentnbLib is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpentnbLib is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpentnbLib.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "XiEqModel.hxx"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(XiEqModel, 0);
    defineRunTimeSelectionTable(XiEqModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiEqModel::XiEqModel
(
    const dictionary& XiEqProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
    :
    XiEqModelCoeffs_
    (
        XiEqProperties.subDict
        (
            word(XiEqProperties.lookup("XiEqModel")) + "Coeffs"
        )
    ),
    thermo_(thermo),
    turbulence_(turbulence),
    Su_(Su)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiEqModel::~XiEqModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::XiEqModel::read(const dictionary& XiEqProperties)
{
    XiEqModelCoeffs_ = XiEqProperties.optionalSubDict(type() + "Coeffs");

    return true;
}


void tnbLib::XiEqModel::writeFields() const
{
    //***HGW It is not clear why B is written here
    if (Su_.mesh().foundObject<volSymmTensorField>("B"))
    {
        const volSymmTensorField& B =
            Su_.mesh().lookupObject<volSymmTensorField>("B");
        B.write();
    }
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::XiEqModel::calculateSchelkinEffect(const scalar uPrimeCoef) const
{
    const fvMesh& mesh = Su_.mesh();

    const volVectorField& U = mesh.lookupObject<volVectorField>("U");
    const volSymmTensorField& CT = mesh.lookupObject<volSymmTensorField>("CT");
    const volScalarField& Nv = mesh.lookupObject<volScalarField>("Nv");
    const volSymmTensorField& nsv =
        mesh.lookupObject<volSymmTensorField>("nsv");

    tmp<volScalarField> tN
    (
        volScalarField::New
        (
            "tN",
            mesh,
            dimensionedScalar(Nv.dimensions(), 0)
        )
    );
    volScalarField& N = tN.ref();
    N.primitiveFieldRef() = Nv.primitiveField() * pow(mesh.V(), 2.0 / 3.0);

    volSymmTensorField ns
    (
        IOobject
        (
            "tns",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedSymmTensor
        (
            "zero",
            nsv.dimensions(),
            Zero
        )
    );
    ns.primitiveFieldRef() = nsv.primitiveField() * pow(mesh.V(), 2.0 / 3.0);

    const volVectorField Uhat
    (
        U / (mag(U) + dimensionedScalar(U.dimensions(), 1e-4))
    );

    const volScalarField nr(sqrt(max(N - (Uhat & ns & Uhat), scalar(1e-4))));

    const scalarField cellWidth(pow(mesh.V(), 1.0 / 3.0));

    const scalarField upLocal(uPrimeCoef * sqrt((U & CT & U) * cellWidth));

    const scalarField deltaUp(upLocal * (max(scalar(1), pow(nr, 0.5)) - 1.0));

    // Re use tN
    N.primitiveFieldRef() = upLocal * (max(scalar(1), pow(nr, 0.5)) - 1.0);

    return tN;
}


// ************************************************************************* //
