#pragma once
#ifndef _EulerSI_Header
#define _EulerSI_Header

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
	tnbLib::EulerSI

Description
	Semi-implicit Euler ODE solver of order (0)1.

	The method calculates the new state from:
	\f[
		y_{n+1} = y_n
		  + \delta_x\left[I - \delta_x\frac{\partial f}{\partial y}\right]^{-1}
			\cdot \left[f(y_n) + \delta_x\frac{\partial f}{\partial x}\right]
	\f]
	The error is estimated directly from the change in the solution,
	i.e. the difference between the 0th and 1st order solutions:
	\f[
		err_{n+1} = y_{n+1} - y_n
	\f]

SourceFiles
	EulerSI.C

\*---------------------------------------------------------------------------*/

#include <ODESolver.hxx>
#include <adaptiveSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class EulerSI Declaration
	\*---------------------------------------------------------------------------*/

	class EulerSI
		:
		public ODESolver,
		public adaptiveSolver
	{
		// Private Data

		mutable scalarField err_;
		mutable scalarField dydx_;
		mutable scalarField dfdx_;
		mutable scalarSquareMatrix dfdy_;
		mutable scalarSquareMatrix a_;
		mutable labelList pivotIndices_;


	public:

		//- Runtime type information
		//TypeName("EulerSI");
		static const char* typeName_() { return "EulerSI"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from ODESystem
		FoamODE_EXPORT EulerSI(const ODESystem& ode, const dictionary& dict);


		//- Destructor
		virtual ~EulerSI()
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

#endif // !_EulerSI_Header
