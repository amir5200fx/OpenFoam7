#pragma once
#include <polyMesh.hxx>
#include <meshTools.hxx>
#include <hexMatcher.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::directionInfo::directionInfo()
    :
    index_(-3),
    n_(Zero)
{}


inline tnbLib::directionInfo::directionInfo
(
    const label index,
    const vector& n
)
    :
    index_(index),
    n_(n)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::directionInfo::valid(TrackingData& td) const
{
    return index_ != -3;
}


template<class TrackingData>
inline bool tnbLib::directionInfo::sameGeometry
(
    const polyMesh&,
    const directionInfo& w2,
    const scalar tol,
    TrackingData& td
)
const
{
    return true;
}


template<class TrackingData>
inline void tnbLib::directionInfo::leaveDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::directionInfo::enterDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{
    if (index_ >= 0)
    {
        const face& f = patch[patchFacei];

        index_ = (f.size() - index_) % f.size();
    }
}


template<class TrackingData>
inline void tnbLib::directionInfo::transform
(
    const polyMesh&,
    const tensor& rotTensor,
    TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::directionInfo::updateCell
(
    const polyMesh& mesh,
    const label thisCelli,
    const label neighbourFacei,
    const directionInfo& neighbourInfo,
    const scalar,       // tol
    TrackingData& td
)
{
    if (index_ >= -2)
    {
        // Already determined.
        return false;
    }

    if (hexMatcher().isA(mesh, thisCelli))
    {
        const face& f = mesh.faces()[neighbourFacei];

        if (neighbourInfo.index() == -2)
        {
            // Geometric information from neighbour
            index_ = -2;
        }
        else if (neighbourInfo.index() == -1)
        {
            // Cut tangential to face. Take any edge connected to face
            // but not used in face.

            // Get first edge on face.
            label edgeI = mesh.faceEdges()[neighbourFacei][0];

            const edge& e = mesh.edges()[edgeI];

            // Find face connected to face through edgeI and on same cell.
            label facei =
                meshTools::otherFace
                (
                    mesh,
                    thisCelli,
                    neighbourFacei,
                    edgeI
                );

            // Find edge on facei which is connected to e.start() but not edgeI.
            index_ =
                meshTools::otherEdge
                (
                    mesh,
                    mesh.faceEdges()[facei],
                    edgeI,
                    e.start()
                );
        }
        else
        {
            // Index is a vertex on the face. Convert to mesh edge.

            // Get mesh edge between f[index_] and f[index_+1]
            label v0 = f[neighbourInfo.index()];
            label v1 = f[(neighbourInfo.index() + 1) % f.size()];

            index_ = findEdge(mesh, mesh.faceEdges()[neighbourFacei], v0, v1);
        }
    }
    else
    {
        // Not a hex so mark this as geometric.
        index_ = -2;
    }


    n_ = neighbourInfo.n();

    return true;
}


template<class TrackingData>
inline bool tnbLib::directionInfo::updateFace
(
    const polyMesh& mesh,
    const label thisFacei,
    const label neighbourCelli,
    const directionInfo& neighbourInfo,
    const scalar,   // tol
    TrackingData& td
)
{
    // Handle special cases first

    if (index_ >= -2)
    {
        // Already determined
        return false;
    }

    // Handle normal cases where topological or geometrical info comes from
    // neighbouring cell

    if (neighbourInfo.index() >= 0)
    {
        // Neighbour has topological direction (and hence is hex). Find cut
        // edge on face.
        index_ =
            edgeToFaceIndex
            (
                mesh,
                neighbourCelli,
                thisFacei,
                neighbourInfo.index()
            );
    }
    else
    {
        // Neighbour has geometric information. Use.
        index_ = -2;
    }


    n_ = neighbourInfo.n();

    return true;
}


template<class TrackingData>
inline bool tnbLib::directionInfo::updateFace
(
    const polyMesh& mesh,
    const label,    // thisFacei
    const directionInfo& neighbourInfo,
    const scalar,   // tol
    TrackingData& td
)
{
    if (index_ >= -2)
    {
        // Already visited.
        return false;
    }
    else
    {
        index_ = neighbourInfo.index();

        n_ = neighbourInfo.n();

        return true;
    }
}


template<class TrackingData>
inline bool tnbLib::directionInfo::equal
(
    const directionInfo& rhs,
    TrackingData& td
) const
{
    return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::directionInfo::operator==
(
    const tnbLib::directionInfo& rhs
    ) const
{
    return  index() == rhs.index() && n() == rhs.n();
}


inline bool tnbLib::directionInfo::operator!=
(
    const tnbLib::directionInfo& rhs
    ) const
{
    return !(*this == rhs);
}


// ************************************************************************* //