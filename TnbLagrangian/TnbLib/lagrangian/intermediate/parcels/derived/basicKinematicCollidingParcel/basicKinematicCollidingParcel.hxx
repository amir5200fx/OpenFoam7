#pragma once
#ifndef _basicKinematicCollidingParcel_Header
#define _basicKinematicCollidingParcel_Header

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
	tnbLib::basicKinematicCollidingParcel

Description
	Definition of basic kinematic colliding parcel

SourceFiles
	basicKinematicParcel.H

\*---------------------------------------------------------------------------*/

#include <contiguous.hxx>
#include <particle.hxx>
#include <KinematicParcel.hxx>
#include <CollidingParcel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef CollidingParcel<KinematicParcel<particle>>
		basicKinematicCollidingParcel;

	template<>
	inline bool contiguous<basicKinematicCollidingParcel>()
	{
		return true;
	}
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_basicKinematicCollidingParcel_Header
