#include <rawSurfaceWriter.hxx>

#include <OFstream.hxx>
#include <OSspecific.hxx>
#include <makeSurfaceWriterMethods.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(rawSurfaceWriter);
	addToRunTimeSelectionTable(surfaceWriter, rawSurfaceWriter, wordDict);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::rawSurfaceWriter::writeLocation
(
	Ostream& os,
	const pointField& points,
	const label pointi
)
{
	const point& pt = points[pointi];
	os << pt.x() << ' ' << pt.y() << ' ' << pt.z() << ' ';
}


inline void tnbLib::rawSurfaceWriter::writeLocation
(
	Ostream& os,
	const pointField& points,
	const faceList& faces,
	const label facei
)
{
	const point& ct = faces[facei].centre(points);
	os << ct.x() << ' ' << ct.y() << ' ' << ct.z() << ' ';
}


namespace tnbLib
{
	template<>
	void tnbLib::rawSurfaceWriter::writeHeader
	(
		Ostream& os,
		const word& fieldName,
		const Field<scalar>& values
	)
	{
		os << values.size() << nl
			<< "#  x  y  z  " << fieldName << nl;
	}


	template<>
	void tnbLib::rawSurfaceWriter::writeHeader
	(
		Ostream& os,
		const word& fieldName,
		const Field<vector>& values
	)
	{
		os << values.size() << nl
			<< "#  x  y  z  "
			<< fieldName << "_x  "
			<< fieldName << "_y  "
			<< fieldName << "_z  "
			<< endl;
	}


	template<>
	void tnbLib::rawSurfaceWriter::writeHeader
	(
		Ostream& os,
		const word& fieldName,
		const Field<sphericalTensor>& values
	)
	{
		os << values.size() << nl
			<< "#  ii  "
			<< fieldName << "_ii" << nl;
	}


	template<>
	void tnbLib::rawSurfaceWriter::writeHeader
	(
		Ostream& os,
		const word& fieldName,
		const Field<symmTensor>& values
	)
	{
		os << values.size() << nl
			<< "#  xx  xy  xz  yy  yz ";
		for (int i = 0; i < 6; ++i)
		{
			os << fieldName << "_" << i << "  ";
		}
		os << endl;
	}


	template<>
	void tnbLib::rawSurfaceWriter::writeHeader
	(
		Ostream& os,
		const word& fieldName,
		const Field<tensor>& values
	)
	{
		os << values.size() << nl
			<< "#  xx  xy  xz  yx  yy  yz  zx  zy  zz";
		for (int i = 0; i < 9; ++i)
		{
			os << fieldName << "_" << i << "  ";
		}
		os << nl;
	}


	template<>
	inline void tnbLib::rawSurfaceWriter::writeData
	(
		Ostream& os,
		const scalar& v
	)
	{
		os << v << nl;
	}


	template<>
	inline void tnbLib::rawSurfaceWriter::writeData
	(
		Ostream& os,
		const vector& v
	)
	{
		os << v[0] << ' ' << v[1] << ' ' << v[2] << nl;
	}


	template<>
	inline void tnbLib::rawSurfaceWriter::writeData
	(
		Ostream& os,
		const sphericalTensor& v
	)
	{
		os << v[0] << nl;
	}


	template<>
	inline void tnbLib::rawSurfaceWriter::writeData
	(
		Ostream& os,
		const symmTensor& v
	)
	{
		os << v[0] << ' ' << v[1] << ' ' << v[2] << ' '
			<< v[3] << ' ' << v[4] << ' ' << v[5] << nl;
	}


	template<>
	inline void tnbLib::rawSurfaceWriter::writeData
	(
		Ostream& os,
		const tensor& v
	)
	{
		os << v[0] << ' ' << v[1] << ' ' << v[2] << ' '
			<< v[3] << ' ' << v[4] << ' ' << v[5] << ' '
			<< v[6] << ' ' << v[7] << ' ' << v[8] << nl;
	}

}


template<class Type>
void tnbLib::rawSurfaceWriter::writeTemplate
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

	OFstream os
	(
		outputDir / fieldName + '_' + surfaceName + ".raw",
		IOstream::ASCII,
		IOstream::currentVersion,
		writeCompression_
	);

	if (verbose)
	{
		Info << "Writing field " << fieldName << " to " << os.name() << endl;
	}

	// Header
	os << "# " << fieldName;
	if (isNodeValues)
	{
		os << "  POINT_DATA ";
	}
	else
	{
		os << "  FACE_DATA ";
	}

	// Header
	writeHeader(os, fieldName, values);

	// Values
	if (isNodeValues)
	{
		forAll(values, elemI)
		{
			writeLocation(os, points, elemI);
			writeData(os, values[elemI]);
		}
	}
	else
	{
		forAll(values, elemI)
		{
			writeLocation(os, points, faces, elemI);
			writeData(os, values[elemI]);
		}
	}
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rawSurfaceWriter::rawSurfaceWriter()
	:
	surfaceWriter(),
	writeCompression_(IOstream::UNCOMPRESSED)
{}


tnbLib::rawSurfaceWriter::rawSurfaceWriter(const dictionary& options)
	:
	surfaceWriter(),
	writeCompression_(IOstream::UNCOMPRESSED)
{
	if (options.found("compression"))
	{
		writeCompression_ =
			IOstream::compressionEnum(options.lookup("compression"));
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::rawSurfaceWriter::~rawSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::rawSurfaceWriter::write
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

	OFstream os
	(
		outputDir / surfaceName + ".raw",
		IOstream::ASCII,
		IOstream::currentVersion,
		writeCompression_
	);

	if (verbose)
	{
		Info << "Writing geometry to " << os.name() << endl;
	}


	// Header
	os << "# geometry NO_DATA " << faces.size() << nl
		<< "#  x  y  z" << nl;

	// Write faces centres
	forAll(faces, elemI)
	{
		writeLocation(os, points, faces, elemI);
		os << nl;
	}

	os << nl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Create write methods
defineSurfaceWriterWriteFields(tnbLib::rawSurfaceWriter);


// ************************************************************************* //