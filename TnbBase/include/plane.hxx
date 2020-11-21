#pragma once
#ifndef _plane_Header
#define _plane_Header

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
	tnbLib::plane

Description
	Geometric class that creates a 2D plane and can return the intersection
	point between a line and the plane.

SourceFiles
	plane.C

\*---------------------------------------------------------------------------*/

#include <point.hxx>
#include <scalarList.hxx>
#include <dictionary.hxx>
#include <line.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class plane;
	FoamBase_EXPORT bool operator==(const plane&, const plane&);
	FoamBase_EXPORT bool operator!=(const plane&, const plane&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const plane&);


	/*---------------------------------------------------------------------------*\
							   Class plane Declaration
	\*---------------------------------------------------------------------------*/

	class plane
	{
	public:

		//- Side of the plane
		enum side
		{
			NORMAL,
			FLIP
		};

		//- A direction and a reference point
		class ray
		{
			point refPoint_;
			vector dir_;

		public:

			ray(const point& refPoint, const vector& dir)
				:
				refPoint_(refPoint),
				dir_(dir)
			{}

			const point& refPoint() const
			{
				return refPoint_;
			}

			const vector& dir() const
			{
				return dir_;
			}
		};


	private:

		// Private Data

			//- Normal
		vector normal_;

		//- Reference point
		point point_;


		// Private Member Functions

			//- Calculates basePoint and normal vector given plane coefficients
		FoamBase_EXPORT void calcPntAndVec(const scalarList& C);

		//- Calculates basePoint and normal vector given three points
		//- Normal vector determined using right hand rule
		FoamBase_EXPORT void calcPntAndVec
		(
			const point& point1,
			const point& point2,
			const point& point3
		);


	public:

		// Constructors

			//- Construct from normal vector through the origin
		FoamBase_EXPORT explicit plane(const vector& normalVector);

		//- Construct from normal vector and point in plane
		FoamBase_EXPORT plane(const point& basePoint, const vector& normalVector);

		//- Construct from three points in plane
		FoamBase_EXPORT plane
		(
			const point& point1,
			const point& point2,
			const point& point3
		);

		//- Construct from coefficients for the
		//  plane equation: ax + by + cz + d = 0
		FoamBase_EXPORT explicit plane(const scalarList& C);

		//- Construct from dictionary
		FoamBase_EXPORT explicit plane(const dictionary& planeDict);

		//- Construct from Istream. Assumes the base + normal notation.
		FoamBase_EXPORT explicit plane(Istream& is);


		// Member Functions

			//- Return plane normal
		FoamBase_EXPORT const vector& normal() const;

		//- Return or return plane base point
		FoamBase_EXPORT const point& refPoint() const;

		//- Return coefficients for the
		//  plane equation: ax + by + cz + d = 0
		FoamBase_EXPORT FixedList<scalar, 4> planeCoeffs() const;

		//- Return a point on the plane
		FoamBase_EXPORT point aPoint() const;

		//- Return nearest point in the plane for the given point
		FoamBase_EXPORT point nearestPoint(const point& p) const;

		//- Return distance from the given point to the plane
		FoamBase_EXPORT scalar distance(const point& p) const;

		//- Return cut coefficient for plane and line defined by
		//  origin and direction
		FoamBase_EXPORT scalar normalIntersect(const point& pnt0, const vector& dir) const;

		//- Return cut coefficient for plane and ray
		scalar normalIntersect(const ray& r) const
		{
			return normalIntersect(r.refPoint(), r.dir());
		}

		//- Return the cutting point between the plane and
		// a line passing through the supplied points
		template<class Point, class PointRef>
		scalar lineIntersect(const line<Point, PointRef>& l) const
		{
			return normalIntersect(l.start(), l.vec());
		}

		//- Return the cutting line between this plane and another.
		//  Returned as direction vector and point line goes through.
		FoamBase_EXPORT ray planeIntersect(const plane&) const;

		//- Return the cutting point between this plane and two other planes
		FoamBase_EXPORT point planePlaneIntersect(const plane&, const plane&) const;

		//- Return the side of the plane that the point is on.
		//  If the point is on the plane, then returns NORMAL.
		FoamBase_EXPORT side sideOfPlane(const point& p) const;

		//- Mirror the supplied point in the plane. Return the mirrored point.
		FoamBase_EXPORT point mirror(const point& p) const;

		//- Write to dictionary
		FoamBase_EXPORT void writeDict(Ostream&) const;


		// friend Operators

		friend FoamBase_EXPORT bool operator==(const plane&, const plane&);
		friend FoamBase_EXPORT bool operator!=(const plane&, const plane&);


		// IOstream Operators

			//- Write plane properties
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const plane&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_plane_Header
