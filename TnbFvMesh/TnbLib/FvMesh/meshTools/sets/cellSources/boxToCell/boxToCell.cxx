#include <boxToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(boxToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, boxToCell, word);
	addToRunTimeSelectionTable(topoSetSource, boxToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::boxToCell::usage_
(
	boxToCell::typeName,
	"\n    Usage: boxToCell (minx miny minz) (maxx maxy maxz)\n\n"
	"    Select all cells with cellCentre within bounding box\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::boxToCell::combine(topoSet& set, const bool add) const
{
	const pointField& ctrs = mesh_.cellCentres();

	forAll(ctrs, celli)
	{
		forAll(bbs_, i)
		{
			if (bbs_[i].contains(ctrs[celli]))
			{
				addOrDelete(set, celli, add);
				break;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boxToCell::boxToCell
(
	const polyMesh& mesh,
	const treeBoundBoxList& bbs
)
	:
	topoSetSource(mesh),
	bbs_(bbs)
{}


tnbLib::boxToCell::boxToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	bbs_
	(
		dict.found("box")
		? treeBoundBoxList(1, treeBoundBox(dict.lookup("box")))
		: dict.lookup("boxes")
	)
{}


tnbLib::boxToCell::boxToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	bbs_(1, treeBoundBox(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boxToCell::~boxToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::boxToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells with center within boxes " << bbs_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells with center within boxes " << bbs_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //