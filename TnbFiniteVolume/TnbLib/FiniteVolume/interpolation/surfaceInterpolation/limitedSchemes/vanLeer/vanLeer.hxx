#pragma once
#ifndef _vanLeer_Header
#define _vanLeer_Header

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
	tnbLib::vanLeerLimiter

Description
	Class with limiter function which returns the limiter for the
	vanLeer differencing scheme based on r obtained from the LimiterFunc
	class.

	Used in conjunction with the template class LimitedScheme.

SourceFiles
	vanLeer.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class vanLeerLimiter Declaration
	\*---------------------------------------------------------------------------*/

	template<class LimiterFunc>
	class vanLeerLimiter
		:
		public LimiterFunc
	{

	public:

		vanLeerLimiter(Istream&)
		{}

		scalar limiter
		(
			const scalar,
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

			return (r + mag(r)) / (1 + mag(r));
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_vanLeer_Header
