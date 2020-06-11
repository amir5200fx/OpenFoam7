#include <unwatchedIOdictionary.hxx>

#include <objectRegistry.hxx>
#include <Pstream.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::unwatchedIOdictionary::unwatchedIOdictionary(const IOobject& io)
	:
	baseIOdictionary(io)
{
	readHeaderOk(IOstream::ASCII, typeName);

	// For if MUST_READ_IF_MODIFIED
	addWatch();
}


tnbLib::unwatchedIOdictionary::unwatchedIOdictionary
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


tnbLib::unwatchedIOdictionary::unwatchedIOdictionary
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


tnbLib::unwatchedIOdictionary::unwatchedIOdictionary
(
	unwatchedIOdictionary&& dict
)
	:
	baseIOdictionary(move(dict)),
	files_(move(dict.files_))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::unwatchedIOdictionary::~unwatchedIOdictionary()
{}


// * * * * * * * * * * * * * * * Members Functions * * * * * * * * * * * * * //

tnbLib::label tnbLib::unwatchedIOdictionary::addWatch(const fileName& f)
{
	label index = -1;

	if (readOpt() == MUST_READ_IF_MODIFIED)
	{
		index = findIndex(files_, f);

		if (index == -1)
		{
			index = files_.size();
			files_.append(f);
		}
	}
	return index;
}


void tnbLib::unwatchedIOdictionary::addWatch()
{
	if (readOpt() == MUST_READ_IF_MODIFIED)
	{
		fileName f = filePath();
		if (!f.size())
		{
			// We don't have this file but would like to re-read it.
			// Possibly if master-only reading mode.
			f = objectPath();
		}

		if (findIndex(files_, f) != -1)
		{
			FatalErrorIn("regIOobject::addWatch()")
				<< "Object " << objectPath() << " of type " << type()
				<< " already watched" << abort(FatalError);
		}

		// If master-only reading only the master will have all dependencies
		// so scatter these to slaves
		bool masterOnly =
			global()
			&& (
				regIOobject::fileModificationChecking == timeStampMaster
				|| regIOobject::fileModificationChecking == inotifyMaster
				);

		if (masterOnly && Pstream::parRun())
		{
			Pstream::scatter(files_);
		}

		addWatch(f);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::unwatchedIOdictionary::operator=(unwatchedIOdictionary&& rhs)
{
	baseIOdictionary::operator=(move(rhs));
	files_ = move(rhs.files_);
}


// ************************************************************************* //