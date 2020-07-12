#include <meshSearchFACE_CENTRE_TRISMeshObject.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(meshSearchFACE_CENTRE_TRISMeshObject, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshSearchFACE_CENTRE_TRISMeshObject::meshSearchFACE_CENTRE_TRISMeshObject
(
	const polyMesh& mesh
)
	:
	MeshObject
	<
	polyMesh,
	tnbLib::GeometricMeshObject,
	meshSearchFACE_CENTRE_TRISMeshObject
	>(mesh),
	meshSearch(mesh, polyMesh::FACE_CENTRE_TRIS)
{}


// ************************************************************************* //