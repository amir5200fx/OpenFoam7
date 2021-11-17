#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::label tnbLib::CV2D::insertPoint
(
    const point2D& p,
    const label type
)
{
    unsigned int nVert = number_of_vertices();

    return insertPoint(toPoint(p), nVert, type);
}


inline tnbLib::label tnbLib::CV2D::insertPoint
(
    const point2D& p,
    const label index,
    const label type
)
{
    return insertPoint(toPoint(p), index, type);
}


inline tnbLib::label tnbLib::CV2D::insertPoint
(
    const Point& p,
    const label index,
    const label type
)
{
    unsigned int nVert = number_of_vertices();

    Vertex_handle vh = insert(p);

    if (nVert == number_of_vertices())
    {
        WarningInFunction
            << "Failed to insert point " << toPoint2D(p) << endl;
    }
    else
    {
        vh->index() = index;
        vh->type() = type;
    }

    return vh->index();
}


inline bool tnbLib::CV2D::insertMirrorPoint
(
    const point2D& nearSurfPt,
    const point2D& surfPt
)
{
    point2D mirrorPoint(2 * surfPt - nearSurfPt);

    if (qSurf_.outside(toPoint3D(mirrorPoint)))
    {
        insertPoint(mirrorPoint, Vb::MIRROR_POINT);
        return true;
    }
    else
    {
        return false;
    }
}


inline void tnbLib::CV2D::insertPointPair
(
    const scalar ppDist,
    const point2D& surfPt,
    const vector2D& n
)
{
    vector2D ppDistn = ppDist * n;

    label master = insertPoint
    (
        surfPt - ppDistn,
        number_of_vertices() + 1
    );

    insertPoint(surfPt + ppDistn, master);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::cv2DControls& tnbLib::CV2D::meshControls() const
{
    return controls_;
}


inline const tnbLib::point2D& tnbLib::CV2D::toPoint2D(const point& p) const
{
    return reinterpret_cast<const point2D&>(p);
}


inline const tnbLib::point2DField tnbLib::CV2D::toPoint2D(const pointField& p) const
{
    point2DField temp(p.size());
    forAll(temp, pointi)
    {
        temp[pointi] = point2D(p[pointi].x(), p[pointi].y());
    }
    return temp;
}


inline tnbLib::point tnbLib::CV2D::toPoint3D(const point2D& p) const
{
    return point(p.x(), p.y(), z_);
}


#ifdef CGAL_INEXACT

inline tnbLib::CV2D::point2DFromPoint tnbLib::CV2D::toPoint2D(const Point& P) const
{
    return reinterpret_cast<point2DFromPoint>(P);
}


inline tnbLib::CV2D::PointFromPoint2D tnbLib::CV2D::toPoint(const point2D& p) const
{
    return reinterpret_cast<PointFromPoint2D>(p);
}

#else

inline tnbLib::CV2D::point2DFromPoint tnbLib::CV2D::toPoint2D(const Point& P) const
{
    return point2D(CGAL::to_double(P.x()), CGAL::to_double(P.y()));
}


inline tnbLib::CV2D::PointFromPoint2D tnbLib::CV2D::toPoint(const point2D& p) const
{
    return Point(p.x(), p.y());
}

#endif


inline tnbLib::point tnbLib::CV2D::toPoint3D(const Point& P) const
{
    return point(CGAL::to_double(P.x()), CGAL::to_double(P.y()), z_);
}


inline void tnbLib::CV2D::movePoint(const Vertex_handle& vh, const Point& P)
{
    int i = vh->index();
    int t = vh->type();

    remove(vh);

    Vertex_handle newVh = insert(P);

    newVh->index() = i;
    newVh->type() = t;

    // label i = vh->index();
    // move(vh, P);
    // vh->index() = i;

     // vh->set_point(P);
     // fast_restore_Delaunay(vh);
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

inline bool tnbLib::boundaryTriangle(const CV2D::Face_handle fc)
{
    return boundaryTriangle
    (
        *fc->vertex(0),
        *fc->vertex(1),
        *fc->vertex(2)
    );
}


inline bool tnbLib::outsideTriangle(const CV2D::Face_handle fc)
{
    return outsideTriangle
    (
        *fc->vertex(0),
        *fc->vertex(1),
        *fc->vertex(2)
    );
}


// ************************************************************************* //
