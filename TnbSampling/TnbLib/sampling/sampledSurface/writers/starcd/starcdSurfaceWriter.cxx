#include <starcdSurfaceWriter.hxx>

#include <MeshedSurfaceProxy.hxx>
#include <makeSurfaceWriterMethods.hxx>

#include <OSspecific.hxx>  // added by amir
#include <OFstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(starcdSurfaceWriter);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	inline void tnbLib::starcdSurfaceWriter::writeData
	(
		Ostream& os,
		const scalar& v
	)
	{
		os << v << nl;
	}


	template<>
	inline void tnbLib::starcdSurfaceWriter::writeData
	(
		Ostream& os,
		const vector& v
	)
	{
		os << v[0] << ' ' << v[1] << ' ' << v[2] << nl;
	}


	template<>
	inline void tnbLib::starcdSurfaceWriter::writeData
	(
		Ostream& os,
		const sphericalTensor& v
	)
	{
		os << v[0] << nl;
	}

}


template<class Type>
inline void tnbLib::starcdSurfaceWriter::writeData
(
	Ostream& os,
	const Type& v
)
{}


template<class Type>
void tnbLib::starcdSurfaceWriter::writeTemplate
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
	if (!isDir(outputDir))
	{
		mkDir(outputDir);
	}

	OFstream os(outputDir / fieldName + '_' + surfaceName + ".usr");

	if (verbose)
	{
		Info << "Writing field " << fieldName << " to " << os.name() << endl;
	}

	// no header, just write values
	forAll(values, elemI)
	{
		os << elemI + 1 << ' ';
		writeData(os, values[elemI]);
	}
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::starcdSurfaceWriter::starcdSurfaceWriter()
	:
	surfaceWriter()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::starcdSurfaceWriter::~starcdSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::starcdSurfaceWriter::write
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const bool verbose
) const
{
	if (!isDir(outputDir))
	{
		mkDir(outputDir);
	}

	fileName outName(outputDir / surfaceName + ".inp");

	if (verbose)
	{
		Info << "Writing geometry to " << outName << endl;
	}

	MeshedSurfaceProxy<face>(points, faces).write(outName);
}


// create write methods
defineSurfaceWriterWriteField(tnbLib::starcdSurfaceWriter, scalar);
defineSurfaceWriterWriteField(tnbLib::starcdSurfaceWriter, vector);
defineSurfaceWriterWriteField(tnbLib::starcdSurfaceWriter, sphericalTensor);


// ************************************************************************* //