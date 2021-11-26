/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

#include "Kunz.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace phaseChangeTwoPhaseMixtures
    {
        defineTypeNameAndDebug(Kunz, 0);
        addToRunTimeSelectionTable(phaseChangeTwoPhaseMixture, Kunz, components);
    }
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseChangeTwoPhaseMixtures::Kunz::Kunz
(
    const volVectorField& U,
    const surfaceScalarField& phi
)
    :
    phaseChangeTwoPhaseMixture(typeName, U, phi),

    UInf_("UInf", dimVelocity, phaseChangeTwoPhaseMixtureCoeffs_),
    tInf_("tInf", dimTime, phaseChangeTwoPhaseMixtureCoeffs_),
    Cc_("Cc", dimless, phaseChangeTwoPhaseMixtureCoeffs_),
    Cv_("Cv", dimless, phaseChangeTwoPhaseMixtureCoeffs_),

    p0_("0", pSat().dimensions(), 0.0),

    mcCoeff_(Cc_* rho2() / tInf_),
    mvCoeff_(Cv_* rho2() / (0.5 * rho1() * sqr(UInf_) * tInf_))
{
    correct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::Pair<tnbLib::tmp<tnbLib::volScalarField>>
tnbLib::phaseChangeTwoPhaseMixtures::Kunz::mDotAlphal() const
{
    const volScalarField& p = alpha1().db().lookupObject<volScalarField>("p");
    volScalarField limitedAlpha1(min(max(alpha1(), scalar(0)), scalar(1)));

    return Pair<tmp<volScalarField>>
        (
            mcCoeff_ * sqr(limitedAlpha1)
            * max(p - pSat(), p0_) / max(p - pSat(), 0.01 * pSat()),

            mvCoeff_ * min(p - pSat(), p0_)
            );
}


tnbLib::Pair<tnbLib::tmp<tnbLib::volScalarField>>
tnbLib::phaseChangeTwoPhaseMixtures::Kunz::mDotP() const
{
    const volScalarField& p = alpha1().db().lookupObject<volScalarField>("p");
    volScalarField limitedAlpha1(min(max(alpha1(), scalar(0)), scalar(1)));

    return Pair<tmp<volScalarField>>
        (
            mcCoeff_ * sqr(limitedAlpha1) * (1.0 - limitedAlpha1)
            * pos0(p - pSat()) / max(p - pSat(), 0.01 * pSat()),

            (-mvCoeff_) * limitedAlpha1 * neg(p - pSat())
            );
}


void tnbLib::phaseChangeTwoPhaseMixtures::Kunz::correct()
{
    phaseChangeTwoPhaseMixture::correct();
}


bool tnbLib::phaseChangeTwoPhaseMixtures::Kunz::read()
{
    if (phaseChangeTwoPhaseMixture::read())
    {
        phaseChangeTwoPhaseMixtureCoeffs_ = optionalSubDict(type() + "Coeffs");

        phaseChangeTwoPhaseMixtureCoeffs_.lookup("UInf") >> UInf_;
        phaseChangeTwoPhaseMixtureCoeffs_.lookup("tInf") >> tInf_;
        phaseChangeTwoPhaseMixtureCoeffs_.lookup("Cc") >> Cc_;
        phaseChangeTwoPhaseMixtureCoeffs_.lookup("Cv") >> Cv_;

        mcCoeff_ = Cc_ * rho2() / tInf_;
        mvCoeff_ = Cv_ * rho2() / (0.5 * rho1() * sqr(UInf_) * tInf_);

        return true;
    }
    else
    {
        return false;
    }
}


// ************************************************************************* //
