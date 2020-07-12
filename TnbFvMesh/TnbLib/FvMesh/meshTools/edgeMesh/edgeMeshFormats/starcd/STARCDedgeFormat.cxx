#include <STARCDedgeFormat.hxx>

#include <ListOps.hxx>
#include <clock.hxx>
#include <PackedBoolList.hxx>
#include <IStringStream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::fileFormats::STARCDedgeFormat::writeLines
(
	Ostream& os,
	const edgeList& edges
)
{
	writeHeader(os, "CELL");

	forAll(edges, edgeI)
	{
		const edge& e = edges[edgeI];
		const label cellId = edgeI + 1;

		os << cellId                    // includes 1 offset
			<< ' ' << starcdLineShape_   // 2(line) shape
			<< ' ' << e.size()
			<< ' ' << 401                // arbitrary value
			<< ' ' << starcdLineType_;   // 5(line)

		os << nl << "  " << cellId << "  "
			<< (e[0] + 1) << "  " << (e[1] + 1) << nl;
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fileFormats::STARCDedgeFormat::writeCase
(
	Ostream& os,
	const pointField& pointLst,
	const label nEdges
)
{
	word caseName = os.name().lessExt().name();

	os << "! STAR-CD file written " << clock::dateTime().c_str() << nl
		<< "! " << pointLst.size() << " points, " << nEdges << " lines" << nl
		<< "! case " << caseName << nl
		<< "! ------------------------------" << nl;

	//     forAll(zoneLst, zoneI)
	//     {
	//         os  << "ctable " << zoneI + 1 << " line" << nl
	//             << "ctname " << zoneI + 1 << " "
	//             << zoneLst[zoneI].name() << nl;
	//     }

	os << "! ------------------------------" << nl
		<< "*set icvo mxv - 1" << nl
		<< "vread " << caseName << ".vrt icvo,,,coded" << nl
		<< "cread " << caseName << ".cel icvo,,,add,coded" << nl
		<< "*set icvo" << nl
		<< "! end" << nl;

	os.flush();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::STARCDedgeFormat::STARCDedgeFormat
(
	const fileName& filename
)
{
	read(filename);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileFormats::STARCDedgeFormat::read
(
	const fileName& filename
)
{
	clear();

	fileName baseName = filename.lessExt();

	// STAR-CD index of points
	List<label> pointId;

	// read points from .vrt file
	readPoints
	(
		IFstream(baseName + ".vrt")(),
		storedPoints(),
		pointId
	);

	// Build inverse mapping (STAR-CD pointId -> index)
	Map<label> mapPointId(2 * pointId.size());
	forAll(pointId, i)
	{
		mapPointId.insert(pointId[i], i);
	}
	pointId.clear();

	// note which points were really used and which can be culled
	PackedBoolList usedPoints(points().size());

	//
	// read .cel file
	// ~~~~~~~~~~~~~~
	IFstream is(baseName + ".cel");
	if (!is.good())
	{
		FatalErrorInFunction
			<< "Cannot read file " << is.name()
			<< exit(FatalError);
	}

	readHeader(is, "PROSTAR_CELL");

	DynamicList<edge>  dynEdges;

	label lineLabel, shapeId, nLabels, cellTableId, typeId;
	DynamicList<label> vertexLabels(64);

	while ((is >> lineLabel).good())
	{
		is >> shapeId >> nLabels >> cellTableId >> typeId;

		vertexLabels.clear();
		vertexLabels.reserve(nLabels);

		// read indices - max 8 per line
		for (label i = 0; i < nLabels; ++i)
		{
			label vrtId;
			if ((i % 8) == 0)
			{
				is >> lineLabel;
			}
			is >> vrtId;

			// convert original vertex id to point label
			vertexLabels.append(mapPointId[vrtId]);
		}

		if (typeId == starcdLineType_)
		{
			if (vertexLabels.size() >= 2)
			{
				dynEdges.append(edge(vertexLabels[0], vertexLabels[1]));

				usedPoints.set(vertexLabels[0]);
				usedPoints.set(vertexLabels[1]);
			}
		}
	}

	mapPointId.clear();

	// not all the points were used, cull them accordingly
	if (unsigned(points().size()) != usedPoints.count())
	{
		label nUsed = 0;

		pointField& pts = storedPoints();
		forAll(pts, pointi)
		{
			if (usedPoints.get(pointi))
			{
				if (nUsed != pointi)
				{
					pts[nUsed] = pts[pointi];
				}

				// map prev -> new id
				mapPointId.set(pointi, nUsed);

				++nUsed;
			}
		}

		pts.setSize(nUsed);

		// renumber edge vertices
		forAll(dynEdges, edgeI)
		{
			edge& e = dynEdges[edgeI];

			e[0] = mapPointId[e[0]];
			e[1] = mapPointId[e[1]];
		}
	}


	storedEdges().transfer(dynEdges);

	return true;
}


void tnbLib::fileFormats::STARCDedgeFormat::write
(
	const fileName& filename,
	const edgeMesh& mesh
)
{
	const pointField& pointLst = mesh.points();
	const edgeList& edgeLst = mesh.edges();

	fileName baseName = filename.lessExt();

	writePoints(OFstream(baseName + ".vrt")(), pointLst);
	writeLines(OFstream(baseName + ".cel")(), edgeLst);

	// write a simple .inp file
	writeCase
	(
		OFstream(baseName + ".inp")(),
		pointLst,
		edgeLst.size()
	);
}


// ************************************************************************* //