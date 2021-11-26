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

#include "twoPhaseMixtureThermo.hxx"

#include <gradientEnergyFvPatchScalarField.hxx>
#include <mixedEnergyFvPatchScalarField.hxx>
#include <collatedFileOperation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(twoPhaseMixtureThermo, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::twoPhaseMixtureThermo::twoPhaseMixtureThermo
(
    const volVectorField& U,
    const surfaceScalarField& phi
)
    :
    psiThermo(U.mesh(), word::null),
    twoPhaseMixture(U.mesh(), *this),
    interfaceProperties(alpha1(), U, *this),
    thermo1_(nullptr),
    thermo2_(nullptr)
{
    {
        volScalarField T1
        (
            IOobject
            (
                IOobject::groupName("T", phase1Name()),
                U.mesh().time().timeName(),
                U.mesh()
            ),
            T_,
            calculatedFvPatchScalarField::typeName
        );
        T1.write();
    }

    {
        volScalarField T2
        (
            IOobject
            (
                IOobject::groupName("T", phase2Name()),
                U.mesh().time().timeName(),
                U.mesh()
            ),
            T_,
            calculatedFvPatchScalarField::typeName
        );
        T2.write();
    }

    // Note: we're writing files to be read in immediately afterwards.
    //       Avoid any thread-writing problems.
    fileHandler().flush();

    thermo1_ = rhoThermo::New(U.mesh(), phase1Name());
    thermo2_ = rhoThermo::New(U.mesh(), phase2Name());

    // thermo1_->validate(phase1Name(), "e");
    // thermo2_->validate(phase2Name(), "e");

    correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::twoPhaseMixtureThermo::~twoPhaseMixtureThermo()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::twoPhaseMixtureThermo::correctThermo()
{
    thermo1_->T() = T_;
    thermo1_->he() = thermo1_->he(p_, T_);
    thermo1_->correct();

    thermo2_->T() = T_;
    thermo2_->he() = thermo2_->he(p_, T_);
    thermo2_->correct();
}


void tnbLib::twoPhaseMixtureThermo::correct()
{
    psi_ = alpha1() * thermo1_->psi() + alpha2() * thermo2_->psi();
    mu_ = alpha1() * thermo1_->mu() + alpha2() * thermo2_->mu();
    alpha_ = alpha1() * thermo1_->alpha() + alpha2() * thermo2_->alpha();

    interfaceProperties::correct();
}


tnbLib::word tnbLib::twoPhaseMixtureThermo::thermoName() const
{
    return thermo1_->thermoName() + ',' + thermo2_->thermoName();
}


bool tnbLib::twoPhaseMixtureThermo::incompressible() const
{
    return thermo1_->incompressible() && thermo2_->incompressible();
}


bool tnbLib::twoPhaseMixtureThermo::isochoric() const
{
    return thermo1_->isochoric() && thermo2_->isochoric();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::he
(
    const volScalarField& p,
    const volScalarField& T
) const
{
    return alpha1() * thermo1_->he(p, T) + alpha2() * thermo2_->he(p, T);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::he
(
    const scalarField& p,
    const scalarField& T,
    const labelList& cells
) const
{
    return
        scalarField(alpha1(), cells) * thermo1_->he(p, T, cells)
        + scalarField(alpha2(), cells) * thermo2_->he(p, T, cells);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::he
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->he(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->he(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::hc() const
{
    return alpha1() * thermo1_->hc() + alpha2() * thermo2_->hc();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::THE
(
    const scalarField& h,
    const scalarField& p,
    const scalarField& T0,
    const labelList& cells
) const
{
    NotImplemented;
    return T0;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::THE
(
    const scalarField& h,
    const scalarField& p,
    const scalarField& T0,
    const label patchi
) const
{
    NotImplemented;
    return T0;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::Cp() const
{
    return alpha1() * thermo1_->Cp() + alpha2() * thermo2_->Cp();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::Cp
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->Cp(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->Cp(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::Cv() const
{
    return alpha1() * thermo1_->Cv() + alpha2() * thermo2_->Cv();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::Cv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->Cv(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->Cv(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::gamma() const
{
    return alpha1() * thermo1_->gamma() + alpha2() * thermo2_->gamma();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::gamma
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->gamma(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->gamma(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::Cpv() const
{
    return alpha1() * thermo1_->Cpv() + alpha2() * thermo2_->Cpv();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::Cpv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->Cpv(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->Cpv(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::CpByCpv() const
{
    return
        alpha1() * thermo1_->CpByCpv()
        + alpha2() * thermo2_->CpByCpv();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::CpByCpv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->CpByCpv(p, T, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->CpByCpv(p, T, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::W() const
{
    return alpha1() * thermo1_->W() + alpha2() * thermo1_->W();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::W
(
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->W(patchi)
        + alpha2().boundaryField()[patchi] * thermo1_->W(patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::nu() const
{
    return mu() / (alpha1() * thermo1_->rho() + alpha2() * thermo2_->rho());
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::nu
(
    const label patchi
) const
{
    return
        mu(patchi)
        / (
            alpha1().boundaryField()[patchi] * thermo1_->rho(patchi)
            + alpha2().boundaryField()[patchi] * thermo2_->rho(patchi)
            );
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::kappa() const
{
    return alpha1() * thermo1_->kappa() + alpha2() * thermo2_->kappa();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::kappa
(
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->kappa(patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->kappa(patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::alphahe() const
{
    return
        alpha1() * thermo1_->alphahe()
        + alpha2() * thermo2_->alphahe();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::alphahe
(
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->alphahe(patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->alphahe(patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::kappaEff
(
    const volScalarField& alphat
) const
{
    return
        alpha1() * thermo1_->kappaEff(alphat)
        + alpha2() * thermo2_->kappaEff(alphat);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::kappaEff
(
    const scalarField& alphat,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->kappaEff(alphat, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->kappaEff(alphat, patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::twoPhaseMixtureThermo::alphaEff
(
    const volScalarField& alphat
) const
{
    return
        alpha1() * thermo1_->alphaEff(alphat)
        + alpha2() * thermo2_->alphaEff(alphat);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::twoPhaseMixtureThermo::alphaEff
(
    const scalarField& alphat,
    const label patchi
) const
{
    return
        alpha1().boundaryField()[patchi] * thermo1_->alphaEff(alphat, patchi)
        + alpha2().boundaryField()[patchi] * thermo2_->alphaEff(alphat, patchi);
}


bool tnbLib::twoPhaseMixtureThermo::read()
{
    if (psiThermo::read())
    {
        return interfaceProperties::read();
    }
    else
    {
        return false;
    }
}


// ************************************************************************* //
