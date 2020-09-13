#include <vtkSurfaceWriter.hxx>

#include <OFstream.hxx>
#include <OSspecific.hxx>
#include <makeSurfaceWriterMethods.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(vtkSurfaceWriter);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::vtkSurfaceWriter::writeGeometry
(
	Ostream& os,
	const pointField& points,
	const faceList& faces
)
{
	// header
	os
		<< "# vtk DataFile Version 2.0" << nl
		<< "sampleSurface" << nl
		<< "ASCII" << nl
		<< "DATASET POLYDATA" << nl;

	// Write vertex coords
	os << "POINTS " << points.size() << " double" << nl;
	forAll(points, pointi)
	{
		const point& pt = points[pointi];
		os << float(pt.x()) << ' '
			<< float(pt.y()) << ' '
			<< float(pt.z()) << nl;
	}
	os << nl;


	// Write faces
	label nNodes = 0;
	forAll(faces, facei)
	{
		nNodes += faces[facei].size();
	}

	os << "POLYGONS " << faces.size() << ' '
		<< faces.size() + nNodes << nl;

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		os << f.size();
		forAll(f, fp)
		{
			os << ' ' << f[fp];
		}
		os << nl;
	}
}


namespace tnbLib
{

	template<>
	void tnbLib::vtkSurfaceWriter::writeData
	(
		Ostream& os,
		const Field<scalar>& values
	)
	{
		os << "1 " << values.size() << " float" << nl;

		forAll(values, elemI)
		{
			if (elemI)
			{
				if (elemI % 10)
				{
					os << ' ';
				}
				else
				{
					os << nl;
				}
			}

			os << float(values[elemI]);
		}
		os << nl;
	}


	template<>
	void tnbLib::vtkSurfaceWriter::writeData
	(
		Ostream& os,
		const Field<vector>& values
	)
	{
		os << "3 " << values.size() << " float" << nl;

		forAll(values, elemI)
		{
			const vector& v = values[elemI];
			os << float(v[0]) << ' ' << float(v[1]) << ' ' << float(v[2])
				<< nl;
		}
	}


	template<>
	void tnbLib::vtkSurfaceWriter::writeData
	(
		Ostream& os,
		const Field<sphericalTensor>& values
	)
	{
		os << "1 " << values.size() << " float" << nl;

		forAll(values, elemI)
		{
			const sphericalTensor& v = values[elemI];
			os << float(v[0]) << nl;
		}
	}


	template<>
	void tnbLib::vtkSurfaceWriter::writeData
	(
		Ostream& os,
		const Field<symmTensor>& values
	)
	{
		os << "6 " << values.size() << " float" << nl;

		forAll(values, elemI)
		{
			const symmTensor& v = values[elemI];
			os << float(v[0]) << ' ' << float(v[1]) << ' ' << float(v[2])
				<< ' '
				<< float(v[3]) << ' ' << float(v[4]) << ' ' << float(v[5])
				<< nl;

		}
	}


	template<>
	void tnbLib::vtkSurfaceWriter::writeData
	(
		Ostream& os,
		const Field<tensor>& values
	)
	{
		os << "9 " << values.size() << " float" << nl;

		forAll(values, elemI)
		{
			const tensor& v = values[elemI];
			os << float(v[0]) << ' ' << float(v[1]) << ' ' << float(v[2])
				<< ' '
				<< float(v[3]) << ' ' << float(v[4]) << ' ' << float(v[5])
				<< ' '
				<< float(v[6]) << ' ' << float(v[7]) << ' ' << float(v[8])
				<< nl;
		}
	}

}


// Write generic field in vtk format
template<class Type>
void tnbLib::vtkSurfaceWriter::writeData
(
	Ostream& os,
	const Field<Type>& values
)
{
	os << "1 " << values.size() << " float" << nl;

	forAll(values, elemI)
	{
		os << float(0) << nl;
	}
}


template<class Type>
void tnbLib::vtkSurfaceWriter::writeTemplate
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

	OFstream os(outputDir / fieldName + '_' + surfaceName + ".vtk");

	if (verbose)
	{
		Info << "Writing field " << fieldName << " to " << os.name() << endl;
	}

	writeGeometry(os, points, faces);

	// start writing data
	if (isNodeValues)
	{
		os << "POINT_DATA ";
	}
	else
	{
		os << "CELL_DATA ";
	}

	os << values.size() << nl
		<< "FIELD attributes 1" << nl
		<< fieldName << " ";

	// Write data
	writeData(os, values);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::vtkSurfaceWriter::vtkSurfaceWriter()
	:
	surfaceWriter()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::vtkSurfaceWriter::~vtkSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::vtkSurfaceWriter::write
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

	OFstream os(outputDir / surfaceName + ".vtk");

	if (verbose)
	{
		Info << "Writing geometry to " << os.name() << endl;
	}

	writeGeometry(os, points, faces);
}


// create write methods
defineSurfaceWriterWriteFields(tnbLib::vtkSurfaceWriter);


// ************************************************************************* //