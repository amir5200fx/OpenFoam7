#include <proxySurfaceWriter.hxx>

#include <MeshedSurfaceProxy.hxx>
#include <makeSurfaceWriterMethods.hxx>

#include <OSspecific.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(proxySurfaceWriter, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::proxySurfaceWriter::proxySurfaceWriter(const word& ext)
	:
	surfaceWriter(),
	ext_(ext)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::proxySurfaceWriter::~proxySurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::proxySurfaceWriter::write
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const bool verbose
) const
{
	// avoid bad values
	if (ext_.empty())
	{
		return;
	}

	if (!isDir(outputDir))
	{
		mkDir(outputDir);
	}

	fileName outName(outputDir / surfaceName + "." + ext_);

	if (verbose)
	{
		Info << "Writing geometry to " << outName << endl;
	}

	MeshedSurfaceProxy<face>(points, faces).write(outName);
}


// ************************************************************************* //