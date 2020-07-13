#include <labelToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(labelToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, labelToCell, word);
	addToRunTimeSelectionTable(topoSetSource, labelToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::labelToCell::usage_
(
	labelToCell::typeName,
	"\n    Usage: labelToCell (i0 i1 .. in)\n\n"
	"    Select cells by cellLabel\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::labelToCell::combine(topoSet& set, const bool add) const
{
	forAll(labels_, labelI)
	{
		addOrDelete(set, labels_[labelI], add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::labelToCell::labelToCell
(
	const polyMesh& mesh,
	const labelList& labels
)
	:
	topoSetSource(mesh),
	labels_(labels)
{}


tnbLib::labelToCell::labelToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	labels_(dict.lookup("value"))
{}


tnbLib::labelToCell::labelToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	labels_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::labelToCell::~labelToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::labelToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells mentioned in dictionary" << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells mentioned in dictionary" << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //