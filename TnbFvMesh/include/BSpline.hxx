#pragma once
#ifndef _BSpline_Header
#define _BSpline_Header

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
	tnbLib::BSpline

Description
	An implementation of B-splines.

	In this implementation, the end tangents are created automatically
	by reflection.

	In matrix form, the \e local interpolation on the interval t=[0..1] is
	described as follows:
	\verbatim
	P(t) = 1/6 * [ t^3 t^2 t 1 ] * [ -1  3 -3  1 ] * [ P-1 ]
								   [  3 -6  3  0 ]   [ P0 ]
								   [ -3  0  3  0 ]   [ P1 ]
								   [  1  4  1  0 ]   [ P2 ]
	\endverbatim

	Where P-1 and P2 represent the neighbouring points or the extrapolated
	end points. Simple reflection is used to automatically create the end
	points.

	The spline is discretized based on the chord length of the individual
	segments. In rare cases (sections with very high curvatures), the
	resulting distribution may be sub-optimal.

	A future implementation could also handle closed splines.

See also
	CatmullRomSpline

SourceFiles
	BSpline.C

\*---------------------------------------------------------------------------*/

#include <polyLine.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class BSpline Declaration
	\*---------------------------------------------------------------------------*/

	class BSpline
		:
		public polyLine
	{
	public:

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT BSpline
		(
			const pointField& knots,
			const bool notImplementedClosed = false
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT BSpline(const BSpline&) = delete;


		// Member Functions

			//- Return the point position corresponding to the curve parameter
			//  0 <= lambda <= 1
		FoamFvMesh_EXPORT point position(const scalar lambda) const;

		//- Return the point position corresponding to the local parameter
		//  0 <= lambda <= 1 on the given segment
		FoamFvMesh_EXPORT point position(const label segment, const scalar lambda) const;

		//- Return the length of the curve
		FoamFvMesh_EXPORT scalar length() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const BSpline&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_BSpline_Header
