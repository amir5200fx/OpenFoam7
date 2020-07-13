#include <pointToPoint.hxx>

#include <polyMesh.hxx>
#include <pointSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, pointToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, pointToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::pointToPoint::usage_
(
	pointToPoint::typeName,
	"\n    Usage: pointToPoint <pointSet>\n\n"
	"    Select all points in the pointSet\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointToPoint::pointToPoint
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::pointToPoint::pointToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set"))
{}


tnbLib::pointToPoint::pointToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointToPoint::~pointToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all from pointSet " << setName_ << " ..." << endl;

		// Load the set
		pointSet loadedSet(mesh_, setName_);

		set.addSet(loadedSet);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all from pointSet " << setName_ << " ..." << endl;

		// Load the set
		pointSet loadedSet(mesh_, setName_);

		set.deleteSet(loadedSet);
	}
}


// ************************************************************************* //