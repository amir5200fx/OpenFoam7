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

#include "PDRDragModel.hxx"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(PDRDragModel, 0);
    defineRunTimeSelectionTable(PDRDragModel, dictionary);
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::PDRDragModel::PDRDragModel
(
    const dictionary& PDRProperties,
    const compressible::RASModel& turbulence,
    const volScalarField& rho,
    const volVectorField& U,
    const surfaceScalarField& phi
)
    :
    regIOobject
    (
        IOobject
        (
            "PDRDragModel",
            U.time().constant(),
            U.db()
        )
    ),
    PDRDragModelCoeffs_
    (
        PDRProperties.subDict
        (
            word(PDRProperties.lookup("PDRDragModel")) + "Coeffs"
        )
    ),
    turbulence_(turbulence),
    rho_(rho),
    U_(U),
    phi_(phi),
    on_(PDRDragModelCoeffs_.lookup("drag"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::PDRDragModel::~PDRDragModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::PDRDragModel::read(const dictionary& PDRProperties)
{
    PDRDragModelCoeffs_ = PDRProperties.optionalSubDict(type() + "Coeffs");

    PDRDragModelCoeffs_.lookup("drag") >> on_;

    return true;
}


// ************************************************************************* //
