#pragma once
#ifndef _UOprocess_Header
#define _UOprocess_Header

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
	tnbLib::UOprocess

Description
	Random UO process.

SourceFiles
	UOprocess.C

\*---------------------------------------------------------------------------*/

#include <RandomProcesses_Module.hxx>
#include <complexFields.hxx>
#include <scalar.hxx>
#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Kmesh;
	class dictionary;

	/*---------------------------------------------------------------------------*\
							   Class UOprocess Declaration
	\*---------------------------------------------------------------------------*/

	class UOprocess
	{
		// Private Data

		Random GaussGen;

		const Kmesh& Mesh;
		const scalar DeltaT, RootDeltaT;
		complexVectorField UOfield;

		scalar Alpha;
		scalar Sigma;
		scalar Kupper;
		scalar Klower;
		scalar Scale;


		// Private Member Functions

		FoamRandomProcesses_EXPORT complexVector WeinerProcess();


	public:

		// Constructors

			//- Construct from wavenumber mesh and timestep
		FoamRandomProcesses_EXPORT UOprocess
		(
			const Kmesh& kmesh,
			const scalar deltaT,
			const dictionary&
		);


		// Member Functions

		FoamRandomProcesses_EXPORT const complexVectorField& newField();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_UOprocess_Header
