#include <enrichedPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::enrichedPatch::completePointMap() const
{
	if (pointMapComplete_)
	{
		FatalErrorInFunction
			<< "Point map already completed"
			<< abort(FatalError);
	}

	pointMapComplete_ = true;

	const Map<label>& pmm = pointMergeMap();

	// Get the mesh points for both patches.  If the point has not been
	// merged away, add it to the map

	// Do master patch
	const labelList& masterMeshPoints = masterPatch_.meshPoints();
	const pointField& masterLocalPoints = masterPatch_.localPoints();

	forAll(masterMeshPoints, pointi)
	{
		if (!pmm.found(masterMeshPoints[pointi]))
		{
			pointMap_.insert
			(
				masterMeshPoints[pointi],
				masterLocalPoints[pointi]
			);
		}
	}

	// Do slave patch
	const labelList& slaveMeshPoints = slavePatch_.meshPoints();
	const pointField& slaveLocalPoints = slavePatch_.localPoints();

	forAll(slaveMeshPoints, pointi)
	{
		if (!pmm.found(slaveMeshPoints[pointi]))
		{
			pointMap_.insert
			(
				slaveMeshPoints[pointi],
				slaveLocalPoints[pointi]
			);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


tnbLib::Map<tnbLib::point>& tnbLib::enrichedPatch::pointMap()
{
	if (!pointMapComplete_)
	{
		completePointMap();
	}

	return pointMap_;
}


const tnbLib::Map<tnbLib::point>& tnbLib::enrichedPatch::pointMap() const
{
	if (!pointMapComplete_)
	{
		completePointMap();
	}

	return pointMap_;
}


// ************************************************************************* //