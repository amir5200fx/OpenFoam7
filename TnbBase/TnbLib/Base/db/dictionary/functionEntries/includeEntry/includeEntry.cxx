#include <includeEntry.hxx>

#include <dictionary.hxx>
#include <IFstream.hxx>
#include <addToMemberFunctionSelectionTable.hxx>
#include <stringOps.hxx>
#include <IOstreams.hxx>
#include <fileOperation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::includeEntry::typeName
(
	tnbLib::functionEntries::includeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeEntry
int tnbLib::functionEntries::includeEntry::debug(0);

bool tnbLib::functionEntries::includeEntry::log(false);


namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEntry,
			execute,
			primitiveEntryIstream
		);
	}
}

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

tnbLib::fileName tnbLib::functionEntries::includeEntry::includeFileName
(
	Istream& is,
	const dictionary& dict
)
{
	fileName fName(is);
	// Substitute dictionary and environment variables. Allow empty
	// substitutions.
	stringOps::inplaceExpand(fName, dict, true, true);

	if (fName.empty() || fName.isAbsolute())
	{
		return fName;
	}
	else
	{
		// relative name
		return fileName(is.name()).path() / fName;
	}
}


tnbLib::fileName tnbLib::functionEntries::includeEntry::includeFileName
(
	const fileName& dir,
	const fileName& f,
	const dictionary& dict
)
{
	fileName fName(f);
	// Substitute dictionary and environment variables. Allow empty
	// substitutions.
	stringOps::inplaceExpand(fName, dict, true, true);

	if (fName.empty() || fName.isAbsolute())
	{
		return fName;
	}
	else
	{
		// relative name
		return dir / fName;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::includeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	const fileName rawFName(is);
	const fileName fName
	(
		includeFileName(is.name().path(), rawFName, parentDict)
	);

	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEntry::log)
		{
			Info << fName << endl;
		}

		// Cache the FoamFile entry if present
		dictionary foamFileDict;
		if (parentDict.found("FoamFile"))
		{
			foamFileDict = parentDict.subDict("FoamFile");
		}

		// Read and clear the FoamFile entry
		parentDict.read(ifs);

		// Reinstate original FoamFile entry
		if (!foamFileDict.isNull())
		{
			dictionary parentDictTmp(parentDict);
			parentDict.clear();
			parentDict.add("FoamFile", foamFileDict);
			parentDict += parentDictTmp;
		}

		return true;
	}
	else
	{
		FatalIOErrorInFunction
		(
			is
		) << "Cannot open include file "
			<< (ifs.name().size() ? ifs.name() : rawFName)
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}


bool tnbLib::functionEntries::includeEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	const fileName rawFName(is);
	const fileName fName
	(
		includeFileName(is.name().path(), rawFName, parentDict)
	);

	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEntry::log)
		{
			Info << fName << endl;
		}
		entry.read(parentDict, ifs);
		return true;
	}
	else
	{
		FatalIOErrorInFunction
		(
			is
		) << "Cannot open include file "
			<< (ifs.name().size() ? ifs.name() : rawFName)
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}

// ************************************************************************* //