#pragma once
#ifndef _CorrectPhi_Header
#define _CorrectPhi_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::CorrectPhi

Description
	Flux correction functions to ensure continuity.

	Required during start-up, restart, mesh-motion etc. when non-conservative
	fluxes may adversely affect the prediction-part of the solution algorithm
	(the part before the first pressure solution which would ensure continuity).
	This is particularly important for VoF and other multi-phase solver in
	which non-conservative fluxes cause unboundedness of the phase-fraction.

SourceFiles
	CorrectPhi.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	class nonOrthogonalSolutionControl;

	//- If the mesh is moving correct the velocity BCs on the moving walls to
	//  ensure the corrected fluxes and velocity are consistent
	void correctUphiBCs
	(
		volVectorField& U,
		surfaceScalarField& phi,
		const bool evaluateUBCs
	);

	//- If the mesh is moving correct the velocity BCs on the moving walls to
	//  ensure the corrected fluxes and velocity are consistent
	void correctUphiBCs
	(
		const volScalarField& rho,
		volVectorField& U,
		surfaceScalarField& phi,
		const bool evaluateUBCs
	);

	template<class RAUfType, class DivUType>
	void CorrectPhi
	(
		volVectorField& U,
		surfaceScalarField& phi,
		const volScalarField& p,
		const RAUfType& rAUf,
		const DivUType& divU,
		nonOrthogonalSolutionControl& pcorrControl,
		const bool evaluateUBCs
	);

	template<class RAUfType, class DivRhoUType>
	void CorrectPhi
	(
		volVectorField& U,
		surfaceScalarField& phi,
		const volScalarField& p,
		const volScalarField& rho,
		const volScalarField& psi,
		const RAUfType& rAUf,
		const DivRhoUType& divRhoU,
		nonOrthogonalSolutionControl& pcorrControl,
		const bool evaluateUBCs
	);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CorrectPhiI.hxx>

//#ifdef NoRepository
//#include <CorrectPhi.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CorrectPhi_Header
