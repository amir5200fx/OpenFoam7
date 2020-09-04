#include <extendedEdgeMeshFormat.hxx>

#include <IFstream.hxx>
#include <Time.hxx>
#include <extendedFeatureEdgeMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::extendedEdgeMeshFormat::extendedEdgeMeshFormat
(
	const fileName& filename
)
{
	read(filename);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileFormats::extendedEdgeMeshFormat::read
(
	const fileName& filename
)
{
	clear();

	fileName dir = filename.path();
	fileName caseName = dir.name();
	fileName rootPath = dir.path();

	// Construct dummy time to use as an objectRegistry
	Time dummyTime
	(
		".",        // rootPath,
		".",        // caseName,
		"system",   // systemName,
		"constant", // constantName,
		false       // enableFunctionObjects
	);

	// Construct IOobject to re-use the headerOk & readHeader
	// (so we can read ascii and binary)
	IOobject io
	(
		filename,
		dummyTime,
		IOobject::NO_READ,
		IOobject::NO_WRITE,
		false
	);

	if (!io.typeHeaderOk<extendedFeatureEdgeMesh>(false))
	{
		FatalErrorInFunction
			<< "Cannot read file " << filename
			<< exit(FatalError);
	}

	const fileName fName(typeFilePath<extendedFeatureEdgeMesh>(io));

	autoPtr<IFstream> isPtr(new IFstream(fName));
	bool ok = false;
	if (isPtr().good())
	{
		Istream& is = isPtr();
		ok = io.readHeader(is);

		if (ok)
		{
			// Use extendedEdgeMesh IO
			is >> *this;
			ok = is.good();
		}
	}

	return ok;
}


// ************************************************************************* //