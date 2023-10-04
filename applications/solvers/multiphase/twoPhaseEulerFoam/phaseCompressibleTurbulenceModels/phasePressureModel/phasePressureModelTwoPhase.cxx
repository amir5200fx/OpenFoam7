/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

#include "phasePressureModelTwoPhase.hxx"

#include "twoPhaseSystem.hxx"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RASModels::phasePressureModel::phasePressureModel
(
    const volScalarField& alpha,
    const volScalarField& rho,
    const volVectorField& U,
    const surfaceScalarField& alphaRhoPhi,
    const surfaceScalarField& phi,
    const transportModel& phase,
    const word& propertiesName,
    const word& type
)
    :
    eddyViscosity
    <
    RASModel<EddyDiffusivity<ThermalDiffusivity
    <
    PhaseCompressibleTurbulenceModel<phaseModel>
    >>>
    >
    (
        type,
        alpha,
        rho,
        U,
        alphaRhoPhi,
        phi,
        phase,
        propertiesName
        ),

    phase_(phase),

    alphaMax_(readScalar(coeffDict_.lookup("alphaMax"))),
    preAlphaExp_(readScalar(coeffDict_.lookup("preAlphaExp"))),
    expMax_(readScalar(coeffDict_.lookup("expMax"))),
    g0_
    (
        "g0",
        dimensionSet(1, -1, -2, 0, 0),
        coeffDict_.lookup("g0")
    )
{
    nut_ == dimensionedScalar(nut_.dimensions(), 0);

    if (type == typeName)
    {
        printCoeffs(type);
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RASModels::phasePressureModel::~phasePressureModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::RASModels::phasePressureModel::read()
{
    if
        (
            eddyViscosity
            <
            RASModel<EddyDiffusivity<ThermalDiffusivity
            <
            PhaseCompressibleTurbulenceModel<phaseModel>
            >>>
            >::read()
            )
    {
        coeffDict().lookup("alphaMax") >> alphaMax_;
        coeffDict().lookup("preAlphaExp") >> preAlphaExp_;
        coeffDict().lookup("expMax") >> expMax_;
        g0_.readIfPresent(coeffDict());

        return true;
    }
    else
    {
        return false;
    }
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::RASModels::phasePressureModel::k() const
{
    NotImplemented;
    return nut_;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::RASModels::phasePressureModel::epsilon() const
{
    NotImplemented;
    return nut_;
}


tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::RASModels::phasePressureModel::R() const
{
    return volSymmTensorField::New
    (
        IOobject::groupName("R", U_.group()),
        mesh_,
        dimensioned<symmTensor>(dimensionSet(0, 2, -2, 0, 0), Zero)
    );
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::RASModels::phasePressureModel::pPrime() const
{
    tmp<volScalarField> tpPrime
    (
        g0_
        * min
        (
            exp(preAlphaExp_ * (alpha_ - alphaMax_)),
            expMax_
        )
    );

    volScalarField::Boundary& bpPrime =
        tpPrime.ref().boundaryFieldRef();

    forAll(bpPrime, patchi)
    {
        if (!bpPrime[patchi].coupled())
        {
            bpPrime[patchi] == 0;
        }
    }

    return tpPrime;
}


tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::RASModels::phasePressureModel::pPrimef() const
{
    tmp<surfaceScalarField> tpPrime
    (
        g0_
        * min
        (
            exp(preAlphaExp_ * (fvc::interpolate(alpha_) - alphaMax_)),
            expMax_
        )
    );

    surfaceScalarField::Boundary& bpPrime =
        tpPrime.ref().boundaryFieldRef();

    forAll(bpPrime, patchi)
    {
        if (!bpPrime[patchi].coupled())
        {
            bpPrime[patchi] == 0;
        }
    }

    return tpPrime;
}


tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::RASModels::phasePressureModel::devRhoReff() const
{
    return volSymmTensorField::New
    (
        IOobject::groupName("devRhoReff", U_.group()),
        mesh_,
        dimensioned<symmTensor>
        (
            rho_.dimensions() * dimensionSet(0, 2, -2, 0, 0),
            Zero
            )
    );
}


tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::RASModels::phasePressureModel::divDevRhoReff
(
    volVectorField& U
) const
{
    return tmp<fvVectorMatrix>
        (
            new fvVectorMatrix
            (
                U,
                rho_.dimensions() * dimensionSet(0, 4, -2, 0, 0)
            )
            );
}


void tnbLib::RASModels::phasePressureModel::correct()
{}


// ************************************************************************* //
