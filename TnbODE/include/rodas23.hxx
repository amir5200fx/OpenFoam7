#pragma once
#ifndef _rodas23_Header
#define _rodas23_Header

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
	tnbLib::rodas23

Description
	L-stable, stiffly-accurate embedded Rosenbrock ODE solver of order (2)3.

	References:
	\verbatim
		Sandu, A., Verwer, J. G., Blom, J. G., Spee, E. J., Carmichael, G. R.,
		& Potra, F. A. (1997).
		Benchmarking stiff ODE solvers for atmospheric chemistry problems II:
		Rosenbrock solvers.
		Atmospheric environment, 31(20), 3459-3472.
	\endverbatim

SourceFiles
	rodas23.C

\*---------------------------------------------------------------------------*/

#include <ODESolver.hxx>
#include <adaptiveSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class rodas23 Declaration
	\*---------------------------------------------------------------------------*/

	class rodas23
		:
		public ODESolver,
		public adaptiveSolver
	{
		// Private Data

		mutable scalarField k1_;
		mutable scalarField k2_;
		mutable scalarField k3_;
		mutable scalarField dy_;
		mutable scalarField err_;
		mutable scalarField dydx_;
		mutable scalarField dfdx_;
		mutable scalarSquareMatrix dfdy_;
		mutable scalarSquareMatrix a_;
		mutable labelList pivotIndices_;

		static FoamODE_EXPORT const scalar
			c3,
			d1, d2,
			a31,
			a41,
			c21, c31, c32,
			c41, c42, c43,
			gamma;

	public:

		//- Runtime type information
		//TypeName("rodas23");
		static const char* typeName_() { return "rodas23"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from ODESystem
		FoamODE_EXPORT rodas23(const ODESystem& ode, const dictionary& dict);


		//- Destructor
		virtual ~rodas23()
		{}


		// Member Functions

			//- Inherit solve from ODESolver
		using ODESolver::solve;

		//- Resize the ODE solver
		FoamODE_EXPORT virtual bool resize();

		//- Solve a single step dx and return the error
		FoamODE_EXPORT virtual scalar solve
		(
			const scalar x0,
			const scalarField& y0,
			const scalarField& dydx0,
			const scalar dx,
			scalarField& y
		) const;

		//- Solve the ODE system and the update the state
		FoamODE_EXPORT virtual void solve
		(
			scalar& x,
			scalarField& y,
			scalar& dxTry
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rodas23_Header
