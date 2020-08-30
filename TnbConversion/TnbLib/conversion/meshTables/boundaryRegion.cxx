#include <boundaryRegion.hxx>

#include <IOMap.hxx>
#include <OFstream.hxx>
#include <stringListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boundaryRegion::boundaryRegion()
	:
	Map<dictionary>()
{}


tnbLib::boundaryRegion::boundaryRegion
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
)
	:
	Map<dictionary>()
{
	readDict(registry, name, instance);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boundaryRegion::~boundaryRegion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::boundaryRegion::append(const dictionary& dict)
{
	label maxId = -1;
	forAllConstIter(Map<dictionary>, *this, iter)
	{
		if (maxId < iter.key())
		{
			maxId = iter.key();
		}
	}

	insert(++maxId, dict);
	return maxId;
}


tnbLib::Map<tnbLib::word> tnbLib::boundaryRegion::names() const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		lookup.insert
		(
			iter.key(),
			iter().lookupOrDefault<word>
			(
				"Label",
				"boundaryRegion_" + tnbLib::name(iter.key())
				)
		);
	}

	return lookup;
}


tnbLib::Map<tnbLib::word> tnbLib::boundaryRegion::names
(
	const UList<wordRe>& patterns
) const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		word lookupName = iter().lookupOrDefault<word>
			(
				"Label",
				"boundaryRegion_" + tnbLib::name(iter.key())
				);

		if (findStrings(patterns, lookupName))
		{
			lookup.insert(iter.key(), lookupName);
		}
	}

	return lookup;
}


tnbLib::Map<tnbLib::word> tnbLib::boundaryRegion::boundaryTypes() const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		lookup.insert
		(
			iter.key(),
			iter().lookupOrDefault<word>("BoundaryType", "patch")
		);
	}

	return lookup;
}


tnbLib::label tnbLib::boundaryRegion::findIndex(const word& name) const
{
	if (name.empty())
	{
		return -1;
	}

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		if (iter().lookupOrDefault<word>("Label", word::null) == name)
		{
			return iter.key();
		}
	}

	return -1;
}


tnbLib::word tnbLib::boundaryRegion::boundaryType(const word& name) const
{
	word bndType("patch");

	label id = this->findIndex(name);
	if (id >= 0)
	{
		operator[](id).readIfPresent<word>("BoundaryType", bndType);
	}

	return bndType;
}


void tnbLib::boundaryRegion::readDict
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
)
{
	clear();

	// read constant/dictName
	IOMap<dictionary> ioObj
	(
		IOobject
		(
			name,
			instance,
			registry,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE,
			false
		)
	);

	if (ioObj.headerOk())
	{
		*this = ioObj;
	}
	else
	{
		Info << "no constant/boundaryRegion information available" << endl;
	}
}


void tnbLib::boundaryRegion::writeDict
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
) const
{
	// write constant/dictName
	IOMap<dictionary> ioObj
	(
		IOobject
		(
			name,
			instance,
			registry,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	ioObj.note() =
		"persistent data for thirdParty mesh <-> OpenFOAM translation";

	Info << "Writing " << ioObj.name() << " to " << ioObj.objectPath() << endl;

	OFstream os(ioObj.objectPath());
	ioObj.writeHeader(os);
	os << *this;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::boundaryRegion::operator=(const boundaryRegion& rhs)
{
	Map<dictionary>::operator=(rhs);
}


void tnbLib::boundaryRegion::operator=(const Map<dictionary>& rhs)
{
	Map<dictionary>::operator=(rhs);
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

void tnbLib::boundaryRegion::rename(const dictionary& mapDict)
{
	if (mapDict.empty())
	{
		return;
	}

	// Use 1st pass to collect all the regions to be changed
	// and 2nd pass to relabel regions.
	// This avoid re-matching any renamed regions

	Map<word> mapping;
	forAllConstIter(dictionary, mapDict, iter)
	{
		word oldName(iter().stream());

		label id = this->findIndex(oldName);
		if (id >= 0)
		{
			mapping.insert(id, iter().keyword());
		}
	}

	forAllConstIter(Map<word>, mapping, iter)
	{
		dictionary& dict = operator[](iter.key());

		Info << "rename patch: " << iter()
			<< " <- " << word(dict.lookup("Label")) << nl;

		dict.set("Label", iter());
	}
}


// ************************************************************************* //