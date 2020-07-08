#include <surfaceFormatsCore.hxx>

#include <Time.hxx>
#include <IFstream.hxx>
#include <OFstream.hxx>
#include <SortableList.hxx>
#include <surfMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::word tnbLib::fileFormats::surfaceFormatsCore::nativeExt("ofs");

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::string tnbLib::fileFormats::surfaceFormatsCore::getLineNoComment
(
	IFstream& is
)
{
	string line;
	do
	{
		is.getLine(line);
	} while ((line.empty() || line[0] == '#') && is.good());

	return line;
}


#if 0
tnbLib::fileName tnbLib::fileFormats::surfaceFormatsCore::localMeshFileName
(
	const word& surfName
)
{
	const word name(surfName.size() ? surfName : surfaceRegistry::defaultName);

	return fileName
	(
		surfaceRegistry::prefix / name / surfMesh::meshSubDir
		/ name + "." + nativeExt
	);
}


tnbLib::fileName tnbLib::fileFormats::surfaceFormatsCore::findMeshInstance
(
	const Time& t,
	const word& surfName
)
{
	fileName localName = localMeshFileName(surfName);

	// Search back through the time directories list to find the time
	// closest to and lower than current time

	instantList ts = t.times();
	label instanceI;

	for (instanceI = ts.size() - 1; instanceI >= 0; --instanceI)
	{
		if (ts[instanceI].value() <= t.timeOutputValue())
		{
			break;
		}
	}

	// Noting that the current directory has already been searched
	// for mesh data, start searching from the previously stored time directory

	if (instanceI >= 0)
	{
		for (label i = instanceI; i >= 0; --i)
		{
			if (isFile(t.path() / ts[i].name() / localName))
			{
				return ts[i].name();
			}
		}
	}

	return t.constant();
}


tnbLib::fileName tnbLib::fileFormats::surfaceFormatsCore::findMeshFile
(
	const Time& t,
	const word& surfName
)
{
	fileName localName = localMeshFileName(surfName);

	// Search back through the time directories list to find the time
	// closest to and lower than current time

	instantList ts = t.times();
	label instanceI;

	for (instanceI = ts.size() - 1; instanceI >= 0; --instanceI)
	{
		if (ts[instanceI].value() <= t.timeOutputValue())
		{
			break;
		}
	}

	// Noting that the current directory has already been searched
	// for mesh data, start searching from the previously stored time directory

	if (instanceI >= 0)
	{
		for (label i = instanceI; i >= 0; --i)
		{
			fileName testName(t.path() / ts[i].name() / localName);

			if (isFile(testName))
			{
				return testName;
			}
		}
	}

	// fallback to "constant"
	return t.path() / t.constant() / localName;
}
#endif


bool tnbLib::fileFormats::surfaceFormatsCore::checkSupport
(
	const wordHashSet& available,
	const word& ext,
	const bool verbose,
	const word& functionName
)
{
	if (available.found(ext))
	{
		return true;
	}
	else if (verbose)
	{
		wordList toc = available.toc();
		SortableList<word> known(move(toc));

		Info << "Unknown file extension for " << functionName
			<< " : " << ext << nl
			<< "Valid types: (";
		// compact output:
		forAll(known, i)
		{
			Info << " " << known[i];
		}
		Info << " )" << endl;
	}

	return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::surfaceFormatsCore::surfaceFormatsCore()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileFormats::surfaceFormatsCore::~surfaceFormatsCore()
{}


// ************************************************************************* //