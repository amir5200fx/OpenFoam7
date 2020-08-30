#include <ensightPartFaces.hxx>

#include <IOstream.hxx>
#include <IStringStream.hxx>
#include <dictionary.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ensightPartFaces, 0);
	addToRunTimeSelectionTable(ensightPart, ensightPartFaces, istream);
}


const tnbLib::List<tnbLib::word> tnbLib::ensightPartFaces::elemTypes_
(
	IStringStream
	(
		"(tria3 quad4 nsided)"
	)()
);


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::ensightPartFaces::classify(const faceList& faces)
{
	// count the shapes
	label nTri = 0;
	label nQuad = 0;
	label nPoly = 0;

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		if (f.size() == 3)
		{
			nTri++;
		}
		else if (f.size() == 4)
		{
			nQuad++;
		}
		else
		{
			nPoly++;
		}
	}

	// we can avoid double looping, but at the cost of allocation

	labelList triCells(nTri);
	labelList quadCells(nQuad);
	labelList polygonCells(nPoly);

	nTri = 0;
	nQuad = 0;
	nPoly = 0;

	// classify the shapes
	forAll(faces, facei)
	{
		const face& f = faces[facei];

		if (f.size() == 3)
		{
			triCells[nTri++] = facei;
		}
		else if (f.size() == 4)
		{
			quadCells[nQuad++] = facei;
		}
		else
		{
			polygonCells[nPoly++] = facei;
		}
	}


	// MUST match with elementTypes
	elemLists_.setSize(elementTypes().size());

	elemLists_[tria3Elements].transfer(triCells);
	elemLists_[quad4Elements].transfer(quadCells);
	elemLists_[nsidedElements].transfer(polygonCells);

	size_ = faces.size();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ensightPartFaces::ensightPartFaces
(
	label partNumber,
	const string& partDescription
)
	:
	ensightPart(partNumber, partDescription),
	faces_(faceList::null()),
	contiguousPoints_(false)
{
	isCellData_ = false;
	offset_ = 0;
	size_ = 0;
}


tnbLib::ensightPartFaces::ensightPartFaces
(
	label partNumber,
	const string& partDescription,
	const pointField& points,
	const faceList& faces,
	const bool contiguousPoints
)
	:
	ensightPart(partNumber, partDescription, points),
	faces_(faces),
	contiguousPoints_(contiguousPoints)
{
	isCellData_ = false;
	offset_ = 0;
	size_ = 0;

	// classify the face shapes
	classify(faces);
}


tnbLib::ensightPartFaces::ensightPartFaces
(
	label partNumber,
	const polyMesh& mesh,
	const polyPatch& patch
)
	:
	ensightPart(partNumber, patch.name(), mesh.points()),
	faces_(mesh.faces()),
	contiguousPoints_(false)
{
	isCellData_ = false;
	offset_ = patch.start();

	// classify the face shapes
	classify(patch);
}


tnbLib::ensightPartFaces::ensightPartFaces(const ensightPartFaces& part)
	:
	ensightPart(part),
	faces_(part.faces_),
	contiguousPoints_(part.contiguousPoints_)
{}


tnbLib::ensightPartFaces::ensightPartFaces(Istream& is)
	:
	ensightPart(),
	faces_(faceList::null()),
	contiguousPoints_(false)
{
	isCellData_ = false;
	reconstruct(is);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ensightPartFaces::~ensightPartFaces()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::ensightPart::localPoints tnbLib::ensightPartFaces::calcLocalPoints() const
{
	if (contiguousPoints_)
	{
		localPoints ptList;
		ptList.list = identity(points_.size());
		ptList.nPoints = points_.size();
		return ptList;
	}

	localPoints ptList(points_);
	labelList& usedPoints = ptList.list;
	label nPoints = 0;

	forAll(elemLists_, typeI)
	{
		const labelUList& idList = elemLists_[typeI];

		// add all points from faces
		forAll(idList, i)
		{
			const label id = idList[i] + offset_;
			const face& f = faces_[id];

			forAll(f, fp)
			{
				if (usedPoints[f[fp]] == -1)
				{
					usedPoints[f[fp]] = nPoints++;
				}
			}
		}
	}

	// this is not absolutely necessary, but renumber anyhow
	nPoints = 0;
	forAll(usedPoints, ptI)
	{
		if (usedPoints[ptI] > -1)
		{
			usedPoints[ptI] = nPoints++;
		}
	}

	ptList.nPoints = nPoints;
	return ptList;
}


void tnbLib::ensightPartFaces::writeConnectivity
(
	ensightGeoFile& os,
	const word& key,
	const faceList& faces,
	const labelUList& idList,
	const labelUList& pointMap
) const
{
	os.writeKeyword(key);
	os.write(idList.size());
	os.newline();

	// write (polygon) face sizes
	if (key == "nsided")
	{
		// write the number of points per face
		forAll(idList, i)
		{
			const label id = idList[i] + offset_;
			const face& f = faces[id];

			os.write(f.size());
			os.newline();
		}
	}

	// write the points describing the face
	forAll(idList, i)
	{
		const label id = idList[i] + offset_;
		const face& f = faces[id];

		// convert global -> local index
		// (note: Ensight indices start with 1)
		forAll(f, fp)
		{
			os.write(pointMap[f[fp]] + 1);
		}
		os.newline();
	}
}


void tnbLib::ensightPartFaces::writeConnectivity
(
	ensightGeoFile& os,
	const word& key,
	const labelUList& idList,
	const labelUList& pointMap
) const
{
	writeConnectivity
	(
		os,
		key,
		faces_,
		idList,
		pointMap
	);
}


void tnbLib::ensightPartFaces::writeGeometry(ensightGeoFile& os) const
{
	ensightPart::writeGeometry(os, points_);
}


// ************************************************************************* //