#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline void tnbLib::cyclicACMIPolyPatch::setUpdated(const bool flag) const
{
	updated_ = flag;
}


inline bool tnbLib::cyclicACMIPolyPatch::updated() const
{
	return updated_;
}


inline const tnbLib::word& tnbLib::cyclicACMIPolyPatch::nonOverlapPatchName() const
{
	return nonOverlapPatchName_;
}


inline const tnbLib::polyPatch& tnbLib::cyclicACMIPolyPatch::nonOverlapPatch() const
{
	// note: use nonOverlapPatchID() as opposed to patch name to initialise
	// demand-driven data

	return this->boundaryMesh()[nonOverlapPatchID()];
}


inline tnbLib::polyPatch& tnbLib::cyclicACMIPolyPatch::nonOverlapPatch()
{
	// note: use nonOverlapPatchID() as opposed to patch name to initialise
	// demand-driven data

	return const_cast<polyPatch&>(this->boundaryMesh()[nonOverlapPatchID()]);
}


inline const tnbLib::scalarField& tnbLib::cyclicACMIPolyPatch::mask() const
{
	if (owner())
	{
		return srcMask_;
	}
	else
	{
		return neighbPatch().tgtMask();
	}
}


inline tnbLib::scalar tnbLib::cyclicACMIPolyPatch::tolerance()
{
	return tolerance_;
}


// ************************************************************************* //