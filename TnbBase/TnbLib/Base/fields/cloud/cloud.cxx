#include <cloud.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cloud, 0);

	const word cloud::prefix("lagrangian");
	word cloud::defaultName("defaultCloud");
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cloud::cloud(const objectRegistry& obr, const word& cloudName)
	:
	objectRegistry
	(
		IOobject
		(
			cloudName,
			obr.time().timeName(),
			prefix,
			obr,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cloud::~cloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cloud::autoMap(const mapPolyMesh&)
{
	NotImplemented;
}


// ************************************************************************* //