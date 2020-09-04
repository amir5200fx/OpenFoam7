#pragma once
inline const tnbLib::mappedPatchBase::sampleMode&
tnbLib::mappedPatchBase::mode() const
{
	return mode_;
}


inline const tnbLib::word& tnbLib::mappedPatchBase::sampleRegion() const
{
	if (sampleRegion_.empty())
	{
		if (!coupleGroup_.valid())
		{
			FatalErrorInFunction
				<< "Supply either a regionName or a coupleGroup"
				<< " for patch " << patch_.name()
				<< " in region " << patch_.boundaryMesh().mesh().name()
				<< exit(FatalError);
		}

		// Try and use patchGroup to find samplePatch and sampleRegion
		label samplePatchID = coupleGroup_.findOtherPatchID
		(
			patch_,
			sampleRegion_
		);

		samplePatch_ = sampleMesh().boundaryMesh()[samplePatchID].name();
	}
	return sampleRegion_;
}


inline const tnbLib::word& tnbLib::mappedPatchBase::samplePatch() const
{
	if (samplePatch_.empty())
	{
		if (!coupleGroup_.valid())
		{
			FatalErrorInFunction
				<< "Supply either a patchName or a coupleGroup"
				<< " for patch " << patch_.name()
				<< " in region " << patch_.boundaryMesh().mesh().name()
				<< exit(FatalError);
		}

		// Try and use patchGroup to find samplePatch and sampleRegion
		label samplePatchID = coupleGroup_.findOtherPatchID
		(
			patch_,
			sampleRegion_
		);

		samplePatch_ = sampleMesh().boundaryMesh()[samplePatchID].name();
	}
	return samplePatch_;
}


inline const tnbLib::word& tnbLib::mappedPatchBase::coupleGroup() const
{
	return coupleGroup_.name();
}


inline tnbLib::label tnbLib::mappedPatchBase::sampleSize() const
{
	switch (mode_)
	{
	case NEARESTPATCHFACEAMI:
	{
		return samplePolyPatch().size();
	}
	case NEARESTCELL:
	{
		return sampleMesh().nCells();
	}
	case NEARESTPATCHFACE:
	{
		return samplePolyPatch().size();
	}
	case NEARESTPATCHPOINT:
	{
		return samplePolyPatch().nPoints();
	}
	case NEARESTFACE:
	{
		const polyMesh& mesh = sampleMesh();
		return mesh.nFaces() - mesh.nInternalFaces();
	}
	default:
	{
		FatalErrorInFunction
			<< "problem." << abort(FatalError);
		return -1;
	}
	}
}


inline const tnbLib::vector& tnbLib::mappedPatchBase::offset() const
{
	return offset_;
}


inline const tnbLib::vectorField& tnbLib::mappedPatchBase::offsets() const
{
	return offsets_;
}


inline bool tnbLib::mappedPatchBase::sameRegion() const
{
	return sameRegion_;
}


inline const tnbLib::mapDistribute& tnbLib::mappedPatchBase::map() const
{
	if (mapPtr_.empty())
	{
		calcMapping();
	}

	return mapPtr_();
}


inline const tnbLib::AMIInterpolation& tnbLib::mappedPatchBase::AMI
(
	bool forceUpdate
) const
{
	if (forceUpdate || AMIPtr_.empty())
	{
		calcAMI();
	}

	return AMIPtr_();
}


// ************************************************************************* //