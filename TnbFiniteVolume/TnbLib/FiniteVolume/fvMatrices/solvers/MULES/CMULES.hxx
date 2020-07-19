#pragma once
#ifndef _CMULES_Header
#define _CMULES_Header

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

Global
	MULES

Description
	CMULES: Multidimensional universal limiter for
	explicit corrected implicit solution.

	Solve a convective-only transport equation using an explicit universal
	multi-dimensional limiter to correct an implicit conservative bounded
	obtained using rigorously bounded schemes such as Euler-implicit in time
	upwind in space.

	Parameters are the variable to solve, the normal convective flux and the
	actual explicit flux of the variable which is also used to return limited
	flux used in the bounded-solution.

SourceFiles
	CMULES.C
	CMULESTemplates.C

\*---------------------------------------------------------------------------*/

#include <MULES.hxx>
#include <EulerDdtScheme.hxx>
#include <localEulerDdtScheme.hxx>
#include <gaussConvectionScheme.hxx>

#endif // !_CMULES_Header
