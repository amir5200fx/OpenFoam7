#pragma once
#ifndef _meshCutAndRemove_Header
#define _meshCutAndRemove_Header

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
    tnbLib::meshCutAndRemove

Description
    like meshCutter but also removes non-anchor side of cell.

SourceFiles
    meshCutAndRemove.C

\*---------------------------------------------------------------------------*/

#include <edgeVertex.hxx>
#include <boolList.hxx>
#include <labelList.hxx>
#include <typeInfo.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class Time;
    class polyTopoChange;
    class cellCuts;
    class polyMesh;
    class face;
    class mapPolyMesh;

    /*---------------------------------------------------------------------------*\
                               Class meshCutAndRemove Declaration
    \*---------------------------------------------------------------------------*/

    class meshCutAndRemove
        :
        public edgeVertex
    {
        // Private Data

            //- Faces added in last setRefinement. Per split cell label of added
            //  face
        Map<label> addedFaces_;

        //- Points added in last setRefinement. Per split edge label of added
        //  point
        HashTable<label, edge, Hash<edge>> addedPoints_;


        // Private Static Functions

            // Returns -1 or index in elems1 of first shared element.
        static FoamDynamicMesh_EXPORT label firstCommon(const labelList& lst1, const labelList& lst2);

        //- Do the elements of edge appear in consecutive order in the list
        static FoamDynamicMesh_EXPORT bool isIn(const edge&, const labelList&);


        // Private Member Functions

            //- Returns -1 or the cell in cellLabels that is cut.
        FoamDynamicMesh_EXPORT label findCutCell(const cellCuts&, const labelList&) const;

        //- Returns first pointi in pointLabels that uses an internal
        //  face. Used to find point to inflate cell/face from (has to be
        //  connected to internal face)
        FoamDynamicMesh_EXPORT label findInternalFacePoint(const labelList& pointLabels) const;

        //- Find point on face that is part of original mesh and that is
        //  point connected to the patch
        FoamDynamicMesh_EXPORT label findPatchFacePoint(const face& f, const label patchi) const;

        //- Get new owner and neighbour of face. Checks anchor points to see if
        // need to get original or added cell.
        FoamDynamicMesh_EXPORT void faceCells
        (
            const cellCuts& cuts,
            const label exposedPatchi,
            const label facei,
            label& own,
            label& nei,
            label& patchID
        ) const;

        //- Get zone information for face.
        FoamDynamicMesh_EXPORT void getZoneInfo
        (
            const label facei,
            label& zoneID,
            bool& zoneFlip
        ) const;

        //- Adds a face from point. Flips face if owner>neighbour
        FoamDynamicMesh_EXPORT void addFace
        (
            polyTopoChange& meshMod,
            const label facei,
            const label masterPointi,
            const face& newFace,
            const label owner,
            const label neighbour,
            const label patchID
        );

        //- Modifies existing facei for either new owner/neighbour or
        //  new face points. Checks if anything changed and flips face
        //  if owner>neighbour
        FoamDynamicMesh_EXPORT void modFace
        (
            polyTopoChange& meshMod,
            const label facei,
            const face& newFace,
            const label owner,
            const label neighbour,
            const label patchID
        );

        // Copies face starting from startFp. Jumps cuts. Marks visited
        // vertices in visited.
        FoamDynamicMesh_EXPORT void copyFace
        (
            const face& f,
            const label startFp,
            const label endFp,
            face& newFace
        ) const;

        //- Split face along cut into two faces. Faces are in same point
        //  order as original face (i.e. maintain normal direction)
        FoamDynamicMesh_EXPORT void splitFace
        (
            const face& f,
            const label v0,
            const label v1,

            face& f0,
            face& f1
        ) const;

        //- Add cuts of edges to face
        FoamDynamicMesh_EXPORT face addEdgeCutsToFace(const label facei) const;

        //- Convert loop of cuts into face.
        FoamDynamicMesh_EXPORT face loopToFace
        (
            const label celli,
            const labelList& loop
        ) const;


    public:

        //- Runtime type information
        /*ClassName("meshCutAndRemove");*/
        static const char* typeName_() { return "meshCutAndRemove"; }
        static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
        static FoamDynamicMesh_EXPORT int debug;


        // Constructors

            //- Construct from mesh
        FoamDynamicMesh_EXPORT meshCutAndRemove(const polyMesh& mesh);

        //- Disallow default bitwise copy construction
        meshCutAndRemove(const meshCutAndRemove&) = delete;


        // Member Functions

            // Edit

                //- Do actual cutting with cut description. Inserts mesh changes
                //  into meshMod.
                //  cuts: all loops and topological information
                //  cutPatch: for every cell that has loop the patch number
                //  exposedPatch: patch for other exposed faces
        FoamDynamicMesh_EXPORT void setRefinement
        (
            const label exposedPatchi,
            const cellCuts& cuts,
            const labelList& cutPatch,
            polyTopoChange& meshMod
        );

        //- Force recalculation of locally stored data on topological change
        FoamDynamicMesh_EXPORT void updateMesh(const mapPolyMesh&);


        // Access

            //- Faces added. Per split cell label of added face
        const Map<label>& addedFaces() const
        {
            return addedFaces_;
        }

        //- Points added. Per split edge label of added point.
        //  (note: fairly useless across topology changes since one of the
        //  points of the edge will probably disappear)
        const HashTable<label, edge, Hash<edge>>& addedPoints() const
        {
            return addedPoints_;
        }


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const meshCutAndRemove&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshCutAndRemove_Header
