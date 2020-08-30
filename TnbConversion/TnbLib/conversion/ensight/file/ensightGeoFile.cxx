#include <ensightGeoFile.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ensightGeoFile::ensightGeoFile
(
	const fileName& pathname,
	IOstream::streamFormat format
)
	:
	ensightFile(pathname, format)
{
	writeBinaryHeader();
	write("Ensight Geometry File");  newline();
	write("=====================");  newline();
	write("node id assign");         newline();
	write("element id assign");      newline();
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ensightGeoFile::~ensightGeoFile()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::ensightGeoFile::writeKeyword(const string& key)
{
	write(key);
	newline();

	return *this;
}


// ************************************************************************* //