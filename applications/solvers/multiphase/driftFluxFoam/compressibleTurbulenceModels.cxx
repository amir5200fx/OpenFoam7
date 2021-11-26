/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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

#define FoamRASModel_EXPORT_DEFINE
#define FoamlaminarModel_EXPORT_DEFINE
#define FoamLESModel_EXPORT_DEFINE

#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#define FoamTurbulenceModel_EXPORT_DEFINE

#define FoamStokes_EXPORT_DEFINE
#define FoamMaxwell_EXPORT_DEFINE
#define FoamGiesekus_EXPORT_DEFINE
#define FoamkEpsilon_EXPORT_DEFINE
#define FoamkOmegaSST_EXPORT_DEFINE
#define FoamSmagorinsky_EXPORT_DEFINE
#define FoamkEqn_EXPORT_DEFINE
#define FoambuoyantKEpsilon_EXPORT_DEFINE
#define FoamLRR_EXPORT_DEFINE
#define FoamSSG_EXPORT_DEFINE

#include "incompressibleTwoPhaseInteractingMixture.hxx"

#include <CompressibleTurbulenceModelTemplate.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <makeTurbulenceModel.hxx>

#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

makeTurbulenceModelTypes
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    incompressibleTwoPhaseInteractingMixture
);

makeBaseTurbulenceModel
(
    geometricOneField,
    volScalarField,
    compressibleTurbulenceModel,
    CompressibleTurbulenceModel,
    incompressibleTwoPhaseInteractingMixture
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
        incompressibleTwoPhaseInteractingMixtureCompressibleTurbulenceModel,   \
        laminar,                                                               \
        Type                                                                   \
    )

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
        incompressibleTwoPhaseInteractingMixtureCompressibleTurbulenceModel,   \
        RAS,                                                                   \
        Type                                                                   \
    )

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (                                                                          \
        incompressibleTwoPhaseInteractingMixtureCompressibleTurbulenceModel,   \
        LES,                                                                   \
        Type                                                                   \
    )

#include <Stokes.hxx>
makeLaminarModel(Stokes);

#include <kEpsilon.hxx>
makeRASModel(kEpsilon);

#include <buoyantKEpsilon.hxx>
makeRASModel(buoyantKEpsilon);

#include <Smagorinsky.hxx>
makeLESModel(Smagorinsky);

#include <kEqn.hxx>
makeLESModel(kEqn);

#include <LRR.hxx>
makeRASModel(LRR);

#include <SSG.hxx>
makeRASModel(SSG);


// ************************************************************************* //
