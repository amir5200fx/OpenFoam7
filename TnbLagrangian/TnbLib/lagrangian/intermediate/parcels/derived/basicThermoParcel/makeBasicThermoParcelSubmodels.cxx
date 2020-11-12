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

#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicThermoCloud.hxx>

#include <makeParcelCloudFunctionObjects.hxx>

// Kinematic
#include <makeParcelForces.hxx>
#include <makeParcelDispersionModels.hxx>
#include <makeParcelInjectionModels.hxx>
#include <makeParcelPatchInteractionModels.hxx>
#include <makeParcelStochasticCollisionModels.hxx>
#include <makeThermoParcelSurfaceFilmModels.hxx> // thermo variant

// Thermodynamic
#include <makeParcelHeatTransferModels.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeParcelCloudFunctionObjects(basicThermoCloud);

// Kinematic sub-models
makeParcelForces(basicThermoCloud);
makeParcelDispersionModels(basicThermoCloud);
makeParcelInjectionModels(basicThermoCloud);
makeParcelPatchInteractionModels(basicThermoCloud);
makeParcelStochasticCollisionModels(basicThermoCloud);
makeParcelSurfaceFilmModels(basicThermoCloud);

// Thermo sub-models
makeParcelHeatTransferModels(basicThermoCloud);


// ************************************************************************* //
