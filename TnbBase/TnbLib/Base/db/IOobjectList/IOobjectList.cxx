#include <IOobjectList.hxx>

#include <Time.hxx>
#include <OSspecific.hxx>
#include <IOList.hxx>

//- added by amir
#include <wordReListMatcher.hxx>
#include <fileOperation.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOobjectList::IOobjectList(const label nIoObjects)
	:
	HashPtrTable<IOobject>(nIoObjects)
{}


tnbLib::IOobjectList::IOobjectList
(
	const objectRegistry& db,
	const fileName& instance,
	const fileName& local,
	IOobject::readOption r,
	IOobject::writeOption w,
	bool registerObject
)
	:
	HashPtrTable<IOobject>()
{
	word newInstance;
	fileNameList ObjectNames = fileHandler().readObjects
	(
		db,
		instance,
		local,
		newInstance
	);


	forAll(ObjectNames, i)
	{
		IOobject* objectPtr = new IOobject
		(
			ObjectNames[i],
			newInstance,
			local,
			db,
			r,
			w,
			registerObject
		);

		// Use object with local scope
		if (objectPtr->typeHeaderOk<IOList<label>>(false))
		{
			insert(ObjectNames[i], objectPtr);
		}
		else
		{
			delete objectPtr;
		}
	}
}


tnbLib::IOobjectList::IOobjectList(const IOobjectList& ioOL)
	:
	HashPtrTable<IOobject>(ioOL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::IOobjectList::~IOobjectList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::IOobjectList::add(IOobject& io)
{
	return insert(io.name(), &io);
}


bool tnbLib::IOobjectList::remove(IOobject& io)
{
	HashPtrTable<IOobject>::iterator iter =
		HashPtrTable<IOobject>::find(io.name());

	if (iter != end())
	{
		return erase(iter);
	}
	else
	{
		return false;
	}
}


tnbLib::IOobject* tnbLib::IOobjectList::lookup(const word& name) const
{
	HashPtrTable<IOobject>::const_iterator iter = find(name);

	if (iter != end())
	{
		if (IOobject::debug)
		{
			InfoInFunction << "Found " << name << endl;
		}

		return const_cast<IOobject*>(*iter);
	}
	else
	{
		if (IOobject::debug)
		{
			InfoInFunction << "Could not find " << name << endl;
		}

		return nullptr;
	}
}


tnbLib::IOobjectList tnbLib::IOobjectList::lookup(const wordRe& name) const
{
	IOobjectList objectsOfName(size());

	forAllConstIter(HashPtrTable<IOobject>, *this, iter)
	{
		if (name.match(iter()->name()))
		{
			if (IOobject::debug)
			{
				InfoInFunction << "Found " << iter.key() << endl;
			}

			objectsOfName.insert(iter.key(), new IOobject(*iter()));
		}
	}

	return objectsOfName;
}


tnbLib::IOobjectList tnbLib::IOobjectList::lookup(const wordReList& patterns) const
{
	wordReListMatcher names(patterns);

	IOobjectList objectsOfName(size());

	forAllConstIter(HashPtrTable<IOobject>, *this, iter)
	{
		if (names.match(iter()->name()))
		{
			if (IOobject::debug)
			{
				InfoInFunction << "Found " << iter.key() << endl;
			}

			objectsOfName.insert(iter.key(), new IOobject(*iter()));
		}
	}

	return objectsOfName;
}


tnbLib::IOobjectList tnbLib::IOobjectList::lookupClass(const word& ClassName) const
{
	IOobjectList objectsOfClass(size());

	forAllConstIter(HashPtrTable<IOobject>, *this, iter)
	{
		if (iter()->headerClassName() == ClassName)
		{
			if (IOobject::debug)
			{
				InfoInFunction << "Found " << iter.key() << endl;
			}

			objectsOfClass.insert(iter.key(), new IOobject(*iter()));
		}
	}

	return objectsOfClass;
}


tnbLib::wordList tnbLib::IOobjectList::names() const
{
	return HashPtrTable<IOobject>::toc();
}


tnbLib::wordList tnbLib::IOobjectList::sortedNames() const
{
	return HashPtrTable<IOobject>::sortedToc();
}


tnbLib::wordList tnbLib::IOobjectList::names(const word& ClassName) const
{
	wordList objectNames(size());

	label count = 0;
	forAllConstIter(HashPtrTable<IOobject>, *this, iter)
	{
		if (iter()->headerClassName() == ClassName)
		{
			objectNames[count++] = iter.key();
		}
	}

	objectNames.setSize(count);

	return objectNames;
}


tnbLib::wordList tnbLib::IOobjectList::sortedNames(const word& ClassName) const
{
	wordList sortedLst = names(ClassName);
	sort(sortedLst);

	return sortedLst;
}


// ************************************************************************* //