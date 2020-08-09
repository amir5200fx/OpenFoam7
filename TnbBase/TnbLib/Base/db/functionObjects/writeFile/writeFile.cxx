#include <writeFile.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>

#include <Pstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionObjects::writeFile::outputPrefix
(
	"postProcessing"
);

tnbLib::label tnbLib::functionObjects::writeFile::addChars = 8;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::writeFile::initStream(Ostream& os) const
{
	os.setf(ios_base::scientific, ios_base::floatfield);
	os.width(charWidth());
}


tnbLib::fileName tnbLib::functionObjects::writeFile::baseFileDir() const
{
	fileName baseDir = fileObr_.time().path();

	if (Pstream::parRun())
	{
		// Put in undecomposed case (Note: gives problems for
		// distributed data running)
		baseDir = baseDir / ".." / outputPrefix;
	}
	else
	{
		baseDir = baseDir / outputPrefix;
	}

	// Append mesh name if not default region
	if (isA<polyMesh>(fileObr_))
	{
		const polyMesh& mesh = refCast<const polyMesh>(fileObr_);
		if (mesh.name() != polyMesh::defaultRegion)
		{
			baseDir = baseDir / mesh.name();
		}
	}

	// Remove any ".."
	baseDir.clean();

	return baseDir;
}


tnbLib::fileName tnbLib::functionObjects::writeFile::baseTimeDir() const
{
	return baseFileDir() / prefix_ / fileObr_.time().timeName();
}


tnbLib::Omanip<int> tnbLib::functionObjects::writeFile::valueWidth
(
	const label offset
) const
{
	return setw(IOstream::defaultPrecision() + addChars + offset);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeFile::writeFile
(
	const objectRegistry& obr,
	const word& prefix
)
	:
	fileObr_(obr),
	prefix_(prefix)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeFile::~writeFile()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::functionObjects::writeFile::charWidth() const
{
	return IOstream::defaultPrecision() + addChars;
}


void tnbLib::functionObjects::writeFile::writeCommented
(
	Ostream& os,
	const string& str
) const
{
	os << setw(1) << "#" << setw(1) << ' '
		<< setf(ios_base::left) << setw(charWidth() - 2) << str.c_str();
}


void tnbLib::functionObjects::writeFile::writeTabbed
(
	Ostream& os,
	const string& str
) const
{
	os << tab << setw(charWidth()) << str.c_str();
}


void tnbLib::functionObjects::writeFile::writeHeader
(
	Ostream& os,
	const string& str
) const
{
	os << setw(1) << "#" << setw(1) << ' '
		<< setf(ios_base::left) << setw(charWidth() - 2) << str.c_str() << nl;
}


void tnbLib::functionObjects::writeFile::writeTime(Ostream& os) const
{
	os << setw(charWidth()) << fileObr_.time().timeName();
}


// ************************************************************************* //