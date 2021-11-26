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

#include "compressibleInterPhaseTransportModel.hxx"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::compressibleInterPhaseTransportModel::compressibleInterPhaseTransportModel
(
    const volScalarField& rho,
    const volVectorField& U,
    const surfaceScalarField& phi,
    const surfaceScalarField& rhoPhi,
    const surfaceScalarField& alphaPhi10,
    const twoPhaseMixtureThermo& mixture
)
    :
    twoPhaseTransport_(false),
    mixture_(mixture),
    phi_(phi),
    alphaPhi10_(alphaPhi10)
{
    {
        IOdictionary turbulenceProperties
        (
            IOobject
            (
                turbulenceModel::propertiesName,
                U.time().constant(),
                U.db(),
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        );

        word simulationType
        (
            turbulenceProperties.lookup("simulationType")
        );

        if (simulationType == "twoPhaseTransport")
        {
            twoPhaseTransport_ = true;
        }
    }

    if (twoPhaseTransport_)
    {
        const volScalarField& alpha1(mixture_.alpha1());
        const volScalarField& alpha2(mixture_.alpha2());

        const volScalarField& rho1 = mixture_.thermo1().rho();
        const volScalarField& rho2 = mixture_.thermo2().rho();

        alphaRhoPhi1_ =
            (
                new surfaceScalarField
                (
                    IOobject::groupName("alphaRhoPhi", alpha1.group()),
                    fvc::interpolate(rho1) * alphaPhi10_
                )
                );

        alphaRhoPhi2_ =
            (
                new surfaceScalarField
                (
                    IOobject::groupName("alphaRhoPhi", alpha2.group()),
                    fvc::interpolate(rho2) * (phi_ - alphaPhi10_)
                )
                );

        turbulence1_ =
            (
                ThermalDiffusivity<PhaseCompressibleTurbulenceModel<fluidThermo>>
                ::New
                (
                    alpha1,
                    rho1,
                    U,
                    alphaRhoPhi1_(),
                    phi,
                    mixture.thermo1()
                )
                );

        turbulence2_ =
            (
                ThermalDiffusivity<PhaseCompressibleTurbulenceModel<fluidThermo>>
                ::New
                (
                    alpha2,
                    rho2,
                    U,
                    alphaRhoPhi2_(),
                    phi,
                    mixture.thermo2()
                )
                );
    }
    else
    {
        turbulence_ = compressible::turbulenceModel::New
        (
            rho,
            U,
            rhoPhi,
            mixture
        );

        turbulence_->validate();
    }
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

//tnbLib::tmp<tnbLib::volScalarField>
//tnbLib::compressibleInterPhaseTransportModel::alphaEff() const
//{
//    if (twoPhaseTransport_)
//    {
//        return
//            mixture_.alpha1() * mixture_.thermo1().alphaEff
//            (
//                turbulence1_->alphat()
//            )
//            + mixture_.alpha2() * mixture_.thermo2().alphaEff
//            (
//                turbulence2_->alphat()
//            );
//    }
//    else
//    {
//        return mixture_.alphaEff(turbulence_->alphat());
//    }
//}
//

//tnbLib::tmp<tnbLib::fvVectorMatrix>
//tnbLib::compressibleInterPhaseTransportModel::divDevRhoReff
//(
//    volVectorField& U
//) const
//{
//    if (twoPhaseTransport_)
//    {
//        return
//            turbulence1_->divDevRhoReff(U)
//            + turbulence2_->divDevRhoReff(U);
//    }
//    else
//    {
//        return turbulence_->divDevRhoReff(U);
//    }
//}
//
//
//void tnbLib::compressibleInterPhaseTransportModel::correctPhasePhi()
//{
//    if (twoPhaseTransport_)
//    {
//        const volScalarField& rho1 = mixture_.thermo1().rho();
//        const volScalarField& rho2 = mixture_.thermo2().rho();
//
//        alphaRhoPhi1_.ref() = fvc::interpolate(rho1) * alphaPhi10_;
//        alphaRhoPhi2_.ref() = fvc::interpolate(rho2) * (phi_ - alphaPhi10_);
//    }
//}


void tnbLib::compressibleInterPhaseTransportModel::correct()
{
    if (twoPhaseTransport_)
    {
        turbulence1_->correct();
        turbulence2_->correct();
    }
    else
    {
        turbulence_->correct();
    }
}


// ************************************************************************* //
