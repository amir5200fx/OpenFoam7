#pragma once
#ifndef _minmodGradientLimiter_Header
#define _minmodGradientLimiter_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::fv::gradientLimiters::minmod

Description
	Minmod gradient limiter

	This is the default gradient limiter which clips the gradient to remove cell
	to face extrapolation unboundedness.  It corresponds to the original
	cellLimitedGrad implementation before the addition of run-time select-able
	limiter functions.

	Example:
	\verbatim
	gradSchemes
	{
		default Gauss linear;
		limited cellLimited Gauss linear 1;
	}
	\endverbatim

See also
	tnbLib::fv::cellLimitedGrad

\*---------------------------------------------------------------------------*/

#include <Istream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace fv
	{

		namespace gradientLimiters
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			class minmod
			{

			public:

				// Constructors

				minmod(Istream&)
				{}


				// Member Functions

				inline scalar limiter(const scalar r) const
				{
					return min(r, 1);
				}
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace gradientLimiters

	} // End namespace fv

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_minmodGradientLimiter_Header
