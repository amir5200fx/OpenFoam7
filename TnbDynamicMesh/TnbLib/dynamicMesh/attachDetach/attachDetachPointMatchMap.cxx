#include <attachDetach.hxx>

#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <primitiveFacePatch.hxx>
#include <polyTopoChanger.hxx>

#include <primitiveFacePatch.hxx>  // added by amir
#include <faceList.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::Map<tnbLib::label>&
tnbLib::attachDetach::pointMatchMap() const
{
	if (!pointMatchMapPtr_)
	{
		calcPointMatchMap();
	}

	return *pointMatchMapPtr_;
}


void tnbLib::attachDetach::calcPointMatchMap() const
{
	if (debug)
	{
		Pout << "void attachDetach::calcPointMatchMap() const "
			<< " for object " << name() << " : "
			<< "Calculating point matching" << endl;
	}

	if (pointMatchMapPtr_)
	{
		FatalErrorInFunction
			<< "Point match map already calculated for object " << name()
			<< abort(FatalError);
	}

	const polyMesh& mesh = topoChanger().mesh();
	const faceList& faces = mesh.faces();

	const polyPatch& masterPatch = mesh.boundaryMesh()[masterPatchID_.index()];
	const polyPatch& slavePatch = mesh.boundaryMesh()[slavePatchID_.index()];

	// Create the reverse patch out of the slave patch
	primitiveFacePatch reverseSlavePatch
	(
		faceList(slavePatch.size()),
		mesh.points()
	);

	const label slavePatchStart = slavePatch.start();

	forAll(reverseSlavePatch, facei)
	{
		reverseSlavePatch[facei] =
			faces[slavePatchStart + facei].reverseFace();
	}

	// Create point merge list and remove merged points
	const labelList& masterMeshPoints = masterPatch.meshPoints();
	const labelList& slaveMeshPoints = reverseSlavePatch.meshPoints();

	const faceList& masterLocalFaces = masterPatch.localFaces();
	const faceList& slaveLocalFaces = reverseSlavePatch.localFaces();

	pointMatchMapPtr_ = new Map<label>(2 * slaveMeshPoints.size());
	Map<label>& removedPointMap = *pointMatchMapPtr_;

	forAll(masterLocalFaces, facei)
	{
		const face& curMasterPoints = masterLocalFaces[facei];
		const face& curSlavePoints = slaveLocalFaces[facei];

		forAll(curMasterPoints, pointi)
		{
			// If the master and slave point labels are the same, the
			// point remains.  Otherwise, the slave point is removed and
			// replaced by the master
			if
				(
					masterMeshPoints[curMasterPoints[pointi]]
					!= slaveMeshPoints[curSlavePoints[pointi]]
					)
			{
				// Pout<< "Matching slave point "
				//     << slaveMeshPoints[curSlavePoints[pointi]]
				//     << " with "
				//     << masterMeshPoints[curMasterPoints[pointi]]
				//     << endl;

				// Grab the addressing
				removedPointMap.insert
				(
					slaveMeshPoints[curSlavePoints[pointi]],
					masterMeshPoints[curMasterPoints[pointi]]
				);
			}
		}
	}

	if (debug)
	{
		Pout << "void attachDetach::calcPointMatchMap() const "
			<< " for object " << name() << " : "
			<< "Finished calculating point matching" << endl;
	}
}


// ************************************************************************* //