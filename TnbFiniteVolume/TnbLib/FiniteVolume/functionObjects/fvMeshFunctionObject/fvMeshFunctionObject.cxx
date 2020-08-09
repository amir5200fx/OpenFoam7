#include <fvMeshFunctionObject.hxx>

#include <Time.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fvMeshFunctionObject, 0);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fvMeshFunctionObject::fvMeshFunctionObject
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	regionFunctionObject(name, runTime, dict),
	mesh_(refCast<const fvMesh>(obr_))
{}


tnbLib::functionObjects::fvMeshFunctionObject::fvMeshFunctionObject
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	regionFunctionObject(name, obr, dict),
	mesh_(refCast<const fvMesh>(obr_))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fvMeshFunctionObject::~fvMeshFunctionObject()
{}


// ************************************************************************* //