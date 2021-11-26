/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
#define FoamLESModel_EXPORT_DEFINE
#define FoamlaminarModel_EXPORT_DEFINE

#include <PhaseCompressibleTurbulenceModel.hxx>
#include <fluidThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <makeTurbulenceModel.hxx>

#include <ThermalDiffusivity.hxx>
#include <EddyDiffusivity.hxx>

#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

makeTurbulenceModelTypes
(
    volScalarField,
    compressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    ThermalDiffusivity,
    fluidThermo
);

makeBaseTurbulenceModel
(
    volScalarField,
    compressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    ThermalDiffusivity,
    fluidThermo
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedLaminarModel                                                  \
    (fluidThermoPhaseCompressibleTurbulenceModel, laminar, Type)

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoPhaseCompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoPhaseCompressibleTurbulenceModel, LES, Type)

#include <Stokes.hxx>
makeLaminarModel(Stokes);

#include <Maxwell.hxx>
makeLaminarModel(Maxwell);

#include <Giesekus.hxx>
makeLaminarModel(Giesekus);

#include <kEpsilon.hxx>
makeRASModel(kEpsilon);

#include <kOmegaSST.hxx>
makeRASModel(kOmegaSST);

#include <Smagorinsky.hxx>
makeLESModel(Smagorinsky);

#include <kEqn.hxx>
makeLESModel(kEqn);

// ************************************************************************* //
