#pragma once
#ifndef _biLinearFitPolynomial_Header
#define _biLinearFitPolynomial_Header

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
	tnbLib::biLinearFitPolynomial

Description
	BiLinear polynomial for interpolation fitting.

	Can be used with the CentredFit scheme to create a biLinear surface
	interpolation scheme

\*---------------------------------------------------------------------------*/

#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class biLinearFitPolynomial Declaration
	\*---------------------------------------------------------------------------*/

	class biLinearFitPolynomial
	{
	public:

		// Member Functions

		static label nTerms(const direction dim)
		{
			return
				(
					dim == 1 ? 2 :
					dim == 2 ? 4 :
					dim == 3 ? 6 : 0
					);
		}

		static void addCoeffs
		(
			scalar* coeffs,
			const vector& d,
			const scalar weight,
			const direction dim
		)
		{
			label curIdx = 0;

			coeffs[curIdx++] = weight;
			coeffs[curIdx++] = weight * d.x();

			if (dim >= 2)
			{
				coeffs[curIdx++] = weight * d.y();
				coeffs[curIdx++] = weight * d.x()*d.y();
			}
			if (dim == 3)
			{
				coeffs[curIdx++] = weight * d.z();
				coeffs[curIdx++] = weight * d.x()*d.z();
			}
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_biLinearFitPolynomial_Header
