#pragma once
#ifndef _seulex_Header
#define _seulex_Header

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
	tnbLib::seulex

Description
	An extrapolation-algorithm, based on the linearly implicit Euler method
	with step size control and order selection.

	Reference:
	\verbatim
		Hairer, E., Nørsett, S. P., & Wanner, G. (1996).
		Solving Ordinary Differential Equations II:
		Stiff and Differential-Algebraic Problems, second edition",
		Springer-Verlag, Berlin.
	\endverbatim

SourceFiles
	seulex.C

\*---------------------------------------------------------------------------*/

#include <ODESolver.hxx>
#include <scalarMatrices.hxx>
#include <labelField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class seulex Declaration
	\*---------------------------------------------------------------------------*/

	class seulex
		:
		public ODESolver
	{
		// Private Data

			// Static constants

		static const label kMaxx_ = 12;
		static const label iMaxx_ = kMaxx_ + 1;

		static FoamODE_EXPORT const scalar
			stepFactor1_, stepFactor2_, stepFactor3_,
			stepFactor4_, stepFactor5_,
			kFactor1_, kFactor2_;

		// Evaluated constants

		scalar jacRedo_;
		labelField nSeq_;
		scalarField cpu_;
		scalarSquareMatrix coeff_;

		// Temporary storage
		// held to avoid dynamic memory allocation between calls
		// and to transfer internal values between functions

		mutable scalar theta_;
		mutable label kTarg_;
		mutable scalarRectangularMatrix table_;

		mutable scalarField dfdx_;
		mutable scalarSquareMatrix dfdy_;
		mutable scalarSquareMatrix a_;
		mutable labelList pivotIndices_;

		// Fields space for "solve" function
		mutable scalarField dxOpt_, temp_;
		mutable scalarField y0_, ySequence_, scale_;

		// Fields used in "seul" function
		mutable scalarField dy_, yTemp_, dydx_;


		// Private Member Functions

			//- Computes the j-th line of the extrapolation table
		FoamODE_EXPORT bool seul
		(
			const scalar x0,
			const scalarField& y0,
			const scalar dxTot,
			const label k,
			scalarField& y,
			const scalarField& scale
		) const;

		//- Polynomial extrpolation
		FoamODE_EXPORT void extrapolate
		(
			const label k,
			scalarRectangularMatrix& table,
			scalarField& y
		) const;


	public:

		//- Runtime type information
		//TypeName("seulex");
		static const char* typeName_() { return "seulex"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from ODESystem
		FoamODE_EXPORT seulex(const ODESystem& ode, const dictionary& dict);


		//- Destructor
		virtual ~seulex()
		{}


		// Member Functions

			//- Resize the ODE solver
		FoamODE_EXPORT virtual bool resize();

		//- Solve the ODE system and the update the state
		FoamODE_EXPORT virtual void solve
		(
			scalar& x,
			scalarField& y,
			stepState& step
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_seulex_Header
