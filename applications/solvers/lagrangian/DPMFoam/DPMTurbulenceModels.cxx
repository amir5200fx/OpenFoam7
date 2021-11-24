/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

#include <includeAllModules.hxx>

#include <PhaseIncompressibleTurbulenceModel.hxx>
#include <singlePhaseTransportModel.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <makeTurbulenceModel.hxx>

#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeTurbulenceModelTypes
(
    volScalarField,
    geometricOneField,
    incompressibleTurbulenceModel,
    PhaseIncompressibleTurbulenceModel,
    singlePhaseTransportModel
);

makeBaseTurbulenceModel
(
    volScalarField,
    geometricOneField,
    incompressibleTurbulenceModel,
    PhaseIncompressibleTurbulenceModel,
    singlePhaseTransportModel
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedTurbulenceModel                                               \
    (singlePhaseTransportModelPhaseIncompressibleTurbulenceModel, laminar, Type)

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (singlePhaseTransportModelPhaseIncompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (singlePhaseTransportModelPhaseIncompressibleTurbulenceModel, LES, Type)

#include <Stokes.hxx>
makeLaminarModel(Stokes);

#include <kEpsilon.hxx>
makeRASModel(kEpsilon);

#include <Smagorinsky.hxx>
makeLESModel(Smagorinsky);

#include <kEqn.hxx>
makeLESModel(kEqn);

// ************************************************************************* //
