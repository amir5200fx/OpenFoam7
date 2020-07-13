#include <zoneToPoint.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(zoneToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, zoneToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, zoneToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::zoneToPoint::usage_
(
	zoneToPoint::typeName,
	"\n    Usage: zoneToPoint zone\n\n"
	"    Select all points in the pointZone."
	" Note:accepts wildcards for zone.\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::zoneToPoint::combine(topoSet& set, const bool add) const
{
	bool hasMatched = false;

	forAll(mesh_.pointZones(), i)
	{
		const pointZone& zone = mesh_.pointZones()[i];

		if (zoneName_.match(zone.name()))
		{
			const labelList& pointLabels = mesh_.pointZones()[i];

			Info << "    Found matching zone " << zone.name()
				<< " with " << pointLabels.size() << " points." << endl;

			hasMatched = true;

			forAll(pointLabels, i)
			{
				// Only do active points
				if (pointLabels[i] < mesh_.nPoints())
				{
					addOrDelete(set, pointLabels[i], add);
				}
			}
		}
	}

	if (!hasMatched)
	{
		WarningInFunction
			<< "Cannot find any pointZone named " << zoneName_ << endl
			<< "Valid names are " << mesh_.pointZones().names() << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::zoneToPoint::zoneToPoint
(
	const polyMesh& mesh,
	const word& zoneName
)
	:
	topoSetSource(mesh),
	zoneName_(zoneName)
{}


tnbLib::zoneToPoint::zoneToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	zoneName_(dict.lookup("name"))
{}


tnbLib::zoneToPoint::zoneToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	zoneName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::zoneToPoint::~zoneToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::zoneToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all points of pointZone " << zoneName_ << " ..."
			<< endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all points of pointZone " << zoneName_ << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //