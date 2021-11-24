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

#include "algebraic.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiModels
    {
        defineTypeNameAndDebug(algebraic, 0);
        addToRunTimeSelectionTable(XiModel, algebraic, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiModels::algebraic::algebraic
(
    const dictionary& XiProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su,
    const volScalarField& rho,
    const volScalarField& b,
    const surfaceScalarField& phi
)
    :
    XiModel(XiProperties, thermo, turbulence, Su, rho, b, phi),
    XiShapeCoef(readScalar(XiModelCoeffs_.lookup("XiShapeCoef"))),
    XiEqModel_(XiEqModel::New(XiProperties, thermo, turbulence, Su)),
    XiGModel_(XiGModel::New(XiProperties, thermo, turbulence, Su))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiModels::algebraic::~algebraic()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiModels::algebraic::Db() const
{
    return XiGModel_->Db();
}


void tnbLib::XiModels::algebraic::correct()
{
    volScalarField XiEqEta(XiEqModel_->XiEq());
    volScalarField GEta(XiGModel_->G());

    volScalarField R(GEta * XiEqEta / (XiEqEta - 0.999));

    volScalarField XiEqStar(R / (R - GEta));

    Xi_ == 1.0 + (1.0 + (2 * XiShapeCoef) * (0.5 - b_)) * (XiEqStar - 1.0);
}


bool tnbLib::XiModels::algebraic::read(const dictionary& XiProperties)
{
    XiModel::read(XiProperties);

    XiModelCoeffs_.lookup("XiShapeCoef") >> XiShapeCoef;

    return true;
}


// ************************************************************************* //
