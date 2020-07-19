#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::word& tnbLib::cyclicAMIPolyPatch::neighbPatchName() const
{
	if (nbrPatchName_.empty())
	{
		// Try and use patchGroup to find samplePatch and sampleRegion
		label patchID = coupleGroup_.findOtherPatchID(*this);

		nbrPatchName_ = boundaryMesh()[patchID].name();
	}
	return nbrPatchName_;
}


inline const tnbLib::vector& tnbLib::cyclicAMIPolyPatch::rotationAxis() const
{
	return rotationAxis_;
}


inline const tnbLib::point& tnbLib::cyclicAMIPolyPatch::rotationCentre() const
{
	return rotationCentre_;
}


inline const tnbLib::vector& tnbLib::cyclicAMIPolyPatch::separationVector() const
{
	return separationVector_;
}


// ************************************************************************* //