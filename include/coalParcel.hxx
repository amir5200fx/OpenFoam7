#pragma once
#ifndef _coalParcel_Header
#define _coalParcel_Header

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

Class
	tnbLib::coalParcel

Description
	Definition of coal parcel

SourceFiles
	CoalParcel.C

\*---------------------------------------------------------------------------*/

#include <contiguous.hxx>
#include <particle.hxx>
#include <KinematicParcel.hxx>
#include <ThermoParcel.hxx>
#include <ReactingParcel.hxx>
#include <ReactingMultiphaseParcel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef ReactingMultiphaseParcel
		<
		ReactingParcel
		<
		ThermoParcel
		<
		KinematicParcel
		<
		particle
		>
		>
		>
		> coalParcel;

	template<>
	inline bool contiguous<coalParcel>()
	{
		return false;
	}
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coalParcel_Header
