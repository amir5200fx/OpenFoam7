#include <polyMesh.hxx>

#include <primitiveMesh.hxx>
#include <globalMeshData.hxx>
#include <MeshObject.hxx>
#include <indexedOctree.hxx>
#include <treeDataCell.hxx>
#include <pointMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::polyMesh::removeBoundary()
{
	if (debug)
	{
		InfoInFunction << "Removing boundary patches." << endl;
	}

	// Remove the point zones
	boundary_.clear();
	boundary_.setSize(0);

	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::polyMesh::clearGeom()
{
	if (debug)
	{
		InfoInFunction << "Clearing geometric data" << endl;
	}

	// Clear all geometric mesh objects
	meshObject::clear<pointMesh, GeometricMeshObject>(*this);
	meshObject::clear<polyMesh, GeometricMeshObject>(*this);

	primitiveMesh::clearGeom();

	boundary_.clearGeom();

	// Reset valid directions (could change with rotation)
	geometricD_ = Zero;
	solutionD_ = Zero;

	// Remove the cell tree
	cellTreePtr_.clear();
}


void tnbLib::polyMesh::clearAddressing(const bool isMeshUpdate)
{
	if (debug)
	{
		InfoInFunction
			<< "Clearing topology  isMeshUpdate:" << isMeshUpdate << endl;
	}

	if (isMeshUpdate)
	{
		// Part of a mesh update. Keep meshObjects that have an updateMesh
		// callback
		meshObject::clearUpto
			<
			pointMesh,
			TopologicalMeshObject,
			UpdateableMeshObject
			>
			(
				*this
				);
		meshObject::clearUpto
			<
			polyMesh,
			TopologicalMeshObject,
			UpdateableMeshObject
			>
			(
				*this
				);
	}
	else
	{
		meshObject::clear<pointMesh, TopologicalMeshObject>(*this);
		meshObject::clear<polyMesh, TopologicalMeshObject>(*this);
	}

	primitiveMesh::clearAddressing();

	// parallelData depends on the processorPatch ordering so force
	// recalculation
	globalMeshDataPtr_.clear();

	// Reset valid directions
	geometricD_ = Zero;
	solutionD_ = Zero;

	// Update zones
	pointZones_.clearAddressing();
	faceZones_.clearAddressing();
	cellZones_.clearAddressing();

	// Remove the stored tet base points
	tetBasePtIsPtr_.clear();

	// Remove the cell tree
	cellTreePtr_.clear();
}


void tnbLib::polyMesh::clearPrimitives()
{
	resetMotion();

	points_.setSize(0);
	faces_.setSize(0);
	owner_.setSize(0);
	neighbour_.setSize(0);

	clearedPrimitives_ = true;
}


void tnbLib::polyMesh::clearOut()
{
	clearGeom();
	clearAddressing();
}


void tnbLib::polyMesh::clearTetBasePtIs()
{
	if (debug)
	{
		InfoInFunction << "Clearing tet base points" << endl;
	}

	tetBasePtIsPtr_.clear();
}


void tnbLib::polyMesh::clearCellTree()
{
	if (debug)
	{
		InfoInFunction << "Clearing cell tree" << endl;
	}

	cellTreePtr_.clear();
}


// ************************************************************************* //