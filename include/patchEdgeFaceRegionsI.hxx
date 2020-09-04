#pragma once
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::patchEdgeFaceRegions::patchEdgeFaceRegions()
{}


inline tnbLib::patchEdgeFaceRegions::patchEdgeFaceRegions
(
	const labelList& regions
)
	:
	regions_(regions)
{}


inline tnbLib::patchEdgeFaceRegions::patchEdgeFaceRegions
(
	const labelPair& regions
)
	:
	regions_(2)
{
	regions_[0] = regions[0];
	regions_[1] = regions[1];
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::labelList& tnbLib::patchEdgeFaceRegions::regions() const
{
	return regions_;
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegions::valid(TrackingData& td) const
{
	return regions_.size() && (findIndex(regions_, labelMax) == -1);
}


template<class Patch, class TrackingData>
inline void tnbLib::patchEdgeFaceRegions::transform
(
	const polyMesh& mesh,
	const Patch& patch,
	const tensor& rotTensor,
	const scalar tol,
	TrackingData& td
)
{}


template<class Patch, class TrackingData>
inline bool tnbLib::patchEdgeFaceRegions::updateEdge
(
	const polyMesh& mesh,
	const Patch& patch,
	const label edgeI,
	const label facei,
	const patchEdgeFaceRegions& faceInfo,
	const scalar tol,
	TrackingData& td
)
{
	const face& f = patch.localFaces()[facei];
	const edge& e = patch.edges()[edgeI];

	label index = findIndex(patch.faceEdges()[facei], edgeI);
	bool sameOrientation = (f[index] == e.start());

	// Get information in edge-order
	edge orientedInfo
	(
		faceInfo.regions_[index],
		faceInfo.regions_[f.fcIndex(index)]
	);
	if (!sameOrientation)
	{
		orientedInfo.flip();
	}

	if (!faceInfo.valid(td))
	{
		FatalErrorInFunction
			<< "problem." << abort(FatalError);
	}

	if ((findIndex(orientedInfo, -1) != -1) || (findIndex(regions_, -1) != -1))
	{
		// Blocked edge/face
		return false;
	}


	bool changed = false;

	regions_.setSize(orientedInfo.size(), labelMax);
	forAll(orientedInfo, i)
	{
		if (orientedInfo[i] != -1 && orientedInfo[i] < regions_[i])
		{
			regions_[i] = orientedInfo[i];
			changed = true;
		}
	}
	return changed;
}


template<class Patch, class TrackingData>
inline bool tnbLib::patchEdgeFaceRegions::updateEdge
(
	const polyMesh& mesh,
	const Patch& patch,
	const patchEdgeFaceRegions& edgeInfo,
	const bool sameOrientation,
	const scalar tol,
	TrackingData& td
)
{
	// Get information in edge-order
	edge orientedInfo(edgeInfo.regions_[0], edgeInfo.regions_[1]);
	if (!sameOrientation)
	{
		orientedInfo.flip();
	}


	if (!edgeInfo.valid(td))
	{
		FatalErrorInFunction
			<< "problem." << abort(FatalError);
	}

	if ((findIndex(orientedInfo, -1) != -1) || (findIndex(regions_, -1) != -1))
	{
		// Blocked edge/face
		return false;
	}


	bool changed = false;

	regions_.setSize(orientedInfo.size(), labelMax);
	forAll(orientedInfo, i)
	{
		if (orientedInfo[i] != -1 && orientedInfo[i] < regions_[i])
		{
			regions_[i] = orientedInfo[i];
			changed = true;
		}
	}
	return changed;
}


template<class Patch, class TrackingData>
inline bool tnbLib::patchEdgeFaceRegions::updateFace
(
	const polyMesh& mesh,
	const Patch& patch,
	const label facei,
	const label edgeI,
	const patchEdgeFaceRegions& edgeInfo,
	const scalar tol,
	TrackingData& td
)
{
	const face& f = patch.localFaces()[facei];
	const edge& e = patch.edges()[edgeI];

	// Find starting point of edge on face.
	label index0 = findIndex(patch.faceEdges()[facei], edgeI);
	label index1 = f.fcIndex(index0);
	bool sameOrientation = (f[index0] == e.start());


	// Get information in face-order
	edge orientedInfo
	(
		edgeInfo.regions_[0],
		edgeInfo.regions_[1]
	);
	if (!sameOrientation)
	{
		orientedInfo.flip();
	}

	if (!edgeInfo.valid(td))
	{
		FatalErrorInFunction
			<< "problem." << abort(FatalError);
	}

	if ((findIndex(orientedInfo, -1) != -1) || (findIndex(regions_, -1) != -1))
	{
		// Blocked edge/face
		return false;
	}


	bool changed = false;

	// Scale if needed
	regions_.setSize(f.size(), labelMax);

	if (orientedInfo[0] < regions_[index0])
	{
		regions_[index0] = orientedInfo[0];
		changed = true;
	}
	if (orientedInfo[1] < regions_[index1])
	{
		regions_[index1] = orientedInfo[1];
		changed = true;
	}

	return changed;
}


template<class TrackingData>
inline bool tnbLib::patchEdgeFaceRegions::equal
(
	const patchEdgeFaceRegions& rhs,
	TrackingData& td
) const
{
	return operator==(rhs);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::patchEdgeFaceRegions::operator==
(
	const tnbLib::patchEdgeFaceRegions& rhs
	) const
{
	return regions() == rhs.regions();
}


inline bool tnbLib::patchEdgeFaceRegions::operator!=
(
	const tnbLib::patchEdgeFaceRegions& rhs
	) const
{
	return !(*this == rhs);
}


// ************************************************************************* //