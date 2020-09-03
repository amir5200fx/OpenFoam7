#include <pointMesh.hxx>

#include <globalMeshData.hxx>
#include <pointMeshMapper.hxx>
#include <pointFields.hxx>
#include <MapGeometricFields.hxx>
#include <MapPointField.hxx>
#include <facePointPatch.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(pointMesh, 0);

}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointMesh::mapFields(const mapPolyMesh& mpm)
{
	if (debug)
	{
		Pout << "void pointMesh::mapFields(const mapPolyMesh&): "
			<< "Mapping all registered pointFields."
			<< endl;
	}
	// Create a mapper
	const pointMeshMapper m(*this, mpm);

	MapGeometricFields<scalar, pointPatchField, pointMeshMapper, pointMesh>(m);
	MapGeometricFields<vector, pointPatchField, pointMeshMapper, pointMesh>(m);
	MapGeometricFields
		<
		sphericalTensor,
		pointPatchField,
		pointMeshMapper,
		pointMesh
		>(m);
	MapGeometricFields<symmTensor, pointPatchField, pointMeshMapper, pointMesh>
		(m);
	MapGeometricFields<tensor, pointPatchField, pointMeshMapper, pointMesh>(m);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointMesh::pointMesh(const polyMesh& pMesh)
	:
	MeshObject<polyMesh, tnbLib::PatchMeshObject, pointMesh>(pMesh),
	GeoMesh<polyMesh>(pMesh),
	boundary_(*this, pMesh.boundaryMesh())
{
	if (debug)
	{
		Pout << "pointMesh::pointMesh(const polyMesh&): "
			<< "Constructing from polyMesh " << pMesh.name()
			<< endl;
	}

	// Calculate the geometry for the patches (transformation tensors etc.)
	boundary_.calcGeometry();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointMesh::~pointMesh()
{
	if (debug)
	{
		Pout << "~pointMesh::pointMesh()"
			<< endl;
		error::printStack(Pout);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointMesh::reset(const bool validBoundary)
{
	const polyMesh& pm = operator()();
	if (debug)
	{
		Pout << "pointMesh::reset(const bool validBoundary): "
			<< "Resetting from polyMesh " << pm.name() << endl;
	}

	boundary_.reset(pm.boundaryMesh());
	if (validBoundary)
	{
		// Calculate the geometry for the patches (transformation tensors etc.)
		boundary_.calcGeometry();
	}
}


bool tnbLib::pointMesh::movePoints()
{
	if (debug)
	{
		Pout << "pointMesh::movePoints(const pointField&): "
			<< "Moving points." << endl;
	}

	boundary_.movePoints(GeoMesh<polyMesh>::mesh_.points());

	return true;
}


void tnbLib::pointMesh::updateMesh(const mapPolyMesh& mpm)
{
	if (debug)
	{
		Pout << "pointMesh::updateMesh(const mapPolyMesh&): "
			<< "Updating for topology changes." << endl;
		Pout << endl;
	}
	boundary_.updateMesh();

	// Map all registered point fields
	mapFields(mpm);
}


void tnbLib::pointMesh::reorderPatches
(
	const labelUList& newToOld,
	const bool validBoundary
)
{
	if (debug)
	{
		Pout << "pointMesh::reorderPatches( const labelUList&, const bool): "
			<< "Updating for reordered patches." << endl;
		Pout << endl;
	}

	boundary_.shuffle(newToOld, validBoundary);

	objectRegistry& db = const_cast<objectRegistry&>(thisDb());
	ReorderPatchFields<pointScalarField>(db, newToOld);
	ReorderPatchFields<pointVectorField>(db, newToOld);
	ReorderPatchFields<pointSphericalTensorField>(db, newToOld);
	ReorderPatchFields<pointSymmTensorField>(db, newToOld);
	ReorderPatchFields<pointTensorField>(db, newToOld);
}


void tnbLib::pointMesh::addPatch(const label patchi)
{
	if (debug)
	{
		Pout << "pointMesh::addPatch(const label): "
			<< "Adding patch at " << patchi << endl;
		Pout << endl;
	}

	const polyBoundaryMesh& pbm = mesh().boundaryMesh();
	if (pbm.size() != boundary_.size())
	{
		FatalErrorInFunction << "Problem :"
			<< " pointBoundaryMesh size :" << boundary_.size()
			<< " polyBoundaryMesh size :" << pbm.size()
			<< exit(FatalError);
	}

	boundary_.set(patchi, facePointPatch::New(pbm[patchi], boundary_).ptr());

	objectRegistry& db = const_cast<objectRegistry&>(thisDb());
	const dictionary d;
	const word patchFieldType("calculated");

	AddPatchFields<pointScalarField>(db, patchi, d, patchFieldType, Zero);
	AddPatchFields<pointVectorField>(db, patchi, d, patchFieldType, Zero);
	AddPatchFields<pointSphericalTensorField>
		(
			db,
			patchi,
			d,
			patchFieldType,
			Zero
			);
	AddPatchFields<pointSymmTensorField>(db, patchi, d, patchFieldType, Zero);
	AddPatchFields<pointTensorField>(db, patchi, d, patchFieldType, Zero);
}


// ************************************************************************* //