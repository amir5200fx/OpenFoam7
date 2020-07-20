#pragma once
#ifndef _filteredLinear3_Header
#define _filteredLinear3_Header

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
	tnbLib::filteredLinear3Limiter

Description
	Class to generate weighting factors for the filteredLinear
	differencing scheme.

	The aim is to remove high-frequency modes with "staggering"
	characteristics by comparing the face gradient with both neighbouring
	cell gradients and introduce small amounts of upwind in order to damp
	these modes.

	Used in conjunction with the template class LimitedScheme.

SourceFiles
	filteredLinear3.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class filteredLinear3Limiter Declaration
	\*---------------------------------------------------------------------------*/

	template<class LimiterFunc>
	class filteredLinear3Limiter
		:
		public LimiterFunc
	{
		// Private Data

			// Scaling corefficient for the gradient ratio,
			// 0 = linear
			// 1 = fully limited
		scalar k_;

	public:

		filteredLinear3Limiter(Istream& is)
			:
			k_(readScalar(is))
		{
			if (k_ < 0 || k_ > 1)
			{
				FatalIOErrorInFunction(is)
					<< "coefficient = " << k_
					<< " should be >= 0 and <= 1"
					<< exit(FatalIOError);
			}
		}

		scalar limiter
		(
			const scalar cdWeight,
			const scalar faceFlux,
			const typename LimiterFunc::phiType& phiP,
			const typename LimiterFunc::phiType& phiN,
			const typename LimiterFunc::gradPhiType& gradcP,
			const typename LimiterFunc::gradPhiType& gradcN,
			const vector& d
		) const
		{
			// Difference across face
			scalar df = phiN - phiP;

			// Twice the differences across face-neighbour cells
			scalar dP = 2 * (d & gradcP);
			scalar dN = 2 * (d & gradcN);

			// Calculate the limiter
			scalar limiter = 1 - k_ * (dN - df)*(dP - df) / max(sqr(dN + dP), small);

			// Limit the limiter between linear and upwind
			return max(min(limiter, 1), 0);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_filteredLinear3_Header
