#include <meshSearchMeshObject.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(meshSearchMeshObject, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshSearchMeshObject::meshSearchMeshObject(const polyMesh& mesh)
	:
	MeshObject<polyMesh, tnbLib::GeometricMeshObject, meshSearchMeshObject>(mesh),
	meshSearch(mesh)
{}


// ************************************************************************* //
