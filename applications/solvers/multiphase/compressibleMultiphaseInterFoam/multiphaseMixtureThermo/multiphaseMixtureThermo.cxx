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

#include "multiphaseMixtureThermo.hxx"

#include "alphaContactAngleFvPatchScalarField.hxx"

#include <Time.hxx>
#include <subCycle.hxx>
#include <MULES.hxx>
#include <fvcDiv.hxx>
#include <fvcGrad.hxx>
#include <fvcSnGrad.hxx>
#include <fvcFlux.hxx>
#include <fvcMeshPhi.hxx>
#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(multiphaseMixtureThermo, 0);
}


const tnbLib::scalar tnbLib::multiphaseMixtureThermo::convertToRad =
tnbLib::constant::mathematical::pi / 180.0;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::multiphaseMixtureThermo::calcAlphas()
{
    scalar level = 0.0;
    alphas_ == 0.0;

    forAllIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        alphas_ += level * phase();
        level += 1.0;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::multiphaseMixtureThermo::multiphaseMixtureThermo
(
    const volVectorField& U,
    const surfaceScalarField& phi
)
    :
    psiThermo(U.mesh(), word::null),
    phases_(lookup("phases"), phaseModel::iNew(p_, T_)),

    mesh_(U.mesh()),
    U_(U),
    phi_(phi),

    rhoPhi_
    (
        IOobject
        (
            "rhoPhi",
            mesh_.time().timeName(),
            mesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh_,
        dimensionedScalar(dimMass / dimTime, 0)
    ),

    alphas_
    (
        IOobject
        (
            "alphas",
            mesh_.time().timeName(),
            mesh_,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh_,
        dimensionedScalar(dimless, 0)
    ),

    sigmas_(lookup("sigmas")),
    dimSigma_(1, 0, -2, 0, 0),
    deltaN_
    (
        "deltaN",
        1e-8 / pow(average(mesh_.V()), 1.0 / 3.0)
    )
{
    calcAlphas();
    alphas_.write();
    correct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::multiphaseMixtureThermo::correct()
{
    forAllIter(PtrDictionary<phaseModel>, phases_, phasei)
    {
        phasei().correct();
    }

    PtrDictionary<phaseModel>::iterator phasei = phases_.begin();

    psi_ = phasei() * phasei().thermo().psi();
    mu_ = phasei() * phasei().thermo().mu();
    alpha_ = phasei() * phasei().thermo().alpha();

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        psi_ += phasei() * phasei().thermo().psi();
        mu_ += phasei() * phasei().thermo().mu();
        alpha_ += phasei() * phasei().thermo().alpha();
    }
}


void tnbLib::multiphaseMixtureThermo::correctRho(const volScalarField& dp)
{
    forAllIter(PtrDictionary<phaseModel>, phases_, phasei)
    {
        phasei().thermo().rho() += phasei().thermo().psi() * dp;
    }
}


tnbLib::word tnbLib::multiphaseMixtureThermo::thermoName() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    word name = phasei().thermo().thermoName();

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        name += ',' + phasei().thermo().thermoName();
    }

    return name;
}


bool tnbLib::multiphaseMixtureThermo::incompressible() const
{
    bool ico = true;

    forAllConstIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        ico &= phase().thermo().incompressible();
    }

    return ico;
}


bool tnbLib::multiphaseMixtureThermo::isochoric() const
{
    bool iso = true;

    forAllConstIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        iso &= phase().thermo().incompressible();
    }

    return iso;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::he
(
    const volScalarField& p,
    const volScalarField& T
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> the(phasei() * phasei().thermo().he(p, T));

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        the.ref() += phasei() * phasei().thermo().he(p, T);
    }

    return the;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::he
(
    const scalarField& p,
    const scalarField& T,
    const labelList& cells
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> the
    (
        scalarField(phasei(), cells) * phasei().thermo().he(p, T, cells)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        the.ref() +=
            scalarField(phasei(), cells) * phasei().thermo().he(p, T, cells);
    }

    return the;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::he
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> the
    (
        phasei().boundaryField()[patchi] * phasei().thermo().he(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        the.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().he(p, T, patchi);
    }

    return the;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::hc() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> thc(phasei() * phasei().thermo().hc());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        thc.ref() += phasei() * phasei().thermo().hc();
    }

    return thc;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::THE
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


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::THE
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


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::rho() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> trho(phasei() * phasei().thermo().rho());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        trho.ref() += phasei() * phasei().thermo().rho();
    }

    return trho;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::rho
