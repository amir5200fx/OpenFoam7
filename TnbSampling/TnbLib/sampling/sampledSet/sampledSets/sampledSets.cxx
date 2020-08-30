#include <sampledSets.hxx>

#include <dictionary.hxx>
#include <Time.hxx>
#include <volFields.hxx>
#include <ListListOps.hxx>
#include <SortableList.hxx>
#include <volPointInterpolation.hxx>
#include <mapPolyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sampledSets, 0);

	addToRunTimeSelectionTable
	(
		functionObject,
		sampledSets,
		dictionary
	);
}

bool tnbLib::sampledSets::verbose_ = false;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::combineSampledSets
(
	PtrList<coordSet>& masterSampledSets,
	labelListList& indexSets
)
{
	// Combine sampleSets from processors. Sort by curveDist. Return
	// ordering in indexSets.
	// Note: only master results are valid

	masterSampledSets_.clear();
	masterSampledSets_.setSize(size());
	indexSets_.setSize(size());

	const PtrList<sampledSet>& sampledSets = *this;

	forAll(sampledSets, setI)
	{
		const sampledSet& samplePts = sampledSets[setI];

		// Collect data from all processors
		List<List<point>> gatheredPts(Pstream::nProcs());
		gatheredPts[Pstream::myProcNo()] = samplePts;
		Pstream::gatherList(gatheredPts);

		List<labelList> gatheredSegments(Pstream::nProcs());
		gatheredSegments[Pstream::myProcNo()] = samplePts.segments();
		Pstream::gatherList(gatheredSegments);

		List<scalarList> gatheredDist(Pstream::nProcs());
		gatheredDist[Pstream::myProcNo()] = samplePts.curveDist();
		Pstream::gatherList(gatheredDist);


		// Combine processor lists into one big list.
		List<point> allPts
		(
			ListListOps::combine<List<point>>
			(
				gatheredPts, accessOp<List<point>>()
				)
		);
		labelList allSegments
		(
			ListListOps::combine<labelList>
			(
				gatheredSegments, accessOp<labelList>()
				)
		);
		scalarList allCurveDist
		(
			ListListOps::combine<scalarList>
			(
				gatheredDist, accessOp<scalarList>()
				)
		);


		if (Pstream::master() && allCurveDist.size() == 0)
		{
			WarningInFunction
				<< "Sample set " << samplePts.name()
				<< " has zero points." << endl;
		}

		// Sort curveDist and use to fill masterSamplePts
		SortableList<scalar> sortedDist(allCurveDist);
		indexSets[setI] = sortedDist.indices();

		masterSampledSets.set
		(
			setI,
			new coordSet
			(
				samplePts.name(),
				samplePts.axis(),
				List<point>(UIndirectList<point>(allPts, indexSets[setI])),
				scalarList(UIndirectList<scalar>(allCurveDist, indexSets[setI]))
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSets::sampledSets
(
	const word& name,
	const Time& t,
	const dictionary& dict
)
	:
	functionObject(name),
	PtrList<sampledSet>(),
	mesh_
	(
		refCast<const fvMesh>
		(
			t.lookupObject<objectRegistry>
			(
				dict.lookupOrDefault("region", polyMesh::defaultRegion)
				)
			)
	),
	loadFromFiles_(false),
	outputPath_(fileName::null),
	searchEngine_(mesh_),
	interpolationScheme_(word::null),
	writeFormat_(word::null)
{
	if (Pstream::parRun())
	{
		outputPath_ = mesh_.time().path() / ".." / "postProcessing" / name;
	}
	else
	{
		outputPath_ = mesh_.time().path() / "postProcessing" / name;
	}
	if (mesh_.name() != fvMesh::defaultRegion)
	{
		outputPath_ = outputPath_ / mesh_.name();
	}
	// Remove ".."
	outputPath_.clean();

	read(dict);
}


tnbLib::sampledSets::sampledSets
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict,
	const bool loadFromFiles
)
	:
	functionObject(name),
	PtrList<sampledSet>(),
	mesh_(refCast<const fvMesh>(obr)),
	loadFromFiles_(loadFromFiles),
	outputPath_(fileName::null),
	searchEngine_(mesh_),
	interpolationScheme_(word::null),
	writeFormat_(word::null)
{
	if (Pstream::parRun())
	{
		outputPath_ = mesh_.time().path() / ".." / "postProcessing" / name;
	}
	else
	{
		outputPath_ = mesh_.time().path() / "postProcessing" / name;
	}
	if (mesh_.name() != fvMesh::defaultRegion)
	{
		outputPath_ = outputPath_ / mesh_.name();
	}
	// Remove ".."
	outputPath_.clean();

	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::~sampledSets()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sampledSets::verbose(const bool verbosity)
{
	verbose_ = verbosity;
}


bool tnbLib::sampledSets::execute()
{
	return true;
}


bool tnbLib::sampledSets::write()
{
	if (size())
	{
		const label nFields = classifyFields();

		if (Pstream::master())
		{
			if (debug)
			{
				Pout << "timeName = " << mesh_.time().timeName() << nl
					<< "scalarFields    " << scalarFields_ << nl
					<< "vectorFields    " << vectorFields_ << nl
					<< "sphTensorFields " << sphericalTensorFields_ << nl
					<< "symTensorFields " << symmTensorFields_ << nl
					<< "tensorFields    " << tensorFields_ << nl;
			}

			if (nFields)
			{
				if (debug)
				{
					Pout << "Creating directory "
						<< outputPath_ / mesh_.time().timeName()
						<< nl << endl;
				}

				mkDir(outputPath_ / mesh_.time().timeName());
			}
		}

		if (nFields)
		{
			sampleAndWrite(scalarFields_);
			sampleAndWrite(vectorFields_);
			sampleAndWrite(sphericalTensorFields_);
			sampleAndWrite(symmTensorFields_);
			sampleAndWrite(tensorFields_);
		}
	}

	return true;
}


bool tnbLib::sampledSets::read(const dictionary& dict)
{
	dict_ = dict;

	bool setsFound = dict_.found("sets");
	if (setsFound)
	{
		dict_.lookup("fields") >> fieldSelection_;
		clearFieldGroups();

		dict.lookup("interpolationScheme") >> interpolationScheme_;
		dict.lookup("setFormat") >> writeFormat_;

		PtrList<sampledSet> newList
		(
			dict_.lookup("sets"),
			sampledSet::iNew(mesh_, searchEngine_)
		);
		transfer(newList);
		combineSampledSets(masterSampledSets_, indexSets_);

		if (this->size())
		{
			Info << "Reading set description:" << nl;
			forAll(*this, setI)
			{
				Info << "    " << operator[](setI).name() << nl;
			}
			Info << endl;
		}
	}

	if (Pstream::master() && debug)
	{
		Pout << "sample fields:" << fieldSelection_ << nl
			<< "sample sets:" << nl << "(" << nl;

		forAll(*this, setI)
		{
			Pout << "  " << operator[](setI) << endl;
		}
		Pout << ")" << endl;
	}

	return true;
}


void tnbLib::sampledSets::correct()
{
	bool setsFound = dict_.found("sets");
	if (setsFound)
	{
		searchEngine_.correct();

		PtrList<sampledSet> newList
		(
			dict_.lookup("sets"),
			sampledSet::iNew(mesh_, searchEngine_)
		);
		transfer(newList);
		combineSampledSets(masterSampledSets_, indexSets_);
	}
}


void tnbLib::sampledSets::updateMesh(const mapPolyMesh& mpm)
{
	if (&mpm.mesh() == &mesh_)
	{
		correct();
	}
}


void tnbLib::sampledSets::movePoints(const polyMesh& mesh)
{
	if (&mesh == &mesh_)
	{
		correct();
	}
}


void tnbLib::sampledSets::readUpdate(const polyMesh::readUpdateState state)
{
	if (state != polyMesh::UNCHANGED)
	{
		correct();
	}
}


// ************************************************************************* //