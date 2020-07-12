#include <VTKedgeFormat.hxx>

#include <OFstream.hxx>
#include <clock.hxx>
#include <IFstream.hxx>
#include <vtkUnstructuredReader.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fileFormats::VTKedgeFormat::writeHeader
(
	Ostream& os,
	const pointField& pointLst
)
{
	// Write header
	os << "# vtk DataFile Version 2.0" << nl
		<< "featureEdgeMesh written " << clock::dateTime().c_str() << nl
		<< "ASCII" << nl
		<< nl
		<< "DATASET POLYDATA" << nl;

	// Write vertex coords
	os << "POINTS " << pointLst.size() << " float" << nl;
	forAll(pointLst, ptI)
	{
		const point& pt = pointLst[ptI];

		os << pt.x() << ' ' << pt.y() << ' ' << pt.z() << nl;
	}
}


void tnbLib::fileFormats::VTKedgeFormat::writeEdges
(
	Ostream& os,
	const UList<edge>& edgeLst
)
{
	os << "LINES " << edgeLst.size() << ' ' << 3 * edgeLst.size() << nl;

	forAll(edgeLst, edgeI)
	{
		const edge& e = edgeLst[edgeI];

		os << "2 " << e[0] << ' ' << e[1] << nl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::VTKedgeFormat::VTKedgeFormat
(
	const fileName& filename
)
{
	read(filename);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileFormats::VTKedgeFormat::read
(
	const fileName& filename
)
{
	IFstream is(filename);
	if (!is.good())
	{
		FatalErrorInFunction
			<< "Cannot read file " << filename
			<< exit(FatalError);
	}

	// Construct dummy time so we have something to create an objectRegistry
	// from
	Time dummyTime
	(
		"dummyRoot",
		"dummyCase",
		"system",
		"constant",
		false           // enableFunctionObjects
	);

	// Make dummy object registry
	objectRegistry obr
	(
		IOobject
		(
			"dummy",
			dummyTime,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	// Construct reader to read file
	vtkUnstructuredReader reader(obr, is);


	// Extract lines
	storedPoints().transfer(reader.points());

	label nEdges = 0;
	forAll(reader.lines(), lineI)
	{
		nEdges += reader.lines()[lineI].size() - 1;
	}
	storedEdges().setSize(nEdges);

	nEdges = 0;
	forAll(reader.lines(), lineI)
	{
		const labelList& verts = reader.lines()[lineI];
		for (label i = 1; i < verts.size(); i++)
		{
			storedEdges()[nEdges++] = edge(verts[i - 1], verts[i]);
		}
	}

	return true;
}


void tnbLib::fileFormats::VTKedgeFormat::write
(
	const fileName& filename,
	const edgeMesh& eMesh
)
{
	OFstream os(filename);
	if (!os.good())
	{
		FatalErrorInFunction
			<< "Cannot open file for writing " << filename
			<< exit(FatalError);
	}

	writeHeader(os, eMesh.points());
	writeEdges(os, eMesh.edges());
}


// ************************************************************************* //