#include <surfaceRegistry.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceRegistry, 0);
}


const tnbLib::word tnbLib::surfaceRegistry::prefix("surfaces");
tnbLib::word tnbLib::surfaceRegistry::defaultName("default");


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceRegistry::surfaceRegistry
(
	const objectRegistry& obr,
	const word& surfName
)
	:
	objectRegistry
	(
		IOobject
		(
		(surfName.size() ? surfName : defaultName),
			obr.time().timeName(),
			prefix,
			obr,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceRegistry::~surfaceRegistry()
{}


// ************************************************************************* //