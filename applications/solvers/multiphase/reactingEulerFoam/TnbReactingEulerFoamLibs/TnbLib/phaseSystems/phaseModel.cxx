/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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

#include <phaseModel.hxx>

#include <phaseSystem.hxx>
#include <diameterModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(phaseModel, 0);
    defineRunTimeSelectionTable(phaseModel, phaseSystem);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseModel::phaseModel
(
    const phaseSystem& fluid,
    const word& phaseName,
    const label index
)
    :
    volScalarField
    (
        IOobject
        (
            IOobject::groupName("alpha", phaseName),
            fluid.mesh().time().timeName(),
            fluid.mesh(),
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        fluid.mesh(),
        dimensionedScalar(dimless, 0)
    ),

    fluid_(fluid),
    name_(phaseName),
    index_(index),
    residualAlpha_
    (
        "residualAlpha",
        dimless,
        fluid.subDict(phaseName).lookup("residualAlpha")
    ),
    alphaMax_(fluid.subDict(phaseName).lookupOrDefault("alphaMax", 1.0))
{
    diameterModel_ = diameterModel::New(fluid.subDict(phaseName), *this);
}


tnbLib::autoPtr<tnbLib::phaseModel> tnbLib::phaseModel::clone() const
{
    NotImplemented;
    return autoPtr<phaseModel>(nullptr);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phaseModel::~phaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::phaseModel::name() const
{
    return name_;
}


const tnbLib::word& tnbLib::phaseModel::keyword() const
{
    return name_;
}


tnbLib::label tnbLib::phaseModel::index() const
{
    return index_;
}


const tnbLib::phaseSystem& tnbLib::phaseModel::fluid() const
{
    return fluid_;
}


const tnbLib::dimensionedScalar& tnbLib::phaseModel::residualAlpha() const
{
    return residualAlpha_;
}


tnbLib::scalar tnbLib::phaseModel::alphaMax() const
{
    return alphaMax_;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phaseModel::d() const
{
    return diameterModel_().d();
}


const tnbLib::autoPtr<tnbLib::diameterModel>& tnbLib::phaseModel::dPtr() const
{
    return diameterModel_;
}


void tnbLib::phaseModel::correct()
{
    diameterModel_->correct();
}


void tnbLib::phaseModel::correctKinematics()
{}


void tnbLib::phaseModel::correctThermo()
{}


void tnbLib::phaseModel::correctTurbulence()
{}


void tnbLib::phaseModel::correctEnergyTransport()
{}


bool tnbLib::phaseModel::read()
{
    return diameterModel_->read(fluid_.subDict(name_));
}


void tnbLib::phaseModel::correctInflowOutflow(surfaceScalarField& alphaPhi) const
{
    surfaceScalarField::Boundary& alphaPhiBf = alphaPhi.boundaryFieldRef();
    const volScalarField::Boundary& alphaBf = boundaryField();
    const surfaceScalarField::Boundary& phiBf = phi()().boundaryField();

    forAll(alphaPhiBf, patchi)
    {
        fvsPatchScalarField& alphaPhip = alphaPhiBf[patchi];

        if (!alphaPhip.coupled())
        {
            alphaPhip = phiBf[patchi] * alphaBf[patchi];
        }
    }
}


// ************************************************************************* //
