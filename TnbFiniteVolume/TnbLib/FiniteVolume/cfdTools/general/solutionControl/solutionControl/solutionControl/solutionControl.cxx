#include <solutionControl.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solutionControl, 0);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::solutionControl::writeData(Ostream&) const
{
	NotImplemented;
	return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solutionControl::solutionControl
(
	const objectRegistry& registry,
	const Time& time,
	const word& algorithmName
)
	:
	regIOobject
	(
		tnbLib::IOobject
		(
			typeName,
			time.timeName(),
			registry,
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::NO_WRITE
		)
	),
	time_(time),
	algorithmName_(algorithmName),
	algorithmSpaceStr_(algorithmName.size(), ' ')
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solutionControl::~solutionControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::solutionControl::read()
{
	return true;
}


// ************************************************************************* //