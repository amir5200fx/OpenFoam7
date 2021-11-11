#pragma once
#ifndef _pointConversion_Header
#define _pointConversion_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
    tnbLib::pointConversion

Description
    Conversion functions between point (tnbLib::) and Point (CGAL::)

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>
#include <point.hxx>
#include <CGALTriangulation3DKernel.hxx>
#include <indexedVertex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef CGAL_INEXACT

	// Define Point to be contiguous for inexact (double storage) kernel
typedef const tnbLib::point& pointFromPoint;
typedef const CGAL::Triangulation_vertex_base_3<K>::Point& PointFrompoint;

#else

typedef tnbLib::point pointFromPoint;
typedef CGAL::Triangulation_vertex_base_3<K>::Point PointFrompoint;

#endif

namespace tnbLib
{

#ifdef CGAL_INEXACT

	template<class Point>
	inline pointFromPoint topoint(const Point& P)
	{
		return reinterpret_cast<pointFromPoint>(P);
	}

	inline PointFrompoint toPoint(const tnbLib::point& p)
	{
		return reinterpret_cast<PointFrompoint>(p);
	}

#else

	template<class Point>
	inline pointFromPoint topoint(const Point& P)
	{
		return tnbLib::point
		(
			CGAL::to_double(P.x()),
			CGAL::to_double(P.y()),
			CGAL::to_double(P.z())
		);
	}

	inline PointFrompoint toPoint(const tnbLib::point& p)
	{
		return PointFrompoint(p.x(), p.y(), p.z());
	}

#endif

	//- Specialisation for indexedVertex.
	template<>
	inline pointFromPoint topoint<CGAL::indexedVertex<K>>
		(
			const CGAL::indexedVertex<K>& P
			)
	{
		return topoint(P.point());
	}

	//- Specialisation for tnbLib::point. Used only as a dummy.
	template<>
	inline pointFromPoint topoint<tnbLib::point>
		(
			const tnbLib::point& P
			)
	{
		return P;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_pointConversion_Header
