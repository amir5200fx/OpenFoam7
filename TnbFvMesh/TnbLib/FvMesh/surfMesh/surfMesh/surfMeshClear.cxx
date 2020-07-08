#include <surfMesh.hxx>

#include <globalMeshData.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::surfMesh::removeZones()
{
	if (debug)
	{
		InfoInFunction << "Removing surface zones." << endl;
	}

	// Remove the surface zones
	storedZones().clear();

	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfMesh::clearGeom()
{
	if (debug)
	{
		InfoInFunction << "Clearing geometric data" << endl;
	}

	MeshReference::clearGeom();
}


void tnbLib::surfMesh::clearAddressing()
{
	if (debug)
	{
		InfoInFunction << "clearing topology" << endl;
	}

	MeshReference::clearPatchMeshAddr();
}


void tnbLib::surfMesh::clearOut()
{
	clearGeom();
	clearAddressing();
}


// ************************************************************************* //