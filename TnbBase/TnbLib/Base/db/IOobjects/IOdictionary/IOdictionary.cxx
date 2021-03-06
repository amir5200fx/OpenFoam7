#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOdictionary::IOdictionary(const IOobject& io)
	:
	baseIOdictionary(io)
{
	readHeaderOk(IOstream::ASCII, typeName);

	// For if MUST_READ_IF_MODIFIED
	addWatch();
}


tnbLib::IOdictionary::IOdictionary
(
	const IOobject& io,
	const dictionary& dict
)
	:
	baseIOdictionary(io, dict)
{
	if (!readHeaderOk(IOstream::ASCII, typeName))
	{
		dictionary::operator=(dict);
	}

	// For if MUST_READ_IF_MODIFIED
	addWatch();
}


tnbLib::IOdictionary::IOdictionary
(
	const IOobject& io,
	Istream& is
)
	:
	baseIOdictionary(io, is)
{
	// Note that we do construct the dictionary null and read in
	// afterwards
	// so that if there is some fancy massaging due to a
	// functionEntry in
	// the dictionary at least the type information is already complete.
	is >> *this;

	// For if MUST_READ_IF_MODIFIED
	addWatch();
}


tnbLib::IOdictionary::IOdictionary
(
	const IOdictionary& dict
)
	:
	baseIOdictionary(dict)
{}


tnbLib::IOdictionary::IOdictionary
(
	IOdictionary&& dict
)
	:
	baseIOdictionary(move(dict))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::IOdictionary::~IOdictionary()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::IOdictionary::operator=(IOdictionary&& rhs)
{
	baseIOdictionary::operator=(move(rhs));
}


// ************************************************************************* //