#pragma once
#ifndef _Rosenbrock12_Header
#define _Rosenbrock12_Header

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
	tnbLib::Rosenbrock12

Description
	L-stable embedded Rosenbrock ODE solver of order (1)2.

	References:
	\verbatim
		Verwer, J. G., Spee, E. J., Blom, J. G., & Hundsdorfer, W. (1999).
		A second-order Rosenbrock method applied to
		photochemical dispersion problems.
		SIAM Journal on Scientific Computing, 20(4), 1456-1480.
	\endverbatim

SourceFiles
	Rosenbrock12.C

\*---------------------------------------------------------------------------*/

#include <ODESolver.hxx>
#include <adaptiveSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class Rosenbrock12 Declaration
	\*---------------------------------------------------------------------------*/

	class Rosenbrock12
		:
		public ODESolver,
		public adaptiveSolver
	{
		// Private Data

		mutable scalarField k1_;
		mutable scalarField k2_;
		mutable scalarField err_;
		mutable scalarField dydx_;
		mutable scalarField dfdx_;
		mutable scalarSquareMatrix dfdy_;
		mutable scalarSquareMatrix a_;
		mutable labelList pivotIndices_;

		static FoamODE_EXPORT const scalar
			a21,
			c21,
			b1, b2,
			gamma,
			c2,
			e1, e2,
			d1, d2;


	public:

		//- Runtime type information
		//TypeName("Rosenbrock12");
		static const char* typeName_() { return "Rosenbrock12"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from ODESystem
		FoamODE_EXPORT Rosenbrock12(const ODESystem& ode, const dictionary& dict);


		//- Destructor
		virtual ~Rosenbrock12()
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

#endif // !_Rosenbrock12_Header
