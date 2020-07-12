#include <edgeMeshFormatsCore.hxx>

#include <Time.hxx>
#include <IFstream.hxx>
#include <OFstream.hxx>
#include <edgeMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::word tnbLib::fileFormats::edgeMeshFormatsCore::nativeExt("eMesh");


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::string tnbLib::fileFormats::edgeMeshFormatsCore::getLineNoComment
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
tnbLib::fileName tnbLib::fileFormats::edgeMeshFormatsCore::localMeshFileName
(
	const word& meshName
)
{
	const word name(meshName.size() ? meshName : surfaceRegistry::defaultName);

	return fileName
	(
		surfaceRegistry::prefix / name / surfMesh::meshSubDir
		/ name + "." + nativeExt
	);
}


tnbLib::fileName tnbLib::fileFormats::edgeMeshFormatsCore::findMeshInstance
(
	const Time& t,
	const word& meshName
)
{
	fileName localName = localMeshFileName(meshName);

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


tnbLib::fileName tnbLib::fileFormats::edgeMeshFormatsCore::findMeshFile
(
	const Time& t,
	const word& meshName
)
{
	fileName localName = localMeshFileName(meshName);

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


bool tnbLib::fileFormats::edgeMeshFormatsCore::checkSupport
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
		wordList known = available.sortedToc();

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

tnbLib::fileFormats::edgeMeshFormatsCore::edgeMeshFormatsCore()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileFormats::edgeMeshFormatsCore::~edgeMeshFormatsCore()
{}


// ************************************************************************* //