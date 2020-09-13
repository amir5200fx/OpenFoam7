/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

#include <basicSprayCloud.hxx>

#include <makeParcelCloudFunctionObjects.hxx>

// Kinematic
#include <makeParcelForces.hxx>
#include <makeThermoParcelTurbulenceForces.hxx> // add turbulence variant
#include <makeParcelDispersionModels.hxx>
#include <makeParcelTurbulenceDispersionModels.hxx> // add turbulence variant
#include <makeSprayParcelInjectionModels.hxx> // Spray variant
#include <makeParcelPatchInteractionModels.hxx>
#include <makeSprayParcelStochasticCollisionModels.hxx> // Spray variant

// Thermodynamic
#include <makeParcelHeatTransferModels.hxx>

// Reacting
#include <makeReactingParcelCompositionModels.hxx>
#include <makeReactingParcelPhaseChangeModels.hxx>
#include <makeReactingParcelSurfaceFilmModels.hxx>

// Spray
#include <DistortedSphereDragForce.hxx>
#include <makeSprayParcelAtomizationModels.hxx>
#include <makeSprayParcelBreakupModels.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeParcelCloudFunctionObjects(basicSprayCloud);

// Kinematic sub-models
makeParcelForces(basicSprayCloud);
makeThermoParcelTurbulenceForces(basicSprayCloud);
makeParcelDispersionModels(basicSprayCloud);
makeParcelTurbulenceDispersionModels(basicSprayCloud);
makeSprayParcelInjectionModels(basicSprayCloud);
makeParcelPatchInteractionModels(basicSprayCloud);
makeSprayParcelStochasticCollisionModels(basicSprayCloud);

// Thermo sub-models
makeParcelHeatTransferModels(basicSprayCloud);

// Reacting sub-models
makeReactingParcelCompositionModels(basicSprayCloud);
makeReactingParcelPhaseChangeModels(basicSprayCloud);
makeReactingParcelSurfaceFilmModels(basicSprayCloud);

// Spray sub-models
makeParticleForceModelType(DistortedSphereDragForce, basicSprayCloud);
makeSprayParcelAtomizationModels(basicSprayCloud);
makeSprayParcelBreakupModels(basicSprayCloud);


// ************************************************************************* //