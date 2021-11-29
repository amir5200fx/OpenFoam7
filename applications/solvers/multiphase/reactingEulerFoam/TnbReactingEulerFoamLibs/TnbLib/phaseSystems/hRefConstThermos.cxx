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

#include <reactingEulerFoamLibs_Module.hxx>

#include <makeReactionThermo.hxx>
#include <makeThermo.hxx>

#include <rhoReactionThermo.hxx>
#include <heRhoThermo.hxx>

#include <specie.hxx>
#include <perfectGas.hxx>
#include <perfectFluid.hxx>
#include <rhoConst.hxx>

#include <sensibleEnthalpy.hxx>

#include <hRefConstThermo.hxx>
#include <eRefConstThermo.hxx>

#include <constTransport.hxx>

#include <pureMixture.hxx>
#include <multiComponentMixture.hxx>

#include <thermoPhysicsTypes.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    // Thermo type typedefs:

    typedef
        constTransport
        <
        species::thermo
        <
        hRefConstThermo
        <
        perfectGas<specie>
        >,
        sensibleEnthalpy
        >
        > constRefGasHThermoPhysics;

    typedef
        constTransport
        <
        species::thermo
        <
        hRefConstThermo
        <
        perfectFluid<specie>
        >,
        sensibleEnthalpy
        >
        > constRefFluidHThermoPhysics;

    typedef
        constTransport
        <
        species::thermo
        <
        eRefConstThermo
        <
        perfectGas<specie>
        >,
        sensibleInternalEnergy
        >
        > constRefGasEThermoPhysics;

    typedef
        constTransport
        <
        species::thermo
        <
        eRefConstThermo
        <
        perfectFluid<specie>
        >,
        sensibleInternalEnergy
        >
        > constRefFluidEThermoPhysics;

    typedef
        constTransport
        <
        species::thermo
        <
        eRefConstThermo
        <
        rhoConst<specie>
        >,
        sensibleInternalEnergy
        >
        > constRefRhoConstEThermoPhysics;

    typedef
        constTransport
        <
        species::thermo
        <
        hRefConstThermo
        <
        rhoConst<specie>
        >,
        sensibleEnthalpy
        >
        > constRefRhoConstHThermoPhysics;


    // pureMixture, sensibleEnthalpy:

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleEnthalpy,
        hRefConstThermo,
        perfectGas,
        specie
    );

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleEnthalpy,
        hRefConstThermo,
        perfectFluid,
        specie
    );

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleEnthalpy,
        hRefConstThermo,
        rhoConst,
        specie
    );


    // pureMixture, sensibleInternalEnergy:

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleInternalEnergy,
        eRefConstThermo,
        perfectGas,
        specie
    );

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleInternalEnergy,
        eRefConstThermo,
        perfectFluid,
        specie
    );

    makeThermos
    (
        rhoThermo,
        heRhoThermo,
        pureMixture,
        constTransport,
        sensibleInternalEnergy,
        eRefConstThermo,
        rhoConst,
        specie
    );


    // multiComponentMixture, sensibleInternalEnergy:

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefGasEThermoPhysics
    );

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefFluidEThermoPhysics
    );

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefRhoConstEThermoPhysics
    );


    // multiComponentMixture, sensibleEnthalpy:

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefRhoConstHThermoPhysics
    );

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefFluidHThermoPhysics
    );

    makeThermoPhysicsReactionThermos
    (
        rhoThermo,
        rhoReactionThermo,
        heRhoThermo,
        multiComponentMixture,
        constRefGasHThermoPhysics
    );


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
