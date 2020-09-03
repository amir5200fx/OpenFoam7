#include <MeshObject.hxx>

#include <IOstreams.hxx>

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(meshObject, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshObject::meshObject(const word& typeName, const objectRegistry& obr)
	:
	regIOobject
	(
		IOobject
		(
			typeName,
			obr.instance(),
			obr
		)
	)
{}


// ************************************************************************* //

