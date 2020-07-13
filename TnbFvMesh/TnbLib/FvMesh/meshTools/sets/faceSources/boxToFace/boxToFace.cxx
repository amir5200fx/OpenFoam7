#include <boxToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(boxToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, boxToFace, word);
	addToRunTimeSelectionTable(topoSetSource, boxToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::boxToFace::usage_
(
	boxToFace::typeName,
	"\n    Usage: boxToFace ((minx miny minz) (maxx maxy maxz))\n\n"
	"    Select all face with faceCentre within bounding box\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::boxToFace::combine(topoSet& set, const bool add) const
{
	const pointField& ctrs = mesh_.faceCentres();

	forAll(ctrs, facei)
	{
		forAll(bbs_, i)
		{
			if (bbs_[i].contains(ctrs[facei]))
			{
				addOrDelete(set, facei, add);
				break;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boxToFace::boxToFace
(
	const polyMesh& mesh,
	const treeBoundBoxList& bbs
)
	:
	topoSetSource(mesh),
	bbs_(bbs)
{}


tnbLib::boxToFace::boxToFace
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


tnbLib::boxToFace::boxToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	bbs_(1, treeBoundBox(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boxToFace::~boxToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::boxToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces with centre within boxes " << bbs_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces with centre within boxes " << bbs_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //