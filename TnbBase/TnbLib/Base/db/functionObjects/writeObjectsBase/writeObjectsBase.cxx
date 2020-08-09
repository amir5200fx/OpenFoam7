#include <writeObjectsBase.hxx>

#include <Time.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::writeObjectsBase::resetWriteObjectName
(
	const wordRe& name
)
{
	writeObjectNames_.clear();
	writeObjectNames_.append(name);
}


void tnbLib::functionObjects::writeObjectsBase::resetWriteObjectNames
(
	const wordReList& names
)
{
	writeObjectNames_.clear();
	writeObjectNames_.append(names);
}


tnbLib::wordList tnbLib::functionObjects::writeObjectsBase::objectNames()
{
	DynamicList<word> allNames(writeObr_.toc().size());
	forAll(writeObjectNames_, i)
	{
		wordList names(writeObr_.names<regIOobject>(writeObjectNames_[i]));

		if (names.size())
		{
			allNames.append(names);
		}
		else
		{
			WarningInFunction
				<< "Object " << writeObjectNames_[i] << " not found in "
				<< "database. Available objects:" << nl << writeObr_.sortedToc()
				<< endl;
		}
	}

	return move(allNames);
}


void tnbLib::functionObjects::writeObjectsBase::writeObject
(
	const regIOobject& obj
)
{
	if (log_) Info << "    writing object " << obj.name() << endl;

	obj.write();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeObjectsBase::writeObjectsBase
(
	const objectRegistry& obr,
	const Switch& log
)
	:
	writeObr_(obr),
	log_(log)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeObjectsBase::~writeObjectsBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::wordReList&
tnbLib::functionObjects::writeObjectsBase::writeObjectNames() const
{
	return writeObjectNames_;
}


bool tnbLib::functionObjects::writeObjectsBase::read(const dictionary& dict)
{
	dict.lookup("objects") >> writeObjectNames_;

	return true;
}


bool tnbLib::functionObjects::writeObjectsBase::write()
{
	wordList names(objectNames());

	if (!names.empty())
	{
		if (!writeObr_.time().writeTime())
		{
			writeObr_.time().writeTimeDict();
		}

		forAll(names, i)
		{
			const regIOobject& obj =
				writeObr_.lookupObject<regIOobject>(names[i]);

			writeObject(obj);
		}
	}

	return true;
}


// ************************************************************************* //