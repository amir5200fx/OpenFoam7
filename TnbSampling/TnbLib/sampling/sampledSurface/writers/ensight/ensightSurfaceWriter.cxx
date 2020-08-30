#include <ensightSurfaceWriter.hxx>

#include <OFstream.hxx>
#include <OSspecific.hxx>
#include <IOmanip.hxx>
#include <ensightPartFaces.hxx>
#include <ensightPTraits.hxx>
#include <makeSurfaceWriterMethods.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(ensightSurfaceWriter);
	addToRunTimeSelectionTable(surfaceWriter, ensightSurfaceWriter, wordDict);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::ensightSurfaceWriter::writeTemplate
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
	if (!isDir(outputDir / fieldName))
	{
		mkDir(outputDir / fieldName);
	}

	// const scalar timeValue = tnbLib::name(this->mesh().time().timeValue());
	const scalar timeValue = 0.0;

	OFstream osCase(outputDir / fieldName / surfaceName + ".case");
	ensightGeoFile osGeom
	(
		outputDir / fieldName / surfaceName + ".000.mesh",
		writeFormat_
	);
	ensightFile osField
	(
		outputDir / fieldName / surfaceName + ".000." + fieldName,
		writeFormat_
	);

	if (verbose)
	{
		Info << "Writing case file to " << osCase.name() << endl;
	}

	osCase
		<< "FORMAT" << nl
		<< "type: ensight gold" << nl
		<< nl
		<< "GEOMETRY" << nl
		<< "model:        1     " << osGeom.name().name() << nl
		<< nl
		<< "VARIABLE" << nl
		<< ensightPTraits<Type>::typeName << " per "
		<< word(isNodeValues ? "node:" : "element:") << setw(10) << 1
		<< "       " << fieldName
		<< "       " << surfaceName.c_str() << ".***." << fieldName << nl
		<< nl
		<< "TIME" << nl
		<< "time set:                      1" << nl
		<< "number of steps:               1" << nl
		<< "filename start number:         0" << nl
		<< "filename increment:            1" << nl
		<< "time values:" << nl
		<< timeValue << nl
		<< nl;

	ensightPartFaces ensPart(0, osGeom.name().name(), points, faces, true);
	osGeom << ensPart;

	// Write field
	osField.writeKeyword(ensightPTraits<Type>::typeName);
	ensPart.writeField(osField, values, isNodeValues);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ensightSurfaceWriter::ensightSurfaceWriter()
	:
	surfaceWriter(),
	writeFormat_(IOstream::ASCII)
{}


tnbLib::ensightSurfaceWriter::ensightSurfaceWriter(const dictionary& options)
	:
	surfaceWriter(),
	writeFormat_(IOstream::ASCII)
{
	// choose ascii or binary format
	if (options.found("format"))
	{
		writeFormat_ = IOstream::formatEnum(options.lookup("format"));
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ensightSurfaceWriter::~ensightSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ensightSurfaceWriter::write
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

	// const scalar timeValue = tnbLib::name(this->mesh().time().timeValue());
	const scalar timeValue = 0.0;

	OFstream osCase(outputDir / surfaceName + ".case");
	ensightGeoFile osGeom
	(
		outputDir / surfaceName + ".000.mesh",
		writeFormat_
	);

	if (verbose)
	{
		Info << "Writing case file to " << osCase.name() << endl;
	}

	osCase
		<< "FORMAT" << nl
		<< "type: ensight gold" << nl
		<< nl
		<< "GEOMETRY" << nl
		<< "model:        1     " << osGeom.name().name() << nl
		<< nl
		<< "TIME" << nl
		<< "time set:                      1" << nl
		<< "number of steps:               1" << nl
		<< "filename start number:         0" << nl
		<< "filename increment:            1" << nl
		<< "time values:" << nl
		<< timeValue << nl
		<< nl;

	ensightPartFaces ensPart(0, osGeom.name().name(), points, faces, true);
	osGeom << ensPart;
}


// create write methods
defineSurfaceWriterWriteFields(tnbLib::ensightSurfaceWriter);


// ************************************************************************* //