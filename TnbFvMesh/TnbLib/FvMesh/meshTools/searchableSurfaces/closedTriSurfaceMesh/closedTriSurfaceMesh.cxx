#include <closedTriSurfaceMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(closedTriSurfaceMesh, 0);
	addToRunTimeSelectionTable(searchableSurface, closedTriSurfaceMesh, dict);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::closedTriSurfaceMesh::closedTriSurfaceMesh
(
	const IOobject& io,
	const triSurface& s
)
	:
	triSurfaceMesh(io, s)
{}


tnbLib::closedTriSurfaceMesh::closedTriSurfaceMesh(const IOobject& io)
	:
	triSurfaceMesh(io)
{}


tnbLib::closedTriSurfaceMesh::closedTriSurfaceMesh
(
	const IOobject& io,
	const dictionary& dict
)
	:
	triSurfaceMesh(io, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::closedTriSurfaceMesh::~closedTriSurfaceMesh()
{}


// ************************************************************************* //