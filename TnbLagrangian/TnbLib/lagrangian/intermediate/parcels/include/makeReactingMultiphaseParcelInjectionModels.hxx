#pragma once
#ifndef _makeReactingMultiphaseParcelInjectionModels_Header
#define _makeReactingMultiphaseParcelInjectionModels_Header

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

#include <CellZoneInjection.hxx>
#include <ConeInjection.hxx>
#include <FieldActivatedInjection.hxx>
#include <ManualInjection.hxx>
#include <NoInjection.hxx>
#include <PatchInjectionTemplate.hxx>
#include <PatchFlowRateInjection.hxx>
#include <ReactingMultiphaseLookupTableInjection.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeReactingMultiphaseParcelInjectionModels(CloudType)                 \
                                                                               \
    makeInjectionModel(CloudType);                                             \
    makeInjectionModelType(CellZoneInjection, CloudType);                      \
    makeInjectionModelType(ConeInjection, CloudType);                          \
    makeInjectionModelType(FieldActivatedInjection, CloudType);                \
    makeInjectionModelType(ManualInjection, CloudType);                        \
    makeInjectionModelType(NoInjection, CloudType);                            \
    makeInjectionModelType(PatchInjection, CloudType);                         \
    makeInjectionModelType(PatchFlowRateInjection, CloudType);                 \
    makeInjectionModelType(ReactingMultiphaseLookupTableInjection, CloudType);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_makeReactingMultiphaseParcelInjectionModels_Header
