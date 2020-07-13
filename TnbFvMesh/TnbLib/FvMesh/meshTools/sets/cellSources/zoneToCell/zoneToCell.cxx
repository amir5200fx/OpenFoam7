#include <zoneToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(zoneToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, zoneToCell, word);
	addToRunTimeSelectionTable(topoSetSource, zoneToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::zoneToCell::usage_
(
	zoneToCell::typeName,
	"\n    Usage: zoneToCell zone\n\n"
	"    Select all cells in the cellZone."
	" Note:accepts wildcards for zone.\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::zoneToCell::combine(topoSet& set, const bool add) const
{
	bool hasMatched = false;

	forAll(mesh_.cellZones(), i)
	{
		const cellZone& zone = mesh_.cellZones()[i];

		if (zoneName_.match(zone.name()))
		{
			const labelList& cellLabels = mesh_.cellZones()[i];

			Info << "    Found matching zone " << zone.name()
				<< " with " << cellLabels.size() << " cells." << endl;

			hasMatched = true;

			forAll(cellLabels, i)
			{
				// Only do active cells
				if (cellLabels[i] < mesh_.nCells())
				{
					addOrDelete(set, cellLabels[i], add);
				}
			}
		}
	}

	if (!hasMatched)
	{
		WarningInFunction
			<< "Cannot find any cellZone named " << zoneName_ << endl
			<< "Valid names are " << mesh_.cellZones().names() << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::zoneToCell::zoneToCell
(
	const polyMesh& mesh,
	const word& zoneName
)
	:
	topoSetSource(mesh),
	zoneName_(zoneName)
{}


tnbLib::zoneToCell::zoneToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	zoneName_(dict.lookup("name"))
{}


tnbLib::zoneToCell::zoneToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	zoneName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::zoneToCell::~zoneToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::zoneToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all cells of cellZone " << zoneName_ << " ..."
			<< endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all cells of cellZone " << zoneName_ << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //