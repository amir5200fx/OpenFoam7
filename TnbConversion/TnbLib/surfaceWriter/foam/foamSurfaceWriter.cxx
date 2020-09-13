#include <foamSurfaceWriter.hxx>

#include <OFstream.hxx>
#include <OSspecific.hxx>
#include <makeSurfaceWriterMethods.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(foamSurfaceWriter);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::foamSurfaceWriter::writeTemplate
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const word& fieldName,
	const Field<Type>& values,
	const bool isNodeValues,
	const bool verbose
) const
{
	fileName surfaceDir(outputDir / surfaceName);

	if (!isDir(surfaceDir))
	{
		mkDir(surfaceDir);
	}

	if (verbose)
	{
		Info << "Writing field " << fieldName << " to " << surfaceDir << endl;
	}

	// geometry should already have been written
	// Values to separate directory (e.g. "scalarField/p")

	fileName foamName(pTraits<Type>::typeName);
	fileName valuesDir(surfaceDir / (foamName + Field<Type>::typeName));

	if (!isDir(valuesDir))
	{
		mkDir(valuesDir);
	}

	// values
	OFstream(valuesDir / fieldName)() << values;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::foamSurfaceWriter::foamSurfaceWriter()
	:
	surfaceWriter()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::foamSurfaceWriter::~foamSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::foamSurfaceWriter::write
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const bool verbose
) const
{
	fileName surfaceDir(outputDir / surfaceName);

	if (!isDir(surfaceDir))
	{
		mkDir(surfaceDir);
	}

	if (verbose)
	{
		Info << "Writing geometry to " << surfaceDir << endl;
	}


	// Points
	OFstream(surfaceDir / "points")() << points;

	// Faces
	OFstream(surfaceDir / "faces")() << faces;

	// Face centers. Not really necessary but very handy when reusing as inputs
	// for e.g. timeVaryingMapped bc.
	pointField faceCentres(faces.size(), point::zero);

	forAll(faces, facei)
	{
		faceCentres[facei] = faces[facei].centre(points);
	}

	OFstream(surfaceDir / "faceCentres")() << faceCentres;
}


// Create write methods
defineSurfaceWriterWriteFields(tnbLib::foamSurfaceWriter);


// ************************************************************************* //