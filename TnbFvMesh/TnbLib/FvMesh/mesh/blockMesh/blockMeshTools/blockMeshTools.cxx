#include <blockMeshTools.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::blockMeshTools::read
(
	Istream& is,
	label& val,
	const dictionary& dict
)
{
	token t(is);
	if (t.isLabel())
	{
		val = t.labelToken();
	}
	else if (t.isWord())
	{
		const word& varName = t.wordToken();
		const entry* ePtr = dict.lookupScopedEntryPtr
		(
			varName,
			true,
			true
		);
		if (ePtr)
		{
			// Read as label
			val = tnbLib::readLabel(ePtr->stream());
		}
		else
		{
			FatalIOErrorInFunction(is)
				<< "Undefined variable "
				<< varName << ". Valid variables are " << dict
				<< exit(FatalIOError);
		}
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "Illegal token " << t.info()
			<< " when trying to read label"
			<< exit(FatalIOError);
	}

	is.fatalCheck
	(
		"operator>>(Istream&, List<T>&) : reading entry"
	);
}


tnbLib::label tnbLib::blockMeshTools::read
(
	Istream& is,
	const dictionary& dict
)
{
	label val;
	read(is, val, dict);
	return val;
}


void tnbLib::blockMeshTools::write
(
	Ostream& os,
	const label val,
	const dictionary& dict
)
{
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isStream())
		{
			label keyVal(tnbLib::readLabel(iter().stream()));
			if (keyVal == val)
			{
				os << iter().keyword();
				return;
			}
		}
	}
	os << val;
}


const tnbLib::keyType& tnbLib::blockMeshTools::findEntry
(
	const dictionary& dict,
	const label val
)
{
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isStream())
		{
			label keyVal(tnbLib::readLabel(iter().stream()));
			if (keyVal == val)
			{
				return iter().keyword();
			}
		}
	}

	return keyType::null;
}


// ************************************************************************* //