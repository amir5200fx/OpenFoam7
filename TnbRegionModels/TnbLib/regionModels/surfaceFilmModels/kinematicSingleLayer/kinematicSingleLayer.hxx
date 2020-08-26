#pragma once
#ifndef _kinematicSingleLayer_Header
#define _kinematicSingleLayer_Header

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

Class
	Foam::regionModels::surfaceFilmModels::kinematicSingleLayer

Description
	Kinematic form of single-cell layer surface film model

SourceFiles
	kinematicSingleLayer.C

\*---------------------------------------------------------------------------*/

#include <SurfaceFilmModel.hxx>
#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrices.hxx>



#include <kinematicSingleLayerI.hxx>

#endif // !_kinematicSingleLayer_Header
