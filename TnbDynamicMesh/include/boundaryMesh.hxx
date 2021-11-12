#pragma once
#ifndef _boundaryMesh_Header
#define _boundaryMesh_Header

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
	tnbLib::boundaryMesh

Description
	Addressing for all faces on surface of mesh. Can either be read
	from polyMesh or from triSurface. Used for repatching existing meshes.

SourceFiles
	boundaryMesh.C

\*---------------------------------------------------------------------------*/

#include <bMesh.hxx>

#include <boundaryPatch.hxx>
#include <PrimitivePatchTemplate.hxx>
#include <PtrList.hxx>
#include <polyPatchList.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class Time;
    class polyMesh;
    class primitiveMesh;

    /*---------------------------------------------------------------------------*\
                               Class boundaryMesh Declaration
    \*---------------------------------------------------------------------------*/

    class boundaryMesh
    {
        // Static data

            //- Normal along which to divide faces into categories
            //  (used in getNearest)
        static const vector splitNormal_;

        //- Distance to face tolerance for getNearest. Triangles are considered
        //  near if they are nearer than distanceTol_*typDim where typDim is
        //  the largest distance from face centre to one of its vertices.
        static const scalar distanceTol_;


        // Private Data

            //- All boundary mesh data. Reconstructed every time faces are repatched
        bMesh* meshPtr_;

        //- Patches. Reconstructed every time faces are repatched.
        PtrList<boundaryPatch> patches_;

        //- For every face in mesh() gives corresponding polyMesh face
        // (not sensible if mesh read from triSurface)
        labelList meshFace_;


        //
        // Edge handling
        //

        //- Points referenced by feature edges.
        pointField featurePoints_;

        //- Feature edges. Indices into featurePoints.
        edgeList featureEdges_;

        //- From feature edge to mesh edge.
        labelList featureToEdge_;

        //- From mesh edges to featureEdges_;
        labelList edgeToFeature_;

        //- Feature 'segments'. Collections of connected featureEdges.
        //  Indices into featureEdges_.
        labelListList featureSegments_;

        //- Additional edges (indices of mesh edges)
        labelList extraEdges_;


        // Private Member Functions

            //- Number of connected feature edges.
        FoamDynamicMesh_EXPORT label nFeatureEdges(label pointi) const;

        //- Step to next feature edge
        FoamDynamicMesh_EXPORT label nextFeatureEdge(const label edgeI, const label vertI) const;

        //- Return connected list of feature edges.
        FoamDynamicMesh_EXPORT labelList collectSegment
        (
            const boolList& isFeaturePoint,
            const label startEdgeI,
            boolList& featVisited
        ) const;

        //- Do point-edge walk to determine nearest (to edgeI). Stops if
        //  distance >= maxDistance. Used to determine edges close to seed
        //  point.
        FoamDynamicMesh_EXPORT  void markEdges
        (
            const label maxDistance,
            const label edgeI,
            const label distance,
            labelList& minDistance,
            DynamicList<label>& visited
        ) const;

        //- Get index of polypatch by name
        FoamDynamicMesh_EXPORT label findPatchID(const polyPatchList&, const word&) const;

        //- Get index of patch for face
        FoamDynamicMesh_EXPORT label whichPatch(const polyPatchList&, const label) const;

        //- Gets labels of changed faces and propagates them to the edges.
        //  Returns labels of edges changed. Fills edgeRegion of visited edges
        //  with current region.
        FoamDynamicMesh_EXPORT labelList faceToEdge
        (
            const boolList& regionEdge,
            const label region,
            const labelList& changedFaces,
            labelList& edgeRegion
        ) const;

        //- Reverse of faceToEdge: gets edges and returns faces
        FoamDynamicMesh_EXPORT labelList edgeToFace
        (
            const label region,
            const labelList& changedEdges,
            labelList& faceRegion
        ) const;

        //- Finds area, starting at facei, delimited by borderEdge. Marks all
        //  faces thus visited with currentZone.
        FoamDynamicMesh_EXPORT void markZone
        (
            const boolList& borderEdge,
            label facei,
            label currentZone,
            labelList& faceZone
        ) const;


    public:

        //- Runtime type information
        /*ClassName("boundaryMesh");*/
        static const char* typeName_() { return "boundaryMesh"; }
        static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
        static FoamDynamicMesh_EXPORT int debug;


        // Constructors

            //- Construct null
        FoamDynamicMesh_EXPORT boundaryMesh();

        //- Disallow default bitwise copy construction
        boundaryMesh(const boundaryMesh&) = delete;


        //- Destructor
        FoamDynamicMesh_EXPORT ~boundaryMesh();

        FoamDynamicMesh_EXPORT void clearOut();


        // Member Functions

            // Access

        const bMesh& mesh() const
        {
            if (!meshPtr_)
            {
                FatalErrorInFunction
                    << "No mesh available. Probably mesh not yet"
                    << " read." << abort(FatalError);
            }
            return *meshPtr_;
        }

        const PtrList<boundaryPatch>& patches() const
        {
            return patches_;
        }


        //- Label of original face in polyMesh (before patchify(...))
        const labelList& meshFace() const
        {
            return meshFace_;
        }

        //- Feature points.
        const pointField& featurePoints() const
        {
            return featurePoints_;
        }

        //- Feature edges. Indices into featurePoints.
        const edgeList& featureEdges() const
        {
            return featureEdges_;
        }

        //- From index into featureEdge to index into meshedges,
        const labelList& featureToEdge() const
        {
            return featureToEdge_;
        }

        //- From edge into featureEdges
        const labelList& edgeToFeature() const
        {
            return edgeToFeature_;
        }

        //- Lists of connected featureEdges. Indices into featureEdges.
        const labelListList& featureSegments() const
        {
            return featureSegments_;
        }

        //- Indices into edges of additional edges.
        const labelList& extraEdges() const
        {
            return extraEdges_;
        }


        // Edit

            //- Read from boundaryMesh of polyMesh.
        FoamDynamicMesh_EXPORT void read(const polyMesh&);

        //- Read from triSurface
        FoamDynamicMesh_EXPORT void readTriSurface(const fileName&);

        //- Write to file.
        FoamDynamicMesh_EXPORT void writeTriSurface(const fileName&) const;

        //- Get bMesh index of nearest face for every boundary face in
        //  pMesh. Gets passed initial search box. If not found
        //  returns -1 for the face.
        FoamDynamicMesh_EXPORT labelList getNearest
        (
            const primitiveMesh& pMesh,
            const vector& searchSpan
        ) const;

        //- Take over patches onto polyMesh from nearest face in *this
        //  (from call to getNearest). Insert as
        //      -new set of patches (newMesh.addPatches)
        //      -topoChanges to change faces.
        // nearest is list of nearest face in *this for every boundary
        // face. oldPatches is list of existing patches in mesh.
        // newMesh is the mesh to which the new patches are added.
        // (so has to be constructed without patches).
        FoamDynamicMesh_EXPORT void patchify
        (
            const labelList& nearest,
            const polyBoundaryMesh& oldPatches,
            polyMesh& newMesh
        ) const;

        // Patches

            //- Get index of patch face is in
        FoamDynamicMesh_EXPORT label whichPatch(const label facei) const;

        //- Get index of patch by name
        FoamDynamicMesh_EXPORT label findPatchID(const word& patchName) const;

        //- Get names of patches
        FoamDynamicMesh_EXPORT wordList patchNames() const;

        //- Add to back of patch list.
        FoamDynamicMesh_EXPORT void addPatch(const word& patchName);

        //- Delete from patch list.
        FoamDynamicMesh_EXPORT void deletePatch(const word& patchName);

        //- Change patch.
        FoamDynamicMesh_EXPORT void changePatchType(const word& patchName, const word& type);

        //- Recalculate face ordering and patches. Return old to new
        //  mapping.
        FoamDynamicMesh_EXPORT void changeFaces(const labelList& patchIDs, labelList& oldToNew);


        // Edges

            //- Set featureEdges, edgeToFeature, featureSegments according
            //  to angle of faces across edge
        FoamDynamicMesh_EXPORT void setFeatureEdges(const scalar minCos);

        //- Set extraEdges to edges 'near' to edgeI. Uses point-edge walk
        //  to determine 'near'.
        FoamDynamicMesh_EXPORT void setExtraEdges(const label edgeI);


        // Faces

            //- Simple triangulation of face subset. Returns number of triangles
            //  needed.
        FoamDynamicMesh_EXPORT label getNTris(const label facei) const;

        //- Simple triangulation of face subset. TotalNTris is total number
        //  of triangles, nTris is per face number of triangles.
        FoamDynamicMesh_EXPORT label getNTris
        (
            const label startFacei,
            const label nFaces,
            labelList& nTris
        ) const;

        //- Simple triangulation of face subset. TotalNTris is total number
        //  of triangles (from call to getNTris)
        //  triVerts is triangle vertices, three per triangle.
        FoamDynamicMesh_EXPORT void triangulate
        (
            const label startFacei,
            const label nFaces,
            const label totalNTris,
            labelList& triVerts
        ) const;

        //- Number of points used in face subset.
        FoamDynamicMesh_EXPORT label getNPoints(const label startFacei, const label nFaces) const;

        //- Same as triangulate but in local vertex numbering.
        //  (Map returned).
        FoamDynamicMesh_EXPORT void triangulateLocal
        (
            const label startFacei,
            const label nFaces,
            const label totalNTris,
            labelList& triVerts,
            labelList& localToGlobal
        ) const;

        // Other

            // Flood filling without crossing protected edges.
        FoamDynamicMesh_EXPORT void markFaces
        (
            const labelList& protectedEdges,
            const label facei,
            boolList& visited
        ) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const boundaryMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_boundaryMesh_Header
