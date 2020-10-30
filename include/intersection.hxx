#pragma once
#ifndef _intersection_Header
#define _intersection_Header 

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
	tnbLib::intersection

Description
	tnbLib::intersection

SourceFiles
   intersection.C

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class intersection Declaration
	\*---------------------------------------------------------------------------*/

	class intersection
	{
		// Static data

			//- Relative tolerance for point in a plane.
			//  The tolerance is relative to the object size.
			//  Used to determine if a half-ray from a point in plane of triangle
			// intersects the triangle or not.
		static FoamBase_EXPORT scalar planarTol_;

	public:

		enum class direction
		{
			vector,
			contactSphere
		};

		enum class algorithm
		{
			fullRay,        // Intersecting with full ray
			halfRay,        // Intersecting with half ray
			visible         // Intersecting with the visible side
		};

		// Static Member Functions

			//- Direction names
		static FoamBase_EXPORT const NamedEnum<direction, 2> directionNames_;

		//- Projection algorithm names
		static FoamBase_EXPORT const NamedEnum<algorithm, 3> algorithmNames_;

		//- Return planar tolerance
		static scalar planarTol()
		{
			return planarTol_;
		}

		//- Set the planar tolerance, returning the previous value
		static scalar setPlanarTol(const scalar t)
		{
			if (t < -vSmall)
			{
				FatalErrorInFunction << abort(FatalError);
			}

			scalar oldTol = planarTol_;
			planarTol_ = t;

			return oldTol;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_intersection_Header
