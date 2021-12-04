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

#include <phaseSystem.hxx>
#include <surfaceTensionModelMultiphase.hxx>
#include <aspectRatioModel.hxx>
#include <surfaceInterpolate.hxx>
#include <fvcDdt.hxx>
#include <localEulerDdtScheme.hxx>

#include <dragModel.hxx>
#include <BlendedInterfacialModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(phaseSystem, 0);
}

const tnbLib::word tnbLib::phaseSystem::propertiesName("phaseProperties");


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::phaseSystem::calcPhi
(
    const phaseModelList& phaseModels
) const
{
    tmp<surfaceScalarField> tmpPhi
    (
        surfaceScalarField::New
        (
            "phi",
            fvc::interpolate(phaseModels[0]) * phaseModels[0].phi()
        )
    );

    for (label phasei = 1; phasei < phaseModels.size(); phasei++)
    {
        tmpPhi.ref() +=
            fvc::interpolate(phaseModels[phasei]) * phaseModels[phasei].phi();
    }

    return tmpPhi;
}


void tnbLib::phaseSystem::generatePairs
(
    const dictTable& modelDicts
)
{
    forAllConstIter(dictTable, modelDicts, iter)
    {
        const phasePairKey& key = iter.key();

        // pair already exists
        if (phasePairs_.found(key))
        {
        }

        // new ordered pair
        else if (key.ordered())
        {
            phasePairs_.insert
            (
                key,
                autoPtr<phasePair>
                (
                    new orderedPhasePair
                    (
                        phaseModels_[key.first()],
                        phaseModels_[key.second()]
                    )
                    )
            );
        }

        // new unordered pair
        else
        {
            phasePairs_.insert
            (
                key,
                autoPtr<phasePair>
                (
                    new phasePair
                    (
                        phaseModels_[key.first()],
                        phaseModels_[key.second()]
                    )
                    )
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseSystem::phaseSystem
(
    const fvMesh& mesh
)
    :
    IOdictionary
    (
        IOobject
        (
            "phaseProperties",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    ),

    mesh_(mesh),

    phaseModels_(lookup("phases"), phaseModel::iNew(*this)),

    phi_(calcPhi(phaseModels_)),

    dpdt_
    (
        IOobject
        (
            "dpdt",
            mesh.time().timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar(dimPressure / dimTime, 0)
    ),

    MRF_(mesh_)
{
    // Groupings
    label movingPhasei = 0;
    label stationaryPhasei = 0;
    label anisothermalPhasei = 0;
    label multiComponentPhasei = 0;
    forAll(phaseModels_, phasei)
    {
        phaseModel& phase = phaseModels_[phasei];
        movingPhasei += !phase.stationary();
        stationaryPhasei += phase.stationary();
        anisothermalPhasei += !phase.isothermal();
        multiComponentPhasei += !phase.pure();
    }
    movingPhaseModels_.resize(movingPhasei);
    stationaryPhaseModels_.resize(stationaryPhasei);
    anisothermalPhaseModels_.resize(anisothermalPhasei);
    multiComponentPhaseModels_.resize(multiComponentPhasei);

    movingPhasei = 0;
    stationaryPhasei = 0;
    anisothermalPhasei = 0;
    multiComponentPhasei = 0;
    forAll(phaseModels_, phasei)
    {
        phaseModel& phase = phaseModels_[phasei];
        if (!phase.stationary())
        {
            movingPhaseModels_.set(movingPhasei++, &phase);
        }
        if (phase.stationary())
        {
            stationaryPhaseModels_.set(stationaryPhasei++, &phase);
        }
        if (!phase.isothermal())
        {
            anisothermalPhaseModels_.set(anisothermalPhasei++, &phase);
        }
        if (!phase.pure())
        {
            multiComponentPhaseModels_.set(multiComponentPhasei++, &phase);
        }
    }

    // Write phi
    phi_.writeOpt() = IOobject::AUTO_WRITE;

    // Blending methods
    forAllConstIter(dictionary, subDict("blending"), iter)
    {
        blendingMethods_.insert
        (
            iter().keyword(),
            blendingMethod::New
            (
                iter().keyword(),
                iter().dict(),
                phaseModels_.toc()
            )
        );
    }

    // Sub-models
    generatePairsAndSubModels("surfaceTension", surfaceTensionModels_);
    generatePairsAndSubModels("aspectRatio", aspectRatioModels_);

    // Update motion fields
    correctKinematics();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phaseSystem::~phaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::phaseSystem::rho() const
{
    const label nMovingPhases = movingPhaseModels_.size();

    tmp<volScalarField> rho(movingPhaseModels_[0] * movingPhaseModels_[0].rho());
    for (label movingPhasei = 1; movingPhasei < nMovingPhases; ++movingPhasei)
    {
        rho.ref() +=
            movingPhaseModels_[movingPhasei]
            * movingPhaseModels_[movingPhasei].rho();
    }

    if (stationaryPhaseModels_.empty())
    {
        return rho;
    }

    volScalarField alpha(movingPhaseModels_[0]);
    for (label movingPhasei = 1; movingPhasei < nMovingPhases; ++movingPhasei)
    {
        alpha += movingPhaseModels_[movingPhasei];
    }

    return rho / alpha;
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::phaseSystem::U() const
{
    const label nMovingPhases = movingPhaseModels_.size();

    tmp<volVectorField> U(movingPhaseModels_[0] * movingPhaseModels_[0].U());
    for (label movingPhasei = 1; movingPhasei < nMovingPhases; ++movingPhasei)
    {
        U.ref() +=
            movingPhaseModels_[movingPhasei]
            * movingPhaseModels_[movingPhasei].U();
    }

    if (stationaryPhaseModels_.empty())
    {
        return U;
    }

    volScalarField alpha(movingPhaseModels_[0]);
    for (label movingPhasei = 1; movingPhasei < nMovingPhases; ++movingPhasei)
    {
        alpha += movingPhaseModels_[movingPhasei];
    }

    return U / alpha;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::phaseSystem::E(const phasePairKey& key) const
{
    if (aspectRatioModels_.found(key))
    {
        return aspectRatioModels_[key]->E();
    }
    else
    {
        return volScalarField::New
        (
            aspectRatioModel::typeName + ":E",
            this->mesh_,
            dimensionedScalar(dimless, 1)
        );
    }
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::phaseSystem::sigma(const phasePairKey& key) const
{
    if (surfaceTensionModels_.found(key))
    {
        return surfaceTensionModels_[key]->sigma();
    }
    else
    {
        return volScalarField::New
        (
            surfaceTensionModel::typeName + ":sigma",
            this->mesh_,
            dimensionedScalar(surfaceTensionModel::dimSigma, 0)
        );
    }
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phaseSystem::dmdt
(
    const phasePairKey& key
) const
{
    return volScalarField::New
    (
        IOobject::groupName("dmdt", phasePairs_[key]->name()),
        this->mesh_,
        dimensionedScalar(dimDensity / dimTime, 0)
    );
}


tnbLib::PtrList<tnbLib::volScalarField> tnbLib::phaseSystem::dmdts() const
{
    PtrList<volScalarField> dmdts(this->phaseModels_.size());

    return dmdts;
}


void tnbLib::phaseSystem::solve()
{}


void tnbLib::phaseSystem::correct()
{
    forAll(phaseModels_, phasei)
    {
        phaseModels_[phasei].correct();
    }
}


void tnbLib::phaseSystem::correctKinematics()
{
    bool updateDpdt = false;

    forAll(phaseModels_, phasei)
    {
        phaseModels_[phasei].correctKinematics();

        updateDpdt = updateDpdt || phaseModels_[phasei].thermo().dpdt();
    }

    // Update the pressure time-derivative if required
    if (updateDpdt)
    {
        dpdt_ = fvc::ddt(phaseModels_.begin()().thermo().p());
    }
}


void tnbLib::phaseSystem::correctThermo()
{
    forAll(phaseModels_, phasei)
    {
        phaseModels_[phasei].correctThermo();
    }
}


void tnbLib::phaseSystem::correctTurbulence()
{
    forAll(phaseModels_, phasei)
    {
        phaseModels_[phasei].correctTurbulence();
    }
}


void tnbLib::phaseSystem::correctEnergyTransport()
{
    forAll(phaseModels_, phasei)
    {
        phaseModels_[phasei].correctEnergyTransport();
    }
}


bool tnbLib::phaseSystem::read()
{
    if (regIOobject::read())
    {
        bool readOK = true;

        forAll(phaseModels_, phasei)
        {
            readOK &= phaseModels_[phasei].read();
        }

        // models ...

        return readOK;
    }
    else
    {
        return false;
    }
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::byDt(const volScalarField& vf)
{
    if (fv::localEulerDdt::enabled(vf.mesh()))
    {
        return fv::localEulerDdt::localRDeltaT(vf.mesh()) * vf;
    }
    else
    {
        return vf / vf.mesh().time().deltaT();
    }
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::byDt(const surfaceScalarField& sf)
{
    if (fv::localEulerDdt::enabled(sf.mesh()))
    {
        return fv::localEulerDdt::localRDeltaTf(sf.mesh()) * sf;
    }
    else
    {
        return sf / sf.mesh().time().deltaT();
    }
}


// ************************************************************************* //
