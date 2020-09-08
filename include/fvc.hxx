#pragma once
#ifndef _fvc_Header
#define _fvc_Header

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

Namespace
	tnbLib::fvc

Description
	Namespace of functions to calculate explicit derivatives.

\*---------------------------------------------------------------------------*/

#include <fv.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceInterpolate.hxx>
#include <fvcVolumeIntegrate.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <fvcAverage.hxx>
#include <fvcReconstruct.hxx>
#include <fvcDdt.hxx>
#include <fvcDDt.hxx>
#include <fvcD2dt2.hxx>
#include <fvcDiv.hxx>
#include <fvcFlux.hxx>
#include <fvcGrad.hxx>
#include <fvcMagSqrGradGrad.hxx>
#include <fvcSnGrad.hxx>
#include <fvcCurl.hxx>
#include <fvcLaplacian.hxx>
#include <fvcSup.hxx>
#include <fvcMeshPhi.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvc_Header
