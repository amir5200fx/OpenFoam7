#include <includeEtcEntry.hxx>

#include <etcFiles.hxx>
#include <stringOps.hxx>
#include <addToMemberFunctionSelectionTable.hxx>
#include <IOstreams.hxx>
#include <fileOperation.hxx>

#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::includeEtcEntry::typeName
(
	tnbLib::functionEntries::includeEtcEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeEtcEntry
int tnbLib::functionEntries::includeEtcEntry::debug(0);

bool tnbLib::functionEntries::includeEtcEntry::log(false);


namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEtcEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeEtcEntry,
			execute,
			primitiveEntryIstream
		);
	}
}

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

tnbLib::fileName tnbLib::functionEntries::includeEtcEntry::includeEtcFileName
(
	const fileName& f,
	const dictionary& dict
)
{
	fileName fName(f);

	// Substitute dictionary and environment variables.
	// Allow empty substitutions.
	stringOps::inplaceExpand(fName, dict, true, true);

	if (fName.empty() || fName.isAbsolute())
	{
		return fName;
	}
	else
	{
		// Search the etc directories for the file
		return findEtcFile(fName);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::includeEtcEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	const fileName rawFName(is);
	const fileName fName
	(
		includeEtcFileName(rawFName, parentDict)
	);

	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEtcEntry::log)
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
		) << "Cannot open etc file "
			<< (ifs.name().size() ? ifs.name() : rawFName)
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}


bool tnbLib::functionEntries::includeEtcEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	const fileName rawFName(is);
	const fileName fName
	(
		includeEtcFileName(rawFName, parentDict)
	);

	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEtcEntry::log)
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
		) << "Cannot open etc file "
			<< (ifs.name().size() ? ifs.name() : rawFName)
			<< " while reading dictionary " << parentDict.name()
			<< exit(FatalIOError);

		return false;
	}
}


// ************************************************************************* //