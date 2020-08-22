#include <repatchPolyTopoChanger.hxx>

#include <polyTopoChanger.hxx>
#include <mapPolyMesh.hxx>
#include <polyModifyFace.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::polyTopoChange& tnbLib::repatchPolyTopoChanger::meshMod()
{
	if (meshModPtr_.empty())
	{
		meshModPtr_.reset(new polyTopoChange(mesh_));
	}
	return meshModPtr_();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::repatchPolyTopoChanger::repatchPolyTopoChanger(polyMesh& mesh)
	:
	mesh_(mesh),
	meshModPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::repatchPolyTopoChanger::changePatches
(
	const List<polyPatch*>& patches
)
{
	if (meshModPtr_.valid())
	{
		FatalErrorInFunction
			<< "Cannot change patches after having changed faces. " << nl
			<< "Please call changePatches first."
			<< exit(FatalError);
	}
	meshModPtr_.clear();
	mesh_.removeBoundary();
	mesh_.addPatches(patches);
}


void tnbLib::repatchPolyTopoChanger::changePatchID
(
	const label faceID,
	const label patchID
)
{
	if (polyTopoChanger::debug)
	{
		// Check that the request is possible
		if
			(
				faceID >= mesh_.faces().size()
				|| patchID >= mesh_.boundaryMesh().size()
				|| mesh_.isInternalFace(faceID)
				)
		{
			FatalErrorInFunction
				<< " patchID: " << patchID << ".  "
				<< "Labels out of range or internal face."
				<< abort(FatalError);
		}
	}

	const label zoneID = mesh_.faceZones().whichZone(faceID);

	bool zoneFlip = false;

	if (zoneID >= 0)
	{
		const faceZone& fZone = mesh_.faceZones()[zoneID];

		zoneFlip = fZone.flipMap()[fZone.whichFace(faceID)];
	}

	meshMod().setAction
	(
		polyModifyFace
		(
			mesh_.faces()[faceID],              // face
			faceID,                             // face ID
			mesh_.faceOwner()[faceID],          // owner
			-1,                                 // neighbour
			false,                              // flip flux
			patchID,                            // patch ID
			false,                              // remove from zone
			zoneID,                             // zone ID
			zoneFlip                            // zone flip
		)
	);
}


void tnbLib::repatchPolyTopoChanger::setFaceZone
(
	const label faceID,
	const label zoneID,
	const bool zoneFlip
)
{
	if (polyTopoChanger::debug)
	{
		// Check that the request is possible
		if (faceID > mesh_.faces().size())
		{
			FatalErrorInFunction
				<< "out of range."
				<< abort(FatalError);
		}
	}

	meshMod().setAction
	(
		polyModifyFace
		(
			mesh_.faces()[faceID],              // face
			faceID,                             // face ID
			mesh_.faceOwner()[faceID],          // owner
			mesh_.faceNeighbour()[faceID],      // neighbour
			false,                              // flip flux
			mesh_.boundaryMesh().whichPatch(faceID),  // patch ID
			true,                               // remove from zone
			zoneID,                             // zone ID
			zoneFlip                            // zone flip
		)
	);
}


void tnbLib::repatchPolyTopoChanger::changeAnchorPoint
(
	const label faceID,
	const label fp
)
{
	if (polyTopoChanger::debug)
	{
		// Check that the request is possible
		if (faceID > mesh_.faces().size())
		{
			FatalErrorInFunction
				<< "out of range."
				<< abort(FatalError);
		}
	}

	const face& f = mesh_.faces()[faceID];

	if ((fp < 0) || (fp >= f.size()))
	{
		FatalErrorInFunction
			<< "Error in definition.  Face point: " << fp
			<< "indexes out of face " << f
			<< abort(FatalError);
	}

	label patchID = mesh_.boundaryMesh().whichPatch(faceID);

	const label zoneID = mesh_.faceZones().whichZone(faceID);

	bool zoneFlip = false;

	if (zoneID >= 0)
	{
		const faceZone& fZone = mesh_.faceZones()[zoneID];

		zoneFlip = fZone.flipMap()[fZone.whichFace(faceID)];
	}

	if (fp == 0)
	{
		// Do dummy modify to keep patch ordering.
		meshMod().setAction
		(
			polyModifyFace
			(
				f,                                  // face
				faceID,                             // face ID
				mesh_.faceOwner()[faceID],          // owner
				-1,                                 // neighbour
				false,                              // flip flux
				patchID,                            // patch ID
				false,                              // remove from zone
				zoneID,                             // zone ID
				zoneFlip                            // zone flip
			)
		);
	}
	else
	{
		// Construct new face with fp as first point.

		face newFace(f.size());

		label fVert = fp;

		forAll(f, i)
		{
			newFace[i] = f[fVert++];

			if (fVert == f.size())
			{
				fVert = 0;
			}
		}


		meshMod().setAction
		(
			polyModifyFace
			(
				newFace,                            // face
				faceID,                             // face ID
				mesh_.faceOwner()[faceID],          // owner
				-1,                                 // neighbour
				false,                              // flip flux
				patchID,                            // patch ID
				false,                              // remove from zone
				zoneID,                             // zone ID
				zoneFlip                            // zone flip
			)
		);
	}
}


void tnbLib::repatchPolyTopoChanger::repatch()
{
	// Change mesh, no inflation
	meshMod().changeMesh(mesh_, false);

	// Clear topo change for the next operation
	meshModPtr_.clear();
}


// ************************************************************************* //