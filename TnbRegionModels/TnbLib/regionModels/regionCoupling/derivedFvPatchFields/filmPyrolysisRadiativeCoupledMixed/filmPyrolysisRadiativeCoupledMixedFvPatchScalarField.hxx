#pragma once
#ifndef _filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header
#define _filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	Foam::filmPyrolysisRadiativeCoupledMixedFvPatchScalarField

Description
	Mixed boundary condition for temperature, to be used in the flow and
	pyrolysis regions when a film region model is used.

	Example usage:
	\verbatim
	myInterfacePatchName
	{
		type            filmPyrolysisRadiativeCoupledMixed;
		Tnbr            T;
		kappa           fluidThermo;
		qr              qr;
		kappaName       none;
		filmDeltaDry    0.0;
		filmDeltaWet    3e-4;
		value           $internalField;
	}
	\endverbatim

	Needs to be on underlying mapped(Wall)FvPatch.
	It calculates local field as:

	\verbatim
		ratio = (filmDelta - filmDeltaDry)/(filmDeltaWet - filmDeltaDry)
	\endverbatim

	when ratio = 1 is considered wet and the film temperature is fixed at
	the wall. If ratio = 0 (dry) it emulates the normal radiative solid BC.

	In between ratio 0 and 1 the gradient and value contributions are
	weighted using the ratio field in the following way:

	\verbatim
		qConv = ratio*htcwfilm*(Tfilm - *this);
		qRad = (1.0 - ratio)*qr;
	\endverbatim

	Then the solid can gain or loose energy through radiation or conduction
	towards the film.

	Notes:

	- kappa and \c kappaName are inherited from temperatureCoupledBase.
	- qr is the radiative flux defined in the radiation model.


See also
	Foam::temperatureCoupledBase

SourceFiles
	filmPyrolysisRadiativeCoupledMixedFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>
#include <temperatureCoupledBase.hxx>


#endif // !_filmPyrolysisRadiativeCoupledMixedFvPatchScalarField_Header
