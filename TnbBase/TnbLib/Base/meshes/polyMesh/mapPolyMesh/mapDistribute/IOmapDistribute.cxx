#include <IOmapDistribute.hxx>

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(IOmapDistribute, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOmapDistribute::IOmapDistribute(const IOobject& io)
	:
	regIOobject(io)
{
	// Temporary warning
	if (io.readOpt() == IOobject::MUST_READ_IF_MODIFIED)
	{
		WarningInFunction
			<< "IOmapDistribute " << name()
			<< " constructed with IOobject::MUST_READ_IF_MODIFIED"
			" but IOmapDistribute does not support automatic rereading."
			<< endl;
	}

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
}


tnbLib::IOmapDistribute::IOmapDistribute
(
	const IOobject& io,
	const mapDistribute& map
)
	:
	regIOobject(io)
{
	// Temporary warning
	if (io.readOpt() == IOobject::MUST_READ_IF_MODIFIED)
	{
		WarningInFunction
			<< "IOmapDistribute " << name()
			<< " constructed with IOobject::MUST_READ_IF_MODIFIED"
			" but IOmapDistribute does not support automatic rereading."
			<< endl;
	}

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
	else
	{
		mapDistribute::operator=(map);
	}
}


tnbLib::IOmapDistribute::IOmapDistribute
(
	const IOobject& io,
	mapDistribute&& map
)
	:
	regIOobject(io),
	mapDistribute(move(map))
{
	// Temporary warning
	if (io.readOpt() == IOobject::MUST_READ_IF_MODIFIED)
	{
		WarningInFunction
			<< "IOmapDistribute " << name()
			<< " constructed with IOobject::MUST_READ_IF_MODIFIED"
			" but IOmapDistribute does not support automatic rereading."
			<< endl;
	}

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::IOmapDistribute::~IOmapDistribute()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::IOmapDistribute::readData(Istream& is)
{
	return (is >> *this).good();
}


bool tnbLib::IOmapDistribute::writeData(Ostream& os) const
{
	return (os << *this).good();
}


// ************************************************************************* //