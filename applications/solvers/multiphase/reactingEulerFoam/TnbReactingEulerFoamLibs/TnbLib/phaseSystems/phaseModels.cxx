/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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
//#define FoamTurbulenceModel_EXPORT_DEFINE
//#define FoamGeometricField_EXPORT_DEFINE

#include <addToRunTimeSelectionTable.hxx>

#include <AnisothermalPhaseModel.hxx>  //moved by Payvand

#include <rhoThermo.hxx>
#include <rhoReactionThermo.hxx>

#include <CombustionModelTemplate.hxx>

#include <phaseModel.hxx>
#include <ThermoPhaseModel.hxx>
#include <IsothermalPhaseModel.hxx>
//#include <AnisothermalPhaseModel.hxx>  // commented by Payvand
#include <PurePhaseModel.hxx>
#include <MultiComponentPhaseModel.hxx>
#include <InertPhaseModel.hxx>
#include <ReactingPhaseModel.hxx>
#include <MovingPhaseModel.hxx>
#include <StationaryPhaseModel.hxx>
#include <TurbulenceModelTemplate.hxx>
#include <GeometricField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    typedef
        AnisothermalPhaseModel
        <
        PurePhaseModel
        <
        InertPhaseModel
        <
        MovingPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoThermo>
        >
        >
        >
        >
        purePhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        purePhaseModel,
        phaseSystem,
        purePhaseModel
    );

    typedef
        AnisothermalPhaseModel
        <
        PurePhaseModel
        <
        InertPhaseModel
        <
        StationaryPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoThermo>
        >
        >
        >
        >
        pureStationaryPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        pureStationaryPhaseModel,
        phaseSystem,
        pureStationaryPhaseModel
    );

    typedef
        IsothermalPhaseModel
        <
        PurePhaseModel
        <
        InertPhaseModel
        <
        MovingPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoThermo>
        >
        >
        >
        >
        pureIsothermalPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        pureIsothermalPhaseModel,
        phaseSystem,
        pureIsothermalPhaseModel
    );

    typedef
        IsothermalPhaseModel
        <
        PurePhaseModel
        <
        InertPhaseModel
        <
        StationaryPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoThermo>
        >
        >
        >
        >
        pureStationaryIsothermalPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        pureStationaryIsothermalPhaseModel,
        phaseSystem,
        pureStationaryIsothermalPhaseModel
    );

    typedef
        AnisothermalPhaseModel
        <
        MultiComponentPhaseModel
        <
        InertPhaseModel
        <
        MovingPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoReactionThermo>
        >
        >
        >
        >
        multiComponentPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        multiComponentPhaseModel,
        phaseSystem,
        multiComponentPhaseModel
    );

    typedef
        IsothermalPhaseModel
        <
        MultiComponentPhaseModel
        <
        InertPhaseModel
        <
        MovingPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoReactionThermo>
        >
        >
        >
        >
        multiComponentIsothermalPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        multiComponentIsothermalPhaseModel,
        phaseSystem,
        multiComponentIsothermalPhaseModel
    );

    typedef
        AnisothermalPhaseModel
        <
        MultiComponentPhaseModel
        <
        ReactingPhaseModel
        <
        MovingPhaseModel
        <
        ThermoPhaseModel<phaseModel, rhoReactionThermo>
        >,
        CombustionModel<rhoReactionThermo>
        >
        >
        >
        reactingPhaseModel;

    addNamedToRunTimeSelectionTable
    (
        phaseModel,
        reactingPhaseModel,
        phaseSystem,
        reactingPhaseModel
    );
}

// ************************************************************************* //
