#pragma once
#ifndef _zeroField_Header
#define _zeroField_Header

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
	tnbLib::zeroField

Description
	A class representing the concept of a field of 0 used to avoid unnecessary
	manipulations for objects which are known to be zero at compile-time.

	Used for example as the argument to a function in which certain terms are
	optional, see source terms in the MULES solvers.

\*---------------------------------------------------------------------------*/

#include <zero.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class zeroField Declaration
	\*---------------------------------------------------------------------------*/

	class zeroField
		:
		public zero
	{
	public:

		// Constructors

			//- Construct null
		zeroField()
		{}


		// Member Operators

		inline scalar operator[](const label) const;

		inline zeroField field() const;

		inline zeroField operator()() const;

		inline zeroField operator-() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <zeroFieldI.hxx>

#endif // !_zeroField_Header
