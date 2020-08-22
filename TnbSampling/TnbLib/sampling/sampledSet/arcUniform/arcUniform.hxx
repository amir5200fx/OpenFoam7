#pragma once
#ifndef _arcUniform_Header
#define _arcUniform_Header

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
	Foam::sampledSets::arcUniform

Description
	Uniform samples along an arc

Usage
	\table
		Property    | Description                            | Req'd? | Default
		centre      | Centre of the circle                   | yes    |
		normal      | Direction normal to the plane of the circle  | yes |
		radial      | Vector from the centre to a point on the arc | yes |
		startAngle  | The angle of the start of the arc in radians | yes |
		endAngle    | The angle of the end of the arc in radians | yes |
		nPoints     | The number of points                   | yes    |
		axis        | The coordinate axis that is written    | yes    |
	\endtable

	Example specification:
	\verbatim
	{
		type        arcUniform;
		centre      (0.95 0 0.25);
		normal      (1 0 0);
		radial      (0 0 0.25);
		startAngle  -1.57079633;
		endAngle    0.52359878;
		nPoints     200;
		axis        x;
	}
	\endverbatim

SourceFiles
	arcUniform.C

\*---------------------------------------------------------------------------*/



#endif // !_arcUniform_Header
