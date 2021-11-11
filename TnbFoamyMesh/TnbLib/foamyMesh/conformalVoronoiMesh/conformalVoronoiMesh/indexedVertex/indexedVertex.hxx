#pragma once
#ifndef _indexedVertex_Header
#define _indexedVertex_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
This file is part of OpenFOAM.

OpenFOAM is free software : you can redistribute itand /or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with OpenFOAM.If not, see < http://www.gnu.org/licenses/>.

Class
CGAL::indexedVertex

Description
An indexed form of CGAL::Triangulation_vertex_base_3<K> used to keep
track of the Delaunay vertices in the tessellation.

SourceFiles
indexedVertexI.H
indexedVertex.C

\* -------------------------------------------------------------------------- - */

#include <Base_Module.hxx>

#include <CGAL/Triangulation_3.h>

#include <CGALTriangulation3DKernel.hxx>
#include <tensor.hxx>
#include <triad.hxx>
#include <InfoProxy.hxx>
#include <point.hxx>
#include <indexedVertexEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace CGAL
{
    template<class Gt, class Vb> class indexedVertex;
}

namespace tnbLib
{

    class Ostream;
    class Istream;

    template<class Gt, class Vb> Ostream& operator<<
        (
            Ostream&,
            const tnbLib::InfoProxy<CGAL::indexedVertex<Gt, Vb>>&
            );

    template<class Gt, class Vb> Ostream& operator<<
        (
            Ostream&,
            const CGAL::indexedVertex<Gt, Vb>&
            );

    template<class Gt, class Vb> Istream& operator>>
        (
            Istream&,
            CGAL::indexedVertex<Gt, Vb>&
            );

    inline Istream& operator>>
        (
            Istream& is,
            CGAL::Point_3<baseK>& p
            );

    inline Ostream& operator<<
        (
            Ostream& os,
            const CGAL::Point_3<baseK>& p
            );

} // End namespace tnbLib


namespace CGAL
{

    /*---------------------------------------------------------------------------*\
                           Class indexedVertex Declaration
    \*---------------------------------------------------------------------------*/

    template<class Gt, class Vb = CGAL::Triangulation_vertex_base_3<Gt>>
    class indexedVertex
        :
        public tnbLib::indexedVertexEnum,
        public Vb
    {
        // Private Data

            //- Type of pair-point
        vertexType type_;

        //- The index for this Delaunay vertex.  For referred vertices, the
        //  index is negative for vertices that are the outer (slave) of point
        //  pairs
        tnbLib::label index_;

        //- Number of the processor that owns this vertex
        int processor_;

        //- Required alignment of the dual cell of this vertex
        tnbLib::tensor alignment_;

        //- Target size of the dual cell of this vertex
        tnbLib::scalar targetCellSize_;

        //- Specify whether the vertex is fixed or movable.
        bool vertexFixed_;


    public:

        typedef typename Vb::Triangulation_data_structure   Tds;
        typedef typename Vb::Point                          Point;
        typedef typename Tds::Vertex_handle                 Vertex_handle;
        typedef typename Tds::Cell_handle                   Cell_handle;

        template<class TDS2>
        struct Rebind_TDS
        {
            typedef typename Vb::template Rebind_TDS<TDS2>::Other   Vb2;
            typedef indexedVertex<Gt, Vb2>                           Other;
        };

        // Constructors

        inline indexedVertex();

        inline indexedVertex(const Point& p);

        inline indexedVertex(const Point& p, vertexType type);

        inline indexedVertex(const tnbLib::point& p, vertexType type);

        inline indexedVertex
        (
            const Point& p,
            tnbLib::label index,
            vertexType type,
            int processor
        );

        inline indexedVertex
        (
            const tnbLib::point& p,
            tnbLib::label index,
            vertexType type,
            int processor
        );

        inline indexedVertex(const Point& p, Cell_handle f);

        inline indexedVertex(Cell_handle f);

        indexedVertex(const indexedVertex& p) = default;


        // Member Functions

        inline tnbLib::label& index();

        inline tnbLib::label index() const;

        inline vertexType& type();

        inline vertexType type() const;

        inline tnbLib::tensor& alignment();

        inline const tnbLib::tensor& alignment() const;

        inline tnbLib::scalar& targetCellSize();

        inline tnbLib::scalar targetCellSize() const;

        //- Is point a far-point
        inline bool farPoint() const;

        //- Is point internal, i.e. not on boundary
        inline bool internalPoint() const;

        //- Is this a referred vertex
        inline bool referred() const;

        //- Is this a "real" point on this processor, i.e. is internal or part
        //  of the boundary description, and not a "far" or "referred" point
        inline bool real() const;

        // For referred vertices, what is the original processor index
        inline int procIndex() const;

        // For referred vertices, set the original processor index
        inline int& procIndex();

        //- Set the point to be internal
        inline void setInternal();

        //- Is point internal and near the boundary
        inline bool nearBoundary() const;

        //- Set the point to be near the boundary
        inline void setNearBoundary();

        //- Is point internal and near a proc boundary
        inline bool nearProcBoundary() const;

        //- Set the point to be near a proc boundary
        inline void setNearProcBoundary();

        //- Either master or slave of pointPair.
        inline bool boundaryPoint() const;

        //- Either original internal point or master of pointPair.
        inline bool internalOrBoundaryPoint() const;

        //- Is point near the boundary or part of the boundary definition
        inline bool nearOrOnBoundary() const;

        //- Part of a feature point
        inline bool featurePoint() const;

        //- Part of a feature edge
        inline bool featureEdgePoint() const;

        //- Part of a surface point pair
        inline bool surfacePoint() const;

        inline bool internalBoundaryPoint() const;
        inline bool internalBaffleSurfacePoint() const;
        inline bool internalBaffleEdgePoint() const;

        inline bool externalBoundaryPoint() const;
        inline bool externalBaffleSurfacePoint() const;
        inline bool externalBaffleEdgePoint() const;

        inline bool constrained() const;

        //- Is the vertex fixed or movable
        inline bool fixed() const;

        //- Fix the vertex so that it can't be moved
        inline bool& fixed();

        inline void operator=(const indexedVertex& rhs)
        {
            Vb::operator=(rhs);

            this->type_ = rhs.type();
            this->index_ = rhs.index();
            this->processor_ = rhs.procIndex();
            this->alignment_ = rhs.alignment();
            this->targetCellSize_ = rhs.targetCellSize();
            this->vertexFixed_ = rhs.fixed();
        }

        inline bool operator==(const indexedVertex& rhs) const
        {
            return
                (
                    // this->point() == rhs.point()
                    this->type_ == rhs.type()
                    && this->index_ == rhs.index()
                    && this->processor_ == rhs.procIndex()
                    && this->vertexFixed_ == rhs.fixed()
                    );
        }

        inline bool operator!=(const indexedVertex& rhs) const
        {
            return !(*this == rhs);
        }


        // Info

            //- Return info proxy.
            //  Used to print indexedVertex information to a stream
        tnbLib::InfoProxy<indexedVertex<Gt, Vb>> info() const
        {
            return *this;
        }

        friend tnbLib::Ostream& tnbLib::operator<< <Gt, Vb>
            (
                tnbLib::Ostream&,
                const tnbLib::InfoProxy<indexedVertex<Gt, Vb>>&
                );

        friend tnbLib::Ostream& tnbLib::operator<< <Gt, Vb>
            (
                tnbLib::Ostream&,
                const indexedVertex<Gt, Vb>&
                );

        friend tnbLib::Istream& tnbLib::operator>> <Gt, Vb>
            (
                tnbLib::Istream&,
                indexedVertex<Gt, Vb>&
                );
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace CGAL

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

#ifdef CGAL_INEXACT
namespace tnbLib
{
    // For inexact representations where the storage type is a double, the data
    // is contiguous. This may not be true for exact number types.
    template<>
    inline bool contiguous
        <
        CGAL::indexedVertex
        <
        K,
        CGAL::Triangulation_vertex_base_3<K>
        >
        >()
    {
        return true;
    }


    template<>
    inline bool contiguous<CGAL::Triangulation_vertex_base_3<K>::Point>()
    {
        return true;
    }

} // End namespace tnbLib
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <indexedVertexI.hxx>

//#ifdef NoRepository
//#include <indexedVertex.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_indexedVertex_Header

