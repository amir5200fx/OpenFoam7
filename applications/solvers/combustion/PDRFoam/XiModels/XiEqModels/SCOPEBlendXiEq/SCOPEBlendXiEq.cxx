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

#include "SCOPEBlendXiEq.hxx"

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiEqModels
    {
        defineTypeNameAndDebug(SCOPEBlend, 0);
        addToRunTimeSelectionTable(XiEqModel, SCOPEBlend, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::XiEqModels::SCOPEBlend::SCOPEBlend
(
    const dictionary& XiEqProperties,
    const psiuReactionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
    :
    XiEqModel(XiEqProperties, thermo, turbulence, Su),
    XiEqModelL_
    (
        XiEqModel::New
        (
            XiEqModelCoeffs_.subDict("XiEqModelL"),
            thermo,
            turbulence,
            Su
        )
    ),
    XiEqModelH_
    (
        XiEqModel::New
        (
            XiEqModelCoeffs_.subDict("XiEqModelH"),
            thermo,
            turbulence,
            Su
        )
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::XiEqModels::SCOPEBlend::~SCOPEBlend()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::XiEqModels::SCOPEBlend::XiEq() const
{
    return pow
    (
        pow4(1.0 / XiEqModelL_->XiEq()) + pow4(1.0 / XiEqModelH_->XiEq()),
        -0.25
    );
}


// ************************************************************************* //
