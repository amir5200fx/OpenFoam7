#pragma once
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class TrackingData>
inline bool tnbLib::wallNormalInfo::update
(
    const wallNormalInfo& w2,
    TrackingData& td
)
{
    if (!w2.valid(td))
    {
        FatalErrorInFunction
            << "Problem: w2 is not valid" << abort(FatalError);

        return false;
    }
    else if (valid(td))
    {
        // our already set. Stop any transfer
        return false;
    }
    else
    {
        normal_ = w2.normal();

        return true;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::wallNormalInfo::wallNormalInfo()
    :
    normal_(point::max)
{}


inline tnbLib::wallNormalInfo::wallNormalInfo(const vector& normal)
    :
    normal_(normal)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::vector& tnbLib::wallNormalInfo::normal() const
{
    return normal_;
}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::valid(TrackingData& td) const
{
    return normal_ != point::max;
}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::sameGeometry
(
    const polyMesh&,
    const wallNormalInfo& w2,
    const scalar tol,
    TrackingData& td
) const
{
    return true;
}


template<class TrackingData>
inline void tnbLib::wallNormalInfo::leaveDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::wallNormalInfo::transform
(
    const polyMesh&,
    const tensor& rotTensor,
    TrackingData& td
)
{}


template<class TrackingData>
inline void tnbLib::wallNormalInfo::enterDomain
(
    const polyMesh&,
    const polyPatch& patch,
    const label patchFacei,
    const point& faceCentre,
    TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::updateCell
(
    const polyMesh&,
    const label thisCelli,
    const label neighbourFacei,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::updateFace
(
    const polyMesh&,
    const label thisFacei,
    const label neighbourCelli,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::updateFace
(
    const polyMesh&,
    const label thisFacei,
    const wallNormalInfo& neighbourWallInfo,
    const scalar tol,
    TrackingData& td
)
{
    return update(neighbourWallInfo, td);
}


template<class TrackingData>
inline bool tnbLib::wallNormalInfo::equal
(
    const wallNormalInfo& rhs,
    TrackingData& td
) const
{
    return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::wallNormalInfo::operator==
(
    const tnbLib::wallNormalInfo& rhs
    ) const
{
    return normal() == rhs.normal();
}


inline bool tnbLib::wallNormalInfo::operator!=
(
    const tnbLib::wallNormalInfo& rhs
    ) const
{
    return !(*this == rhs);
}


// ************************************************************************* //