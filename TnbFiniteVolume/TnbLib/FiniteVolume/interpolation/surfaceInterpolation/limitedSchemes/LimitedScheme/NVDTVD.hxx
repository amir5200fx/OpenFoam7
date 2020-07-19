#pragma once
#ifndef _NVDTVD_Header
#define _NVDTVD_Header

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
	tnbLib::NVDTVD

Description
	tnbLib::NVDTVD

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <vector.hxx>  // added by amir

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class LimitedScheme Declaration
	\*---------------------------------------------------------------------------*/

	class NVDTVD
	{

	public:

		typedef scalar phiType;
		typedef vector gradPhiType;


		// Null Constructor

		NVDTVD()
		{}


		// Member Functions

		scalar phict
		(
			const scalar faceFlux,
			const scalar phiP,
			const scalar phiN,
			const vector& gradcP,
			const vector& gradcN,
			const vector& d
		) const
		{
			scalar gradf = phiN - phiP;

			scalar gradcf;

			if (faceFlux > 0)
			{
				gradcf = d & gradcP;
			}
			else
			{
				gradcf = d & gradcN;
			}

			if (mag(gradf) >= 1000 * mag(gradcf))
			{
				return 1 - 0.5 * 1000 * sign(gradcf)*sign(gradf);
			}
			else
			{
				return 1 - 0.5*gradf / gradcf;
			}
		}


		scalar r
		(
			const scalar faceFlux,
			const scalar phiP,
			const scalar phiN,
			const vector& gradcP,
			const vector& gradcN,
			const vector& d
		) const
		{
			scalar gradf = phiN - phiP;

			scalar gradcf;

			if (faceFlux > 0)
			{
				gradcf = d & gradcP;
			}
			else
			{
				gradcf = d & gradcN;
			}

			if (mag(gradcf) >= 1000 * mag(gradf))
			{
				return 2 * 1000 * sign(gradcf)*sign(gradf) - 1;
			}
			else
			{
				return 2 * (gradcf / gradf) - 1;
			}
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NVDTVD_Header
