#pragma once
#ifndef _fvSolution_Header
#define _fvSolution_Header

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
	tnbLib::fvSolution

Description
	Selector class for finite volume solution solution.
	fvMesh is derived from fvSolution so that all fields have access to the
	fvSolution from the mesh reference they hold.

\*---------------------------------------------------------------------------*/

#include <solution.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class fvSolution Declaration
	\*---------------------------------------------------------------------------*/

	class fvSolution
		:
		public solution
	{
	public:

		// Constructors

			//- Construct for objectRegistry
		fvSolution(const objectRegistry& obr)
			:
			solution(obr, "fvSolution")
		{}

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT fvSolution(const fvSolution&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const fvSolution&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvSolution_Header
