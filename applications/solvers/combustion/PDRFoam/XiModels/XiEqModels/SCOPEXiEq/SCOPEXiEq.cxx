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

#include "SCOPEXiEq.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiEqModels
    {
        defineTypeNameAndDebug(SCOPEXiEq, 0);
        addToRunTimeSelectionTable(XiEqModel, SCOPEXiEq, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiEqModels::SCOPEXiEq::SCOPEXiEq
(
    const dictionary& XiEqProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
    :
    XiEqModel(XiEqProperties, thermo, turbulence, Su),
    XiEqCoef_(readScalar(XiEqModelCoeffs_.lookup("XiEqCoef"))),
    XiEqExp_(readScalar(XiEqModelCoeffs_.lookup("XiEqExp"))),
    lCoef_(readScalar(XiEqModelCoeffs_.lookup("lCoef"))),
    SuMin_(0.01 * Su.average()),
    uPrimeCoef_(readScalar(XiEqModelCoeffs_.lookup("uPrimeCoef"))),
    subGridSchelkin_
    (
        readBool(XiEqModelCoeffs_.lookup("subGridSchelkin"))
    ),
    MaModel
    (
        Su.mesh().lookupObject<IOdictionary>("combustionProperties"),
        thermo
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiEqModels::SCOPEXiEq::~SCOPEXiEq()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiEqModels::SCOPEXiEq::XiEq() const
{
    const volScalarField& k = turbulence_.k();
    const volScalarField& epsilon = turbulence_.epsilon();

    volScalarField up(sqrt((2.0 / 3.0) * k));
    if (subGridSchelkin_)
    {
        up.primitiveFieldRef() += calculateSchelkinEffect(uPrimeCoef_);
    }

    volScalarField l(lCoef_ * sqrt(3.0 / 2.0) * up * k / epsilon);
    volScalarField Rl(up * l * thermo_.rhou() / thermo_.muu());

    volScalarField upBySu(up / (Su_ + SuMin_));
    volScalarField K(0.157 * upBySu / sqrt(Rl));
    volScalarField Ma(MaModel.Ma());

    tmp<volScalarField> tXiEq
    (
        volScalarField::New
        (
            "XiEq",
            epsilon.mesh(),
            dimensionedScalar(dimless, 0)
        )
    );
    volScalarField& xieq = tXiEq.ref();

    forAll(xieq, celli)
    {
        if (Ma[celli] > 0.01)
        {
            xieq[celli] =
                XiEqCoef_ * pow(K[celli] * Ma[celli], -XiEqExp_) * upBySu[celli];
        }
    }

    volScalarField::Boundary& xieqBf = xieq.boundaryFieldRef();

    forAll(xieq.boundaryField(), patchi)
    {
        scalarField& xieqp = xieqBf[patchi];
        const scalarField& Kp = K.boundaryField()[patchi];
        const scalarField& Map = Ma.boundaryField()[patchi];
        const scalarField& upBySup = upBySu.boundaryField()[patchi];

        forAll(xieqp, facei)
        {
            if (Ma[facei] > 0.01)
            {
                xieqp[facei] =
                    XiEqCoef_ * pow(Kp[facei] * Map[facei], -XiEqExp_)
                    * upBySup[facei];
            }
        }
    }

    return tXiEq;
}


bool tnbLib::XiEqModels::SCOPEXiEq::read(const dictionary& XiEqProperties)
{
    XiEqModel::read(XiEqProperties);

    XiEqModelCoeffs_.lookup("XiEqCoef") >> XiEqCoef_;
    XiEqModelCoeffs_.lookup("XiEqExp") >> XiEqExp_;
    XiEqModelCoeffs_.lookup("lCoef") >> lCoef_;
    XiEqModelCoeffs_.lookup("uPrimeCoef") >> uPrimeCoef_;
    XiEqModelCoeffs_.lookup("subGridSchelkin") >> subGridSchelkin_;

    return true;
}


// ************************************************************************* //
