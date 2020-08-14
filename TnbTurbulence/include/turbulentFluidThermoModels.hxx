#pragma once
#ifndef _turbulentFluidThermoModels_Header
#define _turbulentFluidThermoModels_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

#include <CompressibleTurbulenceModelTemplate.hxx>
#include <compressibleTransportModel.hxx>
#include <fluidThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <compressibleMakeTurbulenceModel.hxx>

#include <ThermalDiffusivity.hxx>
#include <EddyDiffusivity.hxx>

#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeTurbulenceModelTypes
(
	geometricOneField,
	volScalarField,
	compressibleTurbulenceModel,
	CompressibleTurbulenceModel,
	ThermalDiffusivity,
	fluidThermo
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedLaminarModel                                                  \
    (fluidThermoCompressibleTurbulenceModel, laminar, Type)

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoCompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoCompressibleTurbulenceModel, LES, Type)


// ************************************************************************* //

#endif // !_turbulentFluidThermoModels_Header
