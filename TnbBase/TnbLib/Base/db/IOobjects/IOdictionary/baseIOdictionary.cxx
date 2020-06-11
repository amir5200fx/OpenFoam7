#include <baseIOdictionary.hxx>

#include <objectRegistry.hxx>
#include <Pstream.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(baseIOdictionary, 0);

	bool baseIOdictionary::writeDictionaries
	(
		debug::infoSwitch("writeDictionaries", 0)
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::baseIOdictionary::baseIOdictionary(const IOobject& io)
	:
	regIOobject(io)
{
	dictionary::name() = IOobject::objectPath();
}


tnbLib::baseIOdictionary::baseIOdictionary
(
	const IOobject& io,
	const dictionary& dict
)
	:
	regIOobject(io)
{
	dictionary::name() = IOobject::objectPath();
}


tnbLib::baseIOdictionary::baseIOdictionary
(
	const IOobject& io,
	Istream& is
)
	:
	regIOobject(io)
{
	dictionary::name() = IOobject::objectPath();
}


tnbLib::baseIOdictionary::baseIOdictionary(const baseIOdictionary& dict)
	:
	regIOobject(dict),
	dictionary(dict)
{}


tnbLib::baseIOdictionary::baseIOdictionary(baseIOdictionary&& dict)
	:
	regIOobject(move(dict)),
	dictionary(move(dict))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::baseIOdictionary::~baseIOdictionary()
{}


// * * * * * * * * * * * * * * * Members Functions * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::baseIOdictionary::name() const
{
	return regIOobject::name();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::baseIOdictionary::operator=(const baseIOdictionary& rhs)
{
	dictionary::operator=(rhs);
}


void tnbLib::baseIOdictionary::operator=(baseIOdictionary&& rhs)
{
	dictionary::operator=(move(rhs));
}


// ************************************************************************* //