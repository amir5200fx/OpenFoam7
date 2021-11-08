#pragma once
#ifndef _cellLooper_Header
#define _cellLooper_Header

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
    tnbLib::cellLooper

Description
    Abstract base class. Concrete implementations know how to cut a cell
    (i.e. determine a loop around the circumference).

    Loop around the cell is given as the vertices to be cut and edges to
    be cut (and a weight between 0 and 1 giving where the cut is to be
    made). Main routine is 'cut' which gets called for every cell and
    gets the current cut situation and expects to return a loop on the
    cell circumference.

    Calling function needs to determine whether cellLooper is compatible with
    existing set of cuts.

    Also contains various utility functions which implementations might want to
    use.

SourceFiles
    cellLooper.C

\*---------------------------------------------------------------------------*/

#include <edgeVertex.hxx>
#include <vector.hxx>
#include <boolList.hxx>
#include <scalarField.hxx>
#include <DynamicList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class polyMesh;
    class plane;

    /*---------------------------------------------------------------------------*\
                               Class cellLooper Declaration
    \*---------------------------------------------------------------------------*/

    class cellLooper
        :
        public edgeVertex
    {

    protected:

        // Protected Member Functions

            //- Get faces (on cell) connected to vertI which are not using edgeI
        FoamDynamicMesh_EXPORT labelList getVertFacesNonEdge
        (
            const label celli,
            const label edgeI,
            const label vertI
        ) const;

        //- Get first edge connected to vertI and on facei
        FoamDynamicMesh_EXPORT label getFirstVertEdge
        (
            const label facei,
            const label vertI
        ) const;

        //- Get edges (on cell) connected to vertI which are not on facei
        FoamDynamicMesh_EXPORT labelList getVertEdgesNonFace
        (
            const label celli,
            const label facei,
            const label vertI
        ) const;

        //- Return edge from cellEdges that is most perpendicular
        //  to refinement direction.
        FoamDynamicMesh_EXPORT label getMisAlignedEdge(const vector& refDir, const label celli) const;


    public:

        //- Runtime type information
        /*TypeName("cellLooper");*/
        static const char* typeName_() { return "cellLooper"; }
        static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
        static FoamDynamicMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Declare run-time constructor selection table

            // For the direct constructor
        declareRunTimeSelectionTable
        (
            autoPtr,
            cellLooper,
            word,
            (
                const polyMesh& mesh
                ),
            (mesh)
        );


        // Constructors

            //- Construct from components
        FoamDynamicMesh_EXPORT cellLooper(const polyMesh& mesh);

        //- Disallow default bitwise copy construction
        FoamDynamicMesh_EXPORT cellLooper(const cellLooper&) = delete;

        //- Clone
        autoPtr<cellLooper> clone() const
        {
            NotImplemented;
            return autoPtr<cellLooper>(nullptr);
        }


        // Selectors

            //- Return a reference to the selected cellLooper
        static FoamDynamicMesh_EXPORT autoPtr<cellLooper> New
        (
            const word& type,
            const polyMesh& mesh
        );


        //- Destructor
        FoamDynamicMesh_EXPORT virtual ~cellLooper();


        // Member Functions

            //- Create cut along circumference of celli. Gets current mesh cuts
            //  vertIsCut, edgeIsCut, edgeWeight).
            //  Cut along circumference is expressed as cellVertCut,
            //  cellEdgeToWeight. Returns true if successful. Still might not
            //  be compatible with existing cuts but this should be handled by
            //  caller).
        virtual bool cut
        (
            const vector& refDir,
            const label celli,
            const boolList& vertIsCut,
            const boolList& edgeIsCut,
            const scalarField& edgeWeight,

            labelList& loop,
            scalarField& loopWeights
        ) const = 0;

        //- Same but now also base point of cut provided (instead of always
        //  cell centre)
        virtual bool cut
        (
            const plane& cutPlane,
            const label celli,
            const boolList& vertIsCut,
            const boolList& edgeIsCut,
            const scalarField& edgeWeight,

            labelList& loop,
            scalarField& loopWeights
        ) const = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellLooper&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_cellLooper_Header
