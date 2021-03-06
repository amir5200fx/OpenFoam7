#pragma once
#ifndef _surfaceLocation_Header
#define _surfaceLocation_Header

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
	tnbLib::surfaceLocation

Description
	Contains information about location on a triSurface

	Access to data:
	  - pointIndexHit provides
		- location
		- bool: hit/miss
		- index (of triangle/point/edge)
	  - elementType() provides
		- what index above relates to. In triangle::proxType
	  - triangle() provides
		- last known triangle

SourceFiles
	surfaceLocation.C

\*---------------------------------------------------------------------------*/

#include <pointIndexHit.hxx>
#include <triPointRef.hxx>
#include <InfoProxy.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class triSurface;


	// Forward declaration of friend functions and operators

	class surfaceLocation;

	FoamFvMesh_EXPORT Istream& operator>>(Istream&, surfaceLocation&);
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfaceLocation&);
	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const InfoProxy<surfaceLocation>&);


	/*---------------------------------------------------------------------------*\
							   Class surfaceLocation Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceLocation
		:
		public pointIndexHit
	{
		// Private Data

		triPointRef::proxType elementType_;

		label triangle_;

	public:


		// Constructors

			//- Construct null
		surfaceLocation()
			:
			pointIndexHit(),
			elementType_(triPointRef::NONE),
			triangle_(-1)
		{}

		//- Construct from components
		surfaceLocation
		(
			const pointIndexHit& pih,
			const triPointRef::proxType elementType,
			const label triangle
		)
			:
			pointIndexHit(pih),
			elementType_(elementType),
			triangle_(triangle)
		{}

		//- Construct from Istream
		surfaceLocation(Istream& is)
			:
			pointIndexHit(is),
			elementType_(triPointRef::proxType(readLabel(is))),
			triangle_(readLabel(is))
		{}


		// Member Functions

		triPointRef::proxType& elementType()
		{
			return elementType_;
		}

		triPointRef::proxType elementType() const
		{
			return elementType_;
		}

		label& triangle()
		{
			return triangle_;
		}

		label triangle() const
		{
			return triangle_;
		}

		//- Normal. Approximate for points.
		FoamFvMesh_EXPORT vector normal(const triSurface& s) const;

		//- Return info proxy.
		//  Used to print token information to a stream
		InfoProxy<surfaceLocation> info() const
		{
			return *this;
		}

		//- Write info to os
		FoamFvMesh_EXPORT void write(Ostream& os, const triSurface& s) const;


		// IOstream Operators

		friend FoamFvMesh_EXPORT Istream& operator>>(Istream& is, surfaceLocation& sl);

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream& os, const surfaceLocation& sl);

		friend FoamFvMesh_EXPORT Ostream& operator<<
			(
				Ostream&,
				const InfoProxy<surfaceLocation>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceLocation_Header
