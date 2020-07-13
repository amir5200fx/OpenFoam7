#include <labelToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(labelToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, labelToFace, word);
	addToRunTimeSelectionTable(topoSetSource, labelToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::labelToFace::usage_
(
	labelToFace::typeName,
	"\n    Usage: labelToFace (i0 i1 .. in)\n\n"
	"    Select faces by label\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::labelToFace::combine(topoSet& set, const bool add) const
{
	forAll(labels_, labelI)
	{
		addOrDelete(set, labels_[labelI], add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::labelToFace::labelToFace
(
	const polyMesh& mesh,
	const labelList& labels
)
	:
	topoSetSource(mesh),
	labels_(labels)
{}


tnbLib::labelToFace::labelToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	labels_(dict.lookup("value"))
{}


tnbLib::labelToFace::labelToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	labels_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::labelToFace::~labelToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::labelToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces mentioned in dictionary" << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces mentioned dictionary" << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //