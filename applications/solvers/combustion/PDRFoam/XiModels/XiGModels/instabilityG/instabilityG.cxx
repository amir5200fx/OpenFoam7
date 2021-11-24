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

#include "instabilityG.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiGModels
    {
        defineTypeNameAndDebug(instabilityG, 0);
        addToRunTimeSelectionTable(XiGModel, instabilityG, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiGModels::instabilityG::instabilityG
(
    const dictionary& XiGProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
    :
    XiGModel(XiGProperties, thermo, turbulence, Su),
    GIn_(XiGModelCoeffs_.lookup("GIn")),
    lambdaIn_(XiGModelCoeffs_.lookup("lambdaIn")),
    XiGModel_(XiGModel::New(XiGModelCoeffs_, thermo, turbulence, Su))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiGModels::instabilityG::~instabilityG()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiGModels::instabilityG::G() const
{
    volScalarField turbXiG(XiGModel_->G());
    return (GIn_ * GIn_ / (GIn_ + turbXiG) + turbXiG);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiGModels::instabilityG::Db() const
{
    const objectRegistry& db = Su_.db();
    const volScalarField& Xi = db.lookupObject<volScalarField>("Xi");
    const volScalarField& rho = db.lookupObject<volScalarField>("rho");
    const volScalarField& mgb = db.lookupObject<volScalarField>("mgb");

    return XiGModel_->Db()
        + rho * Su_ * (Xi - 1.0) * mgb * (0.5 * lambdaIn_) / (mgb + 1.0 / lambdaIn_);
}


bool tnbLib::XiGModels::instabilityG::read(const dictionary& XiGProperties)
{
    XiGModel::read(XiGProperties);

    XiGModelCoeffs_.lookup("GIn") >> GIn_;
    XiGModelCoeffs_.lookup("lambdaIn") >> lambdaIn_;

    return true;
}


// ************************************************************************* //
