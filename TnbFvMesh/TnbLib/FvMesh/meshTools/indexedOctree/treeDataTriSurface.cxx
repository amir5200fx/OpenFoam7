#include <treeDataTriSurface.hxx>

#include <triSurfaceTools.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<>
tnbLib::volumeType tnbLib::treeDataPrimitivePatch<tnbLib::triSurface>::getVolumeType
(
	const indexedOctree<treeDataPrimitivePatch<triSurface>>& oc,
	const point& sample
) const
{
	// Find nearest face to sample
	pointIndexHit info = oc.findNearest(sample, sqr(great));

	if (info.index() == -1)
	{
		FatalErrorInFunction
			<< "Could not find " << sample << " in octree."
			<< abort(FatalError);
	}

	// Get actual intersection point on face
	label facei = info.index();

	triSurfaceTools::sideType t = triSurfaceTools::surfaceSide
	(
		patch_,
		sample,
		facei
	);

	if (t == triSurfaceTools::UNKNOWN)
	{
		return volumeType::unknown;
	}
	else if (t == triSurfaceTools::INSIDE)
	{
		return volumeType::inside;
	}
	else if (t == triSurfaceTools::OUTSIDE)
	{
		return volumeType::outside;
	}
	else
	{
		FatalErrorInFunction
			<< "problem" << abort(FatalError);
		return volumeType::unknown;
	}
}


// ************************************************************************* //