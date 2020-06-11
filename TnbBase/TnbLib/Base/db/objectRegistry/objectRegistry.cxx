#include <objectRegistry.hxx>

#include <Time.hxx>
#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(objectRegistry, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::objectRegistry::parentNotTime() const
{
	return (&parent_ != dynamic_cast<const objectRegistry*>(&time_));
}


// * * * * * * * * * * * * * * * * Constructors *  * * * * * * * * * * * * * //

tnbLib::objectRegistry::objectRegistry
(
	const Time& t,
	const label nIoObjects
)
	:
	regIOobject
	(
		IOobject
		(
			string::validate<word>(t.caseName()),
			t.path(),
			t,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE,
			false
		),
		true    // to flag that this is the top-level regIOobject
	),
	HashTable<regIOobject*>(nIoObjects),
	time_(t),
	parent_(t),
	dbDir_(name()),
	event_(1)
{}


tnbLib::objectRegistry::objectRegistry
(
	const IOobject& io,
	const label nIoObjects
)
	:
	regIOobject(io),
	HashTable<regIOobject*>(nIoObjects),
	time_(io.time()),
	parent_(io.db()),
	dbDir_(parent_.dbDir() / local() / name()),
	event_(1)
{
	writeOpt() = IOobject::AUTO_WRITE;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::objectRegistry::~objectRegistry()
{
	clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::wordList tnbLib::objectRegistry::names() const
{
	return HashTable<regIOobject*>::toc();
}


tnbLib::wordList tnbLib::objectRegistry::sortedNames() const
{
	return HashTable<regIOobject*>::sortedToc();
}


tnbLib::wordList tnbLib::objectRegistry::names(const word& ClassName) const
{
	wordList objectNames(size());

	label count = 0;
	for (const_iterator iter = cbegin(); iter != cend(); ++iter)
	{
		if (iter()->type() == ClassName)
		{
			objectNames[count++] = iter.key();
		}
	}

	objectNames.setSize(count);

	return objectNames;
}


tnbLib::wordList tnbLib::objectRegistry::sortedNames(const word& ClassName) const
{
	wordList sortedLst = names(ClassName);
	sort(sortedLst);

	return sortedLst;
}


const tnbLib::objectRegistry& tnbLib::objectRegistry::subRegistry
(
	const word& name,
	const bool forceCreate
) const
{
	if (forceCreate && !foundObject<objectRegistry>(name))
	{
		objectRegistry* fieldsCachePtr = new objectRegistry
		(
			IOobject
			(
				name,
				time().constant(),
				*this,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			)
		);
		fieldsCachePtr->store();
	}
	return lookupObject<objectRegistry>(name);
}


tnbLib::label tnbLib::objectRegistry::getEvent() const
{
	label curEvent = event_++;

	if (event_ == labelMax)
	{
		if (objectRegistry::debug)
		{
			WarningInFunction
				<< "Event counter has overflowed. "
				<< "Resetting counter on all dependent objects." << nl
				<< "This might cause extra evaluations." << endl;
		}

		// Reset event counter
		curEvent = 1;
		event_ = 2;

		for (const_iterator iter = begin(); iter != end(); ++iter)
		{
			const regIOobject& io = *iter();

			if (objectRegistry::debug)
			{
				Pout << "objectRegistry::getEvent() : "
					<< "resetting count on " << iter.key() << endl;
			}

			if (io.eventNo() != 0)
			{
				const_cast<regIOobject&>(io).eventNo() = curEvent;
			}
		}
	}

	return curEvent;
}


bool tnbLib::objectRegistry::checkIn(regIOobject& io) const
{
	if (objectRegistry::debug)
	{
		Pout << "objectRegistry::checkIn(regIOobject&) : "
			<< name() << " : checking in " << io.name()
			<< " of type " << io.type()
			<< endl;
	}

	return const_cast<objectRegistry&>(*this).insert(io.name(), &io);
}


bool tnbLib::objectRegistry::checkOut(regIOobject& io) const
{
	iterator iter = const_cast<objectRegistry&>(*this).find(io.name());

	if (iter != end())
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::checkOut(regIOobject&) : "
				<< name() << " : checking out " << iter.key()
				<< endl;
		}

		if (iter() != &io)
		{
			if (objectRegistry::debug)
			{
				WarningInFunction
					<< name() << " : attempt to checkOut copy of "
					<< iter.key()
					<< endl;
			}

			return false;
		}
		else
		{
			regIOobject* object = iter();

			bool hasErased = const_cast<objectRegistry&>(*this).erase(iter);

			if (io.ownedByRegistry())
			{
				delete object;
			}

			return hasErased;
		}
	}
	else
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::checkOut(regIOobject&) : "
				<< name() << " : could not find " << io.name()
				<< " in registry " << name()
				<< endl;
		}
	}

	return false;
}


void tnbLib::objectRegistry::clear()
{
	List<regIOobject*> myObjects(size());
	label nMyObjects = 0;

	for (iterator iter = begin(); iter != end(); ++iter)
	{
		if (iter()->ownedByRegistry())
		{
			myObjects[nMyObjects++] = iter();
		}
	}

	for (label i = 0; i < nMyObjects; i++)
	{
		checkOut(*myObjects[i]);
	}
}


void tnbLib::objectRegistry::rename(const word& newName)
{
	regIOobject::rename(newName);

	// adjust dbDir_ as well
	string::size_type i = dbDir_.rfind('/');

	if (i == string::npos)
	{
		dbDir_ = newName;
	}
	else
	{
		dbDir_.replace(i + 1, string::npos, newName);
	}
}


bool tnbLib::objectRegistry::modified() const
{
	forAllConstIter(HashTable<regIOobject*>, *this, iter)
	{
		if (iter()->modified())
		{
			return true;
		}
	}

	return false;
}


void tnbLib::objectRegistry::readModifiedObjects()
{
	for (iterator iter = begin(); iter != end(); ++iter)
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::readModifiedObjects() : "
				<< name() << " : Considering reading object "
				<< iter.key() << endl;
		}

		iter()->readIfModified();
	}
}


bool tnbLib::objectRegistry::readIfModified()
{
	readModifiedObjects();
	return true;
}


bool tnbLib::objectRegistry::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp,
	const bool write
) const
{
	bool ok = true;

	forAllConstIter(HashTable<regIOobject*>, *this, iter)
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::write() : "
				<< name() << " : Considering writing object "
				<< iter.key()
				<< " of type " << iter()->type()
				<< " with writeOpt " << iter()->writeOpt()
				<< " to file " << iter()->objectPath()
				<< endl;
		}

		if (iter()->writeOpt() != NO_WRITE)
		{
			ok = iter()->writeObject(fmt, ver, cmp, write) && ok;
		}
	}

	return ok;
}


// ************************************************************************* //