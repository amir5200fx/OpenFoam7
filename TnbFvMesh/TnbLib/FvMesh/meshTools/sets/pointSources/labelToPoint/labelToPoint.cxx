#include <labelToPoint.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(labelToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, labelToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, labelToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::labelToPoint::usage_
(
	labelToPoint::typeName,
	"\n    Usage: labelToPoint (i0 i1 .. in)\n\n"
	"    Select points by label\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::labelToPoint::combine(topoSet& set, const bool add) const
{
	forAll(labels_, labelI)
	{
		addOrDelete(set, labels_[labelI], add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::labelToPoint::labelToPoint
(
	const polyMesh& mesh,
	const labelList& labels
)
	:
	topoSetSource(mesh),
	labels_(labels)
{}


tnbLib::labelToPoint::labelToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	labels_(dict.lookup("value"))
{}


tnbLib::labelToPoint::labelToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	labels_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::labelToPoint::~labelToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::labelToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding points mentioned in dictionary" << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing points mentioned in dictionary" << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //