#pragma once
#ifndef _linearEqn_Header
#define _linearEqn_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	tnbLib::linearEqn

Description
	Linear equation of the form a*x + b = 0

SourceFiles
	linearEqnI.H

\*---------------------------------------------------------------------------*/

#include <Roots.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class linearEqn Declaration
	\*---------------------------------------------------------------------------*/

	class linearEqn
		:
		public VectorSpace<linearEqn, scalar, 2>
	{
	public:

		//- Coefficient indexing enumeration
		struct coefficient
		{
			enum { a, b };
		};


		// Constructors

			//- Construct null
		inline linearEqn();

		//- Construct initialized to zero
		inline linearEqn(const tnbLib::zero);

		//- Construct from components
		inline linearEqn(const scalar a, const scalar b);


		// Member Functions

			// Access

		inline scalar a() const;
		inline scalar b() const;

		inline scalar& a();
		inline scalar& b();

		//- Evaluate at x
		inline scalar value(const scalar x) const;

		//- Evaluate the derivative at x
		inline scalar derivative(const scalar x) const;

		//- Estimate the error of evaluation at x
		inline scalar error(const scalar x) const;

		//- Get the roots
		inline Roots<1> roots() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <linearEqnI.hxx>

#endif // !_linearEqn_Header
