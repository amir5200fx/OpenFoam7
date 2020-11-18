#pragma once
#include <polyMesh.hxx>
#include <transform.hxx>
#include <orientedSurface.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::patchFaceOrientation::patchFaceOrientation()
	:
	flipStatus_(orientedSurface::UNVISITED)
{}


inline tnbLib::patchFaceOrientation::patchFaceOrientation
(
	const label flipStatus
)
	:
	flipStatus_(flipStatus)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::patchFaceOrientation::flipStatus() const
{
	return flipStatus_;
}


inline void tnbLib::patchFaceOrientation::flip()
{
	if (flipStatus_ == orientedSurface::NOFLIP)
	{
		flipStatus_ = orientedSurface::FLIP;
	}
	else if (flipStatus_ == orientedSurface::FLIP)
	{
		flipStatus_ = orientedSurface::NOFLIP;
	}
}


template<class TrackingData>
inline bool tnbLib::patchFaceOrientation::valid(TrackingData& td) const
{
	return flipStatus_ != orientedSurface::UNVISITED;
}


template<class TrackingData>
inline void tnbLib::patchFaceOrientation::transform
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const tensor& rotTensor,
	const scalar tol,
	TrackingData& td
)
{}


template<class TrackingData>
inline bool tnbLib::patchFaceOrientation::updateEdge
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const label edgeI,
	const label facei,
	const patchFaceOrientation& faceInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (valid(td))
	{
		return false;
	}

	const face& f = patch.localFaces()[facei];
	const edge& e = patch.edges()[edgeI];

	// Pout<< "Updating edge:" << edgeI << " verts:" << e << nl
	//    << "    start:" << patch.localPoints()[e[0]] << nl
	//    << "      end:" << patch.localPoints()[e[1]] << endl;

	patchFaceOrientation consistentInfo(faceInfo);

	// Check how edge relates to face
	if (f.edgeDirection(e) < 0)
	{
		// Create flipped version of faceInfo
		consistentInfo.flip();
	}

	operator=(consistentInfo);
	return true;
}


template<class TrackingData>
inline bool tnbLib::patchFaceOrientation::updateEdge
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const patchFaceOrientation& edgeInfo,
	const bool sameOrientation,
	const scalar tol,
	TrackingData& td
)
{
	if (valid(td))
	{
		return false;
	}

	// Create (flipped/unflipped) version of edgeInfo
	patchFaceOrientation consistentInfo(edgeInfo);

	if (!sameOrientation)
	{
		consistentInfo.flip();
	}

	operator=(consistentInfo);
	return true;
}


template<class TrackingData>
inline bool tnbLib::patchFaceOrientation::updateFace
(
	const polyMesh& mesh,
	const indirectPrimitivePatch& patch,
	const label facei,
	const label edgeI,
	const patchFaceOrientation& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	if (valid(td))
	{
		return false;
	}

	// Transfer flip to face
	const face& f = patch.localFaces()[facei];
	const edge& e = patch.edges()[edgeI];


	// Pout<< "Updating face:" << facei << nl
	//    << "    verts:" << f << nl
	//    << " with edge:" << edgeI << nl
	//    << "    start:" << patch.localPoints()[e[0]] << nl
	//    << "      end:" << patch.localPoints()[e[1]] << endl;


	// Create (flipped/unflipped) version of edgeInfo
	patchFaceOrientation consistentInfo(edgeInfo);

	if (f.edgeDirection(e) > 0)
	{
		consistentInfo.flip();
	}

	operator=(consistentInfo);
	return true;
}


template<class TrackingData>
inline bool tnbLib::patchFaceOrientation::equal
(
	const patchFaceOrientation& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::patchFaceOrientation::operator==
(
	const tnbLib::patchFaceOrientation& rhs
	) const
{
	return flipStatus() == rhs.flipStatus();
}


inline bool tnbLib::patchFaceOrientation::operator!=
(
	const tnbLib::patchFaceOrientation& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //