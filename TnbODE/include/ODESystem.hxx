#pragma once
#ifndef _ODESystem_Header
#define _ODESystem_Header

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
	tnbLib::ODESystem

Description
	Abstract base class for the systems of ordinary differential equations.

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <scalarMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class ODESystem Declaration
	\*---------------------------------------------------------------------------*/

	class ODESystem
	{

	public:

		// Constructors

			//- Construct null
		ODESystem()
		{}


		//- Destructor
		virtual ~ODESystem()
		{}


		// Member Functions

			//- Return the number of equations in the system
		FoamODE_EXPORT virtual label nEqns() const = 0;

		//- Calculate the derivatives in dydx
		FoamODE_EXPORT virtual void derivatives
		(
			const scalar x,
			const scalarField& y,
			scalarField& dydx
		) const = 0;

		//- Calculate the Jacobian of the system
		//  Need by the stiff-system solvers
		FoamODE_EXPORT virtual void jacobian
		(
			const scalar x,
			const scalarField& y,
			scalarField& dfdx,
			scalarSquareMatrix& dfdy
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ODESystem_Header
