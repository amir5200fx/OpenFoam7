/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

#include "phase.hxx"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phase::phase
(
    const word& phaseName,
    const dictionary& phaseDict,
    const volVectorField& U,
    const surfaceScalarField& phi
)
    :
    volScalarField
    (
        IOobject
        (
            IOobject::groupName("alpha", phaseName),
            U.mesh().time().timeName(),
            U.mesh(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        U.mesh()
    ),
    name_(phaseName),
    phaseDict_(phaseDict),
    nuModel_
    (
        viscosityModel::New
        (
            IOobject::groupName("nu", phaseName),
            phaseDict_,
            U,
            phi
        )
    ),
    rho_("rho", dimDensity, phaseDict_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::phase> tnbLib::phase::clone() const
{
    NotImplemented;
    return autoPtr<phase>(nullptr);
}


void tnbLib::phase::correct()
{
    nuModel_->correct();
}


bool tnbLib::phase::read(const dictionary& phaseDict)
{
    phaseDict_ = phaseDict;

    if (nuModel_->read(phaseDict_))
    {
        phaseDict_.lookup("rho") >> rho_;

        return true;
    }
    else
    {
        return false;
    }
}


// ************************************************************************* //
