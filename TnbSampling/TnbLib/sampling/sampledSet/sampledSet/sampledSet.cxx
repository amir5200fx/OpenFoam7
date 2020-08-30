#include <sampledSet.hxx>

#include <polyMesh.hxx>
#include <meshSearch.hxx>
#include <writer.hxx>
#include <lineCell.hxx>
#include <lineCellFace.hxx>
#include <lineFace.hxx>
#include <lineUniform.hxx>

#include <Tuple2.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sampledSet, 0);
	defineRunTimeSelectionTable(sampledSet, word);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSet::setSamples
(
	const List<point>& samplingPts,
	const labelList& samplingCells,
	const labelList& samplingFaces,
	const labelList& samplingSegments,
	const scalarList& samplingCurveDist
)
{
	setSize(samplingPts.size());
	cells_.setSize(samplingCells.size());
	faces_.setSize(samplingFaces.size());
	segments_.setSize(samplingSegments.size());
	curveDist_.setSize(samplingCurveDist.size());

	if
		(
		(cells_.size() != size())
			|| (faces_.size() != size())
			|| (segments_.size() != size())
			|| (curveDist_.size() != size())
			)
	{
		FatalErrorInFunction
			<< "sizes not equal : "
			<< "  points:" << size()
			<< "  cells:" << cells_.size()
			<< "  faces:" << faces_.size()
			<< "  segments:" << segments_.size()
			<< "  curveDist:" << curveDist_.size()
			<< abort(FatalError);
	}

	forAll(samplingPts, sampleI)
	{
		operator[](sampleI) = samplingPts[sampleI];
	}
	curveDist_ = samplingCurveDist;

	cells_ = samplingCells;
	faces_ = samplingFaces;
	segments_ = samplingSegments;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSet::sampledSet
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const word& axis
)
	:
	coordSet(name, axis),
	mesh_(mesh),
	searchEngine_(searchEngine),
	segments_(0),
	cells_(0),
	faces_(0)
{}


tnbLib::sampledSet::sampledSet
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	coordSet(name, dict.lookup("axis")),
	mesh_(mesh),
	searchEngine_(searchEngine),
	segments_(0),
	cells_(0),
	faces_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSet::~sampledSet()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::sampledSet> tnbLib::sampledSet::New
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
{
	const word sampleType(dict.lookup("type"));

	const HashTable<word> oldToNewType =
	{
		Tuple2<word, word>("midPoint", sampledSets::lineCell::typeName),
		Tuple2<word, word>
		(
			"midPointAndFace",
			sampledSets::lineCellFace::typeName
		),
		Tuple2<word, word>("face", sampledSets::lineFace::typeName),
		Tuple2<word, word>("uniform", sampledSets::lineUniform::typeName)
	};

	if (oldToNewType.found(sampleType))
	{
		const word newSampleType = oldToNewType[sampleType];

		FatalErrorInFunction
			<< "Unknown sample set type "
			<< sampleType << nl << nl
			<< "The sample set type " << sampleType << " has been renamed "
			<< newSampleType << nl << nl
			<< "Replace \"type " << sampleType << ";\" with \"type "
			<< newSampleType << ";\" for the set " << name << " in "
			<< dict.name() << exit(FatalError);
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(sampleType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sample set type "
			<< sampleType << nl << nl
			<< "Valid sample set types : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<sampledSet>
		(
			cstrIter()
			(
				name,
				mesh,
				searchEngine,
				dict.optionalSubDict(sampleType + "Coeffs")
				)
			);
}


tnbLib::Ostream& tnbLib::sampledSet::write(Ostream& os) const
{
	coordSet::write(os);

	os << endl << "\t(celli)\t(facei)" << endl;

	forAll(*this, sampleI)
	{
		os << '\t' << cells_[sampleI]
			<< '\t' << faces_[sampleI]
			<< endl;
	}

	return os;
}


// ************************************************************************* //