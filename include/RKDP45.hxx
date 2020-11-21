#pragma once
#ifndef _RKDP45_Header
#define _RKDP45_Header

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
	tnbLib::RKDP45

Description
	4/5th Order Dormand–Prince Runge-Kutta ODE solver.

	References:
	\verbatim
		Dormand, J. R., & Prince, P. J. (1980).
		A family of embedded Runge-Kutta formulae.
		Journal of computational and applied mathematics, 6(1), 19-26.

		Hairer, E., Nørsett, S. P., & Wanner, G. (1993).
		Solving Ordinary Differential Equations I: Nonstiff Problems,
		second edition.
		Springer-Verlag, Berlin.
	\endverbatim

See also
	tnbLib::RKF45
	tnbLib::RKCK45

SourceFiles
	RKDP45.C

\*---------------------------------------------------------------------------*/

#include <ODESolver.hxx>
#include <adaptiveSolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class RKDP45 Declaration
	\*---------------------------------------------------------------------------*/

	class RKDP45
		:
		public ODESolver,
		public adaptiveSolver
	{
		// Private Data

			//- RKDP Constants
		static FoamODE_EXPORT const scalar
			c2, c3, c4, c5,
			a21, a31, a32, a41, a42, a43, a51, a52, a53, a54,
			a61, a62, a63, a64, a65,
			b1, b3, b4, b5, b6,
			e1, e3, e4, e5, e6, e7;

		// Temporary fields
		mutable scalarField yTemp_;
		mutable scalarField k2_;
		mutable scalarField k3_;
		mutable scalarField k4_;
		mutable scalarField k5_;
		mutable scalarField k6_;

		//- Error-estimate field
		mutable scalarField err_;


	public:

		//- Runtime type information
		//TypeName("RKDP45");
		static const char* typeName_() { return "RKDP45"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from ODESystem
		FoamODE_EXPORT RKDP45(const ODESystem& ode, const dictionary& dict);


		//- Destructor
		virtual ~RKDP45()
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

#endif // !_RKDP45_Header