(
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> trho
    (
        phasei().boundaryField()[patchi] * phasei().thermo().rho(patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        trho.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().rho(patchi);
    }

    return trho;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::Cp() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tCp(phasei() * phasei().thermo().Cp());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCp.ref() += phasei() * phasei().thermo().Cp();
    }

    return tCp;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::Cp
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tCp
    (
        phasei().boundaryField()[patchi] * phasei().thermo().Cp(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCp.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().Cp(p, T, patchi);
    }

    return tCp;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::Cv() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tCv(phasei() * phasei().thermo().Cv());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCv.ref() += phasei() * phasei().thermo().Cv();
    }

    return tCv;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::Cv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tCv
    (
        phasei().boundaryField()[patchi] * phasei().thermo().Cv(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCv.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().Cv(p, T, patchi);
    }

    return tCv;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::gamma() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tgamma(phasei() * phasei().thermo().gamma());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tgamma.ref() += phasei() * phasei().thermo().gamma();
    }

    return tgamma;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::gamma
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tgamma
    (
        phasei().boundaryField()[patchi] * phasei().thermo().gamma(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tgamma.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().gamma(p, T, patchi);
    }

    return tgamma;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::Cpv() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tCpv(phasei() * phasei().thermo().Cpv());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCpv.ref() += phasei() * phasei().thermo().Cpv();
    }

    return tCpv;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::Cpv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tCpv
    (
        phasei().boundaryField()[patchi] * phasei().thermo().Cpv(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCpv.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().Cpv(p, T, patchi);
    }

    return tCpv;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::CpByCpv() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tCpByCpv(phasei() * phasei().thermo().CpByCpv());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCpByCpv.ref() += phasei() * phasei().thermo().CpByCpv();
    }

    return tCpByCpv;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::CpByCpv
(
    const scalarField& p,
    const scalarField& T,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tCpByCpv
    (
        phasei().boundaryField()[patchi] * phasei().thermo().CpByCpv(p, T, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tCpByCpv.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().CpByCpv(p, T, patchi);
    }

    return tCpByCpv;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::W() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tW(phasei() * phasei().thermo().W());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tW.ref() += phasei() * phasei().thermo().W();
    }

    return tW;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::W
(
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tW
    (
        phasei().boundaryField()[patchi] * phasei().thermo().W(patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tW.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().W(patchi);
    }

    return tW;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::nu() const
{
    return mu() / rho();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::nu
(
    const label patchi
) const
{
    return mu(patchi) / rho(patchi);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::kappa() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tkappa(phasei() * phasei().thermo().kappa());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tkappa.ref() += phasei() * phasei().thermo().kappa();
    }

    return tkappa;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::kappa
(
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tkappa
    (
        phasei().boundaryField()[patchi] * phasei().thermo().kappa(patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tkappa.ref() +=
            phasei().boundaryField()[patchi] * phasei().thermo().kappa(patchi);
    }

    return tkappa;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::alphahe() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> talphaEff(phasei() * phasei().thermo().alphahe());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        talphaEff.ref() += phasei() * phasei().thermo().alphahe();
    }

    return talphaEff;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::alphahe
(
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> talphaEff
    (
        phasei().boundaryField()[patchi]
        * phasei().thermo().alphahe(patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        talphaEff.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().alphahe(patchi);
    }

    return talphaEff;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::kappaEff
(
    const volScalarField& alphat
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> tkappaEff(phasei() * phasei().thermo().kappaEff(alphat));

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tkappaEff.ref() += phasei() * phasei().thermo().kappaEff(alphat);
    }

    return tkappaEff;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::kappaEff
(
    const scalarField& alphat,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> tkappaEff
    (
        phasei().boundaryField()[patchi]
        * phasei().thermo().kappaEff(alphat, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        tkappaEff.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().kappaEff(alphat, patchi);
    }

    return tkappaEff;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::alphaEff
(
    const volScalarField& alphat
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> talphaEff(phasei() * phasei().thermo().alphaEff(alphat));

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        talphaEff.ref() += phasei() * phasei().thermo().alphaEff(alphat);
    }

    return talphaEff;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::multiphaseMixtureThermo::alphaEff
(
    const scalarField& alphat,
    const label patchi
) const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<scalarField> talphaEff
    (
        phasei().boundaryField()[patchi]
        * phasei().thermo().alphaEff(alphat, patchi)
    );

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        talphaEff.ref() +=
            phasei().boundaryField()[patchi]
            * phasei().thermo().alphaEff(alphat, patchi);
    }

    return talphaEff;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::rCv() const
{
    PtrDictionary<phaseModel>::const_iterator phasei = phases_.begin();

    tmp<volScalarField> trCv(phasei() / phasei().thermo().Cv());

    for (++phasei; phasei != phases_.end(); ++phasei)
    {
        trCv.ref() += phasei() / phasei().thermo().Cv();
    }

    return trCv;
}


tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::multiphaseMixtureThermo::surfaceTensionForce() const
{
    tmp<surfaceScalarField> tstf
    (
        surfaceScalarField::New
        (
            "surfaceTensionForce",
            mesh_,
            dimensionedScalar(dimensionSet(1, -2, -2, 0, 0), 0)
        )
    );

    surfaceScalarField& stf = tstf.ref();

    forAllConstIter(PtrDictionary<phaseModel>, phases_, phase1)
    {
        const phaseModel& alpha1 = phase1();

        PtrDictionary<phaseModel>::const_iterator phase2 = phase1;
        ++phase2;

        for (; phase2 != phases_.end(); ++phase2)
        {
            const phaseModel& alpha2 = phase2();

            sigmaTable::const_iterator sigma =
                sigmas_.find(interfacePair(alpha1, alpha2));

            if (sigma == sigmas_.end())
            {
                FatalErrorInFunction
                    << "Cannot find interface " << interfacePair(alpha1, alpha2)
                    << " in list of sigma values"
                    << exit(FatalError);
            }

            stf += dimensionedScalar(dimSigma_, sigma())
                * fvc::interpolate(K(alpha1, alpha2)) *
                (
                    fvc::interpolate(alpha2) * fvc::snGrad(alpha1)
                    - fvc::interpolate(alpha1) * fvc::snGrad(alpha2)
                    );
        }
    }

    return tstf;
}


void tnbLib::multiphaseMixtureThermo::solve()
{
    const Time& runTime = mesh_.time();

    const dictionary& alphaControls = mesh_.solverDict("alpha");
    label nAlphaSubCycles(readLabel(alphaControls.lookup("nAlphaSubCycles")));
    scalar cAlpha(readScalar(alphaControls.lookup("cAlpha")));

    volScalarField& alpha = phases_.first();

    if (nAlphaSubCycles > 1)
    {
        surfaceScalarField rhoPhiSum(0.0 * rhoPhi_);
        dimensionedScalar totalDeltaT = runTime.deltaT();

        for
            (
                subCycle<volScalarField> alphaSubCycle(alpha, nAlphaSubCycles);
                !(++alphaSubCycle).end();
                )
        {
            solveAlphas(cAlpha);
            rhoPhiSum += (runTime.deltaT() / totalDeltaT) * rhoPhi_;
        }

        rhoPhi_ = rhoPhiSum;
    }
    else
    {
        solveAlphas(cAlpha);
    }
}


tnbLib::tmp<tnbLib::surfaceVectorField> tnbLib::multiphaseMixtureThermo::nHatfv
(
    const volScalarField& alpha1,
    const volScalarField& alpha2
) const
{
    /*
    // Cell gradient of alpha
    volVectorField gradAlpha =
        alpha2*fvc::grad(alpha1) - alpha1*fvc::grad(alpha2);

    // Interpolated face-gradient of alpha
    surfaceVectorField gradAlphaf = fvc::interpolate(gradAlpha);
    */

    surfaceVectorField gradAlphaf
    (
        fvc::interpolate(alpha2) * fvc::interpolate(fvc::grad(alpha1))
        - fvc::interpolate(alpha1) * fvc::interpolate(fvc::grad(alpha2))
    );

    // Face unit interface normal
    return gradAlphaf / (mag(gradAlphaf) + deltaN_);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::multiphaseMixtureThermo::nHatf
(
    const volScalarField& alpha1,
    const volScalarField& alpha2
) const
{
    // Face unit interface normal flux
    return nHatfv(alpha1, alpha2) & mesh_.Sf();
}


// Correction for the boundary condition on the unit normal nHat on
// walls to produce the correct contact angle.

// The dynamic contact angle is calculated from the component of the
// velocity on the direction of the interface, parallel to the wall.

void tnbLib::multiphaseMixtureThermo::correctContactAngle
(
    const phaseModel& alpha1,
    const phaseModel& alpha2,
    surfaceVectorField::Boundary& nHatb
) const
{
    const volScalarField::Boundary& gbf
        = alpha1.boundaryField();

    const fvBoundaryMesh& boundary = mesh_.boundary();

    forAll(boundary, patchi)
    {
        if (isA<alphaContactAngleFvPatchScalarField>(gbf[patchi]))
        {
            const alphaContactAngleFvPatchScalarField& acap =
                refCast<const alphaContactAngleFvPatchScalarField>(gbf[patchi]);

            vectorField& nHatPatch = nHatb[patchi];

            vectorField AfHatPatch
            (
                mesh_.Sf().boundaryField()[patchi]
                / mesh_.magSf().boundaryField()[patchi]
            );

            alphaContactAngleFvPatchScalarField::thetaPropsTable::
                const_iterator tp =
                acap.thetaProps().find(interfacePair(alpha1, alpha2));

            if (tp == acap.thetaProps().end())
            {
                FatalErrorInFunction
                    << "Cannot find interface " << interfacePair(alpha1, alpha2)
                    << "\n    in table of theta properties for patch "
                    << acap.patch().name()
                    << exit(FatalError);
            }

            bool matched = (tp.key().first() == alpha1.name());

            scalar theta0 = convertToRad * tp().theta0(matched);
            scalarField theta(boundary[patchi].size(), theta0);

            scalar uTheta = tp().uTheta();

            // Calculate the dynamic contact angle if required
            if (uTheta > small)
            {
                scalar thetaA = convertToRad * tp().thetaA(matched);
                scalar thetaR = convertToRad * tp().thetaR(matched);

                // Calculated the component of the velocity parallel to the wall
                vectorField Uwall
                (
                    U_.boundaryField()[patchi].patchInternalField()
                    - U_.boundaryField()[patchi]
                );
                Uwall -= (AfHatPatch & Uwall) * AfHatPatch;

                // Find the direction of the interface parallel to the wall
                vectorField nWall
                (
                    nHatPatch - (AfHatPatch & nHatPatch) * AfHatPatch
                );

                // Normalise nWall
                nWall /= (mag(nWall) + small);

                // Calculate Uwall resolved normal to the interface parallel to
                // the interface
                scalarField uwall(nWall & Uwall);

                theta += (thetaA - thetaR) * tanh(uwall / uTheta);
            }


            // Reset nHatPatch to correspond to the contact angle

            scalarField a12(nHatPatch & AfHatPatch);

            scalarField b1(cos(theta));

            scalarField b2(nHatPatch.size());

            forAll(b2, facei)
            {
                b2[facei] = cos(acos(a12[facei]) - theta[facei]);
            }

            scalarField det(1.0 - a12 * a12);

            scalarField a((b1 - a12 * b2) / det);
            scalarField b((b2 - a12 * b1) / det);

            nHatPatch = a * AfHatPatch + b * nHatPatch;

            nHatPatch /= (mag(nHatPatch) + deltaN_.value());
        }
    }
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::multiphaseMixtureThermo::K
(
    const phaseModel& alpha1,
    const phaseModel& alpha2
) const
{
    tmp<surfaceVectorField> tnHatfv = nHatfv(alpha1, alpha2);

    correctContactAngle(alpha1, alpha2, tnHatfv.ref().boundaryFieldRef());

    // Simple expression for curvature
    return -fvc::div(tnHatfv & mesh_.Sf());
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::multiphaseMixtureThermo::nearInterface() const
{
    tmp<volScalarField> tnearInt
    (
        volScalarField::New
        (
            "nearInterface",
            mesh_,
            dimensionedScalar(dimless, 0)
        )
    );

    forAllConstIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        tnearInt.ref() =
            max(tnearInt(), pos0(phase() - 0.01) * pos0(0.99 - phase()));
    }

    return tnearInt;
}


void tnbLib::multiphaseMixtureThermo::solveAlphas
(
    const scalar cAlpha
)
{
    static label nSolves = -1;
    nSolves++;

    word alphaScheme("div(phi,alpha)");
    word alpharScheme("div(phirb,alpha)");

    surfaceScalarField phic(mag(phi_ / mesh_.magSf()));
    phic = min(cAlpha * phic, max(phic));

    PtrList<surfaceScalarField> alphaPhiCorrs(phases_.size());
    int phasei = 0;

    forAllIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        phaseModel& alpha = phase();

        alphaPhiCorrs.set
        (
            phasei,
            new surfaceScalarField
            (
                phi_.name() + alpha.name(),
                fvc::flux
                (
                    phi_,
                    alpha,
                    alphaScheme
                )
            )
        );

        surfaceScalarField& alphaPhiCorr = alphaPhiCorrs[phasei];

        forAllIter(PtrDictionary<phaseModel>, phases_, phase2)
        {
            phaseModel& alpha2 = phase2();

            if (&alpha2 == &alpha) continue;

            surfaceScalarField phir(phic * nHatf(alpha, alpha2));

            alphaPhiCorr += fvc::flux
            (
                -fvc::flux(-phir, alpha2, alpharScheme),
                alpha,
                alpharScheme
            );
        }

        MULES::limit
        (
            1.0 / mesh_.time().deltaT().value(),
            geometricOneField(),
            alpha,
            phi_,
            alphaPhiCorr,
            zeroField(),
            zeroField(),
            oneField(),
            zeroField(),
            true
        );

        phasei++;
    }

    MULES::limitSum(alphaPhiCorrs);

    rhoPhi_ = dimensionedScalar(dimensionSet(1, 0, -1, 0, 0), 0);

    volScalarField sumAlpha
    (
        IOobject
        (
            "sumAlpha",
            mesh_.time().timeName(),
            mesh_
        ),
        mesh_,
        dimensionedScalar(dimless, 0)
    );


    volScalarField divU(fvc::div(fvc::absolute(phi_, U_)));


    phasei = 0;

    forAllIter(PtrDictionary<phaseModel>, phases_, phase)
    {
        phaseModel& alpha = phase();

        surfaceScalarField& alphaPhi = alphaPhiCorrs[phasei];
        alphaPhi += upwind<scalar>(mesh_, phi_).flux(alpha);

        volScalarField::Internal Sp
        (
            IOobject
            (
                "Sp",
                mesh_.time().timeName(),
                mesh_
            ),
            mesh_,
            dimensionedScalar(alpha.dgdt().dimensions(), 0)
        );

        volScalarField::Internal Su
        (
            IOobject
            (
                "Su",
                mesh_.time().timeName(),
                mesh_
            ),
            // Divergence term is handled explicitly to be
            // consistent with the explicit transport solution
            divU * min(alpha, scalar(1))
        );

        {
            const scalarField& dgdt = alpha.dgdt();

            forAll(dgdt, celli)
            {
                if (dgdt[celli] < 0.0 && alpha[celli] > 0.0)
                {
                    Sp[celli] += dgdt[celli] * alpha[celli];
                    Su[celli] -= dgdt[celli] * alpha[celli];
                }
                else if (dgdt[celli] > 0.0 && alpha[celli] < 1.0)
                {
                    Sp[celli] -= dgdt[celli] * (1.0 - alpha[celli]);
                }
            }
        }

        forAllConstIter(PtrDictionary<phaseModel>, phases_, phase2)
        {
            const phaseModel& alpha2 = phase2();

            if (&alpha2 == &alpha) continue;

            const scalarField& dgdt2 = alpha2.dgdt();

            forAll(dgdt2, celli)
            {
                if (dgdt2[celli] > 0.0 && alpha2[celli] < 1.0)
                {
                    Sp[celli] -= dgdt2[celli] * (1.0 - alpha2[celli]);
                    Su[celli] += dgdt2[celli] * alpha[celli];
                }
                else if (dgdt2[celli] < 0.0 && alpha2[celli] > 0.0)
                {
                    Sp[celli] += dgdt2[celli] * alpha2[celli];
                }
            }
        }

        MULES::explicitSolve
        (
            geometricOneField(),
            alpha,
            alphaPhi,
            Sp,
            Su
        );

        rhoPhi_ += fvc::interpolate(alpha.thermo().rho()) * alphaPhi;

        Info << alpha.name() << " volume fraction, min, max = "
            << alpha.weightedAverage(mesh_.V()).value()
            << ' ' << min(alpha).value()
            << ' ' << max(alpha).value()
            << endl;

        sumAlpha += alpha;

        phasei++;
    }

    Info << "Phase-sum volume fraction, min, max = "
        << sumAlpha.weightedAverage(mesh_.V()).value()
        << ' ' << min(sumAlpha).value()
        << ' ' << max(sumAlpha).value()
        << endl;

    calcAlphas();
}


// ************************************************************************* //
