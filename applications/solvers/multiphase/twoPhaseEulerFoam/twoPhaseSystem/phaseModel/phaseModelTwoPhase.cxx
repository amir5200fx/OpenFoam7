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

#include "phaseModelTwoPhase.hxx"

#include "twoPhaseSystem.hxx"
#include "diameterModelTwoPhase.hxx"

#include <fvMatrix.hxx>

#include "PhaseCompressibleTurbulenceModelTwoPhase.hxx"
#include "dragModelTwoPhase.hxx"
#include "heatTransferModelTwoPhase.hxx"

#include <fixedValueFvsPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <slipFvPatchFields.hxx>
#include <partialSlipFvPatchFields.hxx>
#include <fvcFlux.hxx>
#include <surfaceInterpolate.hxx>


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseModel::phaseModel
(
    const twoPhaseSystem& fluid,
    const dictionary& phaseProperties,
    const word& phaseName
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
    phaseDict_
    (
        phaseProperties.subDict(name_)
    ),
    residualAlpha_
    (
        "residualAlpha",
        dimless,
        fluid.subDict(phaseName).lookup("residualAlpha")
    ),
    alphaMax_(phaseDict_.lookupOrDefault("alphaMax", 1.0)),
    thermo_(rhoThermo::New(fluid.mesh(), name_)),
    U_
    (
        IOobject
        (
            IOobject::groupName("U", name_),
            fluid.mesh().time().timeName(),
            fluid.mesh(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        fluid.mesh()
    ),
    alphaPhi_
    (
        IOobject
        (
            IOobject::groupName("alphaPhi", name_),
            fluid.mesh().time().timeName(),
            fluid.mesh()
        ),
        fluid.mesh(),
        dimensionedScalar(dimensionSet(0, 3, -1, 0, 0), 0)
    ),
    alphaRhoPhi_
    (
        IOobject
        (
            IOobject::groupName("alphaRhoPhi", name_),
            fluid.mesh().time().timeName(),
            fluid.mesh()
        ),
        fluid.mesh(),
        dimensionedScalar(dimensionSet(1, 0, -1, 0, 0), 0)
    )
{
    thermo_->validate("phaseModel " + name_, "h", "e");

    const word phiName = IOobject::groupName("phi", name_);

    IOobject phiHeader
    (
        phiName,
        fluid_.mesh().time().timeName(),
        fluid_.mesh(),
        IOobject::NO_READ
    );

    if (phiHeader.typeHeaderOk<surfaceScalarField>(true))
    {
        Info << "Reading face flux field " << phiName << endl;

        phiPtr_.reset
        (
            new surfaceScalarField
            (
                IOobject
                (
                    phiName,
                    fluid_.mesh().time().timeName(),
                    fluid_.mesh(),
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                fluid_.mesh()
            )
        );
    }
    else
    {
        Info << "Calculating face flux field " << phiName << endl;

        wordList phiTypes
        (
            U_.boundaryField().size(),
            calculatedFvPatchScalarField::typeName
        );

        forAll(U_.boundaryField(), i)
        {
            if
                (
                    isA<fixedValueFvPatchVectorField>(U_.boundaryField()[i])
                    || isA<slipFvPatchVectorField>(U_.boundaryField()[i])
                    || isA<partialSlipFvPatchVectorField>(U_.boundaryField()[i])
                    )
            {
                phiTypes[i] = fixedValueFvsPatchScalarField::typeName;
            }
        }

        phiPtr_.reset
        (
            new surfaceScalarField
            (
                IOobject
                (
                    phiName,
                    fluid_.mesh().time().timeName(),
                    fluid_.mesh(),
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                fvc::flux(U_),
                phiTypes
            )
        );
    }

    dPtr_ = diameterModel::New
    (
        phaseDict_,
        *this
    );

    turbulence_ =
        PhaseCompressibleTurbulenceModel<phaseModel>::New
        (
            *this,
            thermo_->rho(),
            U_,
            alphaRhoPhi_,
            phi(),
            *this
        );
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phaseModel::~phaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::phaseModel& tnbLib::phaseModel::otherPhase() const
{
    return fluid_.otherPhase(*this);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phaseModel::d() const
{
    return dPtr_().d();
}


tnbLib::PhaseCompressibleTurbulenceModel<tnbLib::phaseModel>&
tnbLib::phaseModel::turbulence()
{
    return turbulence_();
}


const tnbLib::PhaseCompressibleTurbulenceModel<tnbLib::phaseModel>&
tnbLib::phaseModel::turbulence() const
{
    return turbulence_();
}


void tnbLib::phaseModel::correct()
{
    return dPtr_->correct();
}


bool tnbLib::phaseModel::read(const dictionary& phaseProperties)
{
    phaseDict_ = phaseProperties.subDict(name_);
    return dPtr_->read(phaseDict_);
}


void tnbLib::phaseModel::correctInflowOutflow(surfaceScalarField& alphaPhi) const
{
    surfaceScalarField::Boundary& alphaPhiBf = alphaPhi.boundaryFieldRef();
    const volScalarField::Boundary& alphaBf = boundaryField();
    const surfaceScalarField::Boundary& phiBf = phi().boundaryField();

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
