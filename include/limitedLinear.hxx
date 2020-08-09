#pragma once
#ifndef _limitedLinear_Header
#define _limitedLinear_Header

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
	tnbLib::limitedLinearLimiter

Description
	Class with limiter function which returns the limiter for the
	TVD limited linear differencing scheme based on r obtained from the
	LimiterFunc class.

	Used in conjunction with the template class LimitedScheme.

SourceFiles
	limitedLinear.C

\*---------------------------------------------------------------------------*/


#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class limitedLinearLimiter Declaration
	\*---------------------------------------------------------------------------*/

	template<class LimiterFunc>
	class limitedLinearLimiter
		:
		public LimiterFunc
	{
		scalar k_;
		scalar twoByk_;

	public:

		limitedLinearLimiter(Istream& is)
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

			// Avoid the /0 when k_ = 0
			twoByk_ = 2.0 / max(k_, small);
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
			scalar r = LimiterFunc::r
			(
				faceFlux, phiP, phiN, gradcP, gradcN, d
			);

			return max(min(twoByk_*r, 1), 0);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_limitedLinear_Header
