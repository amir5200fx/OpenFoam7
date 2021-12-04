/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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

#include <LuoSvendsen.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <phaseCompressibleTurbulenceModelMultiphase.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace binaryBreakupModels
        {
            defineTypeNameAndDebug(LuoSvendsen, 0);
            addToRunTimeSelectionTable
            (
                binaryBreakupModel,
                LuoSvendsen,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diameterModels::binaryBreakupModels::LuoSvendsen::LuoSvendsen
(
    const populationBalanceModel& popBal,
    const dictionary& dict
)
    :
    binaryBreakupModel(popBal, dict),
    gammaUpperReg2by11_(),
    gammaUpperReg5by11_(),
    gammaUpperReg8by11_(),
    C4_(dimensionedScalar::lookupOrDefault("C4", dict, dimless, 0.923)),
    beta_(dimensionedScalar::lookupOrDefault("beta", dict, dimless, 2.05)),
    minEddyRatio_
    (
        dimensionedScalar::lookupOrDefault("minEddyRatio", dict, dimless, 11.4)
    ),
    kolmogorovLengthScale_
    (
        IOobject
        (
            "kolmogorovLengthScale",
            popBal_.time().timeName(),
            popBal_.mesh()
        ),
        popBal_.mesh(),
        dimensionedScalar
        (
            "kolmogorovLengthScale",
            dimLength,
            Zero
        )
    )
{
    List<Tuple2<scalar, scalar>> gammaUpperReg2by11Table;
    List<Tuple2<scalar, scalar>> gammaUpperReg5by11Table;
    List<Tuple2<scalar, scalar>> gammaUpperReg8by11Table;

    gammaUpperReg2by11Table.append(Tuple2<scalar, scalar>(0.0, 1.0));
    gammaUpperReg5by11Table.append(Tuple2<scalar, scalar>(0.0, 1.0));
    gammaUpperReg8by11Table.append(Tuple2<scalar, scalar>(0.0, 1.0));

    for (scalar z = 1e-2; z <= 10.0; z = z + 1e-2)
    {
        Tuple2<scalar, scalar> gamma2by11
        (
            z,
            incGammaRatio_Q(2.0 / 11.0, z)
        );

        Tuple2<scalar, scalar> gamma5by11
        (
            z,
            incGammaRatio_Q(5.0 / 11.0, z)
        );

        Tuple2<scalar, scalar> gamma8by11
        (
            z,
            incGammaRatio_Q(8.0 / 11.0, z)
        );

        gammaUpperReg2by11Table.append(gamma2by11);
        gammaUpperReg5by11Table.append(gamma5by11);
        gammaUpperReg8by11Table.append(gamma8by11);
    }

    gammaUpperReg2by11_ =
        new interpolationTable<scalar>
        (
            gammaUpperReg2by11Table,
            interpolationTable<scalar>::CLAMP,
            "gamma2by11"
            );

    gammaUpperReg5by11_ =
        new interpolationTable<scalar>
        (
            gammaUpperReg5by11Table,
            interpolationTable<scalar>::CLAMP,
            "gamma5by11"
            );

    gammaUpperReg8by11_ =
        new interpolationTable<scalar>
        (
            gammaUpperReg8by11Table,
            interpolationTable<scalar>::CLAMP,
            "gamma8by11"
            );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::diameterModels::binaryBreakupModels::LuoSvendsen::correct()
{
    kolmogorovLengthScale_ =
        pow025
        (
            pow3
            (
                popBal_.continuousPhase().nu()
            )
            / popBal_.continuousTurbulence().epsilon()
        );
}


void
tnbLib::diameterModels::binaryBreakupModels::LuoSvendsen::addToBinaryBreakupRate
(
    volScalarField& binaryBreakupRate,
    const label i,
    const label j
)
{
    const phaseModel& continuousPhase = popBal_.continuousPhase();
    const sizeGroup& fi = popBal_.sizeGroups()[i];
    const sizeGroup& fj = popBal_.sizeGroups()[j];

    const dimensionedScalar cf
    (
        pow(fi.x() / fj.x(), 2.0 / 3.0) + pow((1 - fi.x() / fj.x()), 2.0 / 3.0) - 1
    );

    const volScalarField b
    (
        12.0 * cf * popBal_.sigmaWithContinuousPhase(fi.phase())
        / (
            beta_ * continuousPhase.rho() * pow(fj.d(), 5.0 / 3.0)
            * pow(popBal_.continuousTurbulence().epsilon(), 2.0 / 3.0)
            )
    );

    const volScalarField xiMin(minEddyRatio_ * kolmogorovLengthScale_ / fj.d());

    const volScalarField tMin(b / pow(xiMin, 11.0 / 3.0));

    volScalarField integral(3.0 / (11.0 * pow(b, 8.0 / 11.0)));

    forAll(integral, celli)
    {
        integral[celli] *=
            2.0 * pow(b[celli], 3.0 / 11.0) * tgamma(5.0 / 11.0)
            * (
                gammaUpperReg5by11_()(b[celli])
                - gammaUpperReg5by11_()(tMin[celli])
                );
    }

    binaryBreakupRate +=
        C4_ * (1 - popBal_.alphas()) / fj.x()
        * cbrt
        (
            popBal_.continuousTurbulence().epsilon()
            / sqr(fj.d())
        )
        * integral;
}


// ************************************************************************* //
