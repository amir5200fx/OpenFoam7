#include <externalDisplacementMeshMover.hxx>

#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(externalDisplacementMeshMover, 0);
	defineRunTimeSelectionTable(externalDisplacementMeshMover, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::externalDisplacementMeshMover::externalDisplacementMeshMover
(
	const dictionary& dict,
	const List<labelPair>& baffles,
	pointVectorField& pointDisplacement
)
	:
	baffles_(baffles),
	pointDisplacement_(pointDisplacement)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::externalDisplacementMeshMover>
tnbLib::externalDisplacementMeshMover::New
(
	const word& type,
	const dictionary& dict,
	const List<labelPair>& baffles,
	pointVectorField& pointDisplacement
)
{
	Info << "Selecting externalDisplacementMeshMover " << type << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(type);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown externalDisplacementMeshMover type "
			<< type << nl << nl
			<< "Valid externalDisplacementMeshMover types:" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<externalDisplacementMeshMover>
		(
			cstrIter()(dict, baffles, pointDisplacement)
			);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::externalDisplacementMeshMover::~externalDisplacementMeshMover()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::externalDisplacementMeshMover::movePoints(const pointField&)
{
	// No local data to update
}


void tnbLib::externalDisplacementMeshMover::updateMesh(const mapPolyMesh& mpm)
{
	// Renumber baffles
	DynamicList<labelPair> newBaffles(baffles_.size());
	forAll(baffles_, i)
	{
		label f0 = mpm.reverseFaceMap()[baffles_[i].first()];
		label f1 = mpm.reverseFaceMap()[baffles_[i].second()];

		if (f0 >= 0 && f1 >= 0)
		{
			newBaffles.append(labelPair(f0, f1));
		}
	}
	newBaffles.shrink();
	baffles_.transfer(newBaffles);
}


// ************************************************************************* //