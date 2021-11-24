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

#include "basicXiSubG.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiGModels
    {
        defineTypeNameAndDebug(basicSubGrid, 0);
        addToRunTimeSelectionTable(XiGModel, basicSubGrid, dictionary);
    };
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiGModels::basicSubGrid::basicSubGrid
(
    const dictionary& XiGProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
    :
    XiGModel(XiGProperties, thermo, turbulence, Su),
    k1(readScalar(XiGModelCoeffs_.lookup("k1"))),
    XiGModel_(XiGModel::New(XiGModelCoeffs_, thermo, turbulence, Su))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiGModels::basicSubGrid::~basicSubGrid()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiGModels::basicSubGrid::G() const
{
    const objectRegistry& db = Su_.db();
    const volVectorField& U = db.lookupObject<volVectorField>("U");
    const volScalarField& Nv = db.lookupObject<volScalarField>("Nv");
    const volScalarField& Lobs = db.lookupObject<volScalarField>("Lobs");

    tmp<volScalarField> tGtot = XiGModel_->G();
    volScalarField& Gtot = tGtot.ref();

    const scalarField Cw = pow(Su_.mesh().V(), 2.0 / 3.0);
    scalarField N(Nv.primitiveField() * Cw);

    forAll(N, celli)
    {
        if (N[celli] > 1e-3)
        {
            Gtot[celli] += k1 * mag(U[celli]) / Lobs[celli];
        }
    }

    return tGtot;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiGModels::basicSubGrid::Db() const
{
    const objectRegistry& db = Su_.db();
    const volScalarField& Xi = db.lookupObject<volScalarField>("Xi");
    const volScalarField& rho = db.lookupObject<volScalarField>("rho");
    const volScalarField& mgb = db.lookupObject<volScalarField>("mgb");
    const volScalarField& Lobs = db.lookupObject<volScalarField>("Lobs");

    return XiGModel_->Db()
        + rho * Su_ * (Xi - 1.0) * mgb * (0.5 * Lobs) * Lobs / (mgb * Lobs + 1.0);
}


bool tnbLib::XiGModels::basicSubGrid::read(const dictionary& XiGProperties)
{
    XiGModel::read(XiGProperties);

    XiGModelCoeffs_.lookup("k1") >> k1;

    return true;
}


// ************************************************************************* //
