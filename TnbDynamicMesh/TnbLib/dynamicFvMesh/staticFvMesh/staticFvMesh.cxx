#include <staticFvMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(staticFvMesh, 0);
	addToRunTimeSelectionTable(dynamicFvMesh, staticFvMesh, IOobject);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::staticFvMesh::staticFvMesh(const IOobject& io)
	:
	dynamicFvMesh(io)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::staticFvMesh::~staticFvMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::staticFvMesh::update()
{
	return false;
}


// ************************************************************************* //